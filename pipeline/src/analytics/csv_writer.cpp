#include "csv_writer.h"

namespace pipeline {

    CSVWriter::CSVWriter(const std::string& filepath) : file_(filepath) {}

    CSVWriter::~CSVWriter() {
        if (file_.is_open()) {
            file_.close();
        }
    }

    void CSVWriter::write_header(const std::vector<std::string>& columns) {
        for (size_t i = 0; i < columns.size(); ++i) {
            file_ << csv_escape(columns[i]);
            if (i + 1 < columns.size()) file_ << ",";
        }
        file_ << "\n";
    }

    void CSVWriter::write_row_vec(const std::vector<std::string>& values) {
        for (size_t i = 0; i < values.size(); ++i) {
            file_ << csv_escape(values[i]);
            if (i + 1 < values.size()) file_ << ",";
        }
        file_ << "\n";
    }

} // namespace pipeline
