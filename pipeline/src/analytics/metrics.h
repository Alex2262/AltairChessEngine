#pragma once

#include "../core/canonical_position.h"
#include "../core/types.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace pipeline {

    struct MaterialSignatureHash {
        size_t operator()(const MaterialSignature& sig) const {
            return std::hash<uint64_t>{}(sig.to_uint64());
        }
    };

    template<int Precision = 14>
    struct HyperLogLog {
        static constexpr size_t num_registers = 1 << Precision;
        static constexpr uint64_t register_mask = num_registers - 1;

        std::array<uint8_t, num_registers> registers{};

        void add(const uint64_t hash) {
            const size_t index = hash & register_mask;
            const uint64_t w = hash >> Precision;
            const uint8_t rank = leading_zeros(w) + 1;
            registers[index] = std::max(registers[index], rank);
        }

        double estimate() const {
            double sum = 0.0;
            int zeros = 0;

            for (const auto reg : registers) {
                sum += 1.0 / static_cast<double>(1ULL << reg);
                zeros += reg == 0;
            }

            double result = alpha() * num_registers * num_registers / sum;
            if (result <= 2.5 * num_registers && zeros > 0) {
                result = num_registers * std::log(static_cast<double>(num_registers) / zeros);
            }
            return result;
        }

        void merge(const HyperLogLog& other) {
            for (size_t i = 0; i < num_registers; ++i) {
                registers[i] = std::max(registers[i], other.registers[i]);
            }
        }

        void clear() {
            registers.fill(0);
        }

    private:
        static constexpr double alpha() {
            if constexpr (Precision == 4) return 0.673;
            if constexpr (Precision == 5) return 0.697;
            if constexpr (Precision == 6) return 0.709;
            return 0.7213 / (1.0 + 1.079 / num_registers);
        }

        static uint8_t leading_zeros(const uint64_t value) {
            if (value == 0) return 64 - Precision;
            uint8_t count = 0;
            uint64_t mask = 1ULL << (63 - Precision);
            while (mask && !(value & mask)) {
                ++count;
                mask >>= 1;
            }
            return std::min<uint8_t>(count, 64 - Precision);
        }
    };

    using HLL = HyperLogLog<14>;

    struct EvalHistogram {
        static constexpr int num_buckets = 26;
        static constexpr std::array<int, num_buckets + 1> bucket_bounds = {
            -100000, -5000, -3000, -2000, -1500, -1000, -700, -500, -300, -200, -100, -50, -20, 0,
            20, 50, 100, 200, 300, 500, 700, 1000, 1500, 2000, 3000, 5000, 100000
        };

        std::array<uint64_t, num_buckets> counts{};

        void add(int32_t eval);
        uint64_t total() const;
        void write_csv(const std::string& filepath) const;

        static int bucket_for(int32_t eval);
        static std::pair<int, int> bounds_for(int bucket);
    };

    struct WDLDistribution {
        uint64_t win = 0;
        uint64_t draw = 0;
        uint64_t loss = 0;

        void add(WDL wdl);
        uint64_t total() const;
        double win_rate() const;
        double draw_rate() const;
        double loss_rate() const;
        void write_csv(const std::string& filepath) const;
    };

    struct MaterialCounter {
        std::unordered_map<MaterialSignature, uint64_t, MaterialSignatureHash> counts;
        uint64_t total = 0;

        void add(const CanonicalPosition& pos);
        void add(const MaterialSignature& sig);
        uint64_t count(const MaterialSignature& sig) const;
        size_t unique_signatures() const { return counts.size(); }
        std::vector<std::pair<MaterialSignature, uint64_t>> top_n(size_t n) const;
        void write_csv(const std::string& filepath) const;
    };

    struct PieceCountDistribution {
        std::array<std::array<uint64_t, 11>, 10> counts{};
        uint64_t total = 0;

        void add(const CanonicalPosition& pos);
        void add(const MaterialSignature& sig);
        void write_csv(const std::string& filepath) const;
    };

    struct MaterialPhaseStats {
        static constexpr int max_total_material = 206;
        static constexpr int max_side_material = 103;
        static constexpr int max_non_pawn_material = 190;
        static constexpr int max_imbalance = 103;
        static constexpr int max_halfmove_clock = 100;

        std::array<uint64_t, max_total_material + 1> total_material{};
        std::array<uint64_t, max_non_pawn_material + 1> non_pawn_material{};
        std::array<uint64_t, max_side_material + 1> white_material{};
        std::array<uint64_t, max_side_material + 1> black_material{};
        std::array<uint64_t, 2 * max_imbalance + 1> material_imbalance{};
        std::array<uint64_t, max_halfmove_clock + 1> halfmove_clock{};
        uint64_t total = 0;

        void add(const CanonicalPosition& pos, int16_t fifty_move);
        void write_total_material_csv(const std::string& filepath) const;
        void write_non_pawn_material_csv(const std::string& filepath) const;
        void write_material_imbalance_csv(const std::string& filepath) const;
        void write_halfmove_clock_csv(const std::string& filepath) const;
        double average_total_material() const;
        double average_non_pawn_material() const;
        double average_halfmove_clock() const;
    };

    struct SideToMoveStats {
        uint64_t white = 0;
        uint64_t black = 0;

        void add(Color side);
        uint64_t total() const;
        void write_csv(const std::string& filepath) const;
    };

    struct CastlingStats {
        std::array<uint64_t, 16> counts{};

        void add(uint8_t castling);
        uint64_t total() const;
        void write_csv(const std::string& filepath) const;
    };

    struct KingPositionStats {
        std::array<uint64_t, 64> white{};
        std::array<uint64_t, 64> black{};
        uint64_t total = 0;

        void add(const CanonicalPosition& pos);
        void write_csv(const std::string& filepath) const;
    };

    struct EnPassantStats {
        std::array<uint64_t, 64> squares{};
        uint64_t none = 0;

        void add(Square ep);
        uint64_t total() const;
        void write_csv(const std::string& filepath) const;
    };

}  // namespace pipeline
