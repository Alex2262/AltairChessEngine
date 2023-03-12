
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

constexpr int MVV_LVA_VALUES[6] = {100, 300, 350, 500, 900, 2000};

constexpr double KING_PAWN_SHIELD_COEFFICIENTS[8] = {0.8, 1.0, 0.6, 0.0, 0.0, 0.3, 1.0, 0.5};
constexpr int KING_PAWN_SHIELD_OUR_PENALTIES[3] = {-6, -14, -23};
constexpr int KING_PAWN_SHIELD_OPP_PENALTIES[3] = {-19, -8, -16};

constexpr SCORE_TYPE PIECE_ATTACK_MOBILITY[6] = {6, 8, 8, 10, 14, 35};
constexpr SCORE_TYPE PIECE_ATTACK_MOBILITY_PENALTY[6] = {0, 2, 1, 3, 4, 0};

constexpr double MOBILITY_COEFFICIENTS_MID[6] = {0.0, 1.6, 1.2, 0.55, 0.36, 0.0};
constexpr double MOBILITY_COEFFICIENTS_END[6] = {0.0, 1.5, 1.1, 1.0, 1.0, 0.0};

constexpr double OUR_KING_DISTANCE_COEFFICIENTS_MID[6] = {0.0, 1.0, 0.0, 0.0, 0.0, 0.0};
constexpr double OUR_KING_DISTANCE_COEFFICIENTS_END[6] = {0.0, 0.3, 0.0, 0.0, 0.0, 0.0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_MID[6] = {0.0, 2.6, 0.7, 1.8, 0.7, 0.0};
constexpr double OPP_KING_DISTANCE_COEFFICIENTS_END[6] = {0.0, 1.2, 0.2, 1.1, 1.0, 0.0};

constexpr SCORE_TYPE PIECE_VALUES_MID[6] = {  23,  78, 102, 109, 203,   0};

constexpr SCORE_TYPE PIECE_VALUES_END[6] = {  29,  65,  91, 123, 206,   0};

constexpr SCORE_TYPE PAWN_PST_MID[64] = {   0,   0,   0,   0,   0,   0,   0,   0,
                                            0,  29,  -3,  18,   0,  30,  -2, -30,
                                            6,   6,  13,  17,  32,  37,  24,  10,
                                            2,   6,   8,  14,  13,  13,  12,   3,
                                            -2,   2,   4,  11,  11,   8,   5,  -1,
                                            1,   1,   5,   6,   8,   6,  10,   3,
                                            0,   1,   1,   5,   4,  13,   8,   2,
                                            0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE PAWN_PST_END[64] = {   0,   0,   0,   0,   0,   0,   0,   0,
                                            69,  58,  57,  38,  52,  40,  65,  76,
                                            31,  30,  18,   3,  -3,   9,  21,  25,
                                            22,  17,  12,   3,   7,  11,  17,  17,
                                            17,  15,  10,   6,   8,   9,  11,  12,
                                            12,  13,   9,  11,  12,  10,   7,   8,
                                            15,  13,  14,  13,  16,  11,   8,   6,
                                            0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE KNIGHT_PST_MID[64] = {  -3,  17,  33,  25,  54,   5,  34,  20,
                                             25,  29,  51,  49,  32,  54,  32,  41,
                                             42,  68,  48,  54,  59,  72,  66,  52,
                                             62,  61,  52,  65,  56,  62,  52,  59,
                                             65,  63,  59,  58,  59,  55,  57,  59,
                                             65,  59,  62,  59,  60,  57,  62,  59,
                                             67,  57,  60,  64,  59,  61,  53,  61,
                                             34,  67,  52,  55,  62,  51,  61,  57
};

constexpr SCORE_TYPE KNIGHT_PST_END[64] = {  48,  50,  57,  49,  49,  51,  38,  22,
                                             55,  61,  49,  56,  54,  43,  53,  40,
                                             51,  48,  55,  54,  49,  45,  44,  42,
                                             53,  57,  59,  59,  58,  53,  55,  51,
                                             55,  52,  56,  61,  57,  55,  55,  51,
                                             51,  56,  50,  55,  55,  47,  47,  47,
                                             51,  54,  55,  55,  57,  48,  53,  46,
                                             69,  49,  56,  61,  55,  58,  49,  39
};

constexpr SCORE_TYPE BISHOP_PST_MID[64] = {   7,  11, -35, -25, -15, -11,  10,  25,
                                              1,   5,  -7,  -8,  13,  12,   7,  -6,
                                              9,  15,  13,  12,   9,  20,  12,  12,
                                              12,  17,  13,  20,  15,  17,  15,  13,
                                              18,  18,  18,  18,  24,  14,  17,  21,
                                              21,  25,  22,  21,  21,  28,  21,  24,
                                              28,  28,  26,  22,  25,  24,  34,  23,
                                              14,  26,  23,  18,  21,  22,   8,  14
};

constexpr SCORE_TYPE BISHOP_PST_END[64] = {  30,  26,  38,  36,  37,  32,  29,  19,
                                             32,  32,  38,  31,  29,  31,  29,  26,
                                             35,  31,  31,  31,  31,  32,  36,  33,
                                             34,  33,  33,  33,  33,  34,  31,  33,
                                             29,  32,  32,  35,  28,  30,  29,  27,
                                             28,  30,  33,  32,  35,  28,  31,  27,
                                             27,  25,  29,  32,  31,  31,  22,  20,
                                             28,  30,  35,  35,  33,  35,  31,  29
};

constexpr SCORE_TYPE ROOK_PST_MID[64] = {  51,  53,  39,  58,  50,  29,  44,  47,
                                           51,  49,  61,  62,  67,  64,  39,  52,
                                           46,  47,  47,  48,  39,  55,  63,  48,
                                           46,  45,  48,  50,  48,  60,  40,  42,
                                           46,  46,  48,  48,  53,  52,  55,  46,
                                           51,  52,  56,  52,  55,  60,  57,  50,
                                           55,  58,  56,  60,  61,  65,  61,  41,
                                           66,  65,  66,  68,  67,  66,  54,  63
};

constexpr SCORE_TYPE ROOK_PST_END[64] = {  99,  96, 101,  92,  96, 102, 100,  98,
                                           99,  99,  94,  92,  87,  89, 100,  96,
                                           97,  96,  94,  92,  92,  88,  88,  91,
                                           97,  95,  97,  91,  91,  89,  93,  95,
                                           98,  98,  96,  93,  89,  88,  87,  91,
                                           97,  96,  91,  93,  90,  86,  88,  88,
                                           97,  94,  96,  94,  91,  88,  87,  95,
                                           97,  95,  95,  91,  89,  92,  93,  89
};

constexpr SCORE_TYPE QUEEN_PST_MID[64] = { 148, 145, 145, 145, 188, 184, 183, 173,
                                           146, 134, 143, 148, 130, 171, 161, 174,
                                           155, 147, 151, 146, 158, 174, 163, 173,
                                           144, 146, 148, 147, 151, 154, 151, 156,
                                           159, 147, 154, 152, 155, 154, 156, 156,
                                           156, 163, 158, 161, 159, 160, 162, 160,
                                           157, 162, 167, 167, 170, 171, 165, 168,
                                           166, 167, 168, 170, 165, 158, 159, 147
};

constexpr SCORE_TYPE QUEEN_PST_END[64] = { 186, 199, 201, 197, 180, 181, 182, 203,
                                           184, 193, 197, 197, 211, 184, 194, 189,
                                           178, 184, 176, 197, 190, 187, 192, 191,
                                           195, 190, 184, 185, 192, 192, 207, 202,
                                           175, 191, 181, 187, 182, 186, 195, 196,
                                           189, 172, 181, 171, 177, 184, 189, 199,
                                           184, 173, 173, 171, 168, 168, 169, 177,
                                           178, 171, 172, 188, 180, 178, 180, 175
};

constexpr SCORE_TYPE KING_PST_MID[64] = { -21, 110, 130,  31, -71,  -1,  32,  76,
                                          117,  54,  47,  28,  11,  33,   5, -52,
                                          63,  50,  73,  -6,  12,  58,  56,  -7,
                                          33,  22,  38, -25, -36,  -6,  -3, -30,
                                          11,  48,  13, -54, -58, -16, -10, -14,
                                          34,  35,  22, -38, -40,  -4,  10,   1,
                                          33,  36,  21, -38, -34,   3,  17,  13,
                                          13,  31,  26, -43, -20,  -3,  16,   7
};

constexpr SCORE_TYPE KING_PST_END[64] = { -39, -36, -35, -25,   3,   5,  -9, -37,
                                          -27,   4,   2,  -3,   1,  13,   7,  17,
                                          -4,   9,   4,  10,   6,  16,  11,   7,
                                          -5,  13,  13,  20,  21,  21,  17,   6,
                                          -5,  -1,  17,  23,  24,  18,   9,  -4,
                                          -11,   0,  11,  17,  18,  12,   4,  -5,
                                          -17,  -6,   6,  12,  11,   6,  -3, -12,
                                          -28, -18,  -9,   2,  -7,  -2, -15, -25
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_MID[8] = {   0,   4,   1,  -3,  -1,  -9,   7,   0};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_END[8] = {   0,   1,   5,  16,  31,  63,  60,   0};

constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_MID =   -7;
constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_END =    0;

constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -10;
constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_END =   -4;

constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_MID =    4;
constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_END =  -11;

constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_MID =    7;
constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_END =    2;

constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_MID =   -2;
constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_END =   -3;

constexpr SCORE_TYPE BLOCKER_VALUES_MID[6] = {   0,   4,  -1,  17,  11,  -3};

constexpr SCORE_TYPE BLOCKER_VALUES_END[6] = {   0, -18, -22, -22, -11, -36};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_MID[6] = {   0,   5,  -4,   9,   6,  -1};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_END[6] = {   0, -12,  -9, -11,   1, -20};

constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_MID =    2;
constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_END =    5;

constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_MID =   15;
constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_END =   -5;

constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_MID =    1;
constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_END =    6;

constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_MID =   -3;
constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_END =    6;

constexpr SCORE_TYPE BISHOP_PAIR_BONUS_MID =   11;
constexpr SCORE_TYPE BISHOP_PAIR_BONUS_END =   17;


#endif //ANTARESCHESSENGINE_CONSTANTS_H