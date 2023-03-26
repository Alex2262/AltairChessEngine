
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

constexpr SCORE_TYPE MAX_MINOR_PIECE_VALUE_MID = 411;
constexpr SCORE_TYPE PIECE_VALUES_MID[6] = {  94, 411, 393, 580,1352,   0};

constexpr SCORE_TYPE PIECE_VALUES_END[6] = { 114, 325, 329, 620,1235,   0};

constexpr SCORE_TYPE PAWN_PST_MID[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        133, 141,  81, 137,  87, 127,  22,  16,
        4,  18,  43,  57,  82,  71,  45,   8,
        2,  15,  17,  36,  37,  34,  36,   1,
        -5,  -2,   5,  15,  21,  22,  11, -14,
        -14, -21,  -8,  -6,   3,   0,   7, -15,
        -11,  -7,  -9,  -9,  -3,  29,  27,  -6,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE PAWN_PST_END[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        106,  98,  88,  32,  46,  54, 103, 129,
        82,  74,  36,  -9, -18,  26,  62,  91,
        37,  21,   7, -21, -12,   9,  24,  36,
        16,  10,  -7, -13, -13,  -6,   6,  13,
        8,  10,  -2,   0,   5,   0,   3,   9,
        23,  18,  20,   8,  22,   3,  12,  19,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE KNIGHT_PST_MID[64] = {
        -143, -74, -19,  44, 142,-100,  16, -77,
        39,  20,  88,  79,  65,  93,   8,  47,
        30,  84,  81, 100, 127, 153, 110,  87,
        78,  68,  70,  95,  64,  75,  51,  74,
        52,  48,  60,  63,  67,  52,  72,  37,
        36,  39,  45,  47,  54,  37,  36,  20,
        10,  20,  30,  37,  27,  29,  21,  32,
        -68,  18,   1,   2,  19,   6,   5, -30
};

constexpr SCORE_TYPE KNIGHT_PST_END[64] = {
        -28,   3,  28,   0,  -8,  20, -37, -79,
        -6,  20,   9,  36,  28,  -2,  12, -18,
        -2,  13,  37,  38,  15,  11,   0, -25,
        10,  34,  46,  50,  58,  49,  39,  17,
        14,  20,  42,  54,  51,  49,  29,  25,
        -24,  14,  11,  39,  30,  12,   4,  14,
        -11,   8,   7,  30,  42,  12,  20, -11,
        12,  -9,  13,  31,  15,  25,   7, -29
};

constexpr SCORE_TYPE BISHOP_PST_MID[64] = {
        -34,   2, -97, -57, -42, -87,  -5,  28,
        -21,   6,   0, -21,  17,  38,  16, -19,
        24,  25,  42,  26,  52,  64,  77,  41,
        -2,  26,   6,  53,  36,  55,  27,  20,
        11,  16,  22,  35,  49,   7,  21,  37,
        17,  29,  24,  25,  19,  32,  28,  37,
        25,  33,  33,  20,  29,  24,  55,  27,
        39,  26,   8,  12,  -3,  11,   8,  19
};

constexpr SCORE_TYPE BISHOP_PST_END[64] = {
        17,  18,  40,  36,  38,  33,  15,   9,
        34,  21,  31,  28,  33,  17,  19,  27,
        22,  23,  15,  22,  12,  26,  24,  35,
        24,  25,  29,  19,  21,  16,  40,  37,
        11,  18,  23,  21,  12,  27,  15,   8,
        5,  14,  17,  20,  29,  16,   9,  12,
        5,  -1,  10,  20,  16,   6,  20,  -2,
        -12,  11,  33,  23,  26,  32,  27,  -3
};

constexpr SCORE_TYPE ROOK_PST_MID[64] = {
        41,  51,  20,  37,  71,  59,  61, 108,
        27,  11,  39,  49,  52, 100,  38,  62,
        2,  18,  28,  21,  44,  80, 112,  55,
        8,   2,  15,  29,   5,  35,  -4,   5,
        -8, -13,  -8,  -3,  -1,  16,  26,  -8,
        -4,   3,  -2,   5,  -2,  15,  26,   3,
        -4,  14,   6,   9,  15,  29,  28, -43,
        32,  29,  32,  36,  33,  28,   9,  22
};

constexpr SCORE_TYPE ROOK_PST_END[64] = {
        67,  65,  73,  69,  60,  63,  60,  52,
        69,  79,  73,  74,  64,  47,  65,  56,
        65,  63,  62,  66,  56,  52,  40,  44,
        57,  59,  67,  60,  67,  62,  62,  60,
        54,  61,  60,  61,  58,  44,  45,  47,
        35,  41,  42,  45,  45,  36,  31,  27,
        33,  27,  42,  39,  38,  28,  23,  46,
        33,  34,  36,  30,  29,  41,  39,  20
};

constexpr SCORE_TYPE QUEEN_PST_MID[64] = {
        -37, -60, -11, -17,  48,  69,  75,  34,
        -10, -54, -36, -43, -59,  33,  32,  43,
        2,  -9,  -3, -35,  -4,  87,  82,  23,
        4,  -2,  -9, -17, -18,   2,  -6,   7,
        22,  20,  15,  -3,   2,   7,  15,   4,
        31,  49,  38,  24,  18,  22,  32,  17,
        34,  46,  51,  36,  36,  38,  29,   9,
        66,  46,  51,  46,  37,  25,  32,   0
};

constexpr SCORE_TYPE QUEEN_PST_END[64] = {
        57, 108,  72,  57,  51,  37,  31,  68,
        47,  63,  66,  69,  95,  54,  58,  52,
        33,  36,  21,  82,  74,  38,  33,  94,
        37,  54,  52,  61,  80,  71,  90,  88,
        34,  60,  41,  71,  41,  43,  24,  50,
        51,  -8,  31,   9,  11,   8,  -9,  38,
        52,  17,  -3,  15,  -6, -40, -44,  12,
        42,  32,  18,  73,   0, -26, -21, -20
};

constexpr SCORE_TYPE KING_PST_MID[64] = {
        -69, 236, 253,  82,-162, -81,  66, -55,
        192, 152, 144,  34,  13,  52, -36,-152,
        82, 168, 143, -42,  21,  97, 136, -38,
        48,  93,  87, -69,-105,  -2,  -3,-120,
        -19, 117,  45,-119,-111, -57, -29, -97,
        3,  31,   7,-100, -82, -42,  -4, -35,
        19,  17,  -1,-131, -99, -65,  -2,  -6,
        24,  41,   4,-136, -59, -93, -10, -21
};

constexpr SCORE_TYPE KING_PST_END[64] = {
        -103,-100, -88,   0,  43,  10, -20, -36,
        -66, -15, -14,  60,  64,  20,  34,  13,
        -12, -10,   3,  75,  65,  34,  27,  10,
        -28,  -1,  10,  95,  92,  36,  29,  14,
        -36, -34,   3,  96,  93,  32,  13,  -9,
        -45, -19,  -3,  79,  72,  20,  -3, -22,
        -53, -32, -13,  66,  61,  15, -16, -39,
        -107, -71, -43,  38,   4,  -9, -39, -80
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_MID[3][8] = {
        {   0,   1,  -2,  -7,   8,  18,  33,   0},
        {   0,   3,   4,  -3,  18,  60, 321,   0},
        {   0,   3,  39,  -7,  33,  70, 432,   0}
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_END[3][8] = {
        {   0,  11,  22,  50,  77, 141, 179,   0},
        {   0,   3,  14,  40,  86, 159, 120,   0},
        {   0,   3,  19,  23,  61, 116,  49,   0}
};

constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_MID =   -9;
constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_END =    1;

constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -19;
constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_END =  -12;

constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_MID =   -7;
constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_END =  -33;

constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_MID =   -6;
constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_END =    3;

constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -15;
constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_END =   -9;

constexpr SCORE_TYPE PHALANX_PAWN_BONUS_MID[8] = {   0,   1,  18,  21,  33,  52, -57,   0};

constexpr SCORE_TYPE PHALANX_PAWN_BONUS_END[8] = {   0,   1,   7,  17,  70, 147, 435,   0};

constexpr SCORE_TYPE PAWN_SUPPORT_MID[6] = {  18,   0,   2,   0, -10, -68};

constexpr SCORE_TYPE PAWN_SUPPORT_END[6] = {  14,  24,  26,  10,  14,  25};

constexpr SCORE_TYPE PAWN_THREAT_MID[6] = {  10,  64,  80, 102,  74, 225};

constexpr SCORE_TYPE PAWN_THREAT_END[6] = {  10,  31,  59,   1,  25,  16};

constexpr SCORE_TYPE BLOCKER_VALUES_MID[6] = {   0, -11,   4,  27,  16, -66};

constexpr SCORE_TYPE BLOCKER_VALUES_END[6] = {   0, -52, -77, -34, -11, -80};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_MID[6] = {   0,   1,  -5,  21,  24,  -3};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_END[6] = {   0, -22, -27, -19, -18, -33};

constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_MID =   17;
constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_END =   18;

constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_MID =   49;
constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_END =    0;

constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_MID =    3;
constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_END =   26;

constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_MID =    0;
constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_END =   21;

constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_MID =  -19;
constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_END =    0;

constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_MID =  -21;
constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_END =   -8;

constexpr SCORE_TYPE BISHOP_PAIR_BONUS_MID =   28;
constexpr SCORE_TYPE BISHOP_PAIR_BONUS_END =   65;

constexpr SCORE_TYPE TEMPO_BONUS_MID =   24;
constexpr SCORE_TYPE TEMPO_BONUS_END =   21;

constexpr double MOBILITY_COEFFICIENTS_MID[6] = {      0,      3.87,      4.08,      1.4,      0.762,      0};

constexpr double MOBILITY_COEFFICIENTS_END[6] = {      0,      1.99,      3.43,      1.06,      1.83,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -5.68,      0,      0,      0,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,      1.03,      0,      0,      0,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -2.11,      0.0728,     -5.86,     -8.77,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,      0.568,      1.33,      3.28,    -11.4,      0};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_MID[3][8] = {
        {   2,  -1, -30,   0,   0,  -7, -14,   4},
        {   1, -39, -31,   0,   0, -13, -20,   2},
        { -44, -69, -63,   0,   0, -23, -53, -30}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_END[3][8] = {
        {  12,   5,  18,   0,   0,  -6,   9,  18},
        {  28,  29,  19,   0,   0, -19,   9,  22},
        {  30,  21,  14,   0,   0, -11,  23,  36}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_MID[3][8] = {
        {  -3, -25,  -6,   0,   0,  -6, -15,   3},
        {  -2,  -7, -31,   0,   0, -31,   0, -17},
        {  -5, -59,-144,   0,   0, -88, -56, -43}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_END[3][8] = {
        { -13,  -1,  -7,   0,   0,  -5,  -6, -15},
        {  30,  25,  20,   0,   0,  24,  22,  22},
        {  65,  84,  68,   0,   0,  51,  79,  83}
};


#endif //ANTARESCHESSENGINE_CONSTANTS_H