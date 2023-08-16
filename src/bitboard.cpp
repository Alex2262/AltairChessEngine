//
// Created by Alexander Tian on 6/23/23.
//

#include <stdexcept>
#include <iostream>
#include <bitset>
#include <algorithm>
#include "types.h"
#include "bitboard.h"

// Major contributions by Archishmaan Peyyety as a pull request to Alex2262/BitboardEngine

void print_bitboard(BITBOARD bitboard) {
    std::bitset<64> b(bitboard);
    std::string str_bitset = b.to_string();
    for (int i = 0; i < 64; i += 8) {
        std::string x = str_bitset.substr(i, 8);
        std::reverse(x.begin(), x.end());
        for (auto c : x) std::cout << c << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Compiler specific functions, taken from Stockfish https://github.com/official-stockfish/Stockfish
#if defined(__GNUC__) // GCC, Clang, ICC

[[nodiscard]] Square lsb(BITBOARD bitboard) {
    assert(bitboard);
    return static_cast<Square>(__builtin_ctzll(bitboard));
}

[[nodiscard]] Square msb(BITBOARD bitboard) {
    assert(bitboard);
    return static_cast<Square>(63 ^ __builtin_clzll(bitboard));
}

#elif defined(_MSC_VER) // MSVC

#ifdef _WIN64 // MSVC, WIN64
#include <intrin.h>
Square lsb(uint64_t bitboard)
{
    unsigned long idx;
    _BitScanForward64(&idx, bitboard);
    return (Square)idx;
}

Square msb(uint64_t bitboard)
{
    unsigned long idx;
    _BitScanReverse64(&idx, bitboard);
    return (Square)idx;
}

#else // MSVC, WIN32
#include <intrin.h>
Square lsb(BITBOARD bitboard)
{
    unsigned long idx;

    if (bitboard & 0xffffffff)
    {
        _BitScanForward(&idx, int32_t(bitboard));
        return Square(idx);
    }
    else
    {
        _BitScanForward(&idx, int32_t(bitboard >> 32));
        return Square(idx + 32);
    }
}

Square msb(BITBOARD bitboard)
{
    unsigned long idx;

    if (bitboard >> 32)
    {
        _BitScanReverse(&idx, int32_t(bitboard >> 32));
        return Square(idx + 32);
    }
    else
    {
        _BitScanReverse(&idx, int32_t(bitboard));
        return Square(idx);
    }
}

#endif

#else // Compiler is neither GCC nor MSVC compatible

#error "Compiler not supported."

#endif

[[nodiscard]] uint32_t popcount(BITBOARD bitboard) {
    return __builtin_popcountll(bitboard);
}

[[nodiscard]] Square poplsb(BITBOARD& bitboard) {
    Square s = lsb(bitboard);
    bitboard &= bitboard - 1; // compiler optimizes this to _blsr_u64
    return static_cast<Square>(s);
}
