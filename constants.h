
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

constexpr char PIECE_MATCHER[12] = {'P', 'N', 'B', 'R', 'Q', 'K', 'p', 'n', 'b', 'r', 'q', 'k'};
constexpr int GAME_PHASE_SCORES[6] = {0, 1, 1, 2, 4, 0};

constexpr int MVV_LVA_VALUES[6] = { 109, 429, 403, 602,1403,   0};

constexpr SCORE_TYPE PIECE_ATTACK_MOBILITY[6] = {6, 8, 8, 10, 14, 35};
constexpr SCORE_TYPE PIECE_ATTACK_MOBILITY_PENALTY[6] = {0, 2, 1, 3, 4, 0};

constexpr SCORE_TYPE MAX_MINOR_PIECE_VALUE_MID = 391;
constexpr SCORE_TYPE PIECE_VALUES_MID[6] = {  99, 391, 374, 559,1298,   0};

constexpr SCORE_TYPE PIECE_VALUES_END[6] = { 119, 321, 326, 618,1207,   0};

constexpr SCORE_TYPE PAWN_PST_MID[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        111, 144,  60, 118,  77, 152,  37,   3,
        -5,  10,  37,  48,  71,  71,  34,   4,
        -4,  13,  18,  39,  39,  32,  32,  -4,
        -8,  -1,   8,  20,  22,  22,   9, -16,
        -10, -10,   4,   6,  16,  12,  24,  -7,
        -17, -16, -15, -10, -10,  21,  18, -10,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE PAWN_PST_END[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        108,  93,  89,  35,  47,  47,  98, 128,
        79,  71,  33, -10, -17,  23,  60,  85,
        37,  24,   9, -19, -12,  12,  26,  36,
        19,  13,  -3,  -9, -10,  -2,  10,  15,
        9,  11,  -1,   0,   7,   1,   4,   9,
        22,  17,  22,  10,  22,   5,  10,  17,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE KNIGHT_PST_MID[64] = {
        -138, -59, -13,  44, 140, -95,  29, -73,
        37,  19,  87,  77,  63,  93,  10,  45,
        29,  84,  77, 100, 119, 145, 103,  82,
        75,  66,  70,  92,  63,  74,  48,  70,
        54,  49,  59,  61,  65,  51,  69,  39,
        38,  40,  46,  47,  54,  39,  39,  23,
        14,  20,  32,  40,  30,  31,  21,  35,
        -71,  23,   2,   6,  21,   9,  10, -23
};

constexpr SCORE_TYPE KNIGHT_PST_END[64] = {
        -28,  -2,  25,  -2, -10,  18, -39, -81,
        -9,  19,   8,  35,  27,  -2,  11, -18,
        -3,  15,  41,  42,  18,  18,   3, -24,
        9,  41,  53,  56,  65,  55,  46,  18,
        14,  23,  48,  62,  54,  58,  36,  27,
        -22,  18,  17,  40,  37,  19,  13,  17,
        -13,   6,   5,  26,  37,  10,  18, -15,
        10, -16,  10,  26,  12,  20,   2, -31
};

constexpr SCORE_TYPE BISHOP_PST_MID[64] = {
        -32,   2,-100, -53, -40, -84,  -8,  23,
        -26,  -2,  -4, -19,  14,  32,   9, -23,
        2,  17,  33,  22,  39,  43,  50,  18,
        -8,  15,   2,  45,  31,  43,  16,  11,
        7,  11,  15,  29,  40,   5,  16,  33,
        14,  27,  21,  21,  17,  28,  28,  35,
        22,  29,  30,  16,  26,  21,  50,  26,
        33,  23,   7,   7,  -7,  10,   5,  13
};

constexpr SCORE_TYPE BISHOP_PST_END[64] = {
        16,  19,  40,  35,  37,  33,  13,   8,
        33,  25,  34,  29,  35,  20,  23,  26,
        29,  30,  24,  30,  20,  34,  34,  38,
        24,  38,  38,  31,  32,  25,  48,  35,
        13,  27,  32,  32,  21,  34,  23,   8,
        6,  21,  24,  24,  38,  24,  19,  12,
        4,  -2,   9,  19,  16,   6,  18,  -3,
        -14,   8,  29,  22,  25,  27,  25,  -5
};

constexpr SCORE_TYPE ROOK_PST_MID[64] = {
        30,  39,  11,  27,  59,  49,  46, 100,
        17,   0,  29,  38,  41,  87,  30,  50,
        -9,   8,  15,  11,  27,  64,  93,  39,
        -3, -11,   3,  14,  -8,  19, -18,  -6,
        -18, -24, -20, -15, -14,   4,  13, -17,
        -14,  -8, -12,  -8, -12,   3,  16,  -8,
        -12,   4,  -5,  -2,   5,  18,  18, -50,
        23,  19,  22,  27,  23,  20,  -1,  14
};

constexpr SCORE_TYPE ROOK_PST_END[64] = {
        49,  47,  55,  52,  42,  45,  44,  34,
        51,  62,  55,  56,  47,  31,  48,  40,
        47,  46,  45,  48,  40,  35,  24,  28,
        39,  42,  50,  44,  51,  45,  46,  42,
        36,  43,  42,  45,  41,  28,  29,  30,
        18,  24,  24,  27,  30,  20,  15,  12,
        16,  10,  25,  22,  20,  11,   6,  28,
        15,  16,  18,  12,  11,  22,  22,   2
};

constexpr SCORE_TYPE QUEEN_PST_MID[64] = {
        -39, -65, -21, -25,  30,  50,  58,  33,
        -18, -62, -47, -55, -67,  18,  17,  31,
        -11, -23, -17, -49, -25,  68,  55,   8,
        -6, -19, -23, -34, -33, -17, -23,  -9,
        14,   6,   1, -18, -11,  -8,   0,  -5,
        20,  37,  24,  11,   3,   7,  14,   4,
        28,  39,  44,  29,  29,  31,  22,   2,
        58,  39,  46,  42,  30,  17,  23,  -5
};

constexpr SCORE_TYPE QUEEN_PST_END[64] = {
        39,  91,  58,  42,  42,  29,  22,  48,
        33,  49,  56,  59,  81,  44,  47,  41,
        25,  25,  11,  70,  66,  27,  29,  84,
        23,  47,  41,  52,  68,  61,  79,  82,
        19,  47,  29,  58,  29,  32,  15,  36,
        40, -19,  19,  -2,   3,   0, -11,  30,
        33,  -2, -22,  -4, -23, -55, -60,  -4,
        25,  13,  -4,  50, -15, -41, -34, -34
};

constexpr SCORE_TYPE KING_PST_MID[64] = {
        -57, 223, 241,  81,-155, -79,  59, -51,
        179, 141, 135,  23,  13,  49, -42,-149,
        75, 149, 129, -46,  11,  88, 121, -37,
        42,  65,  68, -73,-115, -17, -22,-120,
        -19, 100,  27,-119,-115, -68, -42, -92,
        2,  14,  -5,-101, -88, -49,  -9, -35,
        21,  17,   1,-119, -89, -57,   2,  -1,
        27,  44,  10,-122, -46, -83,  -1, -12
};

constexpr SCORE_TYPE KING_PST_END[64] = {
        -110, -98, -90,   0,  40,   7, -19, -36,
        -67, -18, -16,  61,  62,  18,  33,  11,
        -16, -11,   0,  73,  64,  33,  28,   9,
        -31,   1,   7,  93,  91,  36,  31,  12,
        -40, -35,   1,  93,  90,  33,  15, -11,
        -49, -20,  -6,  76,  71,  19,  -2, -23,
        -58, -37, -19,  60,  55,  10, -19, -42,
        -111, -77, -50,  33,  -2, -14, -43, -82
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_MID[3][8] = {
        {   0,   1, -11,  -8,   5,  22,  48,   0},
        {   0,   3,   3,  -5,  20,  69, 328,   0},
        {   0,   3,  43, -11,  45, 115, 345,   0}
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_END[3][8] = {
        {   0,   8,  17,  44,  74, 137, 166,   0},
        {   0,   3,  14,  39,  85, 156, 114,   0},
        {   0,   3,  28,  33,  67, 114,  84,   0}
};

constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_MID =  -14;
constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_END =   -5;

constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -24;
constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_END =  -17;

constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_MID =  -11;
constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_END =  -34;

constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_MID =   -4;
constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_END =    3;

constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -15;
constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_END =  -11;

constexpr SCORE_TYPE BLOCKER_VALUES_MID[6] = {   0, -13,   3,  22,   9, -76};

constexpr SCORE_TYPE BLOCKER_VALUES_END[6] = {   0, -47, -71, -34,  -9, -77};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_MID[6] = {   0,  -1,  -9,  19,  20,  -6};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_END[6] = {   0, -17, -22, -18, -15, -30};

constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_MID =   16;
constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_END =   18;

constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_MID =   47;
constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_END =    1;

constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_MID =    3;
constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_END =   27;

constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_MID =    0;
constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_END =   21;

constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_MID =  -21;
constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_END =   -1;

constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_MID =  -20;
constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_END =   -8;

constexpr SCORE_TYPE BISHOP_PAIR_BONUS_MID =   26;
constexpr SCORE_TYPE BISHOP_PAIR_BONUS_END =   62;

constexpr SCORE_TYPE TEMPO_BONUS_MID =   16;
constexpr SCORE_TYPE TEMPO_BONUS_END =   20;

constexpr double MOBILITY_COEFFICIENTS_MID[6] = {      0,      3.46,      3.83,      1.36,      0.798,      0};

constexpr double MOBILITY_COEFFICIENTS_END[6] = {      0,      1.65,      2.8,      1.04,      1.76,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -5.46,      0,      0,      0,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,      1.11,      0,      0,      0,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -1.86,      0.332,     -5.53,     -8.7,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,      0.416,      1.25,      3.17,    -10.5,      0};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_MID[3][8] = {
        {   5,   3, -28,   0,   0,  -8, -15,   4},
        {   2, -38, -32,   0,   0, -14, -15,   4},
        { -42, -67, -62,   0,   0, -27, -50, -29}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_END[3][8] = {
        {  13,   7,  20,   0,   0,  -5,   9,  19},
        {  28,  28,  20,   0,   0, -18,   7,  21},
        {  30,  21,  16,   0,   0, -10,  21,  34}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_MID[3][8] = {
        {  -2, -23,  -5,   0,   0,  -4, -15,   3},
        {  -3,  -8, -33,   0,   0, -31,  -3, -15},
        {  -4, -56,-142,   0,   0, -77, -52, -35}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_END[3][8] = {
        { -14,  -1,  -8,   0,   0,  -5,  -6, -15},
        {  29,  25,  20,   0,   0,  23,  22,  21},
        {  62,  80,  65,   0,   0,  49,  75,  78}
};
#endif //ANTARESCHESSENGINE_CONSTANTS_H