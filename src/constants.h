
#pragma once

#include <cstdint>
#include <string>
#include "types.h"

#define ENGINE_NAME                 "Altair"
#define ENGINE_VERSION              "7.2.1"
#define ENGINE_AUTHOR               "Alexander Tian"

#define FAIL_HIGH_STATS_COUNT       5
#define ALPHA_RAISE_STATS_COUNT     5

#define BENCH_DEPTH                 14

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - "
#define KIWIPETE_FEN "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - "

#define NO_HASH_ENTRY       0
#define USE_HASH_MOVE       1
#define RETURN_HASH_SCORE   2

#define TIME_INF            86400000

constexpr Score SCORE_INF = 1000000;
constexpr Score NO_EVALUATION = 500000;
constexpr Score SCORE_NONE = 150000;
constexpr Score MATE_SCORE = 100000;
constexpr Score MATE_BOUND = 99000;

#define MAX_AB_DEPTH        256
#define MAX_QS_DEPTH        64
#define TOTAL_MAX_DEPTH     (MAX_AB_DEPTH + MAX_QS_DEPTH)
#define MAX_GAME_LENGTH     1536
#define DEFAULT_TT_SIZE     16

#define HASH_FLAG_NONE      0
#define HASH_FLAG_UPPER     1
#define HASH_FLAG_LOWER     2
#define HASH_FLAG_EXACT     3

#define MINIMUM_ASP_DEPTH   6

constexpr int LAST_MOVE_COUNTS = 3;
constexpr int LAST_MOVE_PLIES[LAST_MOVE_COUNTS] = {1, 2, 4};

constexpr size_t MAX_MOVES = 256;
constexpr size_t MAX_NOISY = 128;

enum NodeType {
    Exact_Node,
    Lower_Node,
    Upper_Node
};

constexpr char PIECE_MATCHER[12] = {'P', 'N', 'B', 'R', 'Q', 'K',
                                    'p', 'n', 'b', 'r', 'q', 'k'};

const std::string RESET  = "\033[0m";
const std::string RED    = "\033[31m";
const std::string YELLOW = "\033[33m";
const std::string GREEN  = "\033[32m";
const std::string CYAN   = "\033[36m";

constexpr bool ACTIVATE   = true;
constexpr bool DEACTIVATE = false;

constexpr bool USE_NNUE = true;
constexpr bool NO_NNUE  = false;
