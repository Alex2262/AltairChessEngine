

#ifndef ALTAIR_SEE_H
#define ALTAIR_SEE_H

#include "constants.h"
#include "position.h"
#include "move.h"

constexpr SCORE_TYPE SEE_values[13] = {100, 350, 360, 560, 1300, 10000,
                                       100, 350, 360, 560, 1300, 10000, 0};

BITBOARD get_all_attackers(Position& position, Square square);
SCORE_TYPE get_static_exchange_evaluation(Position& position, Move move, SCORE_TYPE threshold);

#endif //ALTAIR_SEE_H
