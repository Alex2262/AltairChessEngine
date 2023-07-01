//
// Created by Alexander Tian on 6/26/23.
//

#ifndef ALTAIRCHESSENGINE_EVALUATION_CONSTANTS_H
#define ALTAIRCHESSENGINE_EVALUATION_CONSTANTS_H

#include "evaluation.h"
#include "types.h"

constexpr int GAME_PHASE_SCORES[6] = {0, 1, 1, 2, 4, 0};

constexpr int MVV_LVA_VALUES[6] = {  87, 390, 429, 561,1234,   0};


constexpr SCORE_TYPE PIECE_VALUES[6] = {S( 117, 150), S( 437, 436), S( 438, 443), S( 592, 806), S(1341,1465), S(   0,   0)};

constexpr SCORE_TYPE PIECE_SQUARE_TABLES[6][64] = {
        {
                S( -32, -58), S( -32, -58), S( -32, -58), S( -32, -58), S( -32, -58), S( -32, -58), S( -32, -58), S( -32, -58),
                S(  93, 145), S( 110, 130), S(  28, 128), S(  84,  66), S(  37,  88), S( 144,  77), S( -18, 147), S( -41, 163),
                S( -17,  60), S(   7,  44), S(  33,  12), S(  37, -24), S(  59, -28), S(  93, -10), S(  32,  20), S(   5,  38),
                S( -21,  27), S(   0,   4), S(  -6,  -3), S(  19, -35), S(  20, -22), S(  32, -19), S(   8,  -2), S( -21,  11),
                S( -27,  13), S( -20,   2), S( -14, -11), S(   1, -18), S(   0, -15), S(  10, -19), S(  -4, -13), S( -23,  -6),
                S( -28,   1), S( -18,  -5), S( -16,  -8), S(  -9, -10), S(  -1,   5), S(   7,  -7), S(  20, -19), S( -10, -10),
                S( -31,  13), S( -19,   2), S( -30,  16), S( -20,   2), S( -24,  23), S(  28,   2), S(  32, -16), S( -14, -15),
                S( -32, -58), S( -32, -58), S( -32, -58), S( -32, -58), S( -32, -58), S( -32, -58), S( -32, -58), S( -32, -58)
        },
        {
                S(-236, -65), S(-132, -23), S( -92,  14), S( -10, -16), S( 106, -26), S(-150,  -1), S( -21, -69), S(-153,-117),
                S( -24, -28), S( -47,   8), S(  67,  -8), S(  42,  29), S(  48,  14), S(  82, -18), S(  -7, -13), S(   7, -42),
                S( -48, -15), S(  26,   9), S(  45,  39), S(  78,  45), S( 113,  17), S( 139,  18), S(  85,  -6), S(  62, -44),
                S(   6,  -3), S(  13,  39), S(  29,  57), S(  59,  62), S(  33,  67), S(  61,  58), S(  27,  41), S(  41,   4),
                S( -14,   5), S(  -9,  21), S(  14,  53), S(  22,  64), S(  33,  55), S(  28,  59), S(  51,  28), S(   2,   9),
                S( -29, -50), S( -12,   3), S(   5,  11), S(  10,  37), S(  24,  29), S(  17,   7), S(  18,  -5), S( -16,  -6),
                S( -46, -45), S( -34, -13), S(  -8, -19), S(   8,  10), S(   6,  22), S(   9, -19), S(  -4, -15), S(   5, -48),
                S(-137, -43), S( -26, -44), S( -40, -12), S( -26,  -2), S(  -9, -16), S( -10, -11), S( -23, -25), S( -57, -70)
        },
        {
                S( -68,  -4), S( -18,  -1), S(-145,  22), S( -94,  17), S( -90,  21), S(-100,   9), S( -50,   6), S(   7, -17),
                S( -38,   6), S(   2,   1), S( -19,  13), S( -27,  10), S(   6,   9), S(  41,  -2), S(   8,  -2), S( -28,  -4),
                S( -18,   9), S(  11,   8), S(  46,   0), S(  20,   5), S(  39,  -1), S(  47,  14), S(  44,  12), S(   3,  18),
                S( -25,   3), S(   9,  18), S(   3,  19), S(  57,  13), S(  33,  16), S(  37,   5), S(   8,  23), S(  -2,  16),
                S(  -4,  -9), S(   2,   6), S(   6,  17), S(  30,  17), S(  41,   4), S(  -7,  18), S(   5,   0), S(  23, -21),
                S(  -1, -17), S(  17,   0), S(  13,   4), S(  11,   6), S(   7,  21), S(  21,   1), S(  15,  -5), S(  21, -16),
                S(   5, -26), S(  19, -30), S(  28, -19), S(   3,  -7), S(  13, -11), S(  11, -24), S(  38,  -1), S(  13, -38),
                S(  28, -56), S(  14, -24), S(  -8,   3), S(  -7,  -7), S( -21,  -6), S( -12,   1), S( -18,  -1), S(  -1, -40)
        },
        {
                S(  25,  13), S(  27,  15), S(   6,  17), S(  11,  18), S(  63,   4), S(  55,   5), S(  19,  15), S( 109,  -2),
                S(   0,  20), S( -11,  28), S(  27,  17), S(  42,  16), S(  47,   8), S( 102, -13), S(  32,  11), S(  56,   1),
                S( -36,  22), S(   1,  13), S(  14,  12), S(  23,   8), S(  35,   1), S(  88,  -5), S( 113, -17), S(  53, -14),
                S( -35,  18), S( -22,  12), S(  -3,  18), S(  17,   7), S(  -3,  15), S(  27,   6), S(  -4,   8), S(  -4,   8),
                S( -54,  12), S( -54,  18), S( -41,  14), S( -30,  13), S( -31,   9), S( -10,  -4), S(   7,  -5), S( -18,  -8),
                S( -57,  -7), S( -40,  -5), S( -46,  -4), S( -35,  -4), S( -32,  -3), S( -14, -17), S(   6, -16), S( -26, -23),
                S( -62, -12), S( -35, -17), S( -43,  -5), S( -31, -13), S( -22, -16), S(  -8, -26), S(  -1, -31), S( -87,  -4),
                S( -26,  -8), S( -22,  -9), S( -13, -12), S(  -1, -23), S(  -5, -21), S(  -1, -16), S( -23, -10), S( -17, -32)
        },
        {
                S( -37, -13), S( -60,  60), S(  -9,  47), S(  22,  20), S(  86,  22), S( 102,  15), S(  83,   1), S(  57,  15),
                S( -25,  -9), S( -71,  33), S( -42,  48), S( -51,  67), S( -42,  91), S(  54,  57), S(  23,  53), S(  39,  40),
                S( -32, -18), S( -30,  -3), S(  -9,  -4), S( -36,  76), S(  -5,  86), S( 101,  43), S( 104,  35), S(  38,  93),
                S( -30, -35), S( -31,  11), S( -36,  30), S( -36,  54), S( -26,  87), S(   2,  85), S(   7,  93), S(  -3, 115),
                S( -23, -35), S( -20,  13), S( -14,  -4), S( -28,  51), S( -13,  32), S(  -5,  43), S(   9,  35), S(  -2,  35),
                S( -24, -33), S(   4, -85), S(  -8, -14), S(  -6, -32), S(  -7, -18), S(   0,  -5), S(  15, -22), S(  -5,  -4),
                S( -24, -63), S(   0, -84), S(  12,-100), S(   5, -62), S(  13, -80), S(  24,-109), S(  18,-106), S( -17, -45),
                S(   0, -74), S( -10, -70), S(  10, -84), S(  12,  -6), S(   5, -78), S(  -3, -98), S(  13, -98), S( -35, -95)
        },
        {
                S( -50,-106), S( 268, -87), S( 198, -54), S( 168, -56), S(-165,   7), S( -69,  32), S(  82, -10), S(  -1, -31),
                S( 227, -63), S( 109,  22), S( 102,  25), S( 104,  13), S(  88,  22), S(  59,  43), S( -38,  59), S(-145,  28),
                S(  59,  19), S( 121,  33), S(  92,  44), S(  17,  39), S(  84,  28), S( 127,  61), S( 145,  53), S( -33,  25),
                S(   1,   8), S(   4,  50), S(  18,  58), S( -17,  69), S( -66,  71), S(  -6,  63), S(   1,  53), S(-100,  27),
                S( -54, -12), S(  72,   2), S( -22,  50), S( -74,  72), S( -63,  72), S( -65,  58), S( -39,  34), S( -96,   6),
                S( -30, -14), S( -34,  19), S( -69,  41), S( -75,  56), S( -59,  53), S( -61,  41), S( -13,  14), S( -34, -10),
                S(  11, -31), S(  -1,  -9), S( -38,  21), S(-113,  39), S( -79,  35), S( -60,  26), S(  12,  -8), S(  29, -42),
                S(  20,-111), S(  65, -66), S(  18, -33), S( -92,  -3), S( -20, -35), S( -76,  -5), S(  33, -45), S(  33,-100)
        }
};


