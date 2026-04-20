#pragma once

#include "shard_format.h"
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace pipeline {

struct ShardCompileOptions {
    size_t max_shard_bytes = 256 * 1024 * 1024;
    size_t shuffle_buffer_records = 200000;
    uint64_t random_seed = 0xA17A11ULL;
};

uint64_t compile_shards(const std::vector<std::string>& input_files,
                        const std::string& output_dir,
                        const ShardCompileOptions& options = {});

}  // namespace pipeline
