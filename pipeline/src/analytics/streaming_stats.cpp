#include "streaming_stats.h"
#include "csv_writer.h"
#include <filesystem>
#include <iostream>
#include <iomanip>

namespace pipeline {

    void StreamingStats::add(const RawRecord& record) {
        ++total_records;

        if (!record.is_valid) return;
        ++valid_records;

        const MaterialSignature signature = MaterialSignature::from_position(record.position);

        eval_hist.add(record.eval);
        wdl.add(record.wdl);
        material.add(signature);
        piece_counts.add(signature);
        material_phase.add(record.position, record.fifty_move);
        side_to_move.add(record.position.side);
        castling.add(record.position.castling);
        king_positions.add(record.position);
        en_passant.add(record.position.ep_square);
        uniqueness.add(record.hash);
    }

    void StreamingStats::write_all_csv(const std::string& output_dir,
                                       const uint64_t total_input_lines,
                                       const uint64_t parse_errors) const {
        namespace fs = std::filesystem;
        fs::create_directories(output_dir);

        write_summary_csv(output_dir + "/summary.csv", total_input_lines, parse_errors);
        eval_hist.write_csv(output_dir + "/eval_histogram.csv");
        wdl.write_csv(output_dir + "/wdl_distribution.csv");
        material.write_csv(output_dir + "/material_distribution.csv");
        piece_counts.write_csv(output_dir + "/piece_counts.csv");
        material_phase.write_total_material_csv(output_dir + "/total_material.csv");
        material_phase.write_non_pawn_material_csv(output_dir + "/non_pawn_material.csv");
        material_phase.write_material_imbalance_csv(output_dir + "/material_imbalance.csv");
        material_phase.write_halfmove_clock_csv(output_dir + "/halfmove_clock.csv");
        side_to_move.write_csv(output_dir + "/side_to_move.csv");
        castling.write_csv(output_dir + "/castling_rights.csv");
        king_positions.write_csv(output_dir + "/king_positions.csv");
        en_passant.write_csv(output_dir + "/en_passant.csv");
    }

    void StreamingStats::write_summary_csv(const std::string& filepath,
                                          const uint64_t total_input_lines,
                                          const uint64_t parse_errors) const {
        CSVWriter writer(filepath);
        writer.write_header({"metric", "value"});

        writer.write_row("total_records", total_input_lines);
        writer.write_row("total_input_lines", total_input_lines);
        writer.write_row("valid_records", valid_records);
        writer.write_row("parse_errors", parse_errors);
        writer.write_row("records_reaching_analytics", total_records);
        writer.write_row("estimated_unique", static_cast<uint64_t>(estimated_unique()));
        writer.write_row("duplicate_ratio", duplicate_ratio());
        writer.write_row("unique_material_configs", material.unique_signatures());
        writer.write_row("average_total_material", material_phase.average_total_material());
        writer.write_row("average_non_pawn_material", material_phase.average_non_pawn_material());
        writer.write_row("average_halfmove_clock", material_phase.average_halfmove_clock());
        writer.write_row("white_to_move", side_to_move.white);
        writer.write_row("black_to_move", side_to_move.black);
        writer.write_row("win_count", wdl.win);
        writer.write_row("draw_count", wdl.draw);
        writer.write_row("loss_count", wdl.loss);
        writer.write_row("win_rate", wdl.win_rate());
        writer.write_row("draw_rate", wdl.draw_rate());
        writer.write_row("loss_rate", wdl.loss_rate());
    }

    // ProgressReporter implementation

    ProgressReporter::ProgressReporter(const uint64_t report_interval)
        : report_interval(report_interval) {}

    void ProgressReporter::start() {
        start_time = std::chrono::steady_clock::now();
        processed = 0;
    }

    void ProgressReporter::tick() {
        ++processed;
        if (processed % report_interval == 0) {
            const auto now = std::chrono::steady_clock::now();
            const double elapsed = std::chrono::duration<double>(now - start_time).count();
            const double rps = processed / elapsed;

            std::cerr << "\rProcessed " << processed << " records ("
                      << std::fixed << std::setprecision(0) << rps << " rec/s)"
                      << std::flush;
        }
    }

    void ProgressReporter::finish() const {
        std::cerr << "\rProcessed " << processed << " records in "
                  << std::fixed << std::setprecision(2) << elapsed_seconds() << "s ("
                  << std::setprecision(0) << records_per_second() << " rec/s)"
                  << std::endl;
    }

    double ProgressReporter::elapsed_seconds() const {
        const auto now = std::chrono::steady_clock::now();
        return std::chrono::duration<double>(now - start_time).count();
    }

    double ProgressReporter::records_per_second() const {
        const double elapsed = elapsed_seconds();
        return elapsed > 0 ? processed / elapsed : 0;
    }

}
