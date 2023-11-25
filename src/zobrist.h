
#ifndef ALTAIR_ZOBRIST_H
#define ALTAIR_ZOBRIST_H

#include "random.h"
#include "constants.h"
#include "types.h"

class ZobristKeysClass {

public:

    PRNG prng = PRNG(31415926); // 695848653836736222

    HASH_TYPE piece_hash_keys[12][64] {};
    HASH_TYPE ep_hash_keys[64] {};
    HASH_TYPE castle_hash_keys[16] {};
    HASH_TYPE side_hash_key = 0;

    ZobristKeysClass() {
        for (auto & piece_hash_key : piece_hash_keys) {
            for (uint64_t& j : piece_hash_key) {
                j = prng.rand64();
            }
        }

        for (uint64_t& ep_hash_key : ep_hash_keys) {
            ep_hash_key = prng.rand64();
        }

        for (uint64_t& castle_hash_key : castle_hash_keys) {
            castle_hash_key = prng.rand64();
        }

        side_hash_key = prng.rand64();
    }
};


ZobristKeysClass ZobristHashKeys = ZobristKeysClass();

#endif //ALTAIR_ZOBRIST_H
