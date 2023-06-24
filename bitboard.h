//
// Created by Alexander Tian on 6/23/23.
//

#ifndef ALTAIRCHESSENGINE_BITBOARD_H
#define ALTAIRCHESSENGINE_BITBOARD_H

#include <cstdint>
#include <cassert>
#include "types.h"

using BITBOARD = uint64_t;

constexpr BITBOARD MASK_FILE[8] = {
        0x101010101010101, 0x202020202020202, 0x404040404040404, 0x808080808080808,
        0x1010101010101010, 0x2020202020202020, 0x4040404040404040, 0x8080808080808080,
};


void print_bitboard(BITBOARD bitboard);

[[nodiscard]] inline BITBOARD from_square(Square square) {
    return 1ULL << square;
}

[[nodiscard]] Square lsb(BITBOARD bitboard);
[[nodiscard]] Square msb(BITBOARD bitboard);

[[nodiscard]] uint32_t popcount(BITBOARD bitboard);
[[nodiscard]] Square poplsb(BITBOARD& bitboard);

template<Direction D> [[nodiscard]] BITBOARD shift(BITBOARD b);

#endif //ALTAIRCHESSENGINE_BITBOARD_H
