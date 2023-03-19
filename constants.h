
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

constexpr int MVV_LVA_VALUES[6] = { 113, 447, 426, 578,1404,   0};

constexpr double KING_PAWN_SHIELD_COEFFICIENTS[8] = {0.8, 1.0, 0.6, 0.0, 0.0, 0.3, 1.0, 0.5};
constexpr int KING_PAWN_SHIELD_OUR_PENALTIES[3] = {-6, -14, -23};
constexpr int KING_PAWN_SHIELD_OPP_PENALTIES[3] = {-19, -8, -16};

constexpr SCORE_TYPE PIECE_ATTACK_MOBILITY[6] = {6, 8, 8, 10, 14, 35};
constexpr SCORE_TYPE PIECE_ATTACK_MOBILITY_PENALTY[6] = {0, 2, 1, 3, 4, 0};

constexpr double OUR_KING_DISTANCE_COEFFICIENTS_MID[6] = {0.0, -1.0, 0.0, 0.0, 0.0, 0.0};
constexpr double OUR_KING_DISTANCE_COEFFICIENTS_END[6] = {0.0, -0.3, 0.0, 0.0, 0.0, 0.0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_MID[6] = {0.0, -2.6, -0.7, -1.8, -0.7, 0.0};
constexpr double OPP_KING_DISTANCE_COEFFICIENTS_END[6] = {0.0, -1.2, -0.2, -1.1, -1.0, 0.0};

constexpr SCORE_TYPE PIECE_VALUES_MID[6] = { 113, 447, 426, 578,1404,   0};

constexpr SCORE_TYPE PIECE_VALUES_END[6] = { 107, 334, 331, 611,1036,   0};

constexpr SCORE_TYPE PAWN_PST_MID[64] = {
           0,   0,   0,   0,   0,   0,   0,   0,
          47, 104,  32,  71,  37, 132, -15, -86,
          19,  20,  41,  43,  92, 122,  58,  23,
          -2,  10,  20,  37,  34,  34,  23,  -5,
         -16,  -9,   8,  22,  27,  25,   9, -13,
          -7, -11,   5,   1,  14,  18,  35,   5,
         -19, -12, -16,  -7,  -9,  41,  34,  -3,
           0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE PAWN_PST_END[64] = {
           0,   0,   0,   0,   0,   0,   0,   0,
         126, 100,  87,  50,  70,  40, 106, 142,
          65,  58,  30,  -6, -25,  -2,  35,  43,
          40,  27,  12, -11,  -3,   6,  21,  25,
          27,  21,   6,  -4,  -2,  -1,   8,   9,
          12,  16,   2,  13,  12,   4,  -3,  -2,
          24,  17,  21,  19,  27,   7,   1,  -4,
           0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE KNIGHT_PST_MID[64] = {
        -205,-126, -54, -67,  74,-125, -43,-131,
        -104, -68,  38,  25, -16,  51, -31, -27,
         -48,  62,  18,  49,  77, 123,  80,  43,
          12,  33,  18,  67,  45,  75,  26,  45,
          18,  32,  32,  30,  45,  35,  42,  21,
          15,  10,  31,  31,  44,  36,  46,  16,
          10, -19,  14,  36,  32,  42,   5,  21,
        -106,  20, -25,  -3,  28,   1,  17,   8
};

constexpr SCORE_TYPE KNIGHT_PST_END[64] = {
         -24,  -9,  20,  -5, -18,  -3, -48, -88,
           5,  27,   1,  26,  20, -11,   4, -37,
          -3,   1,  39,  34,  11,   2,  -7, -34,
           6,  29,  52,  45,  45,  29,  27,  -3,
           7,  13,  39,  52,  39,  38,  23,  -1,
          -6,  25,  17,  34,  32,   8,  -2, -12,
         -22,   4,  17,  15,  23,  -1,   0, -30,
          23, -25,   7,  14,  -2,   7, -24, -56
};

constexpr SCORE_TYPE BISHOP_PST_MID[64] = {
         -21, -10,-150,-101, -68, -71, -25,  22,
         -37, -26, -54, -64,  15,   7, -23, -66,
         -16,  17,   0,  10,  -4,  48,  19,   2,
           0,  12,   5,  33,  17,  28,  10,   6,
          11,  21,  15,  23,  37,   6,  16,  27,
          22,  37,  30,  26,  28,  50,  32,  35,
          36,  46,  39,  26,  38,  39,  70,  27,
         -12,  33,  25,  15,  20,  22, -18,   3
};

constexpr SCORE_TYPE BISHOP_PST_END[64] = {
           7,   3,  26,  23,  27,  18,   8, -13,
          19,  18,  31,  14,  12,  15,  18,  10,
          23,  13,  19,  14,  16,  11,  19,  20,
          18,  24,  23,  21,  24,  18,  16,  18,
           5,  15,  21,  25,   8,  16,  10,   4,
           2,  11,  19,  18,  24,   6,  12,  -1,
           2,  -7,   5,  15,  13,  10, -15, -13,
           1,  11,  16,  17,  13,  18,  17,  -1
};

constexpr SCORE_TYPE ROOK_PST_MID[64] = {
          14,  26, -13,  45,  39, -20,   1,  12,
          17,  14,  55,  64,  82,  89,  -4,  38,
         -14,  -3,  -2,   3, -24,  49,  69,  12,
         -24, -21,  -6,   5,   0,  43, -10, -21,
         -30, -23, -14,  -9,   9,   7,  28, -19,
         -16,  -8,   2,  -3,  14,  30,  23,  -6,
          -9,   7,   2,  16,  26,  42,  27, -37,
          25,  26,  31,  43,  46,  49,   3,  25
};

constexpr SCORE_TYPE ROOK_PST_END[64] = {
          61,  53,  66,  48,  53,  63,  59,  55,
          58,  59,  49,  43,  26,  32,  61,  49,
          54,  54,  50,  49,  49,  30,  29,  35,
          54,  50,  57,  42,  44,  36,  40,  50,
          52,  53,  53,  46,  35,  31,  26,  36,
          44,  46,  34,  40,  29,  21,  25,  25,
          41,  37,  42,  42,  28,  22,  21,  40,
          43,  42,  42,  32,  26,  28,  38,  21
};

constexpr SCORE_TYPE QUEEN_PST_MID[64] = {
         -26, -33, -12, -10, 124, 112,  91,  65,
         -34, -69, -31, -14, -69,  57,  17,  69,
          -5, -24,  -6, -22,  22,  82,  54,  78,
         -41, -33, -25, -27, -12,   2,  -6,   3,
           7, -29,  -6, -12,   1,   2,   7,   7,
          -5,  18,   6,  18,  12,  18,  24,  16,
         -11,  15,  34,  35,  46,  50,  21,  40,
          23,  25,  33,  41,  23,   2,  -3, -40
};

constexpr SCORE_TYPE QUEEN_PST_END[64] = {
          14,  64,  59,  52,  -3,   0,   0,  58,
          19,  48,  59,  65, 109,  27,  53,  31,
          -7,  16,  -4,  64,  40,  25,  32,  29,
          49,  35,  20,  29,  55,  51,  97,  86,
         -14,  39,   7,  36,  13,  32,  60,  57,
          26, -30,   5, -27,  -5,  18,  34,  58,
           4, -27, -31, -32, -43, -38, -33, -20,
         -19, -38, -32,   8,  -2,  -8,   7, -13
};

constexpr SCORE_TYPE KING_PST_MID[64] = {
        -123, 207, 219, 124,-108, -87,  28,  49,
         225,  89,  45, 164,  68,  39, -49,-170,
          84,  79, 112,  23,  66, 100, 128, -45,
           2, -18,  17, -37, -61, -79, -38,-138,
        -102,  27, -61,-141,-148,-104,-101,-120,
          -1,   0, -36,-105,-106, -80, -29, -55,
          17,  27, -24,-114, -96, -53,   3,   8,
         -22,  48,  18,-119, -37, -58,  26,   5
};

constexpr SCORE_TYPE KING_PST_END[64] = {
         -91, -85, -71, -40,   6,  20,  -4, -42,
         -60,   3,  11,  10,  24,  31,  28,  32,
          -7,  15,  15,  35,  26,  39,  31,  13,
         -13,  30,  33,  59,  57,  51,  38,  17,
          -8,  -5,  40,  72,  72,  43,  26,  -6,
         -29,  -2,  23,  57,  57,  32,   9, -13,
         -47, -19,  13,  44,  41,  15, -11, -38,
         -81, -61, -34,  17, -11, -11, -50, -78
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_MID[8] = {   0,   9,   1,  -6,  11,   9,  69,   0};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_END[8] = {   0,   2,  12,  44,  82, 162, 184,   0};

constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_MID =  -23;
constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_END =    0;

constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -34;
constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_END =  -14;

constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_MID =   -7;
constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_END =  -30;

constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_MID =   -6;
constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_END =    3;

constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -17;
constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_END =   -6;

constexpr SCORE_TYPE BLOCKER_VALUES_MID[6] = {   0,  -6, -10,  28,  23, -11};

constexpr SCORE_TYPE BLOCKER_VALUES_END[6] = {   0, -51, -71, -41, -22,-104};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_MID[6] = {   0,   4, -25,  11,   6,  -4};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_END[6] = {   0, -35, -21, -18,  11, -51};

constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_MID =   15;
constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_END =   17;

constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_MID =   61;
constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_END =   -5;

constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_MID =    4;
constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_END =   19;

constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_MID =   -6;
constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_END =   17;

constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_MID =  -22;
constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_END =    3;

constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_MID =  -12;
constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_END =  -13;

constexpr SCORE_TYPE BISHOP_PAIR_BONUS_MID =   37;
constexpr SCORE_TYPE BISHOP_PAIR_BONUS_END =   58;

constexpr double MOBILITY_COEFFICIENTS_MID[6] = {      0,      3.98,      4.52,      2.25,      0.918,      0};

constexpr double MOBILITY_COEFFICIENTS_END[6] = {      0,      0.717,      2.15,      1.07,      3.25,      0};

#endif //ANTARESCHESSENGINE_CONSTANTS_H