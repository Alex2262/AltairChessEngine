//
// Created by Alexander Tian on 6/26/23.
//

#ifndef ALTAIRCHESSENGINE_MOVE_ORDERING_H
#define ALTAIRCHESSENGINE_MOVE_ORDERING_H

#include "types.h"
#include "search.h"
#include "fixed_vector.h"

constexpr SCORE_TYPE SEE_MOVE_ORDERING_THRESHOLD = -108;

SCORE_TYPE score_move(Thread_State& thread_state, Move move, Move tt_move,
                      InformativeMove last_move_one, InformativeMove last_move_two);

SCORE_TYPE score_capture(Thread_State& thread_state, Move move, Move tt_move);

void get_move_scores(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                     Move tt_move, InformativeMove last_move_one, InformativeMove last_move_two);

void get_capture_scores(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                        Move tt_move);

Move sort_next_move(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, int current_count);

#endif //ALTAIRCHESSENGINE_MOVE_ORDERING_H
