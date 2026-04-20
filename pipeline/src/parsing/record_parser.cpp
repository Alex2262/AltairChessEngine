#include "record_parser.h"
#include "fen_parser.h"
#include <cctype>

namespace pipeline {

// Trim whitespace from both ends
static std::string_view trim(std::string_view sv) {
    while (!sv.empty() && std::isspace(static_cast<unsigned char>(sv.front()))) sv.remove_prefix(1);
    while (!sv.empty() && std::isspace(static_cast<unsigned char>(sv.back()))) sv.remove_suffix(1);
    return sv;
}

static bool parse_int32(std::string_view text, int32_t& value) {
    text = trim(text);
    if (text.empty()) return false;

    bool negative = false;
    size_t index = 0;
    if (text[index] == '+' || text[index] == '-') {
        negative = text[index] == '-';
        ++index;
    }

    if (index == text.size()) return false;

    int64_t parsed = 0;
    for (; index < text.size(); ++index) {
        const char c = text[index];
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
        parsed = parsed * 10 + (c - '0');
        if ((!negative && parsed > INT32_MAX) || (negative && parsed > static_cast<int64_t>(INT32_MAX) + 1)) {
            return false;
        }
    }

    value = negative ? static_cast<int32_t>(-parsed) : static_cast<int32_t>(parsed);
    return true;
}

bool RecordParser::parse_wdl(std::string_view wdl_str, WDL& wdl) {
    wdl_str = trim(wdl_str);

    if (wdl_str == "1.0" || wdl_str == "1") {
        wdl = WDL::WIN;
        return true;
    } else if (wdl_str == "0.5") {
        wdl = WDL::DRAW;
        return true;
    } else if (wdl_str == "0.0" || wdl_str == "0") {
        wdl = WDL::LOSS;
        return true;
    }
    return false;
}

bool RecordParser::parse_eval(std::string_view eval_str, int32_t& eval) {
    return parse_int32(eval_str, eval);
}

ParseResult RecordParser::parse_line(std::string_view line, size_t line_number) {
    line = trim(line);
    if (line.empty()) {
        return ParseResult::failure("Empty line", line_number);
    }

    const size_t first_pipe = line.find('|');
    const size_t second_pipe = first_pipe == std::string_view::npos ? std::string_view::npos : line.find('|', first_pipe + 1);
    if (first_pipe == std::string_view::npos || second_pipe == std::string_view::npos ||
        line.find('|', second_pipe + 1) != std::string_view::npos) {
        return ParseResult::failure("Expected 3 pipe-delimited fields", line_number);
    }

    const std::string_view fen_part = trim(line.substr(0, first_pipe));
    const std::string_view eval_part = trim(line.substr(first_pipe + 1, second_pipe - first_pipe - 1));
    const std::string_view wdl_part = trim(line.substr(second_pipe + 1));

    auto fen_result = FenParser::parse(fen_part);
    if (!fen_result.success) {
        return ParseResult::failure("FEN parse error: " + fen_result.error, line_number);
    }

    int32_t eval = 0;
    if (!parse_eval(eval_part, eval)) {
        return ParseResult::failure("Invalid eval value", line_number);
    }

    WDL wdl;
    if (!parse_wdl(wdl_part, wdl)) {
        return ParseResult::failure("Invalid WDL value", line_number);
    }

    RawRecord record;
    record.position = std::move(fen_result.position);
    record.fifty_move = fen_result.fifty_move;
    record.eval = eval;
    record.wdl = wdl;
    record.line_number = line_number;
    record.is_valid = true;
    record.compute_hash();

    return ParseResult::success(std::move(record));
}

// RecordReader implementation

RecordReader::RecordReader(const std::string& filepath)
    : filepath_(filepath), file_(filepath) {}

size_t RecordReader::process(RecordCallback on_record, ErrorCallback on_error) {
    if (!file_.is_open()) {
        if (on_error) {
            on_error("Failed to open file: " + filepath_, 0);
        }
        return 0;
    }

    std::string line;
    size_t line_number = 0;
    size_t total_processed = 0;

    while (std::getline(file_, line)) {
        ++line_number;
        ++total_processed;

        auto result = RecordParser::parse_line(line, line_number);

        if (result.ok()) {
            if (!on_record(*result.record)) {
                break;  // Callback requested stop
            }
        } else if (on_error) {
            on_error(result.error, line_number);
        }
    }

    return total_processed;
}

// MultiFileRecordReader implementation

void MultiFileRecordReader::add_file(const std::string& filepath) {
    files_.push_back(filepath);
}

void MultiFileRecordReader::add_files(const std::vector<std::string>& filepaths) {
    files_.insert(files_.end(), filepaths.begin(), filepaths.end());
}

size_t MultiFileRecordReader::process(RecordCallback on_record,
                                       ErrorCallback on_error,
                                       FileStartCallback on_file_start) {
    size_t total = 0;
    bool should_stop = false;

    for (const auto& filepath : files_) {
        if (should_stop) break;

        if (on_file_start) {
            on_file_start(filepath);
        }

        RecordReader reader(filepath);
        total += reader.process(
            [&](RawRecord& record) {
                bool cont = on_record(record, filepath);
                if (!cont) should_stop = true;
                return cont;
            },
            [&](const std::string& error, size_t line) {
                if (on_error) {
                    on_error(error, line, filepath);
                }
            }
        );
    }

    return total;
}

} // namespace pipeline
