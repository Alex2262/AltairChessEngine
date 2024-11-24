

#ifndef ALTAIR_ATTACKS_H
#define ALTAIR_ATTACKS_H

#include <array>
#include "bitboard.h"


[[nodiscard]] constexpr BITBOARD board_edge(Direction D) {
    if (D == NORTH) return MASK_RANK[RANK_8];
    else if (D == SOUTH) return MASK_RANK[RANK_1];
    else if (D == EAST) return MASK_FILE[FILE_H];
    else if (D == WEST) return MASK_FILE[FILE_A];
    else if (D == NORTH_EAST) return MASK_RANK[RANK_8] | MASK_FILE[FILE_H];
    else if (D == NORTH_WEST) return MASK_RANK[RANK_8] | MASK_FILE[FILE_A];
    else if (D == SOUTH_EAST) return MASK_RANK[RANK_1] | MASK_FILE[FILE_H];
    else if (D == SOUTH_WEST) return MASK_RANK[RANK_1] | MASK_FILE[FILE_A];
    return 0;
}

template<Direction D>
[[nodiscard]] constexpr BITBOARD generate_slow_sliding_attacks(Square square, BITBOARD occupancy) {
    BITBOARD attacks{};
    BITBOARD blockers = board_edge(D);
    BITBOARD square_bb = from_square(square);

    if ((blockers & square_bb) != 0) return attacks;
    blockers |= occupancy;
    do {
        square_bb = shift<D>(square_bb);
        attacks |= square_bb;
    } while ((blockers & square_bb) == 0);

    return attacks;
}

[[nodiscard]] constexpr BITBOARD get_bishop_attacks(Square square, BITBOARD occupancy) {
    return generate_slow_sliding_attacks<NORTH_EAST>(square, occupancy) |
           generate_slow_sliding_attacks<NORTH_WEST>(square, occupancy) |
           generate_slow_sliding_attacks<SOUTH_EAST>(square, occupancy) |
           generate_slow_sliding_attacks<SOUTH_WEST>(square, occupancy);
}

[[nodiscard]] constexpr BITBOARD get_rook_attacks(Square square, BITBOARD occupancy) {
    return generate_slow_sliding_attacks<NORTH>(square, occupancy) |
           generate_slow_sliding_attacks<SOUTH>(square, occupancy) |
           generate_slow_sliding_attacks<EAST>(square, occupancy) |
           generate_slow_sliding_attacks<WEST>(square, occupancy);
}

constexpr BITBOARD get_queen_attacks(Square square, BITBOARD occupancy) {
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

constexpr BITBOARD get_piece_attacks(Piece piece, Square square, BITBOARD occupancy) {
    auto piece_type = static_cast<PieceType>(piece % COLOR_OFFSET);
    if (piece == WHITE_PAWN) return get_pawn_attacks(square, WHITE);
    else if (piece == BLACK_PAWN) return get_pawn_attacks(square, BLACK);
    else if (piece_type == KNIGHT) return get_knight_attacks(square);
    else if (piece_type == BISHOP) return get_bishop_attacks(square, occupancy);
    else if (piece_type == ROOK) return get_rook_attacks(square, occupancy);
    else if (piece_type == QUEEN) return get_queen_attacks(square, occupancy);
    else return get_king_attacks(square);
}

constexpr BITBOARD get_regular_piece_type_attacks_nt(PieceType piece_type, Square square, BITBOARD occupancy) {

    if (piece_type == KNIGHT) return get_knight_attacks(square);
    else if (piece_type == BISHOP) return get_bishop_attacks(square, occupancy);
    else if (piece_type == ROOK) return get_rook_attacks(square, occupancy);
    else if (piece_type == QUEEN) return get_queen_attacks(square, occupancy);
    return get_king_attacks(square);
}

template<PieceType piece_type>
constexpr BITBOARD get_regular_piece_type_attacks(Square square, BITBOARD occupancy) {

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
