#include "metrics.h"

#include "csv_writer.h"
#include <algorithm>

namespace pipeline {

    namespace {

        double percentage(const uint64_t count, const uint64_t total) {
            return total > 0 ? 100.0 * static_cast<double>(count) / static_cast<double>(total) : 0.0;
        }

        std::string square_name(const int square) {
            return {static_cast<char>('a' + square % 8), static_cast<char>('1' + square / 8)};
        }

        constexpr std::array<const char*, 10> kPieceNames = {
            "white_pawn", "white_knight", "white_bishop", "white_rook", "white_queen",
            "black_pawn", "black_knight", "black_bishop", "black_rook", "black_queen"
        };

        constexpr int kPieceValues[6] = {1, 3, 3, 5, 9, 0};

        template <size_t N>
        void write_histogram_csv(const std::string& filepath,
                                 const std::array<uint64_t, N>& counts,
                                 const std::string& value_name,
                                 const std::string& count_name = "count") {
            CSVWriter writer(filepath);
            writer.write_header({value_name, count_name, "percentage"});

            uint64_t total = 0;
            for (const auto count : counts) total += count;

            for (size_t value = 0; value < N; ++value) {
                if (counts[value] > 0) {
                    writer.write_row(value, counts[value], percentage(counts[value], total));
                }
            }
        }

    }  // namespace

    constexpr std::array<int, EvalHistogram::num_buckets + 1> EvalHistogram::bucket_bounds;

    void EvalHistogram::add(const int32_t eval) {
        ++counts[bucket_for(eval)];
    }

    uint64_t EvalHistogram::total() const {
        uint64_t sum = 0;
        for (const auto count : counts) {
            sum += count;
        }
        return sum;
    }

    int EvalHistogram::bucket_for(const int32_t eval) {
        for (int i = 0; i < num_buckets; ++i) {
            if (eval < bucket_bounds[i + 1]) {
                return i;
            }
        }
        return num_buckets - 1;
    }

    std::pair<int, int> EvalHistogram::bounds_for(const int bucket) {
        return {bucket_bounds[bucket], bucket_bounds[bucket + 1]};
    }

    void EvalHistogram::write_csv(const std::string& filepath) const {
        CSVWriter writer(filepath);
        writer.write_header({"bucket_min", "bucket_max", "count", "percentage"});

        const uint64_t sum = total();
        for (int i = 0; i < num_buckets; ++i) {
            const auto [lo, hi] = bounds_for(i);
            writer.write_row(lo, hi, counts[i], percentage(counts[i], sum));
        }
    }

    void WDLDistribution::add(const WDL wdl) {
        switch (wdl) {
            case WDL::WIN:
                ++win;
                break;
            case WDL::DRAW:
                ++draw;
                break;
            case WDL::LOSS:
                ++loss;
                break;
        }
    }

    uint64_t WDLDistribution::total() const {
        return win + draw + loss;
    }

    double WDLDistribution::win_rate() const {
        return total() > 0 ? static_cast<double>(win) / static_cast<double>(total()) : 0.0;
    }

    double WDLDistribution::draw_rate() const {
        return total() > 0 ? static_cast<double>(draw) / static_cast<double>(total()) : 0.0;
    }

    double WDLDistribution::loss_rate() const {
        return total() > 0 ? static_cast<double>(loss) / static_cast<double>(total()) : 0.0;
    }

    void WDLDistribution::write_csv(const std::string& filepath) const {
        CSVWriter writer(filepath);
        writer.write_header({"outcome", "count", "percentage"});
        const uint64_t sum = total();
        writer.write_row("win", win, percentage(win, sum));
        writer.write_row("draw", draw, percentage(draw, sum));
        writer.write_row("loss", loss, percentage(loss, sum));
    }

    void MaterialCounter::add(const CanonicalPosition& pos) {
        add(MaterialSignature::from_position(pos));
    }

    void MaterialCounter::add(const MaterialSignature& sig) {
        ++counts[sig];
        ++total;
    }

    uint64_t MaterialCounter::count(const MaterialSignature& sig) const {
        const auto it = counts.find(sig);
        return it != counts.end() ? it->second : 0;
    }

