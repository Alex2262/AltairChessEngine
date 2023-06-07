//
// Created by Alexander Tian on 5/14/23.
//

#ifndef ALTAIRCHESSENGINE_EVALUATION_CONSTANTS_CPP
#define ALTAIRCHESSENGINE_EVALUATION_CONSTANTS_CPP

#include "constants.h"

constexpr SCORE_TYPE MAX_MINOR_PIECE_VALUE_MID = 438;
constexpr SCORE_TYPE PIECE_VALUES_MID[6] = { 101, 433, 438, 638,1492,   0};

constexpr SCORE_TYPE PIECE_VALUES_END[6] = { 134, 388, 395, 761,1416,   0};

constexpr SCORE_TYPE PAWN_PST_MID[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        177, 153, 101, 164, 111, 209,  55,  51,
        15,  18,  39,  55,  75,  71,  54,   9,
        4,   6,   7,  21,  29,  39,  23,   1,
        -4, -11,   1,   7,  13,  18,   6, -15,
        -16, -19, -15,  -8,   1,  -3,   5, -16,
        -9,  -5, -16,  -5,  -4,  22,  29,  -4,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE PAWN_PST_END[64] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        97,  97,  97,  35,  65,  49, 127, 121,
        71,  72,  40,   3,   0,  37,  70,  90,
        29,  17,  11, -14,  -8,  11,  27,  35,
        9,  11,  -3,  -8,  -7,  -2,  12,  14,
        2,   6,   6,   3,  13,   7,   8,  10,
        14,  14,  26,   1,  33,  11,  19,  18,
        0,   0,   0,   0,   0,   0,   0,   0
};

constexpr SCORE_TYPE KNIGHT_PST_MID[64] = {
        -112, -60, -47,  40, 124,-128,  37, -54,
        63,  31,  85,  74,  84,  98,  12,  61,
        35,  74,  88, 101, 118, 147,  86, 114,
        91,  91,  89,  98,  73,  86,  61,  79,
        69,  75,  75,  75,  78,  60,  86,  55,
        49,  50,  48,  56,  53,  36,  48,  36,
        24,  25,  40,  42,  34,  37,  29,  49,
        -50,  34,   2,  16,  23,  16,  22, -16
};

constexpr SCORE_TYPE KNIGHT_PST_END[64] = {
        37,  62,  85,  51,  43,  81,   8, -18,
        47,  65,  39,  78,  64,  28,  58,  44,
        48,  46,  73,  74,  54,  51,  39,  14,
        55,  61,  77,  90,  89,  82,  68,  69,
        64,  51,  76,  85,  80,  77,  57,  76,
        2,  41,  52,  73,  64,  45,  32,  62,
        51,  67,  23,  62,  76,  35,  57,  50,
        55,  48,  64,  70,  60,  64,  70,  55
};

constexpr SCORE_TYPE BISHOP_PST_MID[64] = {
        -19,  -5,-110, -83, -97, -96,  29,  39,
        -9,  17,  17,   4,  -3,  48,   9,  -1,
        35,  41,  73,  40,  70,  61,  74,  30,
        6,  41,  28,  71,  49,  52,  27,  15,
        23,  35,  44,  54,  65,  31,  31,  43,
        36,  48,  45,  44,  44,  50,  55,  56,
        52,  52,  55,  40,  40,  47,  75,  66,
        65,  55,  37,  29,  29,  36,  40,  50
};

constexpr SCORE_TYPE BISHOP_PST_END[64] = {
        54,  63,  86,  90,  93,  71,  53,  48,
        81,  59,  68,  63,  74,  60,  58,  66,
        57,  60,  57,  62,  52,  75,  61,  78,
        59,  59,  67,  61,  68,  63,  78,  79,
        43,  48,  58,  64,  53,  62,  50,  39,
        31,  38,  47,  51,  63,  44,  35,  38,
        24,  20,  35,  44,  50,  33,  57,  15,
        -1,  24,  71,  54,  48,  66,  61,  16
};

constexpr SCORE_TYPE ROOK_PST_MID[64] = {
        59,  44,  -3,  -7,  44,  43,  60,  98,
        31,  10,  27,  41,  27,  66,  19,  49,
        13,  44,  48,  46,  54, 101, 111,  61,
        26,  25,  36,  51,  33,  47,  18,  22,
        -6,   1,  -6,   7,   2,   8,  17,   6,
        -11,  -3,  -7,  -5, -12,   9,  21,   1,
        -21,   6,  -4,   1,   1,  15,  21, -54,
        14,  12,  19,  24,  19,  13,   7,  14
};

