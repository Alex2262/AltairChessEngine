
#ifndef ANTARESCHESSENGINE_CONSTANTS_H
#define ANTARESCHESSENGINE_CONSTANTS_H

#include <cstdint>

#define N_TUNING_PARAMETERS         16
#define FAIL_HIGH_STATS_COUNT       100
#define ALPHA_RAISE_STATS_COUNT     100

#define BENCH_DEPTH                 14

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - "
#define KIWIPETE_FEN "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - "

#define NO_PIECE_INDEX      -1

#define WHITE_COLOR         0
#define BLACK_COLOR         1

#define NO_HASH_ENTRY       0
#define USE_HASH_MOVE       1
#define RETURN_HASH_SCORE   2

#define TIME_INF            86400000
#define SCORE_INF           1000000
#define NO_EVALUATION       500000
#define MATE_SCORE          100000
#define MATE_BOUND          99000
#define NO_MOVE             0

#define MAX_AB_DEPTH        64
#define TOTAL_MAX_DEPTH     256
#define MAX_TT_SIZE         2666666

#define HASH_FLAG_EXACT     0
#define HASH_FLAG_ALPHA     1
#define HASH_FLAG_BETA      2

#define STARTING_WINDOW     26
#define MINIMUM_ASP_DEPTH   6

#define WHITE_PAWN          0
#define WHITE_KNIGHT        1
#define WHITE_BISHOP        2
#define WHITE_ROOK          3
#define WHITE_QUEEN         4
#define WHITE_KING          5

#define BLACK_PAWN          6
#define BLACK_KNIGHT        7
#define BLACK_BISHOP        8
#define BLACK_ROOK          9
#define BLACK_QUEEN         10
#define BLACK_KING          11

#define EMPTY               12
#define PADDING             13

#define MOVE_TYPE_NORMAL    0
#define MOVE_TYPE_EP        1
#define MOVE_TYPE_CASTLE    2
#define MOVE_TYPE_PROMOTION 3

#define A1      91
#define A8      21
#define H1      98
#define H8      28

#define E1      95
#define E8      25
#define C1      93
#define C8      23
#define G1      97
#define G8      27

enum NodeType {
    Exact_Node,
    Lower_Node,
    Upper_Node
};

typedef uint16_t PIECE_TYPE;
typedef int16_t SQUARE_TYPE;
typedef int16_t PLY_TYPE;
typedef int32_t SCORE_TYPE;
typedef uint32_t MOVE_TYPE;
typedef uint64_t HASH_TYPE;


constexpr int SQUARE_COLOR[64] = {
        0, 1, 0, 1, 0, 1, 0, 1,
        1, 0, 1, 0, 1, 0, 1, 0,
        0, 1, 0, 1, 0, 1, 0, 1,
        1, 0, 1, 0, 1, 0, 1, 0,
        0, 1, 0, 1, 0, 1, 0, 1,
        1, 0, 1, 0, 1, 0, 1, 0,
        0, 1, 0, 1, 0, 1, 0, 1,
        1, 0, 1, 0, 1, 0, 1, 0
};


constexpr SQUARE_TYPE STANDARD_TO_MAILBOX[64] = {
        21, 22, 23, 24, 25, 26, 27, 28,
        31, 32, 33, 34, 35, 36, 37, 38,
        41, 42, 43, 44, 45, 46, 47, 48,
        51, 52, 53, 54, 55, 56, 57, 58,
        61, 62, 63, 64, 65, 66, 67, 68,
        71, 72, 73, 74, 75, 76, 77, 78,
        81, 82, 83, 84, 85, 86, 87, 88,
        91, 92, 93, 94, 95, 96, 97, 98
};

constexpr SQUARE_TYPE MAILBOX_TO_STANDARD[120] = {
        99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
        99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
        99,  0,  1,  2,  3,  4,  5,  6,  7, 99,
        99,  8,  9, 10, 11, 12, 13, 14, 15, 99,
        99, 16, 17, 18, 19, 20, 21, 22, 23, 99,
        99, 24, 25, 26, 27, 28, 29, 30, 31, 99,
        99, 32, 33, 34, 35, 36, 37, 38, 39, 99,
        99, 40, 41, 42, 43, 44, 45, 46, 47, 99,
        99, 48, 49, 50, 51, 52, 53, 54, 55, 99,
        99, 56, 57, 58, 59, 60, 61, 62, 63, 99,
        99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
        99, 99, 99, 99, 99, 99, 99, 99, 99, 99
};

constexpr short WHITE_INCREMENTS[6][8] = {
        {-11,  -9, -10, -20,   0,   0,   0,   0},
        {-21, -19,  -8,  12,  21,  19,   8, -12},
        {-11,  11,   9,  -9,   0,   0,   0,   0},
        {-10,   1,  10,  -1,   0,   0,   0,   0},
        {-11,  11,   9,  -9, -10,   1,  10,  -1},
        {-11, -10,  -9,   1,  11,  10,   9,  -1}
};

