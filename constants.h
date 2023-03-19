
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

constexpr SCORE_TYPE TEMPO_BONUS = 8;

constexpr char PIECE_MATCHER[12] = {'P', 'N', 'B', 'R', 'Q', 'K', 'p', 'n', 'b', 'r', 'q', 'k'};
constexpr int GAME_PHASE_SCORES[6] = {0, 1, 1, 2, 4, 0};

constexpr int MVV_LVA_VALUES[6] = { 109, 429, 403, 602,1403,   0};

constexpr double KING_PAWN_SHIELD_COEFFICIENTS[8] = {0.8, 1.0, 0.6, 0.0, 0.0, 0.3, 1.0, 0.5};
constexpr int KING_PAWN_SHIELD_OUR_PENALTIES[3] = {-6, -14, -23};
constexpr int KING_PAWN_SHIELD_OPP_PENALTIES[3] = {-19, -8, -16};

constexpr SCORE_TYPE PIECE_ATTACK_MOBILITY[6] = {6, 8, 8, 10, 14, 35};
constexpr SCORE_TYPE PIECE_ATTACK_MOBILITY_PENALTY[6] = {0, 2, 1, 3, 4, 0};

constexpr SCORE_TYPE PIECE_VALUES_MID[6] = { 109, 429, 403, 602,1403,   0};

constexpr SCORE_TYPE PIECE_VALUES_END[6] = { 121, 349, 355, 654,1303,   0};

