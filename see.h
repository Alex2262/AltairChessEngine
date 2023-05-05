//
// Created by Alexander Tian on 5/4/23.
//

#ifndef ALTAIRCHESSENGINE_SEE_H
#define ALTAIRCHESSENGINE_SEE_H

#include "constants.h"
#include "position.h"
#include "move.h"

constexpr SCORE_TYPE SEE_MOVE_ORDERING_THRESHOLD = -108;

constexpr SCORE_TYPE SEE_values[13] = {100, 350, 360, 560, 1300, 10000,
                                      100, 350, 360, 560, 1300, 10000, 0};

SQUARE_TYPE get_cheapest_attacker(Position& position, SQUARE_TYPE pos);
SCORE_TYPE get_static_exchange_evaluation(Position& position, MOVE_TYPE move, SCORE_TYPE threshold);

#endif //ALTAIRCHESSENGINE_SEE_H
