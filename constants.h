
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

constexpr int MVV_LVA_VALUES[6] = {  100, 382, 409, 592,1448,   0};

constexpr SCORE_TYPE MAX_MINOR_PIECE_VALUE_MID = 409;
constexpr SCORE_TYPE PIECE_VALUES_MID[6] = { 101, 385, 409, 595,1454,   0};

constexpr SCORE_TYPE PIECE_VALUES_END[6] = { 129, 359, 350, 689,1293,   0};

constexpr SCORE_TYPE PAWN_PST_MID[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        166, 166, 114, 168, 107, 192,  49,  43,
        4,  23,  47,  63,  89,  88,  61,   7,
        -3,  15,  15,  30,  37,  39,  37,  -7,
        -9,  -9,   4,  11,  17,  21,   8, -18,
        -22, -22, -14,  -9,   2,  -5,   7, -20,
        -14,  -7, -14,  -9,  -3,  25,  31,  -8,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE PAWN_PST_END[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        112, 105,  99,  31,  61,  58, 127, 130,
        85,  75,  34, -10, -18,  21,  63,  96,
        44,  24,   9, -20, -13,   8,  26,  42,
        20,  15,  -7, -12, -12,  -6,   9,  16,
        13,  11,   1,  -2,   6,   2,   4,  13,
        26,  19,  24,   7,  24,   6,  15,  21,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE KNIGHT_PST_MID[64] = {
        -119, -60, -18,  45, 129,-109,  17, -59,
        51,  22,  65,  59,  63,  67,  12,  45,
        28,  65,  60,  75,  88, 131,  82,  93,
        82,  70,  54,  73,  41,  54,  42,  78,
        61,  46,  43,  40,  44,  30,  63,  45,
        40,  23,  14,  17,  19,   3,  27,  28,
        19,  24,  12,  15,   9,  15,  28,  46,
        -40,  26,  -3,   0,  17,   5,  15,  -2
};

constexpr SCORE_TYPE KNIGHT_PST_END[64] = {
        -11,  24,  52,  24,  23,  48, -14, -65,
        20,  46,  30,  63,  49,  22,  34,  10,
        23,  35,  52,  58,  39,  31,  27,  -4,
        35,  53,  61,  70,  76,  66,  61,  43,
        41,  42,  58,  73,  68,  60,  48,  45,
        -5,  34,  34,  57,  49,  29,  20,  33,
        16,  38,  24,  60,  68,  29,  36,  16,
        17,  20,  42,  55,  41,  48,  36,  -8
};

constexpr SCORE_TYPE BISHOP_PST_MID[64] = {
        -32,  14, -99, -76, -71, -86,   5,  51,
        -17,   5,   6, -11,  -5,  38,  -4, -27,
        29,  37,  51,  23,  46,  58,  62,  28,
        2,  25,  11,  52,  33,  39,  19,  13,
        14,  18,  25,  30,  47,  12,  19,  40,
        23,  35,  28,  25,  26,  33,  41,  47,
        36,  43,  42,  26,  27,  38,  66,  46,
        53,  35,  27,  20,  15,  26,  18,  37
};

constexpr SCORE_TYPE BISHOP_PST_END[64] = {
        36,  38,  66,  67,  68,  55,  40,  22,
        56,  42,  48,  45,  53,  39,  38,  50,
        39,  38,  28,  37,  26,  42,  44,  59,
        43,  41,  42,  30,  32,  31,  55,  60,
        29,  30,  31,  34,  21,  35,  27,  25,
        18,  23,  26,  29,  37,  23,  16,  19,
        5,   4,  17,  28,  31,  13,  33,  -1,
        -20,  11,  47,  35,  33,  43,  39,  -3
};

constexpr SCORE_TYPE ROOK_PST_MID[64] = {
        47,  43,   7,  14,  40,  42,  18, 100,
        30,  11,  36,  45,  38,  71,  13,  55,
        10,  30,  39,  38,  43,  79,  98,  57,
        18,  15,  33,  44,  20,  49,  -1,  19,
        -10, -14,  -3,   1,   3,  11,  16,   0,
        -9,  -5, -11,  -7,  -7,   6,  13,  -3,
        -15,   5, -10,  -5,   3,  16,  18, -50,
        14,  10,  13,  19,  15,  11,  -1,  13
};

constexpr SCORE_TYPE ROOK_PST_END[64] = {
        58,  63,  72,  74,  65,  63,  66,  51,
        57,  66,  61,  63,  57,  39,  61,  48,
        51,  45,  44,  42,  39,  36,  30,  31,
        48,  44,  49,  41,  47,  41,  49,  48,
        51,  56,  52,  55,  48,  34,  37,  38,
        34,  39,  41,  46,  44,  29,  32,  27,
        32,  26,  43,  39,  37,  25,  21,  46,
        33,  35,  36,  28,  28,  41,  38,  18
};

constexpr SCORE_TYPE QUEEN_PST_MID[64] = {
        -31, -32,  -9,  -8,  33,  55,  59,  21,
        2, -46, -37, -63, -95,   5,   5,  14,
        5,   6,  -5, -50, -42,  46,  49, -18,
        12,   6, -15, -32, -38, -18, -13, -10,
        25,  25,   7,  -5, -10,  -3,  12,   2,
        28,  56,  30,  14,  12,  12,  31,  11,
        32,  50,  50,  27,  23,  37,  26,   6,
        54,  33,  36,  33,  25,   9,  29, -12
};

constexpr SCORE_TYPE QUEEN_PST_END[64] = {
        13,  57,  44,  21,  25,  15,   2,  24,
        15,  53,  66,  70,  96,  49,  42,  36,
        12,  17,  20,  78,  71,  32,  24,  90,
        11,  45,  52,  67,  78,  66,  73,  75,
        4,  37,  38,  72,  50,  49,  26,  12,
        -5, -56,  19,  12,  17,  27,  -4,  10,
        -22, -42, -47,  10,   4, -43, -30, -12,
        -35, -31, -17,  66, -16, -31, -37, -32
};

constexpr SCORE_TYPE KING_PST_MID[64] = {
        -167, 223, 249,  63,-220, -88,  26, -18,
        197, 156, 157,  70,  34,  86, -60,-205,
        66, 181, 166, -15,  72, 127, 167, -55,
        27,  81, 102, -30, -77,  29,  26,-117,
        -22, 147,  59, -98, -79, -25,   3, -98,
        -19,  26,  10, -79, -50, -11,  20, -38,
        5,   6,  -9,-137,-101, -53,   5,  -1,
        3,  24, -20,-151, -71,-102, -20, -27
};

constexpr SCORE_TYPE KING_PST_END[64] = {
        -100,-107, -93,  -8,  45,   6, -27, -70,
        -75,  -7,  -5,  53,  60,  13,  39,  16,
        1,   1,  13,  77,  61,  40,  26,  11,
        -15,  14,  21, 101, 101,  38,  30,  14,
        -34, -31,  14, 104, 100,  31,   8, -11,
        -37, -12,   6,  84,  74,  15, -10, -26,
        -53, -29,  -7,  71,  65,  12, -23, -52,
        -122, -73, -40,  35,   2, -12, -44, -97
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_MID[3][8] = {
        {   0,  -2,   1,  -7,   8,  14,  15,   0},
        {   0,   3,   4,  -5,  19,  45, 319,   0},
        {   0,   3,  54, -11,  39,  48, 694,   0}
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_END[3][8] = {
        {   0,  12,  21,  53,  86, 174, 231,   0},
        {   0,   3,  15,  42,  95, 209, 177,   0},
        {   0,   3,  17,  22,  63, 163, -73,   0}
};

constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_MID =  -10;
constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_END =    0;

constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -20;
constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_END =  -17;

constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_MID =   -7;
constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_END =  -36;

constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_MID =   -6;
constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_END =    2;

constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -15;
constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_END =  -10;

constexpr SCORE_TYPE PHALANX_PAWN_BONUS_MID[8] = {   0,   2,  21,  24,  41,  13,-107,   0};

constexpr SCORE_TYPE PHALANX_PAWN_BONUS_END[8] = {   0,  -2,   4,  16,  75, 170, 464,   0};

constexpr SCORE_TYPE PIECE_SUPPORT_MID[6][6] = {
        {  20,   6,   8,   5,  -7, -83},
        {  11,  18,  17,  19,  23,  16},
        {   3,  16, -61,   9,  16,   7},
        {   5,  15,   9,  12,  11,  12},
        {  -1,   7,   5,   7,  33,   3},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE PIECE_SUPPORT_END[6][6] = {
        {  14,  25,  30,   5,   0,  30},
        {   8,  16,   6,   3,  -7,   2},
        {   3,  19,  71,  14,  17,  11},
        {   5,   5,   9,  15,  44,  -4},
        {   8,   7, -10,  -9,-535, -13},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE PIECE_THREAT_MID[6][6] = {
        {  10,  79,  67, 105,  71, 188},
        {  12,  20,  50,  76,  65, 137},
        {   8,  41,  20,  56,  65,  80},
        {  -7,   6,  12,  10,  66, 138},
        {  -6,   4,   1,  -5,  10,  80},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE PIECE_THREAT_END[6][6] = {
        {  10,  32,  73,   3,  36,  19},
        {  24,  20,  54,  28,  16,  33},
        {  26,  61,  20,  44,  71,  86},
        {  28,  35,  43,  10,  53,  36},
        {  15,  15,  40,  37,  10, 113},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE BLOCKER_VALUES_MID[6][8] = {
        {   0,   0,   0,   0,   0,   0,   0,   0},
        {   0,  30,  -8,   1, -15, -13, 113,   0},
        {   0,  -5,  -7, -14,  -1, -15,  10,   0},
        {   0,  21, -12,   1,  23,   8,  20,   0},
        {   0,   7, -52,  19,  13,  35,  75,   0},
        {   0,  84,  77, -77, -23, -74, -18,   0}
};

constexpr SCORE_TYPE BLOCKER_VALUES_END[6][8] = {
        {   0,   0,   0,   0,   0,   0,   0,   0},
        {   0, -58,  -9, -40, -77,-107,-211,   0},
        {   0, -34, -45, -36, -61,-112,-198,   0},
        {   0, -14,  33,  12,  -3, -45,-125,   0},
        {   0, -16,  63, -37,  -6, -49,  75,   0},
        {   0, -33, -27, -37, -72,-155,-282,   0}
};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_MID[6][8] = {
        {   0,   0,   0,   0,   0,   0,   0,   0},
        {   0,   0, -13,  -1,  12,  47,   0,   0},
        {   0,   1,  -3, -14,   4,  35,   0,   0},
        {   0,   7,  20,  -9,   3,  34,   0,   0},
        {   0,  27,   2,  13,  33,  18,   0,   0},
        {   0, 206,  60, -32,   2,  50,   0,   0}
};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_END[6][8] = {
        {   0,   0,   0,   0,   0,   0,   0,   0},
        {   0, -27, -18, -17, -26,-117,   0,   0},
        {   0, -20, -11,  -5, -30, -69,   0,   0},
        {   0, -17, -19,  16,   6, -59,   0,   0},
        {   0, -13,   3, -23, -33,  96,   0,   0},
        {   0,  -9,  -4,  -9, -40,-130,   0,   0}
};

constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_MID =   20;
constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_END =    7;

constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_MID =   43;
constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_END =    0;

constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_MID =    3;
constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_END =   29;

constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_MID =   -6;
constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_END =   33;

constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_MID =  -21;
constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_END =    1;

constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_MID =  -13;
constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_END =  -11;

constexpr SCORE_TYPE BISHOP_PAIR_BONUS_MID =   27;
constexpr SCORE_TYPE BISHOP_PAIR_BONUS_END =   73;

constexpr SCORE_TYPE TEMPO_BONUS_MID =   26;
constexpr SCORE_TYPE TEMPO_BONUS_END =   26;

constexpr double MOBILITY_COEFFICIENTS_MID[6] = {      0,      6.04,      3.01,      1.89,      0.762,      0};

constexpr double MOBILITY_COEFFICIENTS_END[6] = {      0,      1.74,      2.81,      1.5,      0.308,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -5.65,      0,      0,      0,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,      0.913,      0,      0,      0,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -0.89,      -0.297,     -4.11,    -9.84,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,     -1.08,      1.76,      4.2,      6.13,      0};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_MID[3][8] = {
        {  -1,  -1, -33,   0,   0, -15, -13,   4},
        {  -1, -42, -34,   0,   0, -20, -21,   1},
        { -41, -62, -58,   0,   0, -33, -57, -25}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_END[3][8] = {
        {  13,   5,  18,   0,   0,  -4,  10,  20},
        {  33,  32,  20,   0,   0, -16,  12,  24},
        {  32,  18,  13,   0,   0,  -7,  27,  39}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_MID[3][8] = {
        {   0, -27,  -3,   0,   0,  -4, -18,   9},
        {  -7, -12, -36,   0,   0, -31,   0, -13},
        { -16, -85,-151,   0,   0, -83, -59, -47}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_END[3][8] = {
        { -16,  -1, -10,   0,   0,  -6,  -6, -17},
        {  38,  35,  22,   0,   0,  27,  23,  23},
        {  71,  87,  53,   0,   0,  38,  72,  84}
};

constexpr SCORE_TYPE KING_RING_ATTACKS_MID[2][6] = {
        {   0,  14,  17,  27,  19,   0},
        {   0,   8,   3,   4,   6,   0}
};

constexpr SCORE_TYPE KING_RING_ATTACKS_END[2][6] = {
        {   0, -10,  -4,  -7,  12,   0},
        {   0,   1,   0,   1,  15,   0}
};

#endif //ANTARESCHESSENGINE_CONSTANTS_H