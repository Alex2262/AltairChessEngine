
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

constexpr int MVV_LVA_VALUES[6] = {  104, 397, 424, 618,1498,   0};

constexpr SCORE_TYPE MAX_MINOR_PIECE_VALUE_MID = 424;
constexpr SCORE_TYPE PIECE_VALUES_MID[6] = { 104, 397, 424, 618,1498,   0};

constexpr SCORE_TYPE PIECE_VALUES_END[6] = { 129, 366, 361, 708,1360,   0};

constexpr SCORE_TYPE PAWN_PST_MID[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        167, 161, 106, 163,  99, 187,  40,  40,
        5,  19,  45,  62,  87,  89,  61,   9,
        -3,  12,  12,  30,  35,  39,  34,  -7,
        -8, -11,   5,  11,  18,  22,   7, -17,
        -20, -23, -13,  -7,   3,  -4,   7, -18,
        -13,  -8, -14,  -9,  -2,  26,  31,  -7,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE PAWN_PST_END[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        116, 110, 105,  34,  65,  62, 131, 135,
        89,  80,  37,  -8, -17,  23,  67, 101,
        44,  24,   8, -22, -15,   7,  26,  42,
        21,  15,  -7, -12, -13,  -6,   9,  18,
        13,  12,   2,  -2,   7,   3,   4,  14,
        26,  19,  23,   6,  24,   5,  15,  20,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE KNIGHT_PST_MID[64] = {
        -114, -54, -13,  53, 139,-105,  27, -54,
        60,  30,  74,  69,  72,  75,  19,  53,
        37,  65,  68,  86,  98, 134,  84, 102,
        93,  79,  62,  78,  49,  63,  51,  88,
        70,  56,  52,  50,  54,  39,  74,  54,
        50,  33,  23,  26,  29,  13,  37,  37,
        28,  34,  22,  27,  19,  25,  38,  56,
        -32,  36,   7,   8,  27,  14,  25,   4
};

constexpr SCORE_TYPE KNIGHT_PST_END[64] = {
        -3,  33,  61,  33,  31,  57,  -8, -60,
        28,  55,  39,  72,  59,  30,  42,  19,
        31,  43,  61,  67,  48,  36,  33,   2,
        42,  58,  69,  80,  84,  73,  66,  51,
        49,  49,  66,  82,  77,  69,  57,  54,
        2,  42,  42,  66,  58,  37,  28,  41,
        24,  47,  31,  67,  76,  36,  45,  25,
        26,  29,  50,  64,  48,  56,  45,   0
};

constexpr SCORE_TYPE BISHOP_PST_MID[64] = {
        -25,  20, -99, -72, -67, -83,  12,  59,
        -12,  12,  12,  -7,   0,  45,   2, -23,
        37,  39,  58,  30,  53,  60,  66,  35,
        10,  31,  16,  56,  38,  46,  26,  19,
        21,  26,  33,  39,  55,  20,  27,  49,
        31,  44,  38,  34,  36,  43,  51,  56,
        44,  52,  52,  36,  37,  48,  76,  54,
        62,  44,  37,  32,  26,  35,  26,  45
};

constexpr SCORE_TYPE BISHOP_PST_END[64] = {
        42,  43,  73,  73,  75,  61,  45,  26,
        62,  48,  55,  52,  60,  45,  45,  56,
        45,  45,  34,  43,  33,  49,  51,  66,
        49,  47,  49,  38,  39,  37,  61,  67,
        34,  36,  38,  40,  27,  42,  33,  29,
        23,  28,  32,  35,  44,  28,  21,  24,
        10,   9,  21,  33,  36,  18,  38,   3,
        -17,  16,  54,  40,  37,  50,  44,   0
};

constexpr SCORE_TYPE ROOK_PST_MID[64] = {
        47,  45,   6,  11,  40,  44,  19, 103,
        30,  11,  35,  44,  38,  72,  14,  56,
        11,  35,  45,  45,  49,  89, 106,  61,
        21,  20,  39,  51,  26,  54,   5,  22,
        -8, -11,   0,   4,   5,  14,  21,   2,
        -8,  -2,  -9,  -5,  -7,   9,  15,  -3,
        -14,   8,  -8,  -2,   6,  18,  21, -50,
        16,  14,  18,  23,  19,  14,   1,  15
};

constexpr SCORE_TYPE ROOK_PST_END[64] = {
        63,  68,  78,  80,  71,  69,  74,  56,
        62,  72,  67,  68,  63,  44,  68,  54,
        58,  52,  50,  49,  45,  42,  36,  36,
        55,  51,  56,  47,  54,  48,  56,  55,
        57,  63,  59,  62,  55,  40,  44,  45,
        40,  44,  47,  51,  50,  34,  39,  33,
        36,  31,  48,  43,  42,  30,  27,  52,
        36,  39,  39,  31,  31,  45,  44,  20
};

constexpr SCORE_TYPE QUEEN_PST_MID[64] = {
        -27, -35, -10, -10,  32,  58,  65,  29,
        4, -53, -45, -71,-104,   2,   3,  20,
        6,   2, -11, -57, -48,  46,  52, -13,
        14,   4, -22, -41, -45, -23, -14,  -8,
        28,  23,   4, -12, -17,  -9,  10,   3,
        31,  56,  26,  10,   5,   7,  27,  13,
        41,  52,  51,  26,  22,  34,  25,  11,
        63,  44,  44,  40,  31,  14,  35,  -6
};

constexpr SCORE_TYPE QUEEN_PST_END[64] = {
        11,  61,  46,  22,  27,  15,   0,  20,
        14,  57,  72,  76, 104,  52,  46,  36,
        14,  22,  25,  84,  78,  34,  25,  92,
        10,  49,  58,  75,  85,  71,  79,  78,
        4,  42,  44,  79,  58,  56,  29,  15,
        -5, -54,  24,  17,  24,  32,   1,  12,
        -27, -43, -47,  14,   7, -41, -28, -14,
        -43, -38, -22,  65, -20, -34, -39, -36
};

constexpr SCORE_TYPE KING_PST_MID[64] = {
        -178, 226, 257,  68,-223, -85,  26, -19,
        201, 163, 164,  77,  40,  88, -63,-217,
        69, 189, 177, -11,  81, 136, 177, -55,
        24,  86, 108, -26, -74,  33,  27,-122,
        -24, 154,  63, -99, -78, -24,   3,-102,
        -21,  26,  11, -78, -49, -11,  20, -41,
        3,   4, -10,-141,-104, -56,   4,  -3,
        0,  23, -22,-154, -71,-105, -21, -30
};

constexpr SCORE_TYPE KING_PST_END[64] = {
        -102,-110, -95,  -8,  47,   4, -27, -72,
        -76,  -6,  -4,  55,  63,  14,  41,  17,
        1,   1,  13,  79,  63,  41,  27,  11,
        -14,  15,  22, 104, 104,  39,  31,  14,
        -34, -32,  15, 108, 104,  32,   8, -11,
        -37, -12,   7,  88,  77,  16, -10, -26,
        -53, -29,  -6,  75,  68,  12, -24, -53,
        -125, -75, -40,  37,   3, -13, -45,-101
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_MID[3][8] = {
        {   0,  -2,   0,  -7,   9,  15,  21,   0},
        {   0,   3,   3,  -5,  22,  50, 341,   0},
        {   0,   3,  56,  -9,  45,  43, 625,   0}
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_END[3][8] = {
        {   0,  13,  22,  55,  93, 181, 241,   0},
        {   0,   3,  14,  43, 100, 213, 178,   0},
        {   0,   3,   8,  16,  63, 163, -65,   0}
};

constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_MID =  -10;
constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_END =    2;

constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -21;
constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_END =  -14;

constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_MID =   -6;
constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_END =  -36;

constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_MID =   -5;
constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_END =    6;

constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -14;
constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_END =   -5;

constexpr SCORE_TYPE PHALANX_PAWN_BONUS_MID[8] = {   0,   5,  21,  25,  44,  17, -89,   0};

constexpr SCORE_TYPE PHALANX_PAWN_BONUS_END[8] = {   0,   5,   9,  20,  82, 181, 479,   0};

constexpr SCORE_TYPE PIECE_SUPPORT_MID[6][6] = {
        {  21,   5,   7,   6,  -7, -84},
        {  -6,   1,  -1,   1,   5,  -2},
        {  -6,   7, -54,   0,   7,  -3},
        {   0,  11,   5,   6,   7,   7},
        {  -2,   6,   5,   6,  30,   1},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE PIECE_SUPPORT_END[6][6] = {
        {  18,  22,  30,   7,   2,  31},
        {   3,  11,   1,  -2, -10,  -3},
        {  -5,  11,  59,   5,   8,   3},
        {   1,   2,   7,  13,  44,  -8},
        {   7,   7, -11, -10,-557, -14},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE PIECE_THREAT_MID[6][6] = {
        {  10,  79,  67, 107,  72, 192},
        {  -6,  20,  33,  62,  51, 125},
        {  -2,  34,  20,  49,  59,  75},
        { -10,   3,   8,  10,  64, 138},
        {  -6,   4,   0,  -8,  10,  80},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE PIECE_THREAT_END[6][6] = {
        {  10,  33,  77,   2,  38,  19},
        {  20,  20,  51,  24,  13,  29},
        {  18,  55,  20,  37,  64,  80},
        {  25,  33,  41,  10,  52,  34},
        {  14,  14,  40,  38,  10, 117},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE BLOCKER_VALUES_MID[6][8] = {
        {   0,   0,   0,   0,   0,   0,   0,   0},
        {   0,  25, -12,   1, -16, -13, 127,   0},
        {   0,  -7, -11, -15,  -2, -15,  13,   0},
        {   0,  21, -15,  -4,  18,   2,  18,   0},
        {   0,   6, -55,  19,   9,  30,  69,   0},
        {   0,  74,  80, -78, -20, -77, -18,   0}
};

constexpr SCORE_TYPE BLOCKER_VALUES_END[6][8] = {
        {   0,   0,   0,   0,   0,   0,   0,   0},
        {   0, -60, -10, -40, -79,-111,-220,   0},
        {   0, -34, -46, -37, -64,-118,-209,   0},
        {   0, -19,  29,   8,  -8, -52,-136,   0},
        {   0, -18,  66, -40,  -3, -47,  83,   0},
        {   0, -30, -28, -40, -75,-162,-294,   0}
};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_MID[6][8] = {
        {   0,   0,   0,   0,   0,   0,   0,   0},
        {   0,  -1, -14,  -2,  11,  47,   0,   0},
        {   0,   2,  -3, -15,   3,  36,   0,   0},
        {   0,  10,  24,  -9,   6,  37,   0,   0},
        {   0,  30,   1,  10,  31,  14,   0,   0},
        {   0, 211,  61, -35,   4,  52,   0,   0}
};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_END[6][8] = {
        {   0,   0,   0,   0,   0,   0,   0,   0},
        {   0, -28, -17, -16, -27,-120,   0,   0},
        {   0, -20, -10,  -4, -31, -71,   0,   0},
        {   0, -15, -18,  18,   6, -62,   0,   0},
        {   0, -14,   2, -21, -35, 101,   0,   0},
        {   0,  -7,  -3,  -9, -42,-135,   0,   0}
};

constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_MID =   20;
constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_END =    7;

constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_MID =   45;
constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_END =   -1;

constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_MID =    2;
constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_END =   31;

constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_MID =   -8;
constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_END =   34;

constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_MID =  -22;
constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_END =    1;

constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_MID =  -13;
constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_END =  -11;

constexpr SCORE_TYPE BISHOP_PAIR_BONUS_MID =   28;
constexpr SCORE_TYPE BISHOP_PAIR_BONUS_END =   76;

constexpr SCORE_TYPE TEMPO_BONUS_MID =   27;
constexpr SCORE_TYPE TEMPO_BONUS_END =   27;

constexpr double MOBILITY_COEFFICIENTS_MID[6] = {      0,      5.99,      3.31,      2.18,      1.37,      0};

constexpr double MOBILITY_COEFFICIENTS_END[6] = {      0,      1.73,      3.06,      1.65,      -0.12,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -6.14,      0,      0,      0,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,      0.677,      0,      0,      0,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -1.17,      -0.194,     -4.39,    -10.3,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,     -1.34,      2.02,      4.14,      6.68,      0};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_MID[3][8] = {
        {   0,  -2, -33,   0,   0, -16, -13,   5},
        {   2, -45, -33,   0,   0, -22, -23,   3},
        { -41, -65, -60,   0,   0, -35, -59, -24}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_END[3][8] = {
        {  13,   5,  19,   0,   0,  -4,  11,  21},
        {  33,  33,  21,   0,   0, -17,  13,  25},
        {  33,  19,  13,   0,   0,  -7,  29,  40}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_MID[3][8] = {
        {   0, -28,  -4,   0,   0,  -4, -18,  10},
        {  -8, -14, -37,   0,   0, -32,  -1, -14},
        { -18, -92,-154,   0,   0, -87, -62, -49}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_END[3][8] = {
        { -16,  -1, -11,   0,   0,  -7,  -6, -18},
        {  40,  37,  23,   0,   0,  28,  25,  25},
        {  75,  92,  54,   0,   0,  39,  75,  87}
};

constexpr SCORE_TYPE KING_RING_ATTACKS_MID[2][6] = {
        {   0,  15,  18,  27,  19,   0},
        {   0,   9,   3,   5,   6,   0}
};

constexpr SCORE_TYPE KING_RING_ATTACKS_END[2][6] = {
        {   0, -12,  -4,  -7,  13,   0},
        {   0,   1,   0,   1,  16,   0}
};

constexpr SCORE_TYPE OUTPOST_PENALTY_MID =   -4;
constexpr SCORE_TYPE OUTPOST_PENALTY_END =  -16;

constexpr SCORE_TYPE OUTPOST_KNIGHT_PENALTY_MID =  -27;
constexpr SCORE_TYPE OUTPOST_KNIGHT_PENALTY_END =  -44;

constexpr SCORE_TYPE OUTPOST_BISHOP_PENALTY_MID =  -41;
constexpr SCORE_TYPE OUTPOST_BISHOP_PENALTY_END =   -5;
#endif //ANTARESCHESSENGINE_CONSTANTS_H