//
// Created by Alex Tian on 9/29/2022.
//

#ifndef ANTARESCHESSENGINE_EVALUATION_H
#define ANTARESCHESSENGINE_EVALUATION_H

#include "constants.h"
#include "position.h"
#include "search.h"

struct Score_Struct {
    SCORE_TYPE mid;
    SCORE_TYPE end;
};

void evaluate_pawn(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white);
SCORE_TYPE evaluate(Position& position);

SCORE_TYPE score_move(Engine& engine, MOVE_TYPE move, MOVE_TYPE tt_move, MOVE_TYPE last_move);
SCORE_TYPE score_capture(MOVE_TYPE move, MOVE_TYPE tt_move);

void get_move_scores(Engine& engine, const std::vector<MOVE_TYPE>& moves, std::vector<SCORE_TYPE>& move_scores,
                     MOVE_TYPE tt_move, MOVE_TYPE last_move);
void get_capture_scores(const std::vector<MOVE_TYPE>& moves, std::vector<SCORE_TYPE>& move_scores, MOVE_TYPE tt_move);
void sort_next_move(std::vector<MOVE_TYPE>& moves, std::vector<SCORE_TYPE>& move_scores, int current_count);

#endif //ANTARESCHESSENGINE_EVALUATION_H
