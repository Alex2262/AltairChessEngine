

#ifndef ALTAIR_MOVE_ORDERING_H
#define ALTAIR_MOVE_ORDERING_H

#include "types.h"
#include "search.h"
#include "fixed_vector.h"

constexpr SCORE_TYPE SEE_MOVE_ORDERING_THRESHOLD = -85;

SCORE_TYPE score_move(Thread_State& thread_state, Move move, Move tt_move,
                      InformativeMove last_moves[]);

SCORE_TYPE score_capture(Thread_State& thread_state, Move move, Move tt_move);

void get_move_scores(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                     Move tt_move, InformativeMove last_moves[]);

void get_capture_scores(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                        Move tt_move);

Move sort_next_move(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, int current_count);

#endif //ALTAIR_MOVE_ORDERING_H
