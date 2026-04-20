#pragma once

#include "shard_format.h"
#include <fstream>
#include <string>
#include <vector>

namespace pipeline {

class ShardWriter {
public:
    void open(const std::string& filepath);
    void write_record(const PackedBoardRecord& record);
    void flush();
    void close();

    bool is_open() const { return file.is_open(); }
    bool has_records() const { return record_count > 0; }
    size_t current_size() const { return sizeof(ShardHeader) + bytes_written + buffer.size(); }
    uint32_t current_record_count() const { return record_count; }
    const std::string& current_path() const { return path; }

private:
    std::ofstream file;
    std::string path;
    uint32_t record_count = 0;
    size_t bytes_written = 0;
    std::vector<uint8_t> buffer;
};

}  // namespace pipeline