constexpr SCORE_TYPE ROOK_PST_END[64] = {
        68,  77,  89,  93,  77,  75,  68,  64,
        66,  75,  76,  75,  74,  48,  65,  60,
        63,  55,  55,  55,  46,  44,  38,  44,
        57,  54,  63,  52,  58,  55,  53,  58,
        59,  64,  67,  63,  62,  52,  52,  48,
        42,  49,  52,  54,  52,  38,  43,  36,
        41,  35,  47,  43,  45,  36,  30,  53,
        42,  45,  42,  35,  34,  51,  46,  23
};

constexpr SCORE_TYPE QUEEN_PST_MID[64] = {
        -13, -23,  -6, -11,   6,  54,  90,  54,
        -1, -58, -40, -85,-106,   2,  -4,  19,
        6,   3, -10, -51, -52,  41,  36, -17,
        16,   4, -21, -35, -39, -22, -15,  -7,
        27,  27,   5, -10, -21,  -3,  13,   9,
        33,  54,  34,   9,   5,   3,  29,  19,
        41,  56,  48,  25,  20,  31,  33,  24,
        68,  47,  41,  38,  29,  10,  48,  16
};

constexpr SCORE_TYPE QUEEN_PST_END[64] = {
        11,  52,  43,  24,  45,  23,  -2,   7,
        31,  73,  67,  83, 111,  58,  59,  56,
        21,  25,  35,  80,  90,  44,  45, 104,
        22,  52,  57,  73,  86,  83,  90,  81,
        13,  37,  48,  80,  65,  51,  32,  13,
        -13, -42,  19,  25,  25,  40,  -6,   2,
        -26, -45, -46,  21,  14, -46, -46, -32,
        -44, -33, -12,  73, -11, -32, -56, -42
};

constexpr SCORE_TYPE KING_PST_MID[64] = {
        -173, 225, 300, 107,-212,-136,  62, -16,
        185, 173, 198,  64,  46, 114, -53,-202,
        60, 156, 167, -23,  56, 103, 148, -71,
        -5,  79,  84, -17, -81,  34,  32,-110,
        -1, 143,  68,-110, -61,  -8,  38, -80,
        -36,  20,  12, -76, -52,  -9,  19, -42,
        -9,   2,  -6,-134, -94, -55,   1,  -5,
        -25,  18, -27,-149, -67,-104, -22, -30
};

