
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

#define TEMPO_BONUS                 8

#define DOUBLED_PAWN_PENALTY_MID    18
#define DOUBLED_PAWN_PENALTY_END    26  // Doubled pawns are very easy to target in the endgame.

#define ISOLATED_PAWN_PENALTY_MID   23
#define ISOLATED_PAWN_PENALTY_END   34  // Pawn islands are very bad in the endgame

#define BACKWARDS_PAWN_PENALTY_MID  6
#define BACKWARDS_PAWN_PENALTY_END  8  // Give this a higher base score, but we reduce multipliers in eval_pawn()

#define PASSED_PAWN_BONUS_MID       9
#define PASSED_PAWN_BONUS_END       16  // These are multiplied by the pawn's row.

#define BISHOP_PAIR_BONUS_MID       39
#define BISHOP_PAIR_BONUS_END       56

#define ROOK_SEMI_OPEN_FILE_BONUS_MID   18
#define ROOK_SEMI_OPEN_FILE_BONUS_END   20

#define ROOK_OPEN_FILE_BONUS_MID        27
#define ROOK_OPEN_FILE_BONUS_END        32

#define QUEEN_SEMI_OPEN_FILE_BONUS_MID  5
#define QUEEN_SEMI_OPEN_FILE_BONUS_END  8

#define QUEEN_OPEN_FILE_BONUS_MID       22
#define QUEEN_OPEN_FILE_BONUS_END       26


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

constexpr SCORE_TYPE PIECE_VALUES_MID[6] = {82, 326, 352, 486, 982, 0};
constexpr SCORE_TYPE PIECE_VALUES_END[6] = {96, 292, 304, 512, 936, 0};

constexpr SCORE_TYPE MVV_LVA_VALUES[6] = {100, 300, 350, 500, 950, 3000};

constexpr SCORE_TYPE BLOCKER_VALUES_MID[6] = {0, 31, 14, 22,  8,  3};
constexpr SCORE_TYPE BLOCKER_VALUES_END[6] = {0, 37, 21, 26, 11, 28};

constexpr SCORE_TYPE PIECE_ATTACK_MOBILITY[6] = {6, 8, 8, 10, 14, 35};
constexpr SCORE_TYPE PIECE_ATTACK_MOBILITY_PENALTY[6] = {0, 2, 1, 3, 4, 0};


