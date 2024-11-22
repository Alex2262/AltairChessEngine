

#ifndef ALTAIR_ATTACKS_H
#define ALTAIR_ATTACKS_H

#include <array>
#include "bitboard.h"

static constexpr std::array<BITBOARD, N_SQUARES> WHITE_PAWN_ATTACKS = {
        0x200, 0x500, 0xa00, 0x1400,
        0x2800, 0x5000, 0xa000, 0x4000,
        0x20000, 0x50000, 0xa0000, 0x140000,
        0x280000, 0x500000, 0xa00000, 0x400000,
        0x2000000, 0x5000000, 0xa000000, 0x14000000,
        0x28000000, 0x50000000, 0xa0000000, 0x40000000,
        0x200000000, 0x500000000, 0xa00000000, 0x1400000000,
        0x2800000000, 0x5000000000, 0xa000000000, 0x4000000000,
        0x20000000000, 0x50000000000, 0xa0000000000, 0x140000000000,
        0x280000000000, 0x500000000000, 0xa00000000000, 0x400000000000,
        0x2000000000000, 0x5000000000000, 0xa000000000000, 0x14000000000000,
        0x28000000000000, 0x50000000000000, 0xa0000000000000, 0x40000000000000,
        0x200000000000000, 0x500000000000000, 0xa00000000000000, 0x1400000000000000,
        0x2800000000000000, 0x5000000000000000, 0xa000000000000000, 0x4000000000000000,
        0x0, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0,
};

static constexpr std::array<BITBOARD, N_SQUARES> BLACK_PAWN_ATTACKS = {
        0x0, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0,
        0x2, 0x5, 0xa, 0x14,
        0x28, 0x50, 0xa0, 0x40,
        0x200, 0x500, 0xa00, 0x1400,
        0x2800, 0x5000, 0xa000, 0x4000,
        0x20000, 0x50000, 0xa0000, 0x140000,
        0x280000, 0x500000, 0xa00000, 0x400000,
        0x2000000, 0x5000000, 0xa000000, 0x14000000,
        0x28000000, 0x50000000, 0xa0000000, 0x40000000,
        0x200000000, 0x500000000, 0xa00000000, 0x1400000000,
        0x2800000000, 0x5000000000, 0xa000000000, 0x4000000000,
        0x20000000000, 0x50000000000, 0xa0000000000, 0x140000000000,
        0x280000000000, 0x500000000000, 0xa00000000000, 0x400000000000,
        0x2000000000000, 0x5000000000000, 0xa000000000000, 0x14000000000000,
        0x28000000000000, 0x50000000000000, 0xa0000000000000, 0x40000000000000,
};

static constexpr std::array<BITBOARD, N_SQUARES> KNIGHT_ATTACKS = {
        0x20400, 0x50800, 0xa1100, 0x142200,
        0x284400, 0x508800, 0xa01000, 0x402000,
        0x2040004, 0x5080008, 0xa110011, 0x14220022,
        0x28440044, 0x50880088, 0xa0100010, 0x40200020,
        0x204000402, 0x508000805, 0xa1100110a, 0x1422002214,
        0x2844004428, 0x5088008850, 0xa0100010a0, 0x4020002040,
        0x20400040200, 0x50800080500, 0xa1100110a00, 0x142200221400,
        0x284400442800, 0x508800885000, 0xa0100010a000, 0x402000204000,
        0x2040004020000, 0x5080008050000, 0xa1100110a0000, 0x14220022140000,
        0x28440044280000, 0x50880088500000, 0xa0100010a00000, 0x40200020400000,
        0x204000402000000, 0x508000805000000, 0xa1100110a000000, 0x1422002214000000,
        0x2844004428000000, 0x5088008850000000, 0xa0100010a0000000, 0x4020002040000000,
        0x400040200000000, 0x800080500000000, 0x1100110a00000000, 0x2200221400000000,
        0x4400442800000000, 0x8800885000000000, 0x100010a000000000, 0x2000204000000000,
        0x4020000000000, 0x8050000000000, 0x110a0000000000, 0x22140000000000,
        0x44280000000000, 0x0088500000000000, 0x0010a00000000000, 0x20400000000000
};

