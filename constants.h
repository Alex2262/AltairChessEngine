
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

constexpr int MVV_LVA_VALUES[6] = {  110, 426, 455, 647,1591,   0};

constexpr SCORE_TYPE MAX_MINOR_PIECE_VALUE_MID = 455;
constexpr SCORE_TYPE PIECE_VALUES_MID[6] = { 110, 426, 455, 647,1591,   0};

constexpr SCORE_TYPE PIECE_VALUES_END[6] = { 133, 374, 367, 701,1304,   0};

constexpr SCORE_TYPE PAWN_PST_MID[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        148, 157,  91, 161, 100, 142,  19,   8,
        3,  23,  51,  67,  96,  88,  59,   9,
        -2,  19,  17,  34,  39,  39,  42,  -4,
        -6,  -5,   7,  14,  20,  24,   9, -18,
        -19, -21, -10,  -7,   4,  -5,  11, -20,
        -11,  -3, -11,  -8,   0,  31,  36,  -6,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE PAWN_PST_END[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        128, 119, 108,  40,  58,  67, 122, 152,
        96,  87,  43,  -9, -19,  29,  71, 105,
        46,  26,  12, -18, -10,  12,  29,  44,
        20,  15,  -7, -11, -12,  -6,  10,  16,
        12,  11,   0,   0,   6,   2,   3,  12,
        27,  20,  24,   7,  22,   6,  14,  22,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE KNIGHT_PST_MID[64] = {
        -123, -77, -18,  54, 153,-113,  18, -60,
        44,  27,  69,  63,  60,  67,  10,  38,
        34,  72,  61,  79,  97, 147,  88,  99,
        93,  74,  56,  77,  46,  57,  51,  85,
        66,  49,  47,  42,  48,  34,  70,  51,
        39,  25,  15,  18,  23,   5,  28,  28,
        14,  24,  10,  17,  11,  17,  32,  51,
        -63,  26,  -4,  -1,  22,   5,  17,  -5
};

constexpr SCORE_TYPE KNIGHT_PST_END[64] = {
        -17,  20,  47,  14,   9,  39, -23, -75,
        12,  36,  23,  57,  46,  15,  26,   5,
        13,  27,  48,  49,  28,  19,  18, -14,
        26,  46,  54,  62,  70,  58,  50,  33,
        29,  30,  47,  65,  59,  51,  39,  39,
        -8,  31,  24,  51,  42,  20,  11,  29,
        11,  28,  23,  52,  60,  26,  35,   7,
        37,  15,  32,  52,  31,  44,  25, -17
};

constexpr SCORE_TYPE BISHOP_PST_MID[64] = {
        -22,  22, -97, -54, -37, -99,  11,  36,
        -14,   5,  13, -14,   4,  47,  -6, -34,
        36,  38,  51,  24,  52,  57,  73,  35,
        2,  26,   6,  57,  35,  47,  22,  18,
        14,  16,  28,  35,  50,  13,  19,  45,
        26,  38,  29,  26,  27,  34,  42,  50,
        40,  45,  37,  26,  28,  38,  71,  43,
        51,  37,  27,  22,  12,  27,  23,  36
};

constexpr SCORE_TYPE BISHOP_PST_END[64] = {
        28,  29,  54,  51,  52,  50,  27,  20,
        49,  36,  43,  40,  52,  30,  37,  45,
        34,  35,  26,  35,  25,  41,  39,  51,
        39,  39,  42,  29,  32,  29,  54,  51,
        23,  30,  31,  32,  19,  33,  26,  17,
        13,  24,  27,  30,  37,  25,  15,  17,
        11,   8,  21,  34,  32,  13,  30,   2,
        -5,  20,  49,  36,  38,  45,  38,   2
};

constexpr SCORE_TYPE ROOK_PST_MID[64] = {
        49,  55,   9,  28,  55,  44,  53, 108,
        41,  20,  47,  54,  50,  79,  25,  59,
        21,  41,  48,  41,  58,  86, 122,  61,
        32,  25,  42,  54,  26,  53,   1,  25,
        2,  -1,   3,   9,  13,  23,  31,   3,
        2,   5,   0,   5,  -3,  16,  24,   6,
        -3,  17,   3,   5,  15,  32,  30, -42,
        27,  22,  24,  30,  27,  23,   5,  23
};

constexpr SCORE_TYPE ROOK_PST_END[64] = {
        76,  77,  90,  87,  79,  80,  73,  64,
        70,  83,  76,  79,  69,  58,  75,  64,
        63,  59,  58,  60,  51,  51,  40,  45,
        56,  56,  64,  57,  63,  61,  64,  61,
        61,  67,  67,  70,  63,  48,  51,  53,
        45,  53,  54,  58,  59,  45,  42,  38,
        45,  38,  58,  56,  52,  40,  35,  59,
        47,  50,  52,  46,  43,  57,  54,  33
};

constexpr SCORE_TYPE QUEEN_PST_MID[64] = {
        -8, -27,  17,  -3,  51,  73,  86,  42,
        22, -28, -16, -37, -80,  17,  27,  43,
        33,  23,  11, -40, -24,  78,  72,   9,
        33,  24,   7, -15, -21,  -2,  -3,  11,
        51,  45,  32,  12,  11,  17,  29,  19,
        52,  84,  58,  37,  33,  34,  51,  34,
        54,  73,  76,  51,  49,  57,  49,  29,
        82,  61,  62,  60,  48,  33,  45,   7
};

constexpr SCORE_TYPE QUEEN_PST_END[64] = {
        32,  95,  64,  54,  58,  38,  21,  52,
        40,  73,  92,  95, 128,  78,  70,  54,
        31,  43,  46, 112, 101,  56,  48, 110,
        41,  78,  76,  99, 107,  95, 113,  98,
        20,  65,  69, 105,  72,  77,  54,  46,
        18, -36,  37,  33,  41,  51,  26,  48,
        8, -18, -22,  32,  26, -12,  -8,  16,
        -16, -12,   2,  77,   9, -10,  -4, -14
};

constexpr SCORE_TYPE KING_PST_MID[64] = {
        -163, 211, 287,  62,-201, -84,  81, -65,
        184, 184, 174,  76,  25, 110, -37,-196,
        71, 206, 206,  -2,  68, 155, 189, -41,
        47, 122, 123, -30, -71,  41,  21,-137,
        -38, 150,  82, -99, -88, -21, -11,-110,
        -16,  38,  31, -80, -56, -12,  15, -39,
        8,  13,   4,-144,-105, -57,   6,  -4,
        6,  28, -17,-161, -73,-108, -23, -36
};

constexpr SCORE_TYPE KING_PST_END[64] = {
        -96, -98, -92,  13,  62,  16, -20, -38,
        -64,  -9,  -7,  72,  81,  19,  43,  21,
        -1,  -5,   6,  87,  77,  37,  32,  16,
        -22,   6,  16, 110, 106,  38,  32,  20,
        -30, -33,   8, 112, 109,  34,  16,  -6,
        -38, -13,   2,  95,  86,  21,  -1, -21,
        -49, -27,  -6,  85,  77,  20, -15, -44,
        -110, -69, -34,  54,  18,  -4, -36, -86
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_MID[3][8] = {
        {   0,  -2,  -3,  -9,  10,  22,  48,   0},
        {   0,   3,   2,  -8,  21,  74, 383,   0},
        {   0,   3,  36,  -9,  39,  87, 420,   0}
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_END[3][8] = {
        {   0,  14,  26,  58,  89, 164, 204,   0},
        {   0,   3,  18,  48,  99, 184, 136,   0},
        {   0,   3,  27,  26,  69, 130,  49,   0}
};

constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_MID =  -10;
constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_END =    0;

constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -22;
constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_END =  -15;

constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_MID =   -9;
constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_END =  -38;

constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_MID =   -6;
constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_END =    2;

constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -17;
constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_END =  -10;

constexpr SCORE_TYPE PHALANX_PAWN_BONUS_MID[8] = {   0,   3,  23,  26,  44,  66,  -9,   0};

constexpr SCORE_TYPE PHALANX_PAWN_BONUS_END[8] = {   0,  -2,   6,  17,  76, 167, 460,   0};

constexpr SCORE_TYPE PIECE_SUPPORT_MID[6][6] = {
        {  22,   6,   9,   5,  -6, -81},
        {  12,  19,  17,  21,  25,  17},
        {   4,  19,  19,  11,  17,   9},
        {   5,  18,  12,  13,  14,  13},
        {  -1,   8,   5,   7,  13,   3},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE PIECE_SUPPORT_END[6][6] = {
        {  15,  27,  33,   8,  -1,  30},
        {   9,  15,   8,   6, -10,   1},
        {   2,  17,  33,  12,  17,   9},
        {   3,   4,   9,  15,  36,  -6},
        {   8,   6,  -8,  -1,-537, -14},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE PIECE_THREAT_MID[6][6] = {
        {  10,  88,  78, 121,  79, 256},
        {  12,  20,  55,  81,  70, 154},
        {   9,  46,  20,  62,  75,  95},
        {  -8,   9,  15,  10,  80, 169},
        {  -8,   4,   1,  -6,  10,  92},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE PIECE_THREAT_END[6][6] = {
        {  10,  31,  73,   0,  36,  20},
        {  26,  20,  57,  27,  19,  32},
        {  26,  61,  20,  42,  83,  87},
        {  29,  36,  43,  10,  50,  33},
        {  16,  19,  43,  40,  10, 118},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE BLOCKER_VALUES_MID[6] = {   0,  -8,   4,  18,  14, -75};

constexpr SCORE_TYPE BLOCKER_VALUES_END[6] = {   0, -63, -91, -32,  -8, -94};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_MID[6] = {   0,   6,   3,  14,  24,   0};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_END[6] = {   0, -28, -27, -19, -17, -38};

constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_MID =   22;
constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_END =    5;

constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_MID =   48;
constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_END =    1;

constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_MID =    3;
constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_END =   32;

constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_MID =   -6;
constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_END =   36;

constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_MID =  -24;
constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_END =    1;

constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_MID =  -15;
constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_END =  -11;

constexpr SCORE_TYPE BISHOP_PAIR_BONUS_MID =   31;
constexpr SCORE_TYPE BISHOP_PAIR_BONUS_END =   76;

constexpr SCORE_TYPE TEMPO_BONUS_MID =   30;
constexpr SCORE_TYPE TEMPO_BONUS_END =   27;

constexpr double MOBILITY_COEFFICIENTS_MID[6] = {      0,      6.41,      3.5,      2.06,      0.788,      0};

constexpr double MOBILITY_COEFFICIENTS_END[6] = {      0,      1.8,      2.74,      1.21,      0.37,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -5.89,      0,      0,      0,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,      0.811,      0,      0,      0,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -0.78,      -0.102,     -4.98,    -11,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,     -1.33,      1.51,      4.94,      6.59,      0};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_MID[3][8] = {
        {   3,   3, -37,   0,   0, -12, -15,   6},
        {   4, -41, -39,   0,   0, -23, -20,   2},
        { -41, -71, -72,   0,   0, -36, -57, -27}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_END[3][8] = {
        {  13,   4,  21,   0,   0,  -4,  11,  22},
        {  32,  31,  23,   0,   0, -16,  11,  27},
        {  34,  23,  18,   0,   0,  -7,  28,  41}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_MID[3][8] = {
        {   1, -27,  -5,   0,   0,  -4, -17,  10},
        {  -4, -11, -38,   0,   0, -35,   1, -17},
        {  -7, -76,-167,   0,   0,-102, -59, -47}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_END[3][8] = {
        { -17,  -2,  -9,   0,   0,  -7,  -7, -18},
        {  36,  30,  24,   0,   0,  27,  25,  26},
        {  77, 102,  81,   0,   0,  58,  89,  96}
};

constexpr SCORE_TYPE KING_RING_ATTACKS_MID[2][6] = {
        {   0,  13,  18,  28,  19,   0},
        {   0,   9,   2,   5,   7,   0}
};

constexpr SCORE_TYPE KING_RING_ATTACKS_END[2][6] = {
        {   0, -12,  -3,  -7,  12,   0},
        {   0,   1,   0,   1,  14,   0}
};

#endif //ANTARESCHESSENGINE_CONSTANTS_H