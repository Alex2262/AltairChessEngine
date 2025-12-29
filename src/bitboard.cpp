
#include <stdexcept>
#include <iostream>
#include <bitset>
#include <algorithm>
#include "types.h"
#include "bitboard.h"

void print_bitboard(Bitboard bitboard) {
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

[[nodiscard]] Square lsb(Bitboard bitboard) {
    assert(bitboard);
    return static_cast<Square>(__builtin_ctzll(bitboard));
}

[[nodiscard]] Square msb(Bitboard bitboard) {
    assert(bitboard);
    return static_cast<Square>(63 ^ __builtin_clzll(bitboard));
}

#elif defined(_MSC_VER) // MSVC

#ifdef _WIN64 // MSVC, WIN64
#include <intrin.h>
Square lsb(uint64_t Bitboard)
{
    unsigned long idx;
    _BitScanForward64(&idx, Bitboard);
    return (Square)idx;
}

Square msb(uint64_t Bitboard)
{
    unsigned long idx;
    _BitScanReverse64(&idx, Bitboard);
    return (Square)idx;
}

#else // MSVC, WIN32
#include <intrin.h>
Square lsb(Bitboard Bitboard)
{
    unsigned long idx;

    if (Bitboard & 0xffffffff)
    {
        _BitScanForward(&idx, int32_t(Bitboard));
        return Square(idx);
    }
    else
    {
        _BitScanForward(&idx, int32_t(Bitboard >> 32));
        return Square(idx + 32);
    }
}

Square msb(Bitboard Bitboard)
{
    unsigned long idx;

    if (Bitboard >> 32)
    {
        _BitScanReverse(&idx, int32_t(Bitboard >> 32));
        return Square(idx + 32);
    }
    else
    {
        _BitScanReverse(&idx, int32_t(Bitboard));
        return Square(idx);
    }
}

#endif

#else // Compiler is neither GCC nor MSVC compatible

#error "Compiler not supported."

#endif

[[nodiscard]] uint32_t popcount(Bitboard bitboard) {
    return __builtin_popcountll(bitboard);
}

[[nodiscard]] Square poplsb(Bitboard& bitboard) {
    Square s = lsb(bitboard);
    bitboard &= bitboard - 1; // compiler optimizes this to _blsr_u64
    return static_cast<Square>(s);
}
