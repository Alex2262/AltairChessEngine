//
// Created by Alexander Tian on 4/16/24.
//

#ifndef ALTAIRCHESSENGINE_TIMEMAN_H
#define ALTAIRCHESSENGINE_TIMEMAN_H

#endif //ALTAIRCHESSENGINE_TIMEMAN_H

#include "position.h"
#include "search.h"

double position_time_scale(Position& position);

void time_handler(Engine& engine, double self_time, double inc, double movetime, long movestogo);