constexpr short BLACK_INCREMENTS[6][8] = {
        { 11,   9,  10,  20,   0,   0,   0,   0},
        {-21, -19,  -8,  12,  21,  19,   8, -12},
        {-11,  11,   9,  -9,   0,   0,   0,   0},
        {-10,   1,  10,  -1,   0,   0,   0,   0},
        {-11,  11,   9,  -9, -10,   1,  10,  -1},
        {-11, -10,  -9,   1,  11,  10,   9,  -1}
};

constexpr short WHITE_ATK_INCREMENTS[6][8] = {
        {-11,  -9,   0,   0,   0,   0,   0,   0},
        {-21, -19,  -8,  12,  21,  19,   8, -12},
        {-11,  11,   9,  -9,   0,   0,   0,   0},
        {-10,   1,  10,  -1,   0,   0,   0,   0},
        {-11,  11,   9,  -9, -10,   1,  10,  -1},
        {-11, -10,  -9,   1,  11,  10,   9,  -1}
};

constexpr short BLACK_ATK_INCREMENTS[6][8] = {
        { 11,   9,   0,   0,   0,   0,   0,   0},
        {-21, -19,  -8,  12,  21,  19,   8, -12},
        {-11,  11,   9,  -9,   0,   0,   0,   0},
        {-10,   1,  10,  -1,   0,   0,   0,   0},
        {-11,  11,   9,  -9, -10,   1,  10,  -1},
        {-11, -10,  -9,   1,  11,  10,   9,  -1}
};

constexpr char PIECE_MATCHER[12] = {'P', 'N', 'B', 'R', 'Q', 'K', 'p', 'n', 'b', 'r', 'q', 'k'};
constexpr int GAME_PHASE_SCORES[6] = {0, 1, 1, 2, 4, 0};

constexpr int MVV_LVA_VALUES[6] = {  105, 398, 424, 617,1496,   0};

constexpr SCORE_TYPE PIECE_VALUES_MID[6] = { 105, 398, 424, 617,1496,   0};

constexpr SCORE_TYPE PIECE_VALUES_END[6] = { 133, 366, 360, 707,1360,   0};