constexpr SCORE_TYPE PAWN_PST_MID[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        82, 120,  18,  75,  30, 123, -15, -48,
        -6,  17,  43,  44,  74, 114,  46,  28,
        -7,   7,  17,  39,  38,  46,  27,   3,
        -10,  -6,   5,  20,  22,  23,  13,  -5,
        -10, -15,   1,   5,  15,  16,  25,   6,
        -18, -19, -16, -10, -11,  33,  26,  -1,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE PAWN_PST_END[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        116,  96,  96,  43,  58,  47, 105, 133,
        76,  66,  31,  -4, -14,   4,  38,  48,
        38,  28,  14, -14,  -5,   6,  22,  24,
        25,  22,   3,  -4,  -2,  -2,   7,   8,
        11,  18,   5,   5,  14,   8,   1,  -2,
        23,  21,  27,  16,  30,  16,   1,  -6,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE KNIGHT_PST_MID[64] = {
        -157, -76,  -8,  24, 133,-100,  23, -93,
        24,   2,  85,  66,  58,  96,   3,  24,
        20,  86,  77, 102, 116, 152, 106,  81,
        71,  70,  71,  96,  66,  75,  50,  68,
        56,  48,  60,  61,  66,  51,  68,  35,
        42,  41,  52,  47,  56,  43,  41,  24,
        17,  18,  34,  44,  33,  32,  12,  36,
        -80,  30,  -6,   6,  21,   8,  14, -21
};

constexpr SCORE_TYPE KNIGHT_PST_END[64] = {
        -28,   3,  29,   6,  -1,  23, -34, -87,
        -5,  25,  19,  48,  39,   7,  19, -11,
        3,  23,  55,  58,  35,  33,  15, -22,
        13,  48,  67,  72,  79,  72,  53,  21,
        17,  33,  62,  75,  67,  70,  45,  32,
        -17,  27,  28,  54,  48,  27,  16,  15,
        -15,  11,  15,  33,  45,  14,  29, -17,
        11, -21,  18,  28,  15,  25,  -2, -25
};

constexpr SCORE_TYPE BISHOP_PST_MID[64] = {
        -31,  10,-106, -56, -46, -75,   6,  24,
        -35, -10, -17, -32,  18,  25,  -3, -26,
        1,  21,  33,  18,  41,  52,  54,  19,
        -13,  15,   5,  45,  29,  43,  18,  12,
        6,  10,  15,  30,  44,   8,  12,  37,
        21,  34,  23,  26,  23,  34,  26,  41,
        30,  36,  37,  20,  31,  22,  56,  21,
        33,  36,  15,  13,  -8,  14,   0,  10
};

constexpr SCORE_TYPE BISHOP_PST_END[64] = {
        22,  21,  43,  40,  42,  36,  20,  11,
        38,  29,  43,  37,  35,  29,  32,  34,
        31,  32,  28,  36,  27,  35,  36,  43,
        31,  44,  43,  38,  37,  32,  54,  39,
        17,  34,  39,  39,  27,  38,  31,  12,
        9,  28,  31,  29,  43,  27,  26,  11,
        7,   1,  11,  24,  20,  10,  24,   3,
        -9,  12,  31,  22,  30,  32,  30,   0
};

constexpr SCORE_TYPE ROOK_PST_MID[64] = {
        41,  42,  15,  27,  55,  26,  44,  69,
        12,   1,  24,  30,  44,  86,  21,  51,
        -10,   8,  13,  10,  22,  67, 102,  31,
        -4, -14,   1,  15,  -9,  15, -11,  -7,
        -12, -25, -21, -20, -14,   1,  20, -15,
        -7,  -9,  -8,  -8, -11,   6,  19,  -6,
        -4,   9,   0,   1,  10,  20,  24, -50,
        38,  32,  32,  38,  31,  29,   4,  22
};

constexpr SCORE_TYPE ROOK_PST_END[64] = {
        64,  64,  72,  69,  66,  70,  63,  63,
        71,  78,  73,  78,  63,  48,  69,  60,
        63,  62,  64,  66,  57,  50,  35,  44,
        54,  60,  65,  59,  68,  63,  58,  59,
        48,  59,  60,  60,  58,  43,  44,  42,
        32,  43,  37,  43,  44,  34,  31,  27,
        28,  23,  40,  37,  35,  28,  21,  43,
        29,  31,  33,  26,  28,  37,  38,  17
};

constexpr SCORE_TYPE QUEEN_PST_MID[64] = {
        -44, -50, -37, -28,  32,  47,  44,  44,
        -30, -78, -59, -65, -91,  -4,  -2,  34,
        -11, -23, -24, -63, -34,  79,  56,  12,
        -4, -19, -24, -39, -39, -17, -20,  -8,
        21,   8,   3, -18, -13, -11,  -3,   0,
        25,  44,  31,  15,   9,  10,  14,   8,
        30,  47,  53,  37,  37,  35,  26,  13,
        67,  51,  58,  54,  37,  20,  33,   0
};

constexpr SCORE_TYPE QUEEN_PST_END[64] = {
        57,  90,  75,  48,  52,  33,  43,  54,
        46,  62,  70,  71, 101,  65,  71,  42,
        27,  25,  14,  85,  79,  30,  31,  92,
        26,  48,  50,  56,  78,  60,  85,  89,
        20,  60,  29,  65,  37,  44,  29,  32,
        52,  -9,  25,   3,   7,   2,  -1,  45,
        54,   0,  -8,   7, -23, -48, -55,  -5,
        43,  20,   6,  58, -13, -38, -40, -29
};

constexpr SCORE_TYPE KING_PST_MID[64] = {
        -144, 191, 203, 158, -87,-103,  36, -35,
        171,  65,  82, 112,  75,  55, -55,-194,
        38,  92, 100,  32,  94,  99, 136, -54,
        11,  20,   6, -18, -67, -19, -23,-139,
        -77,  64, -26, -95, -96, -69, -50, -97,
        -17,  -3, -33, -87, -76, -44,  -2, -43,
        26,  29, -12,-113, -90, -50,  12,   3,
        4,  61,  24,-130, -52, -79,   4, -13
};

constexpr SCORE_TYPE KING_PST_END[64] = {
        -92, -82, -64, -38,   6,  23,   1, -29,
        -57,  17,  16,  25,  32,  27,  44,  28,
        6,  20,  32,  43,  29,  46,  39,  19,
        -9,  29,  42,  69,  67,  44,  38,  19,
        -14, -10,  36,  75,  71,  41,  22,  -7,
        -24,   4,  24,  58,  55,  25,   4, -16,
        -38, -20,  10,  45,  41,  16, -12, -35,
        -89, -65, -33,  21, -11,  -5, -36, -77
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_MID[8] = {   0,   1,  -8, -11,   9,  25, 100,   0};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_END[8] = {   0,   8,  20,  52,  89, 162, 180,   0};

constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_MID =  -17;
constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_END =   -5;

constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -28;
constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_END =  -19;

constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_MID =  -16;
constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_END =  -29;

constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_MID =   -5;
constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_END =    2;

constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -16;
constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_END =  -10;

constexpr SCORE_TYPE BLOCKER_VALUES_MID[6] = {   0, -11,   6,  23,  10, -68};

constexpr SCORE_TYPE BLOCKER_VALUES_END[6] = {   0, -54, -75, -34,  -2, -95};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_MID[6] = {   0,   1, -12,  25,  28, -11};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_END[6] = {   0, -23, -24, -22, -29, -42};

constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_MID =   18;
constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_END =   18;

constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_MID =   51;
constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_END =    3;

constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_MID =    4;
constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_END =   26;

constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_MID =   -1;
constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_END =   23;

constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_MID =  -19;
constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_END =   -1;

constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_MID =  -15;
constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_END =  -11;

constexpr SCORE_TYPE BISHOP_PAIR_BONUS_MID =   30;
constexpr SCORE_TYPE BISHOP_PAIR_BONUS_END =   69;

constexpr double MOBILITY_COEFFICIENTS_MID[6] = {      0,      3.22,      3.98,      1.46,      0.805,      0};

constexpr double MOBILITY_COEFFICIENTS_END[6] = {      0,      0.962,      2.74,      1.14,      1.96,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -5.75,      0,      0,      0,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,      1.26,      0,      0,      0,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -2.57,      -0.215,     -7.27,    -10.4,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,      0.406,      1.21,      3.85,    -11.9,      0};

#endif //ANTARESCHESSENGINE_CONSTANTS_H