constexpr SCORE_TYPE PAWN_PST_MID[64] = {
             0,   0,   0,   0,   0,   0,   0,   0,
            45,  50,  55,  60,  65,  55,  30,  10,
            35,  40,  45,  50,  60,  45,  40,  25,
             8,   9,  20,  25,  30,  20,   7,   3,
             0,   0,  13,  18,  20,   8,   3,  -4,
             2,   2,   6,   2,   4,  -5,  12,   0,
             0,   0,   3, -26, -26,  12,  15,  -5,
             0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE KNIGHT_PST_MID[64] = {
           -70, -60, -30, -35,  -5, -30, -20, -70,
           -60,  -5,  40,  20,  20,  40,   5, -40,
           -30,  30,  30,  45,  45,  70,  10,  15,
             0,  10,  30,  50,  50,  60,  10,   5,
           -10,   0,  15,  40,  40,  15,   0, -30,
           -30,   5,   8,  20,  20,   8,  10, -30,
           -40, -20,   1,   5,   5,   1, -20, -40,
           -60, -40, -30, -30, -30, -20, -40, -40
};

constexpr SCORE_TYPE BISHOP_PST_MID[64] = {
           -20, -15, -10, -10, -10, -10, -15, -20,
           -15,   0,   0,   5,  10,  20,   0, -15,
           -10,  20,   5,  45,  30,  45,   0, -10,
           -10,  15,   5,  45,  35,  35,  15, -10,
           -10,  12,  15,  15,  15,  15,  12, -10,
           -10,  10,  10,   7,   7,  10,  10, -10,
           -10,  10,   0,   0,   0,   0,  10, -10,
           -20, -10, -10, -10, -10, -10, -10, -20
};

constexpr SCORE_TYPE ROOK_PST_MID[64] = {
            30,  35,  30,  42,  45,  30,  30,  35,
            25,  35,  50,  55,  65,  60,  30,  30,
             5,  10,  10,  30,  20,  30,  10,   5,
           -20,  -5,  10,  15,  15,  20,  -5, -20,
            30,  -5,  -1,   0,   5,  -1,  -5, -20,
           -35,   0,   0,   0,   0,   0,   0, -30,
           -30, -10,   5,   6,   6,   5,  -5, -40,
           -10,  -8,  10,  18,  18,  10, -20, -20
};

constexpr SCORE_TYPE QUEEN_PST_MID[64] = {
           -20, -10, -10,  -5,  -5, -10, -10, -20,
           -10,  -5,   5,  -5,  -1,   5,   5, -10,
           -10,   0,   5,   5,   5,   5,   0, -10,
            -5,   0,  10,   5,   5,   5,   0,  -5,
            -5,   5,  10,   1,  -1,   5,   5,  -5,
           -10,  15,  15,  15,  15,  15,  10, -10,
           -10,  -2,   5,   0,   0,  -2,   0, -10,
           -20, -10, -10,  -5,  -5, -15, -10, -20
};

constexpr SCORE_TYPE KING_PST_MID[64] = {
           -30, -40, -40, -50, -50, -40, -40, -30,
           -30, -40, -40, -50, -50, -40, -40, -30,
           -30, -40, -40, -50, -50, -40, -40, -30,
           -30, -40, -40, -50, -50, -40, -40, -30,
           -20, -30, -30, -40, -40, -30, -30, -20,
           -10, -20, -20, -40, -40, -20, -20, -10,
            10,  12, -10, -55, -40, -15,  14,  13,
            11,  25,   3, -30,  -5, -20,  27,  22
};


constexpr SCORE_TYPE PAWN_PST_END[64] = {
             0,   0,   0,   0,   0,   0,   0,   0,
            75,  70,  60,  55,  55,  55,  65,  70,
            55,  50,  45,  40,  40,  45,  50,  50,
            30,  30,  20,  26,  26,  20,  25,  30,
            10,   0,   5,   4,   4,   5,   0,   0,
             2,   2,   0,   3,   3,   0,   2,   2,
            10,  10,   5,   5,   5,   3,   1,   0,
             0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE KNIGHT_PST_END[64] = {
           -60, -40, -30, -30, -30, -30, -40, -80,
           -40, -20,   0,   0,   0,   0, -20, -40,
           -30,   0,  20,  25,  25,  20,   0, -30,
           -30,   5,  25,  30,  30,  25,   5, -30,
           -30,   0,  25,  30,  30,  25,   0, -30,
           -30,   5,  20,  25,  25,  20,   5, -30,
           -40, -20,   0,   5,   5,   0, -20, -40,
           -30, -40, -30, -30, -30, -30, -40, -50
};

constexpr SCORE_TYPE BISHOP_PST_END[64] = {
           -20, -10, -10, -10, -10, -10, -10, -20,
           -10,   0,   0,   0,   0,   0,   0, -10,
           -10,   0,   5,  10,  10,   5,   0, -10,
           -10,  15,   5,  25,  25,   5,  15, -10,
           -10,   5,  20,  15,  15,  20,   5, -10,
           -10,  15,  15,  10,  10,  15,  15, -10,
           -10,   5,   0,   0,   0,   0,   5, -10,
           -20, -10, -10, -10, -10, -10, -10, -20
};

constexpr SCORE_TYPE ROOK_PST_END[64] = {
            10,  10,  15,  15,  10,  10,   5,   5,
            10,  20,  23,  25,  25,  23,  20,  10,
             4,  18,  23,  25,  25,  23,  18,   4,
            -5,   0,   8,   8,   8,   8,   0,  -5,
            -5,   0,   0,   0,   0,   0,   0,  -5,
            -5,   0,   0,   0,   0,   0,   0,  -5,
            -5,   0,   5,   5,   5,   5,   0,  -5,
             0,   5,  10,  14,  14,  10,   5,   0
};

constexpr SCORE_TYPE QUEEN_PST_END[64] = {
           -20, -10, -10,  -5,  -5, -10, -10, -20,
           -10,   0,  30,  40,  60,  10,   0, -10,
           -10,   0,  20,  45,  50,  20,   0, -10,
            -5,   0,  10,  45,  55,  30,   0,  -5,
            -5,   0,  20,  45,  35,  20,   0,  -5,
           -10,   5,  20,  20,  20,  20,   5, -10,
           -10,   0,   5,   0,   0,   5,   0, -10,
           -20, -10, -10,  -5,  -5, -10, -10, -20
};

constexpr SCORE_TYPE KING_PST_END[64] = {
           -20, -16, -12, -12, -12,   5,   5,   2,
            14,  16,  20,  26,  26,  20,  16,  14,
            16,  25,  30,  31,  31,  30,  25,  16,
            16,  26,  32,  35,  35,  32,  26,  16,
             8,  25,  30,  33,  33,  30,  25,   8,
             2,   8,  16,  14,  14,  16,   8,   2,
           -18, -14, -10, -10, -10, -10, -14, -18,
           -20, -20, -20, -20, -20, -20, -20, -20
};


#endif //ANTARESCHESSENGINE_CONSTANTS_H