static constexpr std::array<BITBOARD, N_SQUARES> KING_ATTACKS = {
        0x302, 0x705, 0xe0a, 0x1c14,
        0x3828, 0x7050, 0xe0a0, 0xc040,
        0x30203, 0x70507, 0xe0a0e, 0x1c141c,
        0x382838, 0x705070, 0xe0a0e0, 0xc040c0,
        0x3020300, 0x7050700, 0xe0a0e00, 0x1c141c00,
        0x38283800, 0x70507000, 0xe0a0e000, 0xc040c000,
        0x302030000, 0x705070000, 0xe0a0e0000, 0x1c141c0000,
        0x3828380000, 0x7050700000, 0xe0a0e00000, 0xc040c00000,
        0x30203000000, 0x70507000000, 0xe0a0e000000, 0x1c141c000000,
        0x382838000000, 0x705070000000, 0xe0a0e0000000, 0xc040c0000000,
        0x3020300000000, 0x7050700000000, 0xe0a0e00000000, 0x1c141c00000000,
        0x38283800000000, 0x70507000000000, 0xe0a0e000000000, 0xc040c000000000,
        0x302030000000000, 0x705070000000000, 0xe0a0e0000000000, 0x1c141c0000000000,
        0x3828380000000000, 0x7050700000000000, 0xe0a0e00000000000, 0xc040c00000000000,
        0x203000000000000, 0x507000000000000, 0xa0e000000000000, 0x141c000000000000,
        0x2838000000000000, 0x5070000000000000, 0xa0e0000000000000, 0x40c0000000000000,
};


// Get the edge opposite of a direction for calculating
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

constexpr BITBOARD get_pawn_attacks(Square square, Color color) {
    if (color == WHITE) return WHITE_PAWN_ATTACKS[square];
    return BLACK_PAWN_ATTACKS[square];
}

constexpr BITBOARD get_piece_attacks(Piece piece, Square square, BITBOARD occupancy) {
    auto piece_type = static_cast<PieceType>(piece % COLOR_OFFSET);
    if (piece == WHITE_PAWN) return WHITE_PAWN_ATTACKS[square];
    else if (piece == BLACK_PAWN) return BLACK_PAWN_ATTACKS[square];
    else if (piece_type == KNIGHT) return KNIGHT_ATTACKS[square];
    else if (piece_type == BISHOP) return get_bishop_attacks(square, occupancy);
    else if (piece_type == ROOK) return get_rook_attacks(square, occupancy);
    else if (piece_type == QUEEN) return get_queen_attacks(square, occupancy);
    else return KING_ATTACKS[square];
}

constexpr BITBOARD get_regular_piece_type_attacks_nt(PieceType piece_type, Square square, BITBOARD occupancy) {

    if (piece_type == KNIGHT) return KNIGHT_ATTACKS[square];
    else if (piece_type == BISHOP) return get_bishop_attacks(square, occupancy);
    else if (piece_type == ROOK) return get_rook_attacks(square, occupancy);
    else if (piece_type == QUEEN) return get_queen_attacks(square, occupancy);
    return KING_ATTACKS[square];
}

template<PieceType piece_type>
constexpr BITBOARD get_regular_piece_type_attacks(Square square, BITBOARD occupancy) {

    if constexpr (piece_type == KNIGHT) return KNIGHT_ATTACKS[square];
    else if constexpr (piece_type == BISHOP) return get_bishop_attacks(square, occupancy);
    else if constexpr (piece_type == ROOK) return get_rook_attacks(square, occupancy);
    else if constexpr (piece_type == QUEEN) return get_queen_attacks(square, occupancy);
    return KING_ATTACKS[square];
}


consteval std::array<std::array<BITBOARD, 64>, 2> generate_passed_pawn_masks() {
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
