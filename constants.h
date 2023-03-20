
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



constexpr SCORE_TYPE PIECE_VALUES_MID[6] = { 107, 430, 404, 604,1413,   0};

constexpr SCORE_TYPE PIECE_VALUES_END[6] = { 126, 340, 350, 651,1285,   0};

constexpr SCORE_TYPE PAWN_PST_MID[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        76, 125,  16,  76,  34, 128,  -1, -47,
        -5,  15,  41,  51,  79,  88,  34,   3,
        -4,  14,  21,  45,  46,  34,  35,  -3,
        -7,   0,  10,  26,  27,  23,   9, -18,
        -8, -10,   6,   9,  19,  12,  28,  -7,
        -17, -15, -16,  -7,  -9,  23,  21,  -9,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE PAWN_PST_END[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        121,  96,  96,  42,  54,  48, 106, 139,
        85,  76,  36,  -7, -15,  24,  66,  93,
        40,  27,  12, -19, -11,  14,  29,  39,
        21,  15,  -3, -10,  -9,   0,  13,  18,
        10,  13,  -1,   0,   8,   1,   5,  10,
        25,  19,  24,  13,  25,   6,  13,  20,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE KNIGHT_PST_MID[64] = {
        -150, -69,  -8,  19, 134,-105,  27, -81,
        37,  13,  91,  73,  62, 102,   3,  34,
        27,  91,  79, 104, 118, 149, 110,  83,
        75,  71,  74,  99,  68,  78,  50,  74,
        58,  51,  62,  64,  68,  53,  72,  39,
        41,  40,  49,  48,  59,  40,  42,  23,
        14,  21,  36,  43,  33,  34,  17,  37,
        -77,  25,  -5,   8,  22,   9,  11, -18
};

constexpr SCORE_TYPE KNIGHT_PST_END[64] = {
        -28,   3,  26,   6,  -6,  19, -39, -87,
        -6,  23,  12,  39,  29,   0,  17, -14,
        3,  17,  46,  47,  24,  21,   6, -25,
        12,  43,  59,  62,  70,  62,  49,  17,
        16,  30,  53,  66,  58,  62,  40,  31,
        -15,  23,  21,  46,  39,  20,  13,  19,
        -11,  10,  11,  29,  41,  10,  28, -17,
        12, -18,  16,  29,  14,  22,   2, -27
};

constexpr SCORE_TYPE BISHOP_PST_MID[64] = {
        -30,   8,-105, -59, -58, -85,   8,  31,
        -28,   4,  -7, -27,  24,  35,  14, -20,
        1,  23,  35,  22,  44,  52,  57,  19,
        -8,  16,   8,  52,  35,  46,  21,  14,
        8,  13,  16,  35,  46,   9,  17,  41,
        21,  34,  25,  26,  24,  37,  30,  43,
        30,  36,  38,  21,  31,  26,  59,  25,
        35,  36,  12,  15,  -5,  14,   6,  13
};

constexpr SCORE_TYPE BISHOP_PST_END[64] = {
        18,  19,  44,  40,  46,  35,  13,   4,
        35,  26,  40,  36,  34,  27,  25,  30,
        31,  31,  27,  35,  25,  35,  35,  42,
        28,  43,  41,  33,  34,  30,  53,  39,
        17,  30,  37,  36,  24,  38,  28,  11,
        9,  26,  29,  27,  42,  26,  25,  12,
        5,  -1,  10,  23,  19,   9,  20,   1,
        -11,  11,  32,  23,  29,  31,  29,  -1
};

constexpr SCORE_TYPE ROOK_PST_MID[64] = {
        41,  51,  22,  36,  62,  35,  41,  71,
        16,  10,  33,  41,  55,  97,  30,  60,
        -5,  11,  17,  16,  27,  75, 107,  38,
        -1, -13,   4,  22,  -2,  25,  -9,  -4,
        -13, -23, -16, -15,  -9,   9,  19, -15,
        -9,  -8,  -7,  -5,  -8,   9,  23,  -2,
        -6,   7,  -1,   4,  12,  24,  27, -45,
        32,  29,  30,  36,  32,  28,   4,  21
};

constexpr SCORE_TYPE ROOK_PST_END[64] = {
        63,  61,  69,  64,  62,  66,  62,  61,
        70,  75,  71,  74,  60,  47,  68,  57,
        63,  63,  64,  66,  57,  49,  37,  44,
        56,  61,  65,  58,  67,  62,  59,  60,
        49,  59,  59,  60,  57,  42,  45,  44,
        32,  42,  37,  43,  43,  34,  29,  27,
        28,  22,  39,  35,  34,  26,  19,  41,
        27,  29,  31,  25,  25,  35,  35,  15
};

constexpr SCORE_TYPE QUEEN_PST_MID[64] = {
        -36, -48, -32, -21,  41,  64,  58,  49,
        -20, -64, -45, -52, -77,  10,  18,  45,
        -9, -19, -12, -54, -22,  84,  60,  14,
        -3, -18, -21, -31, -29, -12, -13,  -7,
        18,   9,   5, -14,  -8,  -7,   1,   4,
        22,  42,  32,  14,  10,  11,  18,   8,
        25,  44,  51,  35,  36,  35,  27,  14,
        61,  44,  54,  49,  37,  21,  31,   3
};

constexpr SCORE_TYPE QUEEN_PST_END[64] = {
        51,  91,  74,  46,  48,  26,  32,  50,
        46,  58,  66,  69,  97,  61,  60,  36,
        32,  31,  11,  83,  76,  32,  36,  96,
        29,  51,  52,  56,  75,  61,  83,  94,
        24,  61,  30,  65,  36,  44,  29,  30,
        52, -10,  24,   4,   8,   3,  -2,  48,
        56,   1, -12,   6, -21, -43, -52,  -2,
        41,  20,   8,  57, -13, -39, -38, -29
};

constexpr SCORE_TYPE KING_PST_MID[64] = {
        -70, 251, 255,  97,-161, -98,  49, -59,
        227, 141, 148,  32,   6,  44, -49,-196,
        85, 152, 150, -41,  25, 100, 133, -58,
        60,  70,  61, -79,-129, -29, -33,-150,
        -30, 107,  21,-130,-137, -81, -57,-104,
        10,  27,  -6,-115,-104, -55, -14, -50,
        35,  24,   3,-129,-100, -62,   2,  -3,
        27,  49,  11,-135, -51, -90,  -3, -12
};

constexpr SCORE_TYPE KING_PST_END[64] = {
        -118,-108, -92,   1,  46,  12, -12, -36,
        -78, -15, -16,  67,  71,  24,  37,  22,
        -19,  -9,   4,  81,  70,  40,  34,  17,
        -33,   3,  12, 104, 103,  42,  39,  20,
        -36, -34,   6, 104, 102,  40,  21,  -8,
        -50, -20,  -3,  86,  82,  24,   2, -19,
        -63, -40, -17,  70,  64,  14, -17, -41,
        -111, -78, -49,  41,   4, -10, -42, -85
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_MID[8] = {   0,   3,  -6,  -9,   9,  28, 107,   0};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_END[8] = {   0,   8,  18,  49,  86, 154, 181,   0};

constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_MID =  -17;
constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_END =   -4;

constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -28;
constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_END =  -19;

constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_MID =  -10;
constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_END =  -37;

constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_MID =   -5;
constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_END =    4;

constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -17;
constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_END =  -10;

constexpr SCORE_TYPE BLOCKER_VALUES_MID[6] = {   0, -11,   7,  24,  12, -88};

constexpr SCORE_TYPE BLOCKER_VALUES_END[6] = {   0, -53, -76, -38,  -5, -81};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_MID[6] = {   0,   1, -11,  27,  30, -21};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_END[6] = {   0, -22, -24, -25, -33, -31};

constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_MID =   17;
constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_END =   21;

constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_MID =   51;
constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_END =    1;

constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_MID =    4;
constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_END =   29;

constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_MID =   -1;
constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_END =   22;

constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_MID =  -22;
constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_END =   -1;

constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_MID =  -22;
constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_END =   -8;

constexpr SCORE_TYPE BISHOP_PAIR_BONUS_MID =   30;
constexpr SCORE_TYPE BISHOP_PAIR_BONUS_END =   68;

constexpr SCORE_TYPE TEMPO_BONUS_MID =   19;
constexpr SCORE_TYPE TEMPO_BONUS_END =   22;

constexpr double MOBILITY_COEFFICIENTS_MID[6] = {      0,      3.88,      4.27,      1.58,      0.843,      0};

constexpr double MOBILITY_COEFFICIENTS_END[6] = {      0,      1.92,      2.91,      1.16,      2.1,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -5.93,      0,      0,      0,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,      1.2,      0,      0,      0,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -2.17,      0.314,     -6.32,     -9.13,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,      0.563,      1.34,      3.72,    -11.7,      0};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_MID[3][8] = {
        {   9,   1, -34,   0,   0, -11, -17,   5},
        {   3, -46, -36,   0,   0, -16, -15,   7},
        { -39, -75, -70,   0,   0, -30, -54, -30}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_END[3][8] = {
        {  12,  10,  23,   0,   0,  -3,  10,  19},
        {  29,  34,  20,   0,   0, -18,   7,  21},
        {  30,  25,  18,   0,   0,  -8,  24,  37}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_MID[3][8] = {
        {  -7, -24,  -5,   0,   0,  -2, -16,   4},
        {  -8,  -6, -30,   0,   0, -34,  -3, -15},
        {  -6, -44,-128,   0,   0, -69, -57, -45}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_END[3][8] = {
        { -15,  -2,  -8,   0,   0,  -6,  -7, -16},
        {  32,  26,  23,   0,   0,  25,  22,  23},
        {  63,  75,  58,   0,   0,  51,  77,  86}
};
#endif //ANTARESCHESSENGINE_CONSTANTS_H