    std::vector<std::pair<MaterialSignature, uint64_t>> MaterialCounter::top_n(const size_t n) const {
        std::vector<std::pair<MaterialSignature, uint64_t>> sorted(counts.begin(), counts.end());
        const auto split = sorted.begin() + std::min(n, sorted.size());
        std::partial_sort(sorted.begin(), split, sorted.end(),
                          [](const auto& left, const auto& right) { return left.second > right.second; });
        sorted.resize(std::min(n, sorted.size()));
        return sorted;
    }

    void MaterialCounter::write_csv(const std::string& filepath) const {
        CSVWriter writer(filepath);
        writer.write_header({
            "white_pawns", "white_knights", "white_bishops", "white_rooks", "white_queens",
            "black_pawns", "black_knights", "black_bishops", "black_rooks", "black_queens",
            "count", "percentage"
        });

        for (const auto& [signature, count] : top_n(counts.size())) {
            writer.write_row(
                static_cast<int>(signature.counts[0]), static_cast<int>(signature.counts[1]),
                static_cast<int>(signature.counts[2]), static_cast<int>(signature.counts[3]),
                static_cast<int>(signature.counts[4]), static_cast<int>(signature.counts[5]),
                static_cast<int>(signature.counts[6]), static_cast<int>(signature.counts[7]),
                static_cast<int>(signature.counts[8]), static_cast<int>(signature.counts[9]),
                count, percentage(count, total)
            );
        }
    }

    void PieceCountDistribution::add(const CanonicalPosition& pos) {
        add(MaterialSignature::from_position(pos));
    }

    void PieceCountDistribution::add(const MaterialSignature& signature) {
        for (int i = 0; i < 10; ++i) {
            const int piece_count = signature.counts[i];
            if (piece_count <= 10) {
                ++counts[i][piece_count];
            }
        }
        ++total;
    }

    void MaterialPhaseStats::add(const CanonicalPosition& pos, const int16_t fifty_move) {
        int white = 0;
        int black = 0;
        int non_pawn = 0;

        for (const auto piece : pos.board) {
            if (piece == EMPTY) continue;

            const PieceType type = get_piece_type(piece);
            if (type == KING) continue;

            const int value = kPieceValues[type];
            if (get_color(piece) == WHITE) white += value;
            else black += value;

            if (type != PAWN) non_pawn += value;
        }

        const int total_value = white + black;
        const int imbalance = white - black;

        ++total_material[std::min(total_value, max_total_material)];
        ++non_pawn_material[std::min(non_pawn, max_non_pawn_material)];
        ++white_material[std::min(white, max_side_material)];
        ++black_material[std::min(black, max_side_material)];
        ++material_imbalance[std::clamp(imbalance, -max_imbalance, max_imbalance) + max_imbalance];
        ++halfmove_clock[std::min<int>(fifty_move, max_halfmove_clock)];
        ++total;
    }

    void MaterialPhaseStats::write_total_material_csv(const std::string& filepath) const {
        write_histogram_csv(filepath, total_material, "total_material");
    }

    void MaterialPhaseStats::write_non_pawn_material_csv(const std::string& filepath) const {
        write_histogram_csv(filepath, non_pawn_material, "non_pawn_material");
    }

    void MaterialPhaseStats::write_material_imbalance_csv(const std::string& filepath) const {
        CSVWriter writer(filepath);
        writer.write_header({"material_imbalance", "count", "percentage"});

        for (int imbalance = -max_imbalance; imbalance <= max_imbalance; ++imbalance) {
            const uint64_t count = material_imbalance[imbalance + max_imbalance];
            if (count > 0) {
                writer.write_row(imbalance, count, percentage(count, total));
            }
        }
    }

    void MaterialPhaseStats::write_halfmove_clock_csv(const std::string& filepath) const {
        write_histogram_csv(filepath, halfmove_clock, "halfmove_clock");
    }

    double MaterialPhaseStats::average_total_material() const {
        if (total == 0) return 0.0;
        uint64_t sum = 0;
        for (size_t value = 0; value < total_material.size(); ++value) sum += value * total_material[value];
        return static_cast<double>(sum) / static_cast<double>(total);
    }

    double MaterialPhaseStats::average_non_pawn_material() const {
        if (total == 0) return 0.0;
        uint64_t sum = 0;
        for (size_t value = 0; value < non_pawn_material.size(); ++value) sum += value * non_pawn_material[value];
        return static_cast<double>(sum) / static_cast<double>(total);
    }

