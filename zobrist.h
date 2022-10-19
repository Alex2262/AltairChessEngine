//
// Created by Alex Tian on 10/4/2022.
//

#ifndef ANTARESCHESSENGINE_ZOBRIST_H
#define ANTARESCHESSENGINE_ZOBRIST_H

#include <random>
#include "constants.h"


inline uint64_t rand_uint64() {
    uint64_t r = 0;
    for (int i=0; i<64; i++) {
        r = r*2 + rand()%2;
    }
    return r;
}

class ZobristKeysClass {

public:

    HASH_TYPE piece_hash_keys[12][64] {};
    HASH_TYPE ep_hash_keys[64] {};
    HASH_TYPE castle_hash_keys[16] {};
    HASH_TYPE side_hash_key = 0;

    ZobristKeysClass() {
        for (auto & piece_hash_key : piece_hash_keys) {
            for (uint64_t& j : piece_hash_key) {
                j = rand_uint64();
            }
        }

        for (uint64_t& ep_hash_key : ep_hash_keys) {
            ep_hash_key = rand_uint64();
        }

        for (uint64_t& castle_hash_key : castle_hash_keys) {
            castle_hash_key = rand_uint64();
        }

        side_hash_key = rand_uint64();
    }
};


ZobristKeysClass ZobristHashKeys = ZobristKeysClass();

#endif //ANTARESCHESSENGINE_ZOBRIST_H
