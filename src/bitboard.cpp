
#include <stdexcept>
#include <bitset>
#include <algorithm>
#include "types.h"
#include "bitboard.h"

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
