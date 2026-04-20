#include "canonical_zobrist.h"

namespace pipeline {

CanonicalZobrist::CanonicalZobrist() {
    PRNG rng(PIPELINE_SEED);

    // Generate piece-square keys
    for (int piece = 0; piece < 12; ++piece) {
        for (int sq = 0; sq < N_SQUARES; ++sq) {
            piece_keys[piece][sq] = rng.rand64();
        }
    }

    // Side to move key
    side_key = rng.rand64();

    // Castling keys (16 combinations for 4 castling bits)
    for (int i = 0; i < 16; ++i) {
        castling_keys[i] = rng.rand64();
    }

    // En passant square keys
    for (int sq = 0; sq < N_SQUARES; ++sq) {
        ep_keys[sq] = rng.rand64();
    }
}

const CanonicalZobrist& CanonicalZobrist::instance() {
    static CanonicalZobrist instance;
    return instance;
}

} // namespace pipeline
