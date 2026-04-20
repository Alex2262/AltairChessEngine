#pragma once

#include "raw_record.h"
#include <string>
#include <string_view>
#include <fstream>
#include <functional>

namespace pipeline {

// Parser for datagen output format: "{FEN} | {EVAL} | {WDL}"
class RecordParser {
public:
    static ParseResult parse_line(std::string_view line, size_t line_number);

    // Parse WDL value ("1.0", "0.5", "0.0")
    static bool parse_wdl(std::string_view wdl_str, WDL& wdl);
    static bool parse_eval(std::string_view eval_str, int32_t& eval);
};

// Streaming file reader for large files
class RecordReader {
public:
    using RecordCallback = std::function<bool(RawRecord&)>;  // Return false to stop
    using ErrorCallback = std::function<void(const std::string&, size_t)>;

    explicit RecordReader(const std::string& filepath);

    bool is_open() const { return file_.is_open(); }

    size_t process(RecordCallback on_record, ErrorCallback on_error = nullptr);

    const std::string& filepath() const { return filepath_; }

private:
    std::string filepath_;
    std::ifstream file_;
};

// Multi-file reader for processing multiple datagen output files
class MultiFileRecordReader {
public:
    using RecordCallback = std::function<bool(RawRecord&, const std::string&)>;
    using ErrorCallback = std::function<void(const std::string&, size_t, const std::string&)>;
    using FileStartCallback = std::function<void(const std::string&)>;

    // Add files to process
    void add_file(const std::string& filepath);
    void add_files(const std::vector<std::string>& filepaths);

    // Process all files
    size_t process(RecordCallback on_record,
                   ErrorCallback on_error = nullptr,
                   FileStartCallback on_file_start = nullptr);

    // Get list of files
    const std::vector<std::string>& files() const { return files_; }

private:
    std::vector<std::string> files_;
};

} // namespace pipeline