constexpr SCORE_TYPE PASSED_PAWN_BONUSES[3][8] = {
        {S(   0,   0), S(  -7,  24), S( -21,  36), S( -20,  67), S(  -7, 103), S(   9, 193), S(  67, 195), S(   0,   0)},
        {S(   0,   0), S(   0,   0), S(   5,  29), S(   0,  54), S(  23, 110), S(  64, 222), S( 373, 162), S(   0,   0)},
        {S(   0,   0), S(   0,   0), S(  59,  30), S( -18,  43), S(  62,  76), S( 140, 160), S( 167, 133), S(   0,   0)}
};


constexpr SCORE_TYPE PASSED_PAWN_BLOCKERS[6][8] = {
        {S(   0,   0), S(   0,   0), S(   0,   0), S(   0,   0), S(   0,   0), S(   0,   0), S(   0,   0), S(   0,   0)},
        {S(   0,   0), S(   0,   0), S(  15, -40), S( -28,   9), S( -11, -24), S( -21, -72), S( -14,-112), S( 191,-228)},
        {S(   0,   0), S(   0,   0), S( -17, -22), S( -12, -42), S(  -8, -41), S(   4, -67), S( -11,-134), S(  85,-260)},
        {S(   0,   0), S(   0,   0), S(   5, -15), S( -25,  29), S(  -1,   3), S(  19,  -9), S(  16, -58), S(  21,-129)},
        {S(   0,   0), S(   0,   0), S( -17,  -2), S( -59,  64), S(   8, -35), S(   4,  -4), S(  25, -53), S(  86,  69)},
        {S(   0,   0), S(   0,   0), S(  49, -10), S(  59, -16), S( -64, -36), S(  -9, -88), S( -31,-196), S(   0,-315)}
};


