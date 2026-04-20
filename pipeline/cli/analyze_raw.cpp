#include "parsing/record_parser.h"
#include "analytics/streaming_stats.h"
#include "analytics/csv_writer.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <filesystem>

using namespace pipeline;

namespace {

void write_error_summary_csv(const std::string& filepath,
                             const std::unordered_map<std::string, uint64_t>& error_counts,
                             const uint64_t total_parse_errors) {
    CSVWriter writer(filepath);
    writer.write_header({"error", "count", "percentage"});

    std::vector<std::pair<std::string, uint64_t>> sorted(error_counts.begin(), error_counts.end());
    std::sort(sorted.begin(), sorted.end(),
              [](const auto& left, const auto& right) { return left.second > right.second; });

    for (const auto& [error, count] : sorted) {
        const double percentage = total_parse_errors > 0
            ? 100.0 * static_cast<double>(count) / static_cast<double>(total_parse_errors)
            : 0.0;
        writer.write_row(error, count, percentage);
    }
}

}  // namespace

void print_usage(const char* program) {
    std::cerr << "Usage: " << program << " [options] <input_files...>\n"
              << "\n"
              << "Analyze raw datagen output files and produce CSV analytics.\n"
              << "\n"
              << "Options:\n"
              << "  -o, --output <dir>    Output directory for CSV files (default: analytics_output)\n"
              << "  -q, --quiet           Suppress progress output\n"
              << "  -h, --help            Show this help message\n"
              << "\n"
              << "Input files should be in the format: {FEN} | {EVAL} | {WDL}\n"
              << "\n"
              << "Output CSV files:\n"
              << "  summary.csv           - High-level statistics\n"
              << "  eval_histogram.csv    - Evaluation distribution\n"
              << "  wdl_distribution.csv  - Win/Draw/Loss counts\n"
              << "  material_distribution.csv - Material configurations\n"
              << "  piece_counts.csv      - Per-piece count distributions\n"
              << "  side_to_move.csv      - Side to move statistics\n"
              << "  castling_rights.csv   - Castling rights distribution\n"
              << "  king_positions.csv    - King position heatmaps\n"
              << "  en_passant.csv        - En passant square statistics\n";
}

int main(int argc, char* argv[]) {
    std::string output_dir = "analytics_output";
    bool quiet = false;
    std::vector<std::string> input_files;

    // Parse arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            print_usage(argv[0]);
            return 0;
        } else if (arg == "-q" || arg == "--quiet") {
            quiet = true;
        } else if (arg == "-o" || arg == "--output") {
            if (i + 1 >= argc) {
                std::cerr << "Error: --output requires an argument\n";
                return 1;
            }
            output_dir = argv[++i];
        } else if (arg[0] == '-') {
            std::cerr << "Unknown option: " << arg << "\n";
            print_usage(argv[0]);
            return 1;
        } else {
            input_files.push_back(arg);
        }
    }

    if (input_files.empty()) {
        std::cerr << "Error: No input files specified\n";
        print_usage(argv[0]);
        return 1;
    }

    // Verify input files exist
    for (const auto& file : input_files) {
        if (!std::filesystem::exists(file)) {
            std::cerr << "Error: File not found: " << file << "\n";
            return 1;
        }
    }

    if (!quiet) {
        std::cerr << "Analyzing " << input_files.size() << " file(s)...\n";
    }

    // Process files
    StreamingStats stats;
    ProgressReporter progress(quiet ? UINT64_MAX : 100000);
    uint64_t error_count = 0;
    std::unordered_map<std::string, uint64_t> error_counts_by_message;

    MultiFileRecordReader reader;
    reader.add_files(input_files);

    progress.start();

    const uint64_t total_input_lines = reader.process(
        // On record
        [&](RawRecord& record, const std::string&) {
            stats.add(record);
            progress.tick();
            return true;
        },
        // On error
        [&](const std::string& error, size_t line, const std::string& file) {
            ++error_count;
            ++error_counts_by_message[error];
            if (!quiet && error_count <= 10) {
                std::cerr << "\nWarning: " << file << ":" << line << ": " << error << "\n";
            }
        },
        // On file start
        [&](const std::string& file) {
            if (!quiet) {
                std::cerr << "\nProcessing: " << file << "\n";
            }
        }
    );

    progress.finish();

    if (!quiet) {
        std::cerr << "\nWriting CSV files to: " << output_dir << "/\n";
    }

    // Write output
    stats.write_all_csv(output_dir, total_input_lines, error_count);
    write_error_summary_csv(output_dir + "/error_summary.csv", error_counts_by_message, error_count);

    // Print summary
    std::cout << "\n=== Analytics Summary ===\n"
              << "Total input lines:  " << total_input_lines << "\n"
              << "Valid records:      " << stats.valid_records << "\n"
              << "Parse errors:       " << error_count << "\n"
              << "Estimated unique:   " << static_cast<uint64_t>(stats.estimated_unique()) << "\n"
              << "Duplicate ratio:    " << std::fixed << std::setprecision(2)
              << (stats.duplicate_ratio() * 100) << "%\n"
              << "\n"
              << "WDL Distribution:\n"
              << "  Win:  " << stats.wdl.win
              << " (" << std::setprecision(1) << (stats.wdl.win_rate() * 100) << "%)\n"
              << "  Draw: " << stats.wdl.draw
              << " (" << (stats.wdl.draw_rate() * 100) << "%)\n"
              << "  Loss: " << stats.wdl.loss
              << " (" << (stats.wdl.loss_rate() * 100) << "%)\n"
              << "\n"
              << "Side to Move:\n"
              << "  White: " << stats.side_to_move.white << "\n"
              << "  Black: " << stats.side_to_move.black << "\n"
              << "\n"
              << "Unique material configs: " << stats.material.unique_signatures() << "\n"
              << "\n"
              << "Output written to: " << output_dir << "/\n";

    return 0;
}
