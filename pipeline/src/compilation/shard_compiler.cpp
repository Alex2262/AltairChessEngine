#include "shard_compiler.h"

#include "../parsing/record_parser.h"
#include "shard_writer.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>

namespace fs = std::filesystem;

namespace pipeline {

namespace {

struct ManifestShard {
    std::string file;
    uint32_t records = 0;
};

class ShardCompileState {
public:
    ShardCompileState(const std::string& output_dir, const ShardCompileOptions& options)
        : output_dir(output_dir), options(options), rng(options.random_seed) {}

    void append(const PackedBoardRecord& record) {
        buffer.push_back(record);
        flush_random_record_if_needed(options.shuffle_buffer_records);
    }

    void finish() {
        while (!buffer.empty()) {
            write_random_record();
        }

        close_current_shard();
        write_manifest();
    }

    uint64_t records_written() const { return total_records; }

private:
    void flush_random_record_if_needed(const size_t limit) {
        if (limit == 0 || buffer.size() < limit) {
            return;
        }
        write_random_record();
    }

    void write_random_record() {
        if (buffer.empty()) {
            return;
        }

        std::uniform_int_distribution<size_t> dist(0, buffer.size() - 1);
        const size_t idx = dist(rng);
        write_record(buffer[idx]);
        buffer[idx] = buffer.back();
        buffer.pop_back();
    }

    void write_record(const PackedBoardRecord& record) {
        ensure_open_shard();
        writer.write_record(record);
        ++total_records;

        if (writer.current_size() >= options.max_shard_bytes) {
            close_current_shard();
        }

        if (total_records % 1000000 == 0) {
            std::cout << "\rProcessed: " << total_records << std::flush;
        }
    }

    void ensure_open_shard() {
        if (writer.is_open()) {
            return;
        }

        char filename[32];
        std::snprintf(filename, sizeof(filename), "shard_%04u.bin", shard_index++);
        writer.open((fs::path(output_dir) / filename).string());
    }

    void close_current_shard() {
        if (!writer.is_open()) {
            return;
        }

        const std::string file = fs::path(writer.current_path()).filename().string();
        const uint32_t count = writer.current_record_count();
        writer.close();

        if (count > 0) {
            shards.push_back({file, count});
        } else {
            fs::remove(fs::path(output_dir) / file);
        }

    }

    void write_manifest() const {
        std::ofstream manifest(fs::path(output_dir) / "manifest.json");
        manifest << "{\n"
                 << "  \"version\": " << SHARD_VERSION << ",\n"
                 << "  \"format\": \"packed_board_v2\",\n"
                 << "  \"record_size\": " << sizeof(PackedBoardRecord) << ",\n"
                 << "  \"total_records\": " << total_records << ",\n"
                 << "  \"shards\": [\n";

        for (size_t i = 0; i < shards.size(); ++i) {
            manifest << "    {\"file\": \"" << shards[i].file << "\", \"records\": " << shards[i].records << "}";
            if (i + 1 != shards.size()) {
                manifest << ",";
            }
            manifest << "\n";
        }

        manifest << "  ]\n"
                 << "}\n";
    }

    std::string output_dir;
    ShardCompileOptions options;
    std::mt19937_64 rng;
    std::vector<PackedBoardRecord> buffer;
    ShardWriter writer;
    std::vector<ManifestShard> shards;
    uint32_t shard_index = 0;
    uint64_t total_records = 0;
};

}  // namespace

uint64_t compile_shards(const std::vector<std::string>& input_files,
                        const std::string& output_dir,
                        const ShardCompileOptions& options) {
    fs::create_directories(output_dir);

    RecordParser parser;
    ShardCompileState state(output_dir, options);

    for (const auto& filepath : input_files) {
        std::ifstream file(filepath);
        if (!file) {
            std::cerr << "Warning: cannot open " << filepath << "\n";
            continue;
        }

        std::string line;
        size_t line_num = 0;
        while (std::getline(file, line)) {
            ++line_num;
            const auto result = parser.parse_line(line, line_num);
            if (!result.ok()) {
                continue;
            }

            const auto& rec = *result.record;
            const auto packed = pack_record(
                rec.position,
                encode_stm(rec.position.side),
                encode_wdl(rec.wdl),
                static_cast<int16_t>(rec.eval)
            );
            state.append(packed);
        }
    }

    state.finish();
    std::cout << "\nWrote " << state.records_written() << " records\n";
    return state.records_written();
}

}  // namespace pipeline
