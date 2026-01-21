
#pragma once

#include "constants.h"
#include "position.h"
#include "move.h"

constexpr Score SEE_values[13] = {100, 350, 360, 560, 1300, 10000,
                                       100, 350, 360, 560, 1300, 10000, 0};

Bitboard get_all_attackers(const Position& position, Square square);
Score get_static_exchange_evaluation(Position& position, Move move, Score threshold);
