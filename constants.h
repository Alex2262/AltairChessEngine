
#ifndef ANTARESCHESSENGINE_CONSTANTS_H
#define ANTARESCHESSENGINE_CONSTANTS_H

#include <cstdint>
#include "types.h"

#define ENGINE_NAME                 "Altair"
#define ENGINE_VERSION              "4.0.0"
#define ENGINE_AUTHOR               "Alexander Tian"

#define N_TUNING_PARAMETERS         18
#define FAIL_HIGH_STATS_COUNT       5
#define ALPHA_RAISE_STATS_COUNT     5

#define BENCH_DEPTH                 14

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - "
#define KIWIPETE_FEN "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - "

#define NO_HASH_ENTRY       0
#define USE_HASH_MOVE       1
#define RETURN_HASH_SCORE   2

#define TIME_INF            86400000

constexpr SCORE_TYPE SCORE_INF = 1000000;
constexpr SCORE_TYPE NO_EVALUATION = 500000;
constexpr SCORE_TYPE MATE_SCORE = 100000;
constexpr SCORE_TYPE MATE_BOUND = 99000;

#define MAX_AB_DEPTH        256
#define TOTAL_MAX_DEPTH     512
#define MAX_TT_SIZE         2666666

#define HASH_FLAG_EXACT     0
#define HASH_FLAG_ALPHA     1
#define HASH_FLAG_BETA      2

#define STARTING_WINDOW     26
#define MINIMUM_ASP_DEPTH   6

constexpr size_t MAX_MOVES = 256;

enum NodeType {
    Exact_Node,
    Lower_Node,
    Upper_Node
};

constexpr char PIECE_MATCHER[12] = {'P', 'N', 'B', 'R', 'Q', 'K',
                                    'p', 'n', 'b', 'r', 'q', 'k'};

#endif //ANTARESCHESSENGINE_CONSTANTS_H