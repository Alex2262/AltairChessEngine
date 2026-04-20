#include "canonical_position.h"

namespace pipeline {

Hash CanonicalPosition::compute_hash() const {
    const auto& z = zobrist();
    Hash hash = 0;

    // XOR piece-square keys
    for (int sq = 0; sq < N_SQUARES; ++sq) {
        Piece p = board[sq];
        if (p != EMPTY) {
            hash ^= z.piece_keys[p][sq];
        }
    }

    // Side to move
    if (side == BLACK) {
        hash ^= z.side_key;
    }

    // Castling rights
    hash ^= z.castling_keys[castling];

    // En passant square
    if (ep_square != NO_SQUARE) {
        hash ^= z.ep_keys[ep_square];
    }

    return hash;
}

bool CanonicalPosition::operator==(const CanonicalPosition& other) const {
    return board == other.board &&
           side == other.side &&
           castling == other.castling &&
           ep_square == other.ep_square;
}

bool CanonicalPosition::operator<(const CanonicalPosition& other) const {
    // Lexicographic comparison
    if (side != other.side) return side < other.side;
    if (castling != other.castling) return castling < other.castling;
    if (ep_square != other.ep_square) return ep_square < other.ep_square;
    return board < other.board;
}

int CanonicalPosition::count_piece(Piece p) const {
    int count = 0;
    for (const auto piece : board) {
        count += piece == p;
    }
    return count;
}

int CanonicalPosition::count_piece_type(PieceType pt, Color c) const {
    return count_piece(get_piece(pt, c));
}

int CanonicalPosition::total_material() const {
    constexpr int values[6] = {1, 3, 3, 5, 9, 0};
    int total = 0;
    for (const auto p : board) {
        if (p != EMPTY) {
            const PieceType pt = get_piece_type(p);
            if (pt != KING) {
                total += values[pt];
            }
        }
    }
    return total;
}

Square CanonicalPosition::king_square(Color c) const {
    const Piece king = get_piece(KING, c);
    for (int sq = 0; sq < N_SQUARES; ++sq) {
        if (board[sq] == king) {
            return static_cast<Square>(sq);
        }
    }
    return NO_SQUARE;
}

bool CanonicalPosition::is_valid() const {
    int white_kings = 0;
    int black_kings = 0;
    int white_pawns = 0;
    int black_pawns = 0;

    for (int sq = 0; sq < N_SQUARES; ++sq) {
        const Piece piece = board[sq];
        white_kings += piece == WHITE_KING;
        black_kings += piece == BLACK_KING;
        white_pawns += piece == WHITE_PAWN;
        black_pawns += piece == BLACK_PAWN;

        if ((square_rank(static_cast<Square>(sq)) == RANK_1 || square_rank(static_cast<Square>(sq)) == RANK_8) &&
            (piece == WHITE_PAWN || piece == BLACK_PAWN)) {
            return false;
        }
    }

    if (white_kings != 1 || black_kings != 1) return false;
    if (white_pawns > 8 || black_pawns > 8) return false;

    if (ep_square != NO_SQUARE) {
        const int rank = square_rank(ep_square);
        if (side == WHITE && rank != RANK_6) return false;
        if (side == BLACK && rank != RANK_3) return false;
    }

    return true;
}

MaterialSignature MaterialSignature::from_position(const CanonicalPosition& pos) {
    MaterialSignature sig;
    for (const auto p : pos.board) {
        if (p == EMPTY) continue;
        const PieceType pt = get_piece_type(p);
        if (pt == KING) continue;  // Don't count kings
        const Color c = get_color(p);
        const int idx = static_cast<int>(pt) + (c == BLACK ? 5 : 0);
        sig.counts[idx]++;
    }
    return sig;
}

uint64_t MaterialSignature::to_uint64() const {
    // Pack counts into 64 bits (6 bits per count, max 63)
    uint64_t result = 0;
    for (int i = 0; i < 10; ++i) {
        result |= static_cast<uint64_t>(counts[i] & 0x3F) << (i * 6);
    }
    return result;
}

} // namespace pipeline
