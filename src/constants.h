
#pragma once

#include <cstdint>
#include <string>
#include "types.h"

inline constexpr std::string_view ENGINE_NAME    = "Altair";
inline constexpr std::string_view ENGINE_VERSION = "7.2.1";
inline constexpr std::string_view ENGINE_AUTHOR  = "Alexander Tian";

inline constexpr std::string_view START_FEN    = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - ";
inline constexpr std::string_view KIWIPETE_FEN = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ";

inline constexpr int FAIL_HIGH_STATS_COUNT = 10;
inline constexpr int ALPHA_RAISE_STATS_COUNT = 10;

inline constexpr Ply BENCH_DEPTH = 14;

inline constexpr short NO_HASH_ENTRY     = 0;
inline constexpr short USE_HASH_MOVE     = 1;
inline constexpr short RETURN_HASH_SCORE = 2;

inline constexpr uint64_t TIME_INF = 86400000;

inline constexpr Score SCORE_INF     = 1000000;
inline constexpr Score NO_EVALUATION = 500000;
inline constexpr Score SCORE_NONE    = 150000;
inline constexpr Score MATE_SCORE    = 100000;
inline constexpr Score MATE_BOUND    = 99000;

inline constexpr Ply MAX_AB_DEPTH    = 256;
inline constexpr Ply MAX_QS_DEPTH    = 64;
inline constexpr Ply TOTAL_MAX_DEPTH = (MAX_AB_DEPTH + MAX_QS_DEPTH);
inline constexpr Ply MAX_GAME_LENGTH = 1536;

inline constexpr int DEFAULT_TT_SIZE = 16;

inline constexpr int HASH_FLAG_NONE  = 0;
inline constexpr int HASH_FLAG_UPPER = 1;
inline constexpr int HASH_FLAG_LOWER = 2;
inline constexpr int HASH_FLAG_EXACT = 3;

inline constexpr Ply MINIMUM_ASP_DEPTH = 6;

inline constexpr int LAST_MOVE_COUNTS = 3;
inline constexpr int LAST_MOVE_PLIES[LAST_MOVE_COUNTS] = {1, 2, 4};

inline constexpr size_t MAX_MOVES = 256;
inline constexpr size_t MAX_NOISY = 128;

inline constexpr std::string_view RESET  = "\033[0m";
inline constexpr std::string_view RED    = "\033[31m";
inline constexpr std::string_view YELLOW = "\033[33m";
inline constexpr std::string_view GREEN  = "\033[32m";
inline constexpr std::string_view CYAN   = "\033[36m";

inline constexpr bool ACTIVATE   = true;
inline constexpr bool DEACTIVATE = false;

inline constexpr char PIECE_MATCHER[12] = {'P', 'N', 'B', 'R', 'Q', 'K',
                                           'p', 'n', 'b', 'r', 'q', 'k'};

