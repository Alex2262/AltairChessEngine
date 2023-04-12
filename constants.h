
#ifndef ANTARESCHESSENGINE_CONSTANTS_H
#define ANTARESCHESSENGINE_CONSTANTS_H

#include <cstdint>

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

#define STARTING_WINDOW     45

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

constexpr int MVV_LVA_VALUES[6] = { 109, 429, 403, 602,1403,   0};

constexpr SCORE_TYPE MAX_MINOR_PIECE_VALUE_MID = 405;
constexpr SCORE_TYPE PIECE_VALUES_MID[6] = {  99, 399, 405, 606,1449,   0};

constexpr SCORE_TYPE PIECE_VALUES_END[6] = { 121, 336, 341, 652,1305,   0};

constexpr SCORE_TYPE PAWN_PST_MID[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        127, 140,  75, 135,  84, 126,  14,   2,
        2,  18,  45,  57,  85,  73,  49,   7,
        -2,  17,  14,  30,  34,  33,  38,  -3,
        -5,  -5,   8,  14,  19,  24,   8, -16,
        -16, -18,  -8,  -4,   7,  -1,  10, -17,
        -9,  -2,  -7,  -5,   3,  30,  33,  -4,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE PAWN_PST_END[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        116, 108,  98,  38,  53,  61, 111, 139,
        89,  81,  40,  -7, -16,  29,  66,  97,
        43,  24,  12, -15,  -8,  12,  27,  41,
        18,  14,  -6, -10, -10,  -5,  10,  15,
        11,  10,   0,   0,   6,   2,   3,  11,
        24,  19,  21,   7,  20,   6,  13,  21,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE KNIGHT_PST_MID[64] = {
        -109, -63,  -6,  68, 162, -82,  36, -46,
        46,  28,  78,  72,  68,  78,  20,  50,
        33,  70,  65,  87, 107, 149, 100, 106,
        91,  75,  61,  87,  64,  73,  67,  91,
        66,  50,  49,  50,  54,  47,  78,  53,
        42,  28,  19,  21,  24,   6,  26,  25,
        21,  26,  15,  19,  13,  15,  28,  46,
        -53,  31,   1,   3,  22,   3,  17,  -8
};

constexpr SCORE_TYPE KNIGHT_PST_END[64] = {
        -21,  12,  37,   3,  -2,  26, -32, -75,
        5,  28,  16,  45,  33,   6,  17,  -6,
        7,  22,  41,  39,  17,  11,   8, -22,
        17,  36,  46,  50,  53,  44,  34,  21,
        19,  23,  40,  55,  51,  43,  30,  30,
        -17,  22,  18,  45,  38,  20,  10,  21,
        -1,  16,  15,  42,  51,  21,  29,   0,
        22,   2,  21,  40,  22,  35,  16, -25
};

constexpr SCORE_TYPE BISHOP_PST_MID[64] = {
        -22,  16, -90, -48, -27, -78,  12,  36,
        -16,  -3,   6, -17,  13,  51,   4, -17,
        28,  28,  41,  24,  57,  65,  81,  47,
        -4,  21,   6,  58,  34,  51,  22,  26,
        9,  12,  25,  31,  47,   7,  15,  42,
        23,  32,  21,  22,  19,  27,  33,  45,
        35,  36,  32,  19,  21,  28,  61,  36,
        44,  34,  22,  15,   5,  20,  18,  30
};

constexpr SCORE_TYPE BISHOP_PST_END[64] = {
        21,  22,  46,  42,  42,  39,  19,  13,
        40,  30,  36,  33,  41,  21,  28,  33,
        27,  29,  20,  28,  17,  31,  29,  40,
        31,  30,  34,  21,  25,  21,  46,  41,
        17,  23,  24,  26,  14,  27,  21,  12,
        7,  17,  22,  24,  31,  19,  10,  12,
        5,   3,  15,  27,  25,   9,  24,  -3,
        -10,  13,  40,  29,  31,  37,  31,  -3
};

constexpr SCORE_TYPE ROOK_PST_MID[64] = {
        43,  48,  12,  33,  66,  61,  59, 111,
        30,  13,  41,  48,  52,  91,  34,  65,
        4,  21,  29,  23,  44,  85, 116,  61,
        13,   5,  16,  30,   8,  39,  -3,  13,
        -11, -16, -12,  -9,  -3,  16,  28,  -8,
        -8,  -7, -13,  -8, -13,  11,  21,  -2,
        -10,   7,  -6,  -6,   5,  21,  23, -45,
        19,  13,  14,  18,  16,  11,  -2,  14
};

constexpr SCORE_TYPE ROOK_PST_END[64] = {
        52,  53,  63,  59,  49,  49,  46,  38,
        47,  57,  50,  52,  42,  29,  46,  37,
        42,  38,  37,  39,  31,  26,  16,  21,
        36,  36,  44,  37,  43,  39,  40,  40,
        39,  45,  44,  48,  42,  25,  27,  32,
        23,  31,  31,  35,  36,  22,  19,  17,
        23,  17,  34,  33,  30,  19,  13,  36,
        24,  26,  28,  23,  22,  35,  31,  11
};

constexpr SCORE_TYPE QUEEN_PST_MID[64] = {
        -31, -52,   0, -15,  51,  70,  88,  32,
        -4, -50, -38, -45, -62,  25,  33,  41,
        7,  -7, -11, -39, -18,  93,  86,  30,
        5,  -6, -14, -27, -30,  -4, -10,   8,
        23,  18,   6, -16, -11,  -5,  10,   3,
        30,  49,  26,   8,   3,   6,  26,  15,
        32,  41,  44,  19,  17,  24,  18,   4,
        55,  38,  35,  30,  20,   6,  20,  -9
};

constexpr SCORE_TYPE QUEEN_PST_END[64] = {
        34,  87,  49,  39,  33,  20,   6,  52,
        20,  35,  46,  50,  76,  36,  31,  34,
        8,  10,   4,  63,  58,  13,   8,  74,
        15,  40,  34,  45,  69,  56,  80,  73,
        11,  41,  29,  61,  31,  37,  11,  34,
        28, -34,  18,   2,   5,   5, -21,  24,
        30,  -1, -19,  12,  -5, -41, -44,   5,
        28,  15,   8,  62,  -2, -27, -25, -29
};

constexpr SCORE_TYPE KING_PST_MID[64] = {
        -96, 242, 271,  81,-168, -72, 104, -45,
        199, 166, 146,  48,  24,  78, -39,-155,
        75, 171, 147, -38,  25, 106, 151, -28,
        48,  93,  79, -66,-105,  -2,  -1,-123,
        -31, 119,  41,-125,-116, -57, -30, -99,
        -7,  22,  -1,-103, -83, -43,  -1, -36,
        13,  10,  -7,-137,-102, -65,   1,  -2,
        15,  34,  -5,-136, -54, -93, -11, -24
};

constexpr SCORE_TYPE KING_PST_END[64] = {
        -100,-102, -93,  -1,  44,   6, -29, -43,
        -69, -14, -11,  61,  65,  14,  34,   9,
        -8,  -8,   5,  77,  68,  33,  26,   7,
        -27,   2,  14,  98,  95,  35,  27,  11,
        -34, -33,   6,  99,  96,  31,  11, -13,
        -43, -17,   0,  82,  75,  18,  -6, -26,
        -52, -31, -10,  69,  63,  13, -19, -45,
        -106, -70, -41,  38,   5, -12, -41, -84
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_MID[3][8] = {
        {   0,  -2,  -3,  -9,   8,  17,  42,   0},
        {   0,   3,   2,  -7,  19,  66, 360,   0},
        {   0,   3,  34, -11,  35,  76, 322,   0}
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_END[3][8] = {
        {   0,  13,  23,  53,  81, 150, 189,   0},
        {   0,   3,  16,  44,  91, 168, 124,   0},
        {   0,   3,  23,  25,  64, 118,  87,   0}
};

constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_MID =   -9;
constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_END =    0;

constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -20;
constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_END =  -13;

constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_MID =   -7;
constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_END =  -35;

constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_MID =   -5;
constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_END =    2;

constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -15;
constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_END =   -9;

constexpr SCORE_TYPE PHALANX_PAWN_BONUS_MID[8] = {   0,   3,  20,  23,  39,  64,  17,   0};

constexpr SCORE_TYPE PHALANX_PAWN_BONUS_END[8] = {   0,  -2,   5,  16,  70, 152, 413,   0};

constexpr SCORE_TYPE PIECE_SUPPORT_MID[6][6] = {
        {  20,   5,   8,   3,  -6, -73},
        {  10,  17,  15,  19,  22,  16},
        {   5,  18,   9,  11,  18,   9},
        {   4,  16,  11,  11,  13,  12},
        {   1,   9,   7,   8,  29,   3},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE PIECE_SUPPORT_END[6][6] = {
        {  14,  25,  31,   8,   6,  27},
        {   8,  13,   6,   4, -10,   1},
        {   2,  15,  34,  11,  13,   8},
        {   4,   4,   9,  15,  37,  -4},
        {   8,   8,  -3,  -1,-513, -12},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE PIECE_THREAT_MID[6][6] = {
        {  10,  80,  73, 109,  76, 240},
        {  11,  20,  49,  72,  62, 127},
        {  10,  42,  20,  57,  70,  90},
        {  -5,   8,  15,  10,  70, 157},
        {  -4,   5,   4,  -3,  10,  96},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE PIECE_THREAT_END[6][6] = {
        {  10,  29,  66,   0,  32,  17},
        {  22,  20,  51,  25,  19,  33},
        {  23,  55,  20,  38,  67,  78},
        {  27,  34,  40,  10,  48,  29},
        {  17,  15,  34,  36,  10,  81},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE BLOCKER_VALUES_MID[6] = {   0,  -8,   4,  19,  14, -64};

constexpr SCORE_TYPE BLOCKER_VALUES_END[6] = {   0, -57, -83, -31,  -9, -87};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_MID[6] = {   0,   5,   0,  15,  21,   0};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_END[6] = {   0, -25, -24, -17, -16, -36};

constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_MID =   19;
constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_END =    5;

constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_MID =   44;
constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_END =    0;

constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_MID =    2;
constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_END =   25;

constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_MID =   -5;
constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_END =   28;

constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_MID =  -22;
constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_END =    1;

constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_MID =  -22;
constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_END =   -9;

constexpr SCORE_TYPE BISHOP_PAIR_BONUS_MID =   28;
constexpr SCORE_TYPE BISHOP_PAIR_BONUS_END =   68;

constexpr SCORE_TYPE TEMPO_BONUS_MID =   27;
constexpr SCORE_TYPE TEMPO_BONUS_END =   24;

constexpr double MOBILITY_COEFFICIENTS_MID[6] = {      0,      5.72,      3.61,      2.12,      1.18,      0};

constexpr double MOBILITY_COEFFICIENTS_END[6] = {      0,      1.38,      2.4,      1.33,      1.47,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -5.98,      0,      0,      0,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,      0.792,      0,      0,      0,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -2.33,      0.261,     -6.07,    -10.2,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,      0.864,      1.53,      4.19,     -9.45,      0};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_MID[3][8] = {
        {   4,   3, -29,   0,   0, -10, -12,   7},
        {   5, -33, -31,   0,   0, -20, -17,   4},
        { -45, -69, -65,   0,   0, -32, -55, -29}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_END[3][8] = {
        {  12,   4,  16,   0,   0,  -4,   9,  19},
        {  29,  27,  19,   0,   0, -16,  10,  24},
        {  32,  20,  14,   0,   0,  -8,  24,  38}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_MID[3][8] = {
        {  -2, -26,  -6,   0,   0,  -5, -17,   5},
        {  -5,  -7, -34,   0,   0, -32,   1, -20},
        {  -7, -64,-154,   0,   0, -93, -54, -46}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_END[3][8] = {
        { -14,  -1,  -8,   0,   0,  -6,  -6, -16},
        {  33,  27,  22,   0,   0,  25,  23,  24},
        {  70,  91,  73,   0,   0,  54,  82,  88}
};


#endif //ANTARESCHESSENGINE_CONSTANTS_H