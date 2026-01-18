
#pragma once

#include "position.h"
#include "search.h"

double position_time_scale(const Position& position);

void time_handler(Engine& engine, double self_time, double inc, double movetime, long movestogo);