constexpr SCORE_TYPE PASSED_PAWN_BLOCKERS_2[6][8] = {
        {S(   0,   0), S(   0,   0), S(   0,   0), S(   0,   0), S(   0,   0), S(   0,   0), S(   0,   0), S(   0,   0)},
        {S(   0,   0), S(   0,   0), S(   0,   0), S( -20, -12), S( -33,  -1), S(  -8, -10), S(   9, -28), S(  46,-112)},
        {S(   0,   0), S(   0,   0), S(   0,   0), S( -24,   2), S( -25,   1), S( -30,  -2), S(  -9, -37), S(  26, -77)},
        {S(   0,   0), S(   0,   0), S(   0,   0), S(   4, -12), S(  26, -19), S(   0,  16), S(   5,   9), S(  38, -55)},
        {S(   0,   0), S(   0,   0), S(   0,   0), S(   6,  17), S( -13,   9), S(  -1, -15), S(  29, -48), S(  25,  75)},
        {S(   0,   0), S(   0,   0), S(   0,   0), S( 205,   3), S(  49,   7), S( -44,  -2), S(  29, -50), S(  79,-158)}
};


constexpr SCORE_TYPE PHALANX_PAWN_BONUSES[8] = {S(   0,   0), S(   0, -12), S(   1,  -5), S(  16,   7), S(  38,  68), S(  49, 150), S(  22, 416), S(   0,   0)};

constexpr SCORE_TYPE ISOLATED_PAWN_PENALTY = S(  -8, -47);

constexpr SCORE_TYPE BISHOP_PAIR_BONUS = S(  27,  79);

constexpr SCORE_TYPE TEMPO_BONUS = S(  14,  21);

constexpr SCORE_TYPE MOBILITY_VALUES[6] = {S(   0,   0), S(   6,   0), S(   8,   5), S(   5,   3), S(   3,   3), S(   0,   0)};

constexpr SCORE_TYPE SEMI_OPEN_FILE_VALUES[6] = {S(   0,   0), S(   0,   0), S(   0,   0), S(  16,  16), S(  -2,  31), S( -36,  10)};

constexpr SCORE_TYPE OPEN_FILE_VALUES[6] = {S(   0,   0), S(   0,   0), S(   0,   0), S(  50,   1), S(  -3,  25), S( -69,  -2)};

#endif //ALTAIRCHESSENGINE_EVALUATION_CONSTANTS_H
