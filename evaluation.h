//
// Created by Alex Tian on 9/29/2022.
//

#ifndef ANTARESCHESSENGINE_EVALUATION_H
#define ANTARESCHESSENGINE_EVALUATION_H

#include "constants.h"
#include "position.h"
#include "search.h"

SCORE_TYPE evaluate(const Position& position);

SCORE_TYPE score_move(Engine& engine, MOVE_TYPE move);
SCORE_TYPE score_capture(MOVE_TYPE move);

void get_move_scores(Engine& engine, const std::vector<MOVE_TYPE>& moves, std::vector<SCORE_TYPE>& move_scores);
void get_capture_scores(const std::vector<MOVE_TYPE>& moves, std::vector<SCORE_TYPE>& move_scores);
void sort_next_move(std::vector<MOVE_TYPE>& moves, std::vector<SCORE_TYPE>& move_scores, int current_count);

#endif //ANTARESCHESSENGINE_EVALUATION_H