constexpr SCORE_TYPE PAWN_PST_MID[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        173, 168, 112, 169, 105, 194,  49,  45,
        4,  19,  44,  61,  86,  88,  60,   8,
        -3,  12,  12,  28,  34,  38,  35,  -7,
        -9, -11,   3,   9,  16,  20,   7, -19,
        -22, -24, -15,  -9,   1,  -5,   7, -19,
        -13,  -7, -13,  -8,  -2,  27,  32,  -6,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE PAWN_PST_END[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        116, 110, 104,  33,  65,  61, 131, 135,
        90,  80,  37,  -8, -17,  23,  66, 101,
        47,  26,  10, -20, -12,   9,  28,  44,
        21,  16,  -7, -12, -12,  -6,  10,  18,
        14,  12,   2,  -2,   7,   3,   4,  14,
        27,  20,  24,   7,  25,   6,  16,  22,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE KNIGHT_PST_MID[64] = {
        -117, -57, -12,  54, 142,-104,  24, -54,
        59,  31,  76,  69,  73,  77,  20,  53,
        37,  76,  73,  88, 102, 147,  94, 103,
        94,  82,  66,  86,  53,  66,  53,  89,
        70,  57,  54,  51,  55,  41,  74,  54,
        49,  34,  24,  27,  30,  13,  37,  36,
        27,  33,  23,  27,  19,  26,  37,  55,
        -35,  35,   7,   8,  27,  14,  24,   4
};

constexpr SCORE_TYPE KNIGHT_PST_END[64] = {
        -4,  32,  60,  32,  30,  56,  -7, -61,
        27,  54,  39,  72,  58,  30,  42,  18,
        31,  43,  61,  67,  48,  38,  35,   3,
        42,  62,  70,  79,  85,  75,  70,  51,
        49,  50,  67,  82,  77,  69,  57,  53,
        1,  42,  41,  66,  58,  37,  27,  40,
        23,  46,  31,  68,  77,  36,  44,  24,
        25,  29,  50,  63,  48,  56,  45,  -2
};

constexpr SCORE_TYPE BISHOP_PST_MID[64] = {
        -25,  20, -98, -73, -68, -83,  12,  61,
        -12,  12,  12,  -6,   0,  45,   2, -22,
        37,  44,  59,  30,  54,  66,  70,  34,
        9,  32,  18,  61,  40,  46,  26,  19,
        20,  25,  33,  38,  55,  19,  26,  47,
        30,  43,  36,  33,  34,  42,  49,  56,
        44,  52,  51,  35,  36,  47,  75,  54,
        61,  44,  36,  30,  23,  34,  26,  45
};

constexpr SCORE_TYPE BISHOP_PST_END[64] = {
        41,  43,  72,  73,  74,  61,  45,  26,
        62,  47,  55,  51,  60,  45,  44,  56,
        45,  44,  34,  43,  32,  48,  50,  65,
        48,  47,  47,  36,  38,  37,  62,  66,
        34,  35,  37,  40,  26,  41,  33,  30,
        22,  28,  31,  35,  43,  28,  21,  24,
        9,   9,  21,  33,  36,  17,  38,   3,
        -17,  15,  53,  40,  38,  49,  44,   0
};

constexpr SCORE_TYPE ROOK_PST_MID[64] = {
        47,  44,   5,  10,  39,  43,  20, 102,
        29,  11,  36,  45,  39,  72,  14,  56,
        11,  36,  46,  45,  49,  89, 106,  62,
        21,  21,  39,  51,  27,  55,   5,  23,
        -8, -11,   0,   4,   6,  14,  21,   2,
        -9,  -2,  -9,  -5,  -7,   9,  16,  -3,
        -14,   7,  -8,  -2,   6,  18,  20, -50,
        16,  13,  17,  23,  19,  14,   1,  15
};

constexpr SCORE_TYPE ROOK_PST_END[64] = {
        63,  68,  78,  80,  71,  69,  73,  56,
        62,  72,  67,  68,  62,  44,  68,  54,
        58,  52,  50,  49,  45,  42,  36,  36,
        55,  51,  56,  47,  54,  47,  55,  55,
        57,  63,  59,  61,  55,  40,  44,  45,
        40,  44,  47,  51,  50,  33,  39,  33,
        36,  31,  48,  43,  41,  29,  26,  51,
        36,  39,  39,  31,  31,  45,  43,  20
};

constexpr SCORE_TYPE QUEEN_PST_MID[64] = {
        -27, -34, -10, -11,  32,  56,  66,  29,
        3, -52, -45, -71,-104,   1,   3,  20,
        6,   2, -11, -58, -48,  46,  51, -14,
        14,   4, -22, -41, -46, -23, -14,  -8,
        28,  24,   4, -12, -17,  -9,  10,   3,
        31,  57,  26,  11,   6,   7,  27,  13,
        40,  52,  51,  26,  22,  35,  25,  11,
        63,  43,  44,  39,  31,  14,  35,  -6
};

constexpr SCORE_TYPE QUEEN_PST_END[64] = {
        10,  60,  46,  23,  27,  17,   0,  20,
        14,  57,  72,  76, 103,  52,  46,  35,
        13,  21,  25,  85,  77,  35,  25,  92,
        11,  49,  58,  75,  86,  72,  78,  79,
        4,  41,  44,  79,  58,  56,  29,  14,
        -5, -55,  24,  16,  23,  32,   0,  11,
        -27, -43, -47,  13,   7, -42, -29, -14,
        -43, -37, -22,  65, -20, -35, -40, -38
};

constexpr SCORE_TYPE KING_PST_MID[64] = {
        -177, 229, 259,  68,-225, -88,  26, -21,
        203, 164, 165,  77,  40,  91, -60,-214,
        69, 190, 177, -10,  80, 137, 176, -56,
        27,  85, 109, -26, -76,  33,  29,-121,
        -24, 153,  63, -99, -79, -24,   4,-101,
        -22,  26,  10, -79, -50, -11,  20, -41,
        2,   4, -10,-142,-105, -56,   4,  -3,
        0,  23, -22,-155, -71,-106, -22, -30
};

constexpr SCORE_TYPE KING_PST_END[64] = {
        -103,-111, -96,  -8,  47,   6, -28, -72,
        -77,  -7,  -5,  55,  63,  13,  40,  16,
        1,   1,  13,  80,  63,  41,  27,  11,
        -15,  15,  22, 105, 105,  40,  31,  14,
        -34, -32,  14, 108, 104,  32,   8, -11,
        -37, -12,   7,  88,  77,  16, -10, -27,
        -54, -29,  -7,  75,  68,  12, -24, -54,
        -126, -75, -41,  37,   3, -13, -45,-101
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_MID[3][8] = {
        {   0,  -3,   0,  -7,   8,  14,  13,   0},
        {   0,   3,   3,  -5,  20,  48, 331,   0},
        {   0,   3,  56, -10,  42,  50, 695,   0}
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_END[3][8] = {
        {   0,  12,  22,  55,  90, 181, 241,   0},
        {   0,   3,  15,  44,  99, 216, 184,   0},
        {   0,   3,  17,  22,  66, 168, -69,   0}
};

#endif //ANTARESCHESSENGINE_CONSTANTS_H