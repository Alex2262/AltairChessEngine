#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

namespace pipeline {


    class CSVWriter {
    public:
        explicit CSVWriter(const std::string& filepath);
        ~CSVWriter();

        bool is_open() const { return file_.is_open(); }

        void write_header(const std::vector<std::string>& columns);
        void write_row_vec(const std::vector<std::string>& values);

        template<typename... Args>
        void write_row(Args&&... args) {
            std::ostringstream ss;
            write_values(ss, std::forward<Args>(args)...);
            file_ << ss.str() << "\n";
        }

        void flush() { file_.flush(); }
        void close() { file_.close(); }

    private:
        std::ofstream file_;

        template<typename T>
        void write_values(std::ostringstream& ss, T&& value) {
            ss << value;
        }

        template<typename T, typename... Rest>
        void write_values(std::ostringstream& ss, T&& first, Rest&&... rest) {
            ss << first << ",";
            write_values(ss, std::forward<Rest>(rest)...);
        }
    };

    inline std::string csv_escape(const std::string& value) {
        if (value.find(',') != std::string::npos ||
            value.find('"') != std::string::npos ||
            value.find('\n') != std::string::npos) {
            std::string escaped = "\"";
            for (char c : value) {
                if (c == '"') escaped += "\"\"";
                else escaped += c;
            }
            escaped += "\"";
            return escaped;
        }
        return value;
    }

}
