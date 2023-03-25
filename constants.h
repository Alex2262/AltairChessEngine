
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

constexpr SCORE_TYPE MAX_MINOR_PIECE_VALUE_MID = 410;
constexpr SCORE_TYPE PIECE_VALUES_MID[6] = { 104, 410, 387, 566,1323,   0};

constexpr SCORE_TYPE PIECE_VALUES_END[6] = { 121, 331, 335, 616,1225,   0};

constexpr SCORE_TYPE PAWN_PST_MID[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        122, 157,  71, 131,  89, 166,  49,  10,
        -5,  10,  38,  49,  73,  72,  33,   3,
        -6,  13,  17,  39,  39,  31,  33,  -6,
        -11,  -5,   2,  15,  17,  19,   7, -20,
        -10, -11,   4,   7,  15,  13,  24,  -9,
        -15, -15, -13,  -8,  -8,  26,  22,  -7,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE PAWN_PST_END[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        108,  92,  88,  32,  43,  43,  95, 128,
        84,  75,  36,  -9, -17,  25,  63,  90,
        39,  24,   9, -21, -13,  10,  25,  37,
        20,  14,  -2,  -8,  -9,  -1,  10,  16,
        10,  12,  -1,   0,   8,   2,   5,  11,
        25,  21,  25,  11,  26,   7,  14,  21,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE KNIGHT_PST_MID[64] = {
        -147, -67, -20,  39, 137,-103,  25, -79,
        32,  14,  84,  73,  58,  89,   5,  39,
        23,  79,  73,  95, 117, 143,  99,  78,
        71,  61,  66,  89,  59,  70,  43,  66,
        48,  43,  53,  55,  59,  46,  64,  32,
        32,  35,  41,  42,  49,  33,  32,  16,
        7,  14,  27,  34,  24,  25,  14,  28,
        -78,  16,  -4,  -1,  14,   3,   2, -32
};

constexpr SCORE_TYPE KNIGHT_PST_END[64] = {
        -32,  -3,  23,  -4, -12,  16, -43, -86,
        -11,  18,   6,  34,  25,  -4,   9, -21,
        -4,  13,  39,  41,  17,  16,   1, -27,
        8,  40,  52,  55,  64,  54,  45,  16,
        13,  22,  47,  61,  53,  57,  35,  26,
        -25,  16,  15,  39,  36,  17,  11,  15,
        -15,   4,   4,  25,  36,   8,  16, -18,
        8, -18,   8,  25,  10,  19,   2, -34
};

constexpr SCORE_TYPE BISHOP_PST_MID[64] = {
        -33,   2,-103, -55, -45, -86,  -7,  24,
        -27,  -1,  -5, -20,  15,  32,   9, -24,
        2,  16,  34,  22,  40,  43,  50,  19,
        -9,  15,   1,  46,  31,  43,  16,  11,
        6,  11,  15,  29,  40,   4,  16,  32,
        14,  27,  20,  21,  17,  28,  28,  34,
        20,  30,  30,  16,  26,  21,  51,  24,
        33,  22,   6,   7,  -8,   9,   3,  12
};

constexpr SCORE_TYPE BISHOP_PST_END[64] = {
        16,  17,  40,  35,  37,  33,  14,   7,
        33,  24,  33,  29,  34,  20,  22,  26,
        29,  30,  23,  29,  20,  35,  34,  38,
        24,  38,  38,  30,  32,  25,  47,  35,
        13,  26,  31,  32,  20,  34,  23,   8,
        5,  20,  24,  23,  37,  23,  18,  11,
        4,  -3,   9,  19,  15,   5,  17,  -4,
        -15,   9,  28,  21,  24,  26,  25,  -6
};

constexpr SCORE_TYPE ROOK_PST_MID[64] = {
        39,  49,  19,  36,  69,  57,  57, 111,
        26,   9,  38,  47,  50,  98,  39,  59,
        1,  16,  25,  20,  37,  74, 103,  49,
        7,  -2,  12,  24,   1,  29, -10,   3,
        -10, -16, -12,  -7,  -6,  12,  21, -10,
        -5,   0,  -3,   1,  -4,  12,  25,   0,
        -4,  13,   4,   7,  14,  28,  27, -43,
        32,  28,  31,  36,  32,  29,   8,  23
};

constexpr SCORE_TYPE ROOK_PST_END[64] = {
        68,  67,  74,  71,  61,  65,  62,  53,
        70,  82,  74,  76,  66,  50,  67,  59,
        67,  65,  64,  68,  59,  55,  43,  46,
        59,  61,  69,  63,  70,  64,  65,  62,
        55,  62,  62,  65,  60,  47,  48,  49,
        36,  43,  43,  46,  49,  39,  33,  31,
        34,  28,  43,  40,  38,  29,  24,  47,
        34,  35,  37,  31,  30,  40,  40,  21
};

constexpr SCORE_TYPE QUEEN_PST_MID[64] = {
        -31, -57, -11, -15,  41,  62,  70,  43,
        -10, -54, -38, -48, -60,  28,  28,  40,
        -2, -15,  -8, -40, -15,  78,  64,  18,
        3, -10, -15, -26, -24,  -8, -13,   0,
        23,  15,  10,  -9,  -3,   1,  10,   3,
        29,  46,  33,  20,  12,  16,  23,  13,
        37,  49,  54,  38,  39,  40,  31,  12,
        68,  49,  56,  51,  39,  27,  33,   5
};

constexpr SCORE_TYPE QUEEN_PST_END[64] = {
        51, 104,  71,  54,  54,  40,  32,  61,
        46,  62,  68,  72,  94,  56,  59,  53,
        37,  38,  23,  83,  78,  40,  42,  97,
        35,  58,  53,  64,  80,  74,  92,  96,
        32,  61,  41,  71,  41,  45,  27,  49,
        52,  -7,  32,  10,  15,  13,   0,  43,
        47,   9, -11,   7, -12, -44, -49,  10,
        38,  26,   9,  64,  -3, -30, -22, -22
};

constexpr SCORE_TYPE KING_PST_MID[64] = {
        -62, 232, 251,  80,-166, -79,  60, -54,
        188, 143, 140,  29,   9,  48, -44,-158,
        79, 158, 135, -48,  13,  88, 124, -41,
        44,  72,  73, -76,-119, -16, -24,-124,
        -19, 104,  30,-124,-121, -72, -44, -96,
        2,  14,  -5,-106, -93, -52, -12, -37,
        22,  18,   0,-126, -95, -62,   0,  -3,
        26,  44,   9,-129, -51, -88,  -5, -17
};

constexpr SCORE_TYPE KING_PST_END[64] = {
        -106, -98, -88,   2,  45,  10, -17, -34,
        -66, -13, -13,  63,  66,  22,  38,  16,
        -12,  -8,   4,  77,  67,  37,  31,  12,
        -28,   4,  11,  97,  95,  39,  35,  15,
        -37, -32,   4,  97,  94,  37,  18,  -9,
        -46, -17,  -2,  80,  75,  22,   0, -22,
        -56, -35, -15,  64,  58,  13, -17, -41,
        -110, -74, -46,  37,   1, -11, -41, -81
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_MID[3][8] = {
        {   0,   0, -11,  -7,   4,  22,  41,   0},
        {   0,   3,   2,  -2,  21,  71, 332,   0},
        {   0,   3,  41,  -8,  50, 119, 421,   0}
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_END[3][8] = {
        {   0,   7,  19,  45,  75, 137, 173,   0},
        {   0,   3,  15,  41,  90, 163, 125,   0},
        {   0,   3,  30,  36,  74, 126,  61,   0}
};

constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_MID =  -17;
constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_END =   -7;

constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -27;
constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_END =  -17;

constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_MID =  -12;
constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_END =  -34;

constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_MID =   -9;
constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_END =   -1;

constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -15;
constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_END =   -9;

constexpr SCORE_TYPE PHALANX_PAWN_BONUS_MID[8] = {   0,  -9,  -7,  11,  25,  50,-130,   0};

constexpr SCORE_TYPE PHALANX_PAWN_BONUS_END[8] = {   0, -12,  -6,   5,  60, 138, 437,   0};

constexpr SCORE_TYPE BLOCKER_VALUES_MID[6] = {   0, -13,   3,  23,   9, -78};

constexpr SCORE_TYPE BLOCKER_VALUES_END[6] = {   0, -46, -72, -33,  -9, -78};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_MID[6] = {   0,  -1,  -9,  20,  21,  -4};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_END[6] = {   0, -17, -23, -19, -16, -33};

constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_MID =   17;
constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_END =   18;

constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_MID =   48;
constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_END =    1;

constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_MID =    3;
constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_END =   27;

constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_MID =    0;
constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_END =   21;

constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_MID =  -21;
constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_END =    0;

constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_MID =  -20;
constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_END =   -8;

constexpr SCORE_TYPE BISHOP_PAIR_BONUS_MID =   27;
constexpr SCORE_TYPE BISHOP_PAIR_BONUS_END =   63;

constexpr SCORE_TYPE TEMPO_BONUS_MID =   17;
constexpr SCORE_TYPE TEMPO_BONUS_END =   20;

constexpr double MOBILITY_COEFFICIENTS_MID[6] = {      0,      3.48,      3.87,      1.4,      0.797,      0};

constexpr double MOBILITY_COEFFICIENTS_END[6] = {      0,      1.71,      2.87,      1.08,      1.82,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -5.61,      0,      0,      0,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,      1.15,      0,      0,      0,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -1.97,      0.29,     -5.69,     -8.89,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,      0.436,      1.24,      3.27,    -10.8,      0};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_MID[3][8] = {
        {   3,   2, -30,   0,   0,  -7, -14,   4},
        {  -1, -40, -33,   0,   0, -14, -15,   4},
        { -45, -70, -65,   0,   0, -27, -51, -31}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_END[3][8] = {
        {  12,   6,  19,   0,   0,  -5,   9,  18},
        {  28,  28,  19,   0,   0, -19,   7,  20},
        {  30,  21,  15,   0,   0, -10,  21,  35}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_MID[3][8] = {
        {  -2, -23,  -5,   0,   0,  -5, -16,   3},
        {  -1,  -7, -31,   0,   0, -33,  -4, -15},
        {  -4, -57,-148,   0,   0, -82, -57, -37}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_END[3][8] = {
        { -14,  -1,  -7,   0,   0,  -5,  -5, -15},
        {  30,  26,  21,   0,   0,  25,  24,  22},
        {  64,  85,  69,   0,   0,  51,  80,  82}
};

#endif //ANTARESCHESSENGINE_CONSTANTS_H