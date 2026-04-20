#include "shard_writer.h"

#include <cstring>
#include <stdexcept>

namespace pipeline {

void ShardWriter::open(const std::string& filepath) {
    path = filepath;
    file.open(filepath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open shard file: " + filepath);
    }

    const ShardHeader header {.record_size = static_cast<uint16_t>(sizeof(PackedBoardRecord))};
    file.write(reinterpret_cast<const char*>(&header), sizeof(header));

    buffer.clear();
    buffer.reserve(1024 * 1024);
    record_count = 0;
    bytes_written = 0;
}

void ShardWriter::write_record(const PackedBoardRecord& record) {
    const size_t offset = buffer.size();
    buffer.resize(offset + sizeof(PackedBoardRecord));
    std::memcpy(buffer.data() + offset, &record, sizeof(PackedBoardRecord));
    ++record_count;

    if (buffer.size() >= 1024 * 1024) {
        flush();
    }
}

void ShardWriter::flush() {
    if (buffer.empty()) {
        return;
    }

    file.write(reinterpret_cast<const char*>(buffer.data()), static_cast<std::streamsize>(buffer.size()));
    bytes_written += buffer.size();
    buffer.clear();
}

void ShardWriter::close() {
    if (!file.is_open()) {
        return;
    }

    flush();

    ShardHeader header;
    header.record_count = record_count;
    header.record_size = static_cast<uint16_t>(sizeof(PackedBoardRecord));

    file.seekp(0);
    file.write(reinterpret_cast<const char*>(&header), sizeof(header));
    file.close();
}

}  // namespace pipeline