    double MaterialPhaseStats::average_halfmove_clock() const {
        if (total == 0) return 0.0;
        uint64_t sum = 0;
        for (size_t value = 0; value < halfmove_clock.size(); ++value) sum += value * halfmove_clock[value];
        return static_cast<double>(sum) / static_cast<double>(total);
    }

    void PieceCountDistribution::write_csv(const std::string& filepath) const {
        CSVWriter writer(filepath);
        std::vector<std::string> header = {"piece_type"};
        for (int count = 0; count <= 10; ++count) {
            header.push_back("count_" + std::to_string(count));
        }
        writer.write_header(header);

        for (int piece = 0; piece < 10; ++piece) {
            std::vector<std::string> row = {kPieceNames[piece]};
            for (int count = 0; count <= 10; ++count) {
                row.push_back(std::to_string(counts[piece][count]));
            }
            writer.write_row_vec(row);
        }
    }

    void SideToMoveStats::add(const Color side) {
        if (side == WHITE) {
            ++white;
        } else {
            ++black;
        }
    }

    uint64_t SideToMoveStats::total() const {
        return white + black;
    }

    void SideToMoveStats::write_csv(const std::string& filepath) const {
        CSVWriter writer(filepath);
        writer.write_header({"side", "count", "percentage"});
        const uint64_t sum = total();
        writer.write_row("white", white, percentage(white, sum));
        writer.write_row("black", black, percentage(black, sum));
    }

    void CastlingStats::add(const uint8_t castling) {
        if (castling < counts.size()) {
            ++counts[castling];
        }
    }

    uint64_t CastlingStats::total() const {
        uint64_t sum = 0;
        for (const auto count : counts) {
            sum += count;
        }
        return sum;
    }

    void CastlingStats::write_csv(const std::string& filepath) const {
        CSVWriter writer(filepath);
        writer.write_header({"castling_rights", "K", "Q", "k", "q", "count", "percentage"});

        const uint64_t sum = total();
        for (int rights_mask = 0; rights_mask < 16; ++rights_mask) {
            std::string rights;
            if (rights_mask == 0) {
                rights = "-";
            } else {
                if (rights_mask & 1) rights += "K";
                if (rights_mask & 2) rights += "Q";
                if (rights_mask & 4) rights += "k";
                if (rights_mask & 8) rights += "q";
            }

            writer.write_row(
                rights,
                (rights_mask & 1) ? 1 : 0,
                (rights_mask & 2) ? 1 : 0,
                (rights_mask & 4) ? 1 : 0,
                (rights_mask & 8) ? 1 : 0,
                counts[rights_mask],
                percentage(counts[rights_mask], sum)
            );
        }
    }

    void KingPositionStats::add(const CanonicalPosition& pos) {
        const Square white_king = pos.king_square(WHITE);
        const Square black_king = pos.king_square(BLACK);
        if (white_king != NO_SQUARE) {
            ++white[white_king];
        }
        if (black_king != NO_SQUARE) {
            ++black[black_king];
        }
        ++total;
    }

    void KingPositionStats::write_csv(const std::string& filepath) const {
        CSVWriter writer(filepath);
        writer.write_header({"square", "file", "rank", "white_king_count", "black_king_count"});
        for (int square = 0; square < 64; ++square) {
            writer.write_row(square_name(square), square % 8, square / 8, white[square], black[square]);
        }
    }

    void EnPassantStats::add(const Square ep) {
        if (ep == NO_SQUARE) {
            ++none;
        } else if (ep < 64) {
            ++squares[ep];
        }
    }

    uint64_t EnPassantStats::total() const {
        uint64_t sum = none;
        for (const auto count : squares) {
            sum += count;
        }
        return sum;
    }

    void EnPassantStats::write_csv(const std::string& filepath) const {
        CSVWriter writer(filepath);
        writer.write_header({"ep_square", "count", "percentage"});

        const uint64_t sum = total();
        writer.write_row("none", none, percentage(none, sum));

        for (int square = 0; square < 64; ++square) {
            const int rank = square / 8;
            if ((rank == 2 || rank == 5) && squares[square] > 0) {
                writer.write_row(square_name(square), squares[square], percentage(squares[square], sum));
            }
        }
    }

}  // namespace pipeline
