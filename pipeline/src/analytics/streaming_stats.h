#pragma once

#include "../parsing/raw_record.h"
#include "metrics.h"
#include <string>
#include <chrono>

namespace pipeline {

    // Aggregates all analytics in a streaming fashion
    struct StreamingStats {
        uint64_t total_records = 0;
        uint64_t valid_records = 0;
        EvalHistogram eval_hist;
        WDLDistribution wdl;
        MaterialCounter material;
        PieceCountDistribution piece_counts;
        MaterialPhaseStats material_phase;
        SideToMoveStats side_to_move;
        CastlingStats castling;
        KingPositionStats king_positions;
        EnPassantStats en_passant;
        HLL uniqueness;

        // Process a single record
        void add(const RawRecord& record);

        uint64_t invalid_records() const { return total_records - valid_records; }
        double estimated_unique() const { return uniqueness.estimate(); }
        double duplicate_ratio() const {
            double unique = estimated_unique();
            return valid_records > 0 ? std::max(0.0, 1.0 - unique / valid_records) : 0;
        }

        // Export all analytics to CSV files in a directory
        void write_all_csv(const std::string& output_dir,
                           uint64_t total_input_lines,
                           uint64_t parse_errors) const;

        // Write summary CSV
        void write_summary_csv(const std::string& filepath,
                               uint64_t total_input_lines,
                               uint64_t parse_errors) const;
    };

    // Progress reporter for long-running operations
    struct ProgressReporter {
        explicit ProgressReporter(uint64_t report_interval = 1000000);

        void start();
        void tick();
        void finish() const;

        uint64_t count() const { return processed; }
        double elapsed_seconds() const;
        double records_per_second() const;

        uint64_t processed = 0;
        uint64_t report_interval;
        std::chrono::steady_clock::time_point start_time;
    };

}
