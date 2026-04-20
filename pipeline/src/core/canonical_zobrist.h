#pragma once

#include "types.h"
#include <array>

namespace pipeline {

// PRNG for generating Zobrist keys (same algorithm as engine, different seed)
class PRNG {
public:
    explicit PRNG(uint64_t seed) : state_(seed) {}

    uint64_t rand64() {
        state_ ^= state_ >> 12;
        state_ ^= state_ << 25;
        state_ ^= state_ >> 27;
        return state_ * 0x2545F4914F6CDD1DULL;
    }

private:
    uint64_t state_;
};

// Zobrist keys for canonical position hashing
// Uses a different seed than the engine (271828182845 vs 31415926)
// to ensure pipeline hashes are independent
struct CanonicalZobrist {
    // Different seed than engine for isolation
    static constexpr uint64_t PIPELINE_SEED = 271828182845ULL;

    std::array<std::array<Hash, N_SQUARES>, 12> piece_keys;  // [piece][square]
    Hash side_key;                                            // Side to move
    std::array<Hash, 16> castling_keys;                       // 4-bit castling combinations
    std::array<Hash, N_SQUARES> ep_keys;                      // En passant squares

    CanonicalZobrist();

    static const CanonicalZobrist& instance();
};

// Global instance accessor
inline const CanonicalZobrist& zobrist() {
    return CanonicalZobrist::instance();
}

} // namespace pipeline
