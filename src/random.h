
#pragma once

//A pseudorandom number generator inspired from Stockfish
class PRNG {

public:
    uint64_t s;

    uint64_t rand64() {
        s ^= s >> 12, s ^= s << 25, s ^= s >> 27;
        return s * 2685821657736338717LL;
    }

    PRNG(uint64_t seed) : s(seed) {}
};
