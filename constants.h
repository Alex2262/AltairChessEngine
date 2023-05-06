
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
constexpr SCORE_TYPE PIECE_VALUES_MID[6] = { 100, 382, 409, 592,1448,   0};

constexpr SCORE_TYPE PIECE_VALUES_END[6] = { 128, 354, 348, 685,1268,   0};

constexpr SCORE_TYPE PAWN_PST_MID[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        145, 159, 106, 164, 105, 167,  28,  14,
        4,  20,  48,  64,  88,  86,  57,   6,
        -2,  16,  15,  30,  37,  38,  38,  -6,
        -8,  -8,   5,  11,  17,  21,   9, -17,
        -21, -22, -13,  -8,   2,  -5,   8, -19,
        -13,  -6, -13,  -8,  -2,  26,  32,  -7,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE PAWN_PST_END[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        112,  98,  87,  19,  43,  46, 112, 132,
        89,  80,  38, -12, -22,  24,  66, 100,
        43,  23,   9, -19, -12,   9,  26,  40,
        18,  14,  -7, -11, -12,  -6,   9,  15,
        12,  11,   1,  -2,   6,   3,   3,  12,
        25,  18,  23,   6,  23,   5,  14,  19,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE KNIGHT_PST_MID[64] = {
        -119, -58, -18,  45, 131,-108,  19, -60,
        50,  22,  64,  58,  63,  67,  12,  44,
        28,  64,  59,  75,  87, 129,  81,  92,
        81,  69,  53,  71,  41,  53,  41,  77,
        60,  45,  42,  39,  43,  29,  62,  44,
        39,  23,  13,  16,  19,   3,  26,  27,
        16,  22,  11,  14,   8,  15,  26,  44,
        -58,  24,  -5,  -2,  16,   4,  14,  -6
};

constexpr SCORE_TYPE KNIGHT_PST_END[64] = {
        -13,  21,  49,  22,  19,  46, -16, -66,
        17,  43,  28,  60,  46,  20,  32,   9,
        20,  32,  49,  55,  36,  28,  25,  -8,
        30,  49,  56,  66,  71,  62,  56,  39,
        36,  37,  54,  68,  64,  56,  44,  41,
        -6,  33,  32,  55,  47,  26,  18,  31,
        20,  39,  24,  59,  67,  27,  35,  16,
        46,  22,  44,  54,  40,  48,  35,   2
};

constexpr SCORE_TYPE BISHOP_PST_MID[64] = {
        -31,  12, -96, -68, -61, -84,   8,  49,
        -17,   4,   6, -10,  -5,  38,  -4, -28,
        28,  36,  50,  22,  45,  58,  62,  27,
        2,  23,  10,  51,  32,  38,  18,  12,
        13,  17,  24,  30,  46,  11,  18,  39,
        22,  34,  27,  23,  24,  32,  40,  46,
        34,  42,  40,  25,  25,  37,  65,  44,
        48,  31,  26,  18,  12,  24,  15,  34
};

constexpr SCORE_TYPE BISHOP_PST_END[64] = {
        31,  31,  59,  59,  58,  50,  32,  19,
        51,  37,  44,  40,  49,  33,  34,  45,
        34,  33,  24,  33,  22,  37,  38,  53,
        38,  36,  37,  25,  28,  26,  50,  53,
        22,  25,  26,  28,  16,  30,  23,  18,
        14,  19,  23,  26,  33,  19,  12,  15,
        8,   4,  17,  28,  30,  11,  30,   0,
        -11,  19,  47,  36,  33,  42,  39,   2
};

constexpr SCORE_TYPE ROOK_PST_MID[64] = {
        45,  42,   7,  13,  40,  43,  17,  97,
        30,  10,  35,  44,  38,  69,  12,  54,
        9,  30,  39,  38,  43,  78,  97,  55,
        19,  16,  33,  43,  19,  49,   0,  19,
        -10, -14,  -3,   1,   2,  11,  15,   0,
        -9,  -5, -12,  -7,  -8,   6,  14,  -3,
        -15,   5, -10,  -5,   3,  15,  17, -49,
        13,   9,  12,  18,  14,  11,  -1,  13
};

constexpr SCORE_TYPE ROOK_PST_END[64] = {
        56,  61,  70,  72,  63,  60,  65,  50,
        54,  64,  59,  61,  55,  38,  59,  46,
        48,  42,  41,  40,  36,  34,  28,  28,
        42,  41,  46,  38,  45,  39,  46,  44,
        46,  54,  50,  52,  47,  33,  36,  35,
        29,  37,  39,  43,  42,  27,  30,  23,
        31,  25,  42,  38,  36,  25,  20,  43,
        34,  37,  37,  29,  29,  41,  38,  18
};

constexpr SCORE_TYPE QUEEN_PST_MID[64] = {
        -32, -32,  -9,  -6,  33,  57,  58,  20,
        2, -46, -37, -63, -94,   5,   5,  14,
        6,   6,  -6, -50, -42,  45,  48, -17,
        13,   6, -14, -32, -37, -18, -13, -10,
        25,  25,   7,  -6, -11,  -3,  11,   2,
        28,  56,  29,  14,  12,  12,  30,  11,
        32,  50,  50,  27,  23,  36,  26,   7,
        54,  34,  37,  33,  25,   9,  28, -12
};

constexpr SCORE_TYPE QUEEN_PST_END[64] = {
        15,  58,  45,  21,  26,  15,   3,  25,
        15,  53,  67,  71,  96,  50,  45,  37,
        12,  17,  21,  78,  72,  33,  24,  89,
        10,  45,  51,  67,  77,  66,  73,  73,
        5,  38,  39,  73,  51,  50,  27,  13,
        -4, -56,  19,  12,  17,  28,  -3,  12,
        -20, -42, -47,  10,   5, -42, -29, -11,
        -40, -34, -20,  63, -17, -31, -36, -33
};

constexpr SCORE_TYPE KING_PST_MID[64] = {
        -150, 225, 253,  66,-208, -73,  39, -32,
        202, 159, 163,  80,  30,  90, -49,-192,
        66, 183, 175, -10,  71, 131, 172, -49,
        32,  84, 101, -29, -76,  24,  27,-126,
        -20, 150,  63, -97, -79, -23,   3, -95,
        -18,  30,  14, -80, -51, -11,  18, -39,
        2,   5,  -9,-137,-101, -55,   3,  -3,
        -1,  21, -22,-154, -73,-104, -22, -30
};

constexpr SCORE_TYPE KING_PST_END[64] = {
        -100,-107, -93,  -4,  46,   5, -27, -60,
        -77,  -9,  -8,  52,  62,  12,  37,  14,
        -5,  -5,   6,  75,  61,  34,  22,   8,
        -22,   6,  15,  98,  96,  34,  25,  11,
        -39, -37,   7, 100,  97,  27,   6, -15,
        -41, -17,   1,  83,  72,  14,  -9, -27,
        -49, -29,  -7,  73,  66,  14, -21, -48,
        -113, -70, -37,  42,   7,  -9, -40, -92
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_MID[3][8] = {
        {   0,  -2,  -1,  -8,   9,  15,  26,   0},
        {   0,   3,   2,  -7,  20,  53, 347,   0},
        {   0,   3,  52, -14,  39,  53, 539,   0}
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_END[3][8] = {
        {   0,  13,  24,  56,  85, 159, 204,   0},
        {   0,   3,  18,  46,  96, 184, 134,   0},
        {   0,   3,  18,  28,  66, 144, -31,   0}
};

constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_MID =  -10;
constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_END =    1;

constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -20;
constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_END =  -16;

constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_MID =   -7;
constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_END =  -37;

constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_MID =   -6;
constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_END =    2;

constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -15;
constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_END =   -9;

constexpr SCORE_TYPE PHALANX_PAWN_BONUS_MID[8] = {   0,   2,  21,  24,  41,  27, -67,   0};

constexpr SCORE_TYPE PHALANX_PAWN_BONUS_END[8] = {   0,  -2,   4,  15,  72, 162, 453,   0};

constexpr SCORE_TYPE PIECE_SUPPORT_MID[6][6] = {
        {  20,   5,   8,   4,  -7, -80},
        {  11,  18,  16,  19,  23,  15},
        {   4,  16, -33,  10,  16,   7},
        {   5,  16,  10,  12,  12,  12},
        {  -1,   7,   5,   7,  39,   4},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE PIECE_SUPPORT_END[6][6] = {
        {  14,  26,  32,   7,   0,  31},
        {   8,  15,   6,   3,  -7,   1},
        {   2,  18,  57,  13,  16,  11},
        {   3,   2,   7,  13,  41,  -6},
        {   8,   6, -10,  -9,-538, -13},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE PIECE_THREAT_MID[6][6] = {
        {  10,  79,  67, 109,  70, 198},
        {  11,  20,  50,  75,  65, 134},
        {   8,  41,  20,  56,  65,  79},
        {  -7,   7,  12,  10,  66, 138},
        {  -6,   4,   1,  -5,  10,  80},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE PIECE_THREAT_END[6][6] = {
        {  10,  30,  70,   1,  36,  18},
        {  24,  20,  53,  27,  15,  33},
        {  25,  60,  20,  42,  69,  84},
        {  26,  33,  39,  10,  50,  33},
        {  15,  14,  39,  36,  10, 109},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE BLOCKER_VALUES_MID[6] = {   0,  -5,   5,  14,  14, -67};

constexpr SCORE_TYPE BLOCKER_VALUES_END[6] = {   0, -63, -87, -28,  -7, -92};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_MID[6] = {   0,   4,  -1,  15,  21,   4};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_END[6] = {   0, -25, -23, -20, -10, -36};

constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_MID =   19;
constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_END =    7;

constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_MID =   42;
constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_END =    2;

constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_MID =    3;
constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_END =   29;

constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_MID =   -6;
constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_END =   33;

constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_MID =  -21;
constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_END =    1;

constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_MID =  -13;
constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_END =  -10;

constexpr SCORE_TYPE BISHOP_PAIR_BONUS_MID =   27;
constexpr SCORE_TYPE BISHOP_PAIR_BONUS_END =   72;

constexpr SCORE_TYPE TEMPO_BONUS_MID =   26;
constexpr SCORE_TYPE TEMPO_BONUS_END =   25;

constexpr double MOBILITY_COEFFICIENTS_MID[6] = {      0,      5.83,      3.2,      1.78,      0.672,      0};

constexpr double MOBILITY_COEFFICIENTS_END[6] = {      0,      1.54,      2.85,      1.1,      0.229,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -5.8,      0,      0,      0,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,      0.827,      0,      0,      0,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -1.02,      -0.165,     -4.35,    -9.62,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,     -1.07,      1.79,      4.06,      6.29,      0};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_MID[3][8] = {
        {  -1,  -1, -33,   0,   0, -14, -13,   4},
        {   0, -42, -34,   0,   0, -20, -21,   1},
        { -41, -63, -58,   0,   0, -33, -55, -25}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_END[3][8] = {
        {  13,   6,  19,   0,   0,  -4,  11,  20},
        {  32,  31,  21,   0,   0, -17,  13,  24},
        {  33,  19,  14,   0,   0,  -7,  27,  38}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_MID[3][8] = {
        {   0, -27,  -4,   0,   0,  -4, -18,   9},
        {  -7, -12, -36,   0,   0, -31,   0, -13},
        { -15, -90,-162,   0,   0, -91, -66, -49}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_END[3][8] = {
        { -15,  -1,  -9,   0,   0,  -6,  -6, -17},
        {  36,  33,  21,   0,   0,  26,  23,  23},
        {  76, 104,  81,   0,   0,  56,  90,  94}
};

constexpr SCORE_TYPE KING_RING_ATTACKS_MID[2][6] = {
        {   0,  13,  17,  26,  19,   0},
        {   0,   8,   3,   4,   6,   0}
};

constexpr SCORE_TYPE KING_RING_ATTACKS_END[2][6] = {
        {   0, -10,  -4,  -7,  12,   0},
        {   0,   1,   0,   1,  14,   0}
};

#endif //ANTARESCHESSENGINE_CONSTANTS_H