#pragma once

#include "types.h"
#include "canonical_zobrist.h"
#include <array>

namespace pipeline {

// Canonical position representation
// Includes: board, side to move, castling rights, en passant
// Excludes: fifty-move clock (not part of position identity)
struct CanonicalPosition {
    std::array<Piece, N_SQUARES> board;  // 64 squares
    Color side;                           // Side to move
    uint8_t castling;                     // 4-bit castling rights (KQkq)
    Square ep_square;                     // En passant square (NO_SQUARE if none)

    CanonicalPosition() : side(WHITE), castling(0), ep_square(NO_SQUARE) { board.fill(EMPTY); }

    // Compute Zobrist hash (canonical identity)
    Hash compute_hash() const;

    // Equality and comparison (for sorting/dedup)
    bool operator==(const CanonicalPosition& other) const;
    bool operator<(const CanonicalPosition& other) const;

    // Get piece counts for analytics
    int count_piece(Piece p) const;
    int count_piece_type(PieceType pt, Color c) const;
    int total_material() const;  // Sum of piece values (P=1, N=3, B=3, R=5, Q=9)

    // Find king positions
    Square king_square(Color c) const;

    // Validation
    bool is_valid() const;
};

// Material signature for analytics
struct MaterialSignature {
    std::array<uint8_t, 10> counts;  // WP, WN, WB, WR, WQ, BP, BN, BB, BR, BQ

    MaterialSignature() { counts.fill(0); }

    static MaterialSignature from_position(const CanonicalPosition& pos);

    bool operator==(const MaterialSignature& other) const {
        return counts == other.counts;
    }

    bool operator<(const MaterialSignature& other) const {
        return counts < other.counts;
    }

    // For use as hash key
    uint64_t to_uint64() const;
};

} // namespace pipeline
