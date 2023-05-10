//
// Created by Alex Tian on 9/29/2022.
//

#ifndef ANTARESCHESSENGINE_EVALUATION_H
#define ANTARESCHESSENGINE_EVALUATION_H

#include <iostream>
#include "constants.h"
#include "position.h"
#include "search.h"
#include "cmath"

struct Score_Struct {
    SCORE_TYPE mid;
    SCORE_TYPE end;
};

SCORE_TYPE evaluate(Position& position);

SCORE_TYPE score_move(const Engine& engine, Position& position, MOVE_TYPE move, MOVE_TYPE tt_move, MOVE_TYPE last_move);
SCORE_TYPE score_capture(const Engine& engine, Position& position, MOVE_TYPE move, MOVE_TYPE tt_move);

void get_move_scores(const Engine& engine, Position& position, const std::vector<MOVE_TYPE>& moves, std::vector<SCORE_TYPE>& move_scores,
                     MOVE_TYPE tt_move, MOVE_TYPE last_move);
void get_capture_scores(const Engine& engine, Position& position, const std::vector<MOVE_TYPE>& moves, std::vector<SCORE_TYPE>& move_scores,
                        MOVE_TYPE tt_move);
void sort_next_move(std::vector<MOVE_TYPE>& moves, std::vector<SCORE_TYPE>& move_scores, int current_count);

#endif //ANTARESCHESSENGINE_EVALUATION_H