constexpr SCORE_TYPE KING_PST_END[64] = {
        -73, -77, -67,   7,  63,  30,  -9, -68,
        -43,  25,  23,  81,  82,  32,  63,  27,
        30,  33,  37,  93,  80,  63,  46,  24,
        11,  33,  41, 106, 108,  46,  38,  18,
        -24, -17,  22, 106,  95,  28,   4, -15,
        -30,  -5,  11,  81,  71,  12,  -9, -26,
        -40, -25,  -8,  62,  56,   8, -25, -52,
        -111, -74, -37,  20, -10, -21, -50,-107
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_MID[3][8] = {
        {   0,  -2,  -1,  -5,  12,  28,  21,   0},
        {   0,   3,   5,  -4,  29,  67, 339,   0},
        {   0,   3,  46,  12,  60,  95, 678,   0}
};

constexpr SCORE_TYPE PASSED_PAWN_BONUSES_END[3][8] = {
        {   0,  11,  19,  48,  76, 147, 206,   0},
        {   0,   3,  10,  38,  88, 190, 176,   0},
        {   0,   3,   4,  -2,  57, 123, -45,   0}
};

constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_MID =  -10;
constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY_END =   -1;

constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -20;
constexpr SCORE_TYPE ISOLATED_PAWN_SEMI_OPEN_FILE_PENALTY_END =  -15;

constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_MID =   -7;
constexpr SCORE_TYPE DOUBLED_PAWN_PENALTY_END =  -37;

constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_MID =   -4;
constexpr SCORE_TYPE BACKWARDS_PAWN_PENALTY_END =    4;

constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_MID =  -14;
constexpr SCORE_TYPE BACKWARDS_PAWN_SEMI_OPEN_FILE_PENALTY_END =   -4;

constexpr SCORE_TYPE PHALANX_PAWN_BONUS_MID[8] = {   0,   6,  21,  23,  49,  75,  47,   0};

constexpr SCORE_TYPE PHALANX_PAWN_BONUS_END[8] = {   0,   1,   7,  23,  86, 171, 362,   0};

constexpr SCORE_TYPE PIECE_SUPPORT_MID[6][6] = {
        {  20,   4,   8,   7,  -6, -83},
        {  -6,   2,   0,   2,   6,  -2},
        {  -9,   3, -17,   0,   5,  -3},
        {   1,  11,   5,   7,   5,   6},
        {  -1,   6,   5,   6,  97,   0},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE PIECE_SUPPORT_END[6][6] = {
        {  17,  20,  28,   7,   4,  31},
        {   2,  11,   1,  -3,  -7,  -3},
        {  -9,   7,  27,   0,   7,   0},
        {  -1,  -1,   4,  11,  47, -10},
        {   7,   8, -15,  -9,-608, -12},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE PIECE_THREAT_MID[6][6] = {
        {  10,  72,  66, 103,  67, 141},
        {  -5,  20,  29,  54,  51, 110},
        {  -2,  32,  20,  47,  55,  54},
        {  -7,   5,  13,  10,  68, 133},
        {  -5,   5,   2,  -2,  10,  73},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE PIECE_THREAT_END[6][6] = {
        {  10,  36,  80,   3,  34,  19},
        {  18,  20,  54,  30,  10,  27},
        {  16,  49,  20,  35,  53,  78},
        {  23,  30,  35,  10,  38,  25},
        {  15,   9,  32,  30,  10, 109},
        {   0,   0,   0,   0,   0,   0}
};

constexpr SCORE_TYPE BLOCKER_VALUES_MID[6][8] = {
        {   0,   0,   0,   0,   0,   0,   0,   0},
        {   0,   6, -23,  -2,  -7, -23, 124,   0},
        {   0, -10,  -9, -17,   4, -20,   5,   0},
        {   0,   4, -15,   5,  11,  13,  16,   0},
        {   0,  52, -49,  19,   8,  25,  38,   0},
        {   0,  69,  49,-104, -41, -87, -56,   0}
};

constexpr SCORE_TYPE BLOCKER_VALUES_END[6][8] = {
        {   0,   0,   0,   0,   0,   0,   0,   0},
        {   0, -34,  -6, -39, -84,-116,-222,   0},
        {   0, -25, -48, -37, -63,-114,-208,   0},
        {   0, -19,  17,  -2, -14, -69,-142,   0},
        {   0, -74,  46, -38, -14, -48,  70,   0},
        {   0, -28, -20, -36, -65,-133,-236,   0}
};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_MID[6][8] = {
        {   0,   0,   0,   0,   0,   0,   0,   0},
        {   0,  -7,   2,   2,   4,  48,   0,   0},
        {   0,  -1,  -3, -11,   1,  32,   0,   0},
        {   0,   0,  14,  -4,  17,  32,   0,   0},
        {   0,  10,   7,  15,  27,   4,   0,   0},
        {   0, 186,  48, -35,   4,  28,   0,   0}
};

constexpr SCORE_TYPE BLOCKER_TWO_SQUARE_VALUES_END[6][8] = {
        {   0,   0,   0,   0,   0,   0,   0,   0},
        {   0, -18, -19, -19, -18,-117,   0,   0},
        {   0,  -7,  -5,  -4, -30, -70,   0,   0},
        {   0, -19, -11,  14,   1, -59,   0,   0},
        {   0,   5, -28, -29, -22,  92,   0,   0},
        {   0,   3,  -1,  -3, -28, -96,   0,   0}
};

constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_MID =   19;
constexpr SCORE_TYPE ROOK_SEMI_OPEN_FILE_BONUS_END =    7;

constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_MID =   42;
constexpr SCORE_TYPE ROOK_OPEN_FILE_BONUS_END =    3;

constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_MID =    1;
constexpr SCORE_TYPE QUEEN_SEMI_OPEN_FILE_BONUS_END =   35;

constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_MID =   -5;
constexpr SCORE_TYPE QUEEN_OPEN_FILE_BONUS_END =   31;

constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_MID =  -23;
constexpr SCORE_TYPE KING_SEMI_OPEN_FILE_PENALTY_END =    2;

constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_MID =  -12;
constexpr SCORE_TYPE KING_OPEN_FILE_PENALTY_END =  -14;

constexpr SCORE_TYPE BISHOP_PAIR_BONUS_MID =   26;
constexpr SCORE_TYPE BISHOP_PAIR_BONUS_END =   78;

constexpr SCORE_TYPE TEMPO_BONUS_MID =   25;
constexpr SCORE_TYPE TEMPO_BONUS_END =   21;

constexpr SCORE_TYPE KNIGHT_MOBILITY_MID[9] = { -39, -28,  -7,   8,  24,  30,  40,  52,  68};

constexpr SCORE_TYPE KNIGHT_MOBILITY_END[9] = {-114, -43, -25,   4,  16,  32,  41,  43,  33};

constexpr SCORE_TYPE BISHOP_MOBILITY_MID[14] = {  -60, -43, -16,  -1,  12,  24,  28,  32,  32,  37,  45,  65,  68, 114};

constexpr SCORE_TYPE BISHOP_MOBILITY_END[14] = {-184, -96,  -3,   8,  12,  23,  39,  46,  57,  61,  62,  52,  68,  36};

constexpr SCORE_TYPE ROOK_MOBILITY_MID[15] = { -100, -35, -39, -24, -20, -11,  -6,  -4,   4,  10,  15,  21,  31,  46,  89};

constexpr SCORE_TYPE ROOK_MOBILITY_END[15] = {-200,-175, -29, -10,  21,   5,  11,  27,  31,  34,  44,  48,  51,  46,  25};

constexpr SCORE_TYPE QUEEN_MOBILITY_MID[28] = {   -90, -75, -60, -54, -62, -38, -33, -27, -24, -14,  -7,  -3,   3,   9,  11,  10,  17,  12,  13,  11,  18,  22,  44,  33,  35,  32, -31, 201};

constexpr SCORE_TYPE QUEEN_MOBILITY_END[28] = {   -190, -170, -150,-163, -99, -64,  45,  75,  68,  24,   2,   9,   9,  14,  17,  25,  22,  32,  33,  39,  36,  35,  12,  15,  17,  -5,   9,-116};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -5.26,      0,      0,      0,      0};

constexpr double OWN_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,      -0.339,      0,      0,      0,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_MID[6] = {      0,     -1.7,      -0.062,     -4.01,    -9.85,      0};

constexpr double OPP_KING_DISTANCE_COEFFICIENTS_END[6] = {      0,     -0.947,      1.99,      3.53,      5.45,      0};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_MID[3][8] = {
        {   0,   2, -33,   0,   0, -17, -12,   6},
        {   2, -43, -35,   0,   0, -17, -23,   1},
        { -40, -58, -47,   0,   0, -31, -58, -25}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OWN_PENALTIES_END[3][8] = {
        {  11,   2,  20,   0,   0,  -5,  12,  23},
        {  28,  27,  21,   0,   0, -20,  12,  25},
        {  22,   6,   8,   0,   0, -10,  26,  36}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_MID[3][8] = {
        {  -3, -36,  -3,   0,   0,  -3, -19,   2},
        {  -1, -23, -34,   0,   0, -27,  -6,  -7},
        { -29,-114,-121,   0,   0, -92, -49, -39}
};

constexpr SCORE_TYPE KING_PAWN_SHIELD_OPP_PENALTIES_END[3][8] = {
        {  -5,   4,  -8,   0,   0,  -5,  -5, -11},
        {  31,  28,  13,   0,   0,  28,  19,  17},
        {  61,  85,  47,   0,   0,  39,  61,  66}
};

constexpr SCORE_TYPE KING_RING_ATTACKS_MID[2][6] = {
        {   0,  13,  20,  27,  19,   0},
        {   0,   8,   5,   6,   6,   0}
};

constexpr SCORE_TYPE KING_RING_ATTACKS_END[2][6] = {
        {   0,  -8,  -3,  -6,  15,   0},
        {   0,   2,   1,   1,  17,   0}
};

constexpr SCORE_TYPE OUTPOST_PENALTY_MID =   -3;
constexpr SCORE_TYPE OUTPOST_PENALTY_END =  -18;

constexpr SCORE_TYPE OUTPOST_KNIGHT_PENALTY_MID =  -28;
constexpr SCORE_TYPE OUTPOST_KNIGHT_PENALTY_END =  -45;

constexpr SCORE_TYPE OUTPOST_BISHOP_PENALTY_MID =  -38;
constexpr SCORE_TYPE OUTPOST_BISHOP_PENALTY_END =  -12;

constexpr SCORE_TYPE SQUARE_OF_THE_PAWN_MID =  -17;
constexpr SCORE_TYPE SQUARE_OF_THE_PAWN_END =   63;

#endif //ALTAIRCHESSENGINE_EVALUATION_CONSTANTS_CPP
