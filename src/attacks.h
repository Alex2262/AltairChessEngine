

#ifndef ALTAIR_ATTACKS_H
#define ALTAIR_ATTACKS_H

#include <array>
#include "bitboard.h"

#if defined(__APPLE__) && defined(__MACH__)

    [[nodiscard]] inline BITBOARD reverse_bits(BITBOARD b) {
        b = (b & 0x5555555555555555) << 1 | ((b >> 1) & 0x5555555555555555);
        b = (b & 0x3333333333333333) << 2 | ((b >> 2) & 0x3333333333333333);
        b = (b & 0x0f0f0f0f0f0f0f0f) << 4 | ((b >> 4) & 0x0f0f0f0f0f0f0f0f);
        b = (b & 0x00ff00ff00ff00ff) << 8 | ((b >> 8) & 0x00ff00ff00ff00ff);

        return (b << 48) | ((b & 0xffff0000) << 16) | ((b >> 16) & 0xffff0000) | (b >> 48);
    }

#else

    #include "immintrin.h"
    [[nodiscard]] inline BITBOARD reverse_bits(BITBOARD b) {
        return _pdep_u64(b, 0xFFFFFFFFFFFFFFFF);
    }

#endif

[[nodiscard]] inline BITBOARD hyperbola_quintessence(Square square, BITBOARD occupancy, BITBOARD mask) {
    BITBOARD mask_occ = mask & occupancy;
    BITBOARD reversed = reverse_bits(mask_occ);
    BITBOARD from_sq_rev = reverse_bits(from_square(square));

    return (((mask_occ - from_square(square) * 2) ^
             reverse_bits(reversed - from_sq_rev * 2)) & mask);
}


// Generate attacks for bishops and rooks
[[nodiscard]] inline BITBOARD get_bishop_attacks(Square square, BITBOARD occupancy) {
    return hyperbola_quintessence(square, occupancy, MASK_DIAGONAL[diagonal_of(square)]) |
           hyperbola_quintessence(square, occupancy, MASK_ANTI_DIAGONAL[anti_diagonal_of(square)]);
}

[[nodiscard]] inline BITBOARD get_rook_attacks(Square square, BITBOARD occupancy) {
    return hyperbola_quintessence(square, occupancy, MASK_FILE[file_of(square)]) |
           hyperbola_quintessence(square, occupancy, MASK_RANK[rank_of(square)]);
}

[[nodiscard]] inline BITBOARD get_queen_attacks(Square square, BITBOARD occupancy) {
    return get_bishop_attacks(square, occupancy) | get_rook_attacks(square, occupancy);
}

constexpr BITBOARD get_knight_attacks(Square square) {
    BITBOARD sq = from_square(square);
    BITBOARD res =
            shift<EAST>(shift<NORTH_NORTH>(sq)) | shift<WEST>(shift<NORTH_NORTH>(sq)) |
            shift<EAST>(shift<SOUTH_SOUTH>(sq)) | shift<WEST>(shift<SOUTH_SOUTH>(sq)) |
            shift<NORTH_WEST>(shift<WEST>(sq)) | shift<SOUTH_WEST>(shift<WEST>(sq))   |
            shift<NORTH_EAST>(shift<EAST>(sq)) | shift<SOUTH_EAST>(shift<EAST>(sq));

    return res;
}

constexpr BITBOARD get_king_attacks(Square square) {
    BITBOARD sq = from_square(square);
    BITBOARD res =
            shift<NORTH>(sq) | shift<EAST>(sq) | shift<SOUTH>(sq) | shift<WEST>(sq) |
            shift<NORTH_EAST>(sq) | shift<NORTH_WEST>(sq) | shift<SOUTH_EAST>(sq) | shift<SOUTH_WEST>(sq);

    return res;
}

constexpr BITBOARD get_pawn_attacks(Square square, Color color) {
    if (color == WHITE) {
        BITBOARD res = shift<NORTH>(from_square(square));
        return shift<WEST>(res) | shift<EAST>(res);
    }

    BITBOARD res = shift<SOUTH>(from_square(square));
    return shift<WEST>(res) | shift<EAST>(res);
}

inline BITBOARD get_piece_attacks(Piece piece, Square square, BITBOARD occupancy) {
    auto piece_type = static_cast<PieceType>(piece % COLOR_OFFSET);
    if (piece == WHITE_PAWN) return get_pawn_attacks(square, WHITE);
    else if (piece == BLACK_PAWN) return get_pawn_attacks(square, BLACK);
    else if (piece_type == KNIGHT) return get_knight_attacks(square);
    else if (piece_type == BISHOP) return get_bishop_attacks(square, occupancy);
    else if (piece_type == ROOK) return get_rook_attacks(square, occupancy);
    else if (piece_type == QUEEN) return get_queen_attacks(square, occupancy);
    else return get_king_attacks(square);
}

inline BITBOARD get_regular_piece_type_attacks_nt(PieceType piece_type, Square square, BITBOARD occupancy) {

    if (piece_type == KNIGHT) return get_knight_attacks(square);
    else if (piece_type == BISHOP) return get_bishop_attacks(square, occupancy);
    else if (piece_type == ROOK) return get_rook_attacks(square, occupancy);
    else if (piece_type == QUEEN) return get_queen_attacks(square, occupancy);
    return get_king_attacks(square);
}

template<PieceType piece_type>
inline BITBOARD get_regular_piece_type_attacks(Square square, BITBOARD occupancy) {

    if constexpr (piece_type == KNIGHT) return get_knight_attacks(square);
    else if constexpr (piece_type == BISHOP) return get_bishop_attacks(square, occupancy);
    else if constexpr (piece_type == ROOK) return get_rook_attacks(square, occupancy);
    else if constexpr (piece_type == QUEEN) return get_queen_attacks(square, occupancy);
    return get_king_attacks(square);
}


constexpr std::array<std::array<BITBOARD, 64>, 2> generate_passed_pawn_masks() {
    std::array<std::array<BITBOARD, 64>, 2> masks{};

    for (int i = 0; i < 64; i++) {
        masks[WHITE][i] = from_square(static_cast<Square>(i));
        masks[WHITE][i] |= shift<EAST>(masks[WHITE][i]) | shift<WEST>(masks[WHITE][i]);
        masks[WHITE][i] ^= fill<NORTH>(masks[WHITE][i]);
    }

    for (int i = 0; i < 64; i++) {
        masks[BLACK][i] = from_square(static_cast<Square>(i));
        masks[BLACK][i] |= shift<EAST>(masks[BLACK][i]) | shift<WEST>(masks[BLACK][i]);
        masks[BLACK][i] ^= fill<SOUTH>(masks[BLACK][i]);
    }

    return masks;
}

constexpr auto passed_pawn_masks = generate_passed_pawn_masks();

constexpr BITBOARD get_pawn_bitboard_attacks(BITBOARD pawns, Color color) {
    BITBOARD attacks = color == WHITE ? shift<NORTH>(pawns) : shift<SOUTH>(pawns);
    return shift<WEST>(attacks) | shift<EAST>(attacks);
}


#endif //ALTAIR_ATTACKS_H
