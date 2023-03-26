//
// Created by Alex Tian on 9/29/2022.
//

#ifndef ANTARESCHESSENGINE_EVALUATION_H
#define ANTARESCHESSENGINE_EVALUATION_H

#include "constants.h"
#include "position.h"
#include "search.h"
#include "cmath"

struct Score_Struct {
    SCORE_TYPE mid;
    SCORE_TYPE end;
};

inline SCORE_TYPE get_distance(SQUARE_TYPE square_1, SQUARE_TYPE square_2) {
    SQUARE_TYPE row_1 = 8 - square_1 / 8, col_1 = square_1 % 8 + 1;
    SQUARE_TYPE row_2 = 8 - square_2 / 8, col_2 = square_2 % 8 + 1;

    return abs(row_1 - row_2) + abs(col_1 - col_2);
}

void evaluate_king_pawn(const Position& position, Score_Struct& scores, SQUARE_TYPE file, bool is_white);
void evaluate_pawn(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white);
void evaluate_knight(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white);
void evaluate_bishop(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white);
void evaluate_rook(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white);
void evaluate_queen(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white);
void evaluate_king(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white);

double evaluate_drawishness(const int white_piece_amounts[6], const int black_piece_amounts[6],
                            SCORE_TYPE white_material, SCORE_TYPE black_material, bool opp_colored_bishops);
SCORE_TYPE evaluate(Position& position);

SCORE_TYPE score_move(const Engine& engine, MOVE_TYPE move, MOVE_TYPE tt_move, MOVE_TYPE last_move);
SCORE_TYPE score_capture(MOVE_TYPE move, MOVE_TYPE tt_move);

void get_move_scores(const Engine& engine, const std::vector<MOVE_TYPE>& moves, std::vector<SCORE_TYPE>& move_scores,
                     MOVE_TYPE tt_move, MOVE_TYPE last_move);
void get_capture_scores(const std::vector<MOVE_TYPE>& moves, std::vector<SCORE_TYPE>& move_scores,
                        MOVE_TYPE tt_move);
void sort_next_move(std::vector<MOVE_TYPE>& moves, std::vector<SCORE_TYPE>& move_scores, int current_count);

#endif //ANTARESCHESSENGINE_EVALUATION_H
