#include "../src/compilation/shard_compiler.h"
#include <iostream>
#include <vector>
#include <glob.h>

std::vector<std::string> expand_globs(const std::vector<std::string>& patterns) {
    std::vector<std::string> files;
    for (const auto& pattern : patterns) {
        glob_t glob_result;
        if (glob(pattern.c_str(), GLOB_TILDE | GLOB_NOCHECK, nullptr, &glob_result) == 0) {
            for (size_t i = 0; i < glob_result.gl_pathc; ++i) {
                files.push_back(glob_result.gl_pathv[i]);
            }
        }
        globfree(&glob_result);
    }
    return files;
}

int main(int argc, char* argv[]) {
    std::string output_dir = "shards";
    pipeline::ShardCompileOptions options;
    size_t max_shard_mb = options.max_shard_bytes / (1024 * 1024);
    std::vector<std::string> input_patterns;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-o" || arg == "--output") && i + 1 < argc) {
            output_dir = argv[++i];
        } else if (arg == "--max-shard-mb" && i + 1 < argc) {
            max_shard_mb = std::stoull(argv[++i]);
        } else if (arg == "--shuffle-buffer" && i + 1 < argc) {
            options.shuffle_buffer_records = std::stoull(argv[++i]);
        } else if (arg == "--seed" && i + 1 < argc) {
            options.random_seed = std::stoull(argv[++i]);
        } else if (arg == "-h" || arg == "--help") {
            std::cout << "Usage: " << argv[0] << " [options] <input_files...>\n"
                      << "  -o, --output <dir>     Output directory (default: shards/)\n"
                      << "  --max-shard-mb <n>     Max shard size in MB (default: 256)\n"
                      << "  --shuffle-buffer <n>   Shuffle buffer size in records (default: 200000)\n"
                      << "  --seed <n>             RNG seed for shard mixing\n";
            return 0;
        } else if (arg[0] != '-') {
            input_patterns.push_back(arg);
        }
    }

    if (input_patterns.empty()) {
        std::cerr << "Error: No input files specified\n";
        return 1;
    }

    auto input_files = expand_globs(input_patterns);
    if (input_files.empty()) {
        std::cerr << "Error: No matching files found\n";
        return 1;
    }

    std::cout << "Compiling " << input_files.size() << " files to " << output_dir << "\n";
    options.max_shard_bytes = max_shard_mb * 1024 * 1024;
    pipeline::compile_shards(input_files, output_dir, options);
    return 0;
}
