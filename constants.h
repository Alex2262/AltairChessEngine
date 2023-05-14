
#ifndef ANTARESCHESSENGINE_CONSTANTS_H
#define ANTARESCHESSENGINE_CONSTANTS_H

#include <cstdint>

#define N_TUNING_PARAMETERS         18
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

constexpr int MVV_LVA_VALUES[6] = {  103, 392, 419, 606,1472,   0};

constexpr SCORE_TYPE MAX_MINOR_PIECE_VALUE_MID = 419;
constexpr SCORE_TYPE PIECE_VALUES_MID[6] = { 103, 392, 419, 606,1472,   0};

constexpr SCORE_TYPE PIECE_VALUES_END[6] = { 128, 372, 368, 726,1400,   0};

constexpr SCORE_TYPE PAWN_PST_MID[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        180, 175, 113, 166, 110, 202,  48,  50,
        9,  20,  42,  57,  83,  86,  60,  12,
        0,  13,  11,  27,  33,  37,  33,  -7,
        -5, -11,   3,   9,  16,  20,   6, -17,
        -18, -22, -15,  -9,   1,  -5,   6, -18,
        -10,  -7, -15, -11,  -4,  24,  30,  -7,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE PAWN_PST_END[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        96,  91,  94,  31,  65,  56, 124, 123,
        73,  70,  38,   3,   0,  30,  67,  92,
        28,  17,  10, -13,  -7,  11,  27,  38,
        7,  11,  -3,  -5,  -6,  -3,  10,  15,
        1,   7,   5,   5,  13,   6,   5,  11,
        13,  14,  26,  12,  30,   9,  16,  17,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE KNIGHT_PST_MID[64] = {
        -114, -58, -16,  51, 129,-109,  13, -55,
        57,  27,  72,  65,  67,  70,  18,  50,
        35,  63,  65,  82,  95, 131,  82, 100,
        91,  77,  59,  75,  46,  61,  48,  85,
        67,  53,  49,  47,  51,  37,  71,  51,
        47,  31,  21,  24,  27,  11,  35,  34,
        25,  31,  20,  24,  17,  23,  35,  53,
        -34,  33,   4,   5,  24,  11,  22,   0
};

constexpr SCORE_TYPE KNIGHT_PST_END[64] = {
        0,  39,  66,  37,  40,  60,   0, -55,
        34,  60,  42,  77,  64,  36,  45,  23,
        35,  47,  64,  71,  51,  38,  36,   6,
        46,  63,  72,  83,  88,  76,  70,  56,
        56,  55,  71,  86,  80,  72,  61,  58,
        7,  46,  46,  69,  61,  40,  33,  47,
        30,  53,  35,  72,  81,  41,  50,  32,
        31,  35,  56,  69,  54,  63,  51,  10
};

constexpr SCORE_TYPE BISHOP_PST_MID[64] = {
        -27,  16, -99, -71, -69, -83,  12,  55,
        -14,   9,   9, -11,  -2,  41,  -2, -25,
        34,  36,  54,  27,  49,  55,  62,  32,
        7,  28,  12,  52,  34,  42,  23,  17,
        17,  22,  30,  35,  52,  16,  24,  45,
        28,  41,  34,  31,  32,  40,  48,  52,
        41,  49,  48,  33,  33,  45,  72,  51,
        58,  41,  33,  28,  23,  31,  23,  42
};

constexpr SCORE_TYPE BISHOP_PST_END[64] = {
        46,  49,  75,  75,  78,  62,  51,  32,
        68,  52,  60,  57,  65,  51,  50,  58,
        49,  50,  40,  49,  39,  56,  56,  70,
        52,  52,  54,  44,  45,  43,  66,  71,
        41,  41,  43,  46,  32,  47,  37,  35,
        29,  34,  37,  40,  49,  34,  27,  30,
        17,  15,  27,  39,  42,  23,  44,   8,
        -11,  21,  60,  46,  43,  56,  51,   5
};

constexpr SCORE_TYPE ROOK_PST_MID[64] = {
        46,  45,   5,   8,  38,  42,  15, 100,
        28,   9,  34,  43,  36,  71,  14,  55,
        9,  34,  45,  43,  48,  88, 104,  60,
        20,  19,  37,  50,  26,  53,   4,  21,
        -9, -12,  -1,   3,   4,  13,  20,   1,
        -10,  -4, -11,  -6,  -8,   8,  13,  -5,
        -15,   6,  -9,  -3,   4,  17,  19, -51,
        14,  12,  16,  22,  18,  13,   0,  14
};

constexpr SCORE_TYPE ROOK_PST_END[64] = {
        67,  72,  82,  85,  76,  73,  78,  60,
        66,  76,  71,  72,  67,  48,  71,  57,
        62,  55,  53,  53,  48,  45,  40,  40,
        58,  55,  60,  51,  57,  51,  59,  58,
        62,  68,  63,  65,  59,  44,  47,  49,
        45,  49,  52,  56,  54,  39,  44,  38,
        42,  36,  52,  48,  46,  34,  31,  56,
        42,  44,  44,  36,  36,  49,  49,  26
};

constexpr SCORE_TYPE QUEEN_PST_MID[64] = {
        -27, -35,  -9, -11,  31,  58,  64,  29,
        5, -52, -45, -71,-104,   1,   3,  20,
        8,   4, -11, -58, -48,  45,  51, -13,
        16,   4, -22, -41, -45, -23, -14,  -8,
        28,  23,   3, -12, -17, -10,  10,   3,
        30,  56,  26,  10,   5,   6,  26,  12,
        40,  51,  50,  25,  21,  34,  24,  10,
        62,  44,  43,  39,  31,  13,  34,  -6
};

constexpr SCORE_TYPE QUEEN_PST_END[64] = {
        11,  61,  45,  23,  27,  14,   2,  19,
        12,  56,  71,  74, 103,  51,  45,  34,
        9,  18,  24,  85,  78,  34,  25,  91,
        7,  49,  59,  76,  85,  72,  79,  78,
        5,  43,  44,  80,  58,  58,  30,  14,
        -2, -52,  26,  18,  25,  35,   2,  14,
        -24, -41, -45,  15,   9, -40, -26, -11,
        -40, -37, -20,  67, -19, -32, -39, -35
};

constexpr SCORE_TYPE KING_PST_MID[64] = {
        -199, 218, 285, 105,-225,-115,   4,  22,
        196, 143, 170,  73,  27,  90, -80,-228,
        54, 173, 157, -25,  59, 113, 163, -55,
        13,  73,  95, -39, -90,  18,  13,-123,
        -19, 150,  58, -98, -75, -24,   4, -96,
        -16,  30,  11, -76, -47,  -7,  23, -38,
        2,   6,  -7,-134, -98, -51,   7,   0,
        2,  25, -18,-146, -65,-100, -17, -27
};

constexpr SCORE_TYPE KING_PST_END[64] = {
        -69, -76, -71,   3,  60,  26,  -4, -68,
        -51,  26,  22,  75,  81,  34,  62,  30,
        22,  24,  33,  90,  77,  59,  44,  20,
        2,  28,  32, 103, 103,  44,  38,  17,
        -26, -25,  17,  96,  92,  27,   7, -11,
        -32, -11,   5,  75,  64,   9, -13, -26,
        -47, -29, -11,  59,  53,   4, -28, -54,
        -124, -77, -46,  19, -13, -23, -51,-103
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_MID[3][8] = {
        {   0,  -1,   0,  -6,  13,  23,  17,   0},
        {   0,   3,   4,  -3,  25,  55, 324,   0},
        {   0,   3,  56,  -9,  47,  47, 724,   0}
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_END[3][8] = {
        {   0,  10,  19,  46,  74, 149, 212,   0},
        {   0,   3,  12,  35,  85, 189, 166,   0},
        {   0,   3,   5,  11,  54, 143, -50,   0}
};

constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_MID =  -10;
constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_END =    0;

constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -21;
constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_END =  -14;

constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_MID =   -6;
constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_END =  -34;

constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_MID =   -4;
constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_END =    6;

constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -14;
constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_END =   -5;

constexpr SCORE_TYPE PHALANX_PAWN_BONUS_MID[8] = {   0,   5,  21,  25,  43,  11,-121,   0};

constexpr SCORE_TYPE PHALANX_PAWN_BONUS_END[8] = {   0,   4,   8,  20,  85, 190, 507,   0};

constexpr SCORE_TYPE PIECE_SUPPORT_MID[6][6] = {
        {  21,   5,   7,   6,  -7, -85},
        {  -6,   1,  -1,   1,   5,  -2},
        {  -6,   7, -69,   0,   7,  -3},
        {   0,  11,   5,   6,   7,   7},
        {  -2,   7,   5,   5,  25,   1},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE PIECE_SUPPORT_END[6][6] = {
        {  17,  22,  30,   7,   1,  31},
        {   3,  11,   1,  -2, -10,  -3},
        {  -5,  10,  67,   4,   8,   3},
        {   0,   1,   6,  12,  43,  -8},
        {   6,   7, -12, -10,-547, -14},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE PIECE_THREAT_MID[6][6] = {
        {  10,  79,  66, 107,  72, 181},
        {  -6,  20,  33,  61,  51, 124},
        {  -2,  33,  20,  48,  58,  74},
        { -10,   3,   8,  10,  63, 136},
        {  -7,   4,   0,  -8,  10,  79},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE PIECE_THREAT_END[6][6] = {
        {  10,  33,  77,   2,  40,  32},
        {  21,  20,  52,  25,  13,  30},
        {  18,  55,  20,  38,  64,  81},
        {  26,  33,  41,  10,  53,  36},
        {  14,  14,  40,  38,  10, 120},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE BLOCKER_VALUES_MID[6][8] = {
        {   0,   0,   0,   0,   0,   0,   0,   0},
        {   0,  23, -12,   1, -14, -11, 134,   0},
        {   0,  -5, -10, -15,  -2, -14,  18,   0},
        {   0,  21, -15,  -2,  21,   6,  26,   0},
        {   0,   9, -55,  21,  11,  34,  79,   0},
        {   0,  58,  59, -83, -30, -82, -25,   0}
};

constexpr SCORE_TYPE BLOCKER_VALUES_END[6][8] = {
        {   0,   0,   0,   0,   0,   0,   0,   0},
        {   0, -59,  -8, -36, -78,-109,-230,   0},
        {   0, -34, -46, -36, -62,-118,-212,   0},
        {   0, -18,  29,   6, -10, -55,-145,   0},
        {   0, -23,  66, -42,  -4, -50,  71,   0},
        {   0, -19, -22, -32, -58,-137,-254,   0}
};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_MID[6][8] = {
        {   0,   0,   0,   0,   0,   0,   0,   0},
        {   0,   0, -14,  -2,  10,  51,   0,   0},
        {   0,   2,  -2, -14,   3,  39,   0,   0},
        {   0,  13,  25,  -6,   9,  43,   0,   0},
        {   0,  33,   4,  11,  32,  16,   0,   0},
        {   0, 195,  50, -42,   4,  46,   0,   0}
};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_END[6][8] = {
        {   0,   0,   0,   0,   0,   0,   0,   0},
        {   0, -27, -16, -13, -20,-121,   0,   0},
        {   0, -21, -10,  -2, -27, -70,   0,   0},
        {   0, -19, -20,  17,   3, -68,   0,   0},
        {   0, -19,  -1, -21, -33,  98,   0,   0},
        {   0,   0,  -1,  -1, -28,-109,   0,   0}
};

constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_MID =   19;
constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_END =    7;

constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_MID =   45;
constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_END =   -1;

constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_MID =    1;
constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_END =   32;

constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_MID =   -8;
constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_END =   35;

constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_MID =  -23;
constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_END =    3;

constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_MID =  -11;
constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_END =  -14;

constexpr SCORE_TYPE BISHOP_PAIR_BONUS_MID =   28;
constexpr SCORE_TYPE BISHOP_PAIR_BONUS_END =   76;

constexpr SCORE_TYPE TEMPO_BONUS_MID =   28;
constexpr SCORE_TYPE TEMPO_BONUS_END =   23;

constexpr double MOBILITY_COEFFICIENTS_MID[6] = {      0,      5.99,      3.21,      2.19,      1.45,      0};

constexpr double MOBILITY_COEFFICIENTS_END[6] = {      0,      2.01,      3.03,      1.66,      -0.128,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -6.02,      0,      0,      0,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,      0.677,      0,      0,      0,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -1.11,      -0.248,     -4.22,    -10.4,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,     -1.3,      1.89,      3.82,      6.4,      0};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_MID[3][8] = {
        {   1,  -1, -33,   0,   0, -16, -13,   5},
        {   2, -45, -34,   0,   0, -21, -23,   3},
        { -37, -61, -58,   0,   0, -35, -58, -23}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_END[3][8] = {
        {  13,   4,  19,   0,   0,  -3,  10,  21},
        {  32,  31,  21,   0,   0, -16,  13,  24},
        {  21,   9,   9,   0,   0,  -9,  24,  35}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_MID[3][8] = {
        {  -4, -29,  -4,   0,   0,  -4, -19,   8},
        {  -5, -12, -35,   0,   0, -32,   0, -13},
        { -12, -85,-156,   0,   0, -87, -58, -43}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_END[3][8] = {
        {  -5,   4,  -9,   0,   0,  -5,  -4, -13},
        {  31,  30,  18,   0,   0,  27,  22,  19},
        {  58,  75,  46,   0,   0,  36,  67,  70}
};

constexpr SCORE_TYPE KING_RING_ATTACKS_MID[2][6] = {
        {   0,  14,  18,  27,  18,   0},
        {   0,   9,   3,   5,   6,   0}
};

constexpr SCORE_TYPE KING_RING_ATTACKS_END[2][6] = {
        {   0, -11,  -4,  -7,  14,   0},
        {   0,   1,   0,   1,  16,   0}
};

constexpr SCORE_TYPE OUTPOST_PENALTY_MID =   -4;
constexpr SCORE_TYPE OUTPOST_PENALTY_END =  -16;

constexpr SCORE_TYPE OUTPOST_KNIGHT_PENALTY_MID =  -26;
constexpr SCORE_TYPE OUTPOST_KNIGHT_PENALTY_END =  -45;

constexpr SCORE_TYPE OUTPOST_BISHOP_PENALTY_MID =  -41;
constexpr SCORE_TYPE OUTPOST_BISHOP_PENALTY_END =   -5;

constexpr SCORE_TYPE SQUARE_OF_THE_PAWN_MID =  -22;
constexpr SCORE_TYPE SQUARE_OF_THE_PAWN_END =   67;

#endif //ANTARESCHESSENGINE_CONSTANTS_H