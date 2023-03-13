
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

constexpr SCORE_TYPE PIECE_VALUES_MID[6] = { 106, 456, 457, 592,1360,   0};

constexpr SCORE_TYPE PIECE_VALUES_END[6] = { 106, 331, 351, 629,1133,   0};

constexpr SCORE_TYPE PAWN_PST_MID[64] = {   0,   0,   0,   0,   0,   0,   0,   0,
                                            56, 108,  26,  75,  38, 136, -12, -78,
                                            26,  26,  51,  57, 103, 132,  65,  30,
                                            6,  18,  24,  47,  46,  41,  30,   3,
                                            -10,  -6,   5,  31,  32,  27,  12,  -7,
                                            -6, -10,   5,   2,  14,  21,  36,   9,
                                            -20, -15, -19, -13, -13,  44,  31,  -3,
                                            0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE PAWN_PST_END[64] = {   0,   0,   0,   0,   0,   0,   0,   0,
                                            121,  95,  85,  45,  66,  35, 102, 138,
                                            65,  58,  30,  -7, -24,  -2,  36,  44,
                                            40,  27,  13, -11,  -4,   6,  21,  25,
                                            27,  22,   9,  -5,  -2,   1,   9,  10,
                                            14,  17,   4,  15,  14,   6,  -2,  -1,
                                            26,  20,  25,  26,  30,   9,   4,  -1,
                                            0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE KNIGHT_PST_MID[64] = {-213,-130, -54, -64,  81,-131, -37,-135,
                                           -97, -57,  68,  35,   9,  69, -19, -20,
                                           -47,  82,  43,  74, 103, 148,  94,  51,
                                           11,  40,  32,  79,  58,  93,  35,  43,
                                           14,  34,  38,  33,  49,  40,  41,  15,
                                           6,  14,  37,  34,  44,  39,  50,   8,
                                           0, -30,  13,  23,  21,  41,   2,  10,
                                           -119,   8, -39, -16,  14,  -8,   6,   3
};

constexpr SCORE_TYPE KNIGHT_PST_END[64] = { -26, -14,  12, -12, -26,  -7, -52, -90,
                                            -2,  18, -15,  16,   6, -24,  -6, -44,
                                            -9, -12,  22,  19,  -5, -13, -17, -41,
                                            -2,  19,  39,  33,  33,  15,  17,  -9,
                                            2,   6,  29,  43,  30,  28,  16,  -6,
                                            -10,  17,   7,  26,  24,   1,  -9, -16,
                                            -24,   1,   9,  14,  20,  -9,  -6, -32,
                                            19, -32,   3,  11,  -4,   3, -28, -60
};

constexpr SCORE_TYPE BISHOP_PST_MID[64] = { -33,  -7,-155, -95, -72, -71, -12,  12,
                                            -44,  -3, -40, -51,  29,  37,   1, -63,
                                            -18,  27,  34,  32,  27,  65,  31,  -2,
                                            -3,  13,  19,  53,  38,  43,  12,   0,
                                            -2,  21,  20,  31,  45,  16,  15,  13,
                                            8,  28,  24,  24,  22,  44,  28,  22,
                                            20,  30,  30,   9,  22,  29,  56,  15,
                                            -38,  12,  -5, -10,  -3,  -3, -42, -21
};

constexpr SCORE_TYPE BISHOP_PST_END[64] = {  -1,  -7,  19,  14,  20,  12,  -3, -22,
                                             10,   9,  24,   9,   7,   6,  10,  -1,
                                             15,   7,  13,  12,  12,  11,  14,  12,
                                             10,  22,  22,  23,  27,  17,  13,  11,
                                             0,  13,  23,  29,  13,  16,   8,  -3,
                                             -5,   9,  21,  19,  25,   8,   6,  -9,
                                             -6, -12,   2,  14,  13,   6, -18, -22,
                                             -8,   4,   6,  12,   6,  10,  11,  -7
};

constexpr SCORE_TYPE ROOK_PST_MID[64] = {  24,  39,   3,  60,  56,  -4,  13,  25,
                                           24,  21,  63,  66,  89,  97,   1,  43,
                                           -12,   2,   7,  10, -16,  58,  77,  18,
                                           -25, -17,  -3,  10,   7,  49,  -1, -16,
                                           -29, -25, -19,  -9,   6,   7,  31, -15,
                                           -25, -10,  -8, -14,   6,  24,  25,  -8,
                                           -18,  -2, -13,   2,  11,  33,  17, -49,
                                           16,  13,  14,  29,  32,  36,  -8,  15
};

constexpr SCORE_TYPE ROOK_PST_END[64] = {  43,  34,  48,  29,  33,  44,  40,  36,
                                           39,  41,  30,  26,   7,  15,  44,  31,
                                           37,  37,  31,  30,  30,  11,  11,  17,
                                           37,  32,  40,  24,  25,  18,  21,  32,
                                           33,  36,  37,  29,  18,  14,   8,  16,
                                           28,  28,  19,  24,  13,   5,   7,   7,
                                           26,  22,  29,  27,  15,   7,   7,  25,
                                           29,  30,  33,  21,  14,  16,  25,   6
};

constexpr SCORE_TYPE QUEEN_PST_MID[64] = { -29,  -7,  16,  13, 142, 130,  89,  68,
                                           -24, -48, -10,   1, -48,  79,  37,  79,
                                           7,  -7,  18,   1,  44, 101,  71,  85,
                                           -29, -20,  -9,  -7,   6,  20,   7,  12,
                                           14, -17,   7,   2,  13,  16,  19,  18,
                                           1,  28,  12,  25,  18,  25,  36,  25,
                                           -13,  17,  41,  33,  42,  52,  25,  41,
                                           21,  13,  23,  40,  15,  -5, -15, -39
};

constexpr SCORE_TYPE QUEEN_PST_END[64] = {  27,  69,  63,  63,   5,   6,  17,  66,
                                            17,  57,  70,  78, 122,  44,  69,  30,
                                            -4,  27,  18,  87,  69,  48,  48,  33,
                                            51,  57,  47,  65,  91,  85, 115,  91,
                                            -8,  60,  35,  71,  48,  61,  75,  55,
                                            29, -18,  32,   3,  23,  40,  41,  54,
                                            6, -13, -22, -10, -17, -24, -24, -23,
                                            -12, -17, -14,   4,  12,  -2,  15, -21
};

constexpr SCORE_TYPE KING_PST_MID[64] = {-103, 221, 217,  60,-182, -90,  31,  71,
                                         231,  95,  47,  89,  10,  43, -41,-154,
                                         93,  85, 115, -31,   0, 108, 137, -37,
                                         15, -11,  24, -85,-101, -65, -26,-124,
                                         -89,  32, -55,-173,-180, -99, -96,-113,
                                         11,   7, -30,-122,-122, -74, -23, -48,
                                         26,  35, -15,-129,-107, -45,   9,  15,
                                         -13,  53,  19,-130, -42, -59,  26,  13
};

constexpr SCORE_TYPE KING_PST_END[64] = { -85, -80, -64, -45,   6,  27,   1, -38,
                                          -53,   9,  16,   7,  19,  36,  32,  36,
                                          -1,  19,  20,  28,  23,  42,  34,  19,
                                          -9,  35,  37,  50,  50,  54,  42,  22,
                                          -4,   0,  45,  60,  64,  48,  31,  -1,
                                          -25,   3,  27,  44,  48,  37,  15,  -8,
                                          -41, -15,  17,  32,  32,  20,  -6, -31,
                                          -74, -55, -28,   3, -24,  -5, -42, -71
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_MID[8] = {   0,  12,   3,  -6,  11,   9,  78,   0};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_END[8] = {   0,   2,  13,  44,  81, 160, 185,   0};

constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_MID =  -23;
constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_END =   -1;

constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -36;
constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_END =  -13;

constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_MID =   -7;
constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_END =  -29;

constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_MID =    2;
constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_END =    4;

constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -15;
constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_END =   -7;

constexpr SCORE_TYPE BLOCKER_VALUES_MID[6] = {   0,  -8, -10,  36,  25,  -9};

constexpr SCORE_TYPE BLOCKER_VALUES_END[6] = {   0, -50, -71, -41, -19,-105};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_MID[6] = {   0,   2, -25,  20,   5,   1};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_END[6] = {   0, -33, -18, -19,   9, -52};

constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_MID =   28;
constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_END =   15;

constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_MID =   76;
constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_END =   -5;

constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_MID =    3;
constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_END =   24;

constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_MID =   -6;
constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_END =   37;

constexpr SCORE_TYPE BISHOP_PAIR_BONUS_MID =   39;
constexpr SCORE_TYPE BISHOP_PAIR_BONUS_END =   58;


#endif //ANTARESCHESSENGINE_CONSTANTS_H