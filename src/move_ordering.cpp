
#include <iostream>
#include "evaluation_constants.h"
#include "move_ordering.h"
#include "see.h"
#include "search.h"

SCORE_TYPE score_move(Thread_State& thread_state, Move move, Move tt_move,
                      InformativeMove last_moves[]) {
    assert(move != NO_MOVE);

    if (move == tt_move) return 100000;

    SCORE_TYPE score = 0;

    Position& position = thread_state.position;

    Piece selected = position.board[move.origin()];
    Piece occupied = position.board[move.target()];

    auto selected_type = get_piece_type(selected, position.side);

    MoveType move_type = move.type();
    InformativeMove informative_move = InformativeMove(move, selected, occupied);

    if (move_type == MOVE_TYPE_PROMOTION) {
        auto promotion_piece_type = static_cast<PieceType>(move.promotion_type() + 1);
        if (promotion_piece_type == QUEEN) {
            score += thread_state.move_ordering_parameters.queen_promotion_margin;
        } else {
            score = score + thread_state.move_ordering_parameters.other_promotion_margin +
                    MVV_LVA_VALUES[promotion_piece_type];
        }
    }

    if (move.is_capture(position)) {
        auto occupied_type = get_piece_type(occupied, ~position.side);
        score += thread_state.move_ordering_parameters.capture_scale * MVV_LVA_VALUES[occupied_type]
                - MVV_LVA_VALUES[selected_type];

        bool winning_capture = get_static_exchange_evaluation(position, move, SEE_MOVE_ORDERING_THRESHOLD);

        score += thread_state.capture_history[winning_capture][selected][occupied][move.target()];

        // Only Use SEE under certain conditions since it is expensive
        if (winning_capture)
            score += thread_state.move_ordering_parameters.winning_capture_margin;

        score += thread_state.move_ordering_parameters.base_capture_margin;
    }

    else {
        // score 1st and 2nd killer move
        if (thread_state.killer_moves[0][thread_state.search_ply] == informative_move) score +=
                thread_state.move_ordering_parameters.first_killer_margin;
        else if (thread_state.killer_moves[1][thread_state.search_ply] == informative_move) score +=
                thread_state.move_ordering_parameters.second_killer_margin;

        score += thread_state.history_moves[selected][move.target()];

        for (int last_move_index = 0; last_move_index < LAST_MOVE_COUNTS; last_move_index++) {
            if (last_moves[last_move_index] != NO_INFORMATIVE_MOVE) {
                score += thread_state.get_continuation_history_entry(last_moves[last_move_index], informative_move);
            }
        }

        if (move_type == MOVE_TYPE_EP) score += thread_state.move_ordering_parameters.winning_capture_margin +
                thread_state.move_ordering_parameters.capture_scale * (MVV_LVA_VALUES[PAWN] / 2);
        else if (move_type == MOVE_TYPE_CASTLE) score += thread_state.move_ordering_parameters.castle_margin;
    }

    return score;
}

SCORE_TYPE score_capture(Thread_State& thread_state, Move move, Move tt_move) {
    assert(move != NO_MOVE);

    if (move == tt_move) return 100000;

    SCORE_TYPE score = 0;

    Position& position = thread_state.position;

    Piece selected = position.board[move.origin()];
    Piece occupied = position.board[move.target()];

    auto selected_type = get_piece_type(selected, position.side);
    auto occupied_type = get_piece_type(occupied, ~position.side);

    bool winning_capture = get_static_exchange_evaluation(position, move, SEE_MOVE_ORDERING_THRESHOLD);

    score += thread_state.capture_history[winning_capture][selected][occupied][move.target()];

    if (winning_capture)
        score += thread_state.move_ordering_parameters.winning_capture_margin;

    score += thread_state.move_ordering_parameters.capture_scale * MVV_LVA_VALUES[occupied_type]
            - MVV_LVA_VALUES[selected_type];

    score += thread_state.move_ordering_parameters.base_capture_margin;

    return score;
}

void get_move_scores(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                     Move tt_move, InformativeMove last_moves[]) {
    for (ScoredMove& scored_move : current_scored_moves) {
        scored_move.score = score_move(thread_state, scored_move.move, tt_move, last_moves);
    }
}

void get_capture_scores(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                        Move tt_move) {
    for (ScoredMove& scored_move : current_scored_moves) {
        scored_move.score = score_capture(thread_state, scored_move.move, tt_move);
    }
}

Move sort_next_move(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, int current_count) {
	auto best_score = current_scored_moves[current_count].score;
	auto best_idx = current_count;
    for (auto next_count = current_count + 1; next_count < static_cast<int>(current_scored_moves.size()); next_count++) {
        if (best_score < current_scored_moves[next_count].score) {
			best_score = current_scored_moves[next_count].score;
			best_idx = next_count;
        }
    }
	std::swap(current_scored_moves[current_count], current_scored_moves[best_idx]);
	return current_scored_moves[current_count].move;
}

Generator::Generator(Thread_State& thread_state_passed) {
    thread_state = &thread_state_passed;
    position = &thread_state->position;
}

void Generator::reset_qsearch(Move tt_move_passed) {
    moves_generated = false;
    tt_probe_successful = false;

    stage = Stage::TT_probe;
    tt_move = tt_move_passed;

    move_index = 0;
}

void Generator::reset_negamax(Move tt_move_passed, InformativeMove last_moves_passed[]) {
    moves_generated = false;
    tt_probe_successful = false;

    stage = Stage::TT_probe;
    tt_move = tt_move_passed;

    move_index = 0;

    for (int last_move_i = 0; last_move_i < LAST_MOVE_COUNTS; last_move_i++) {
        last_moves[last_move_i] = last_moves_passed[last_move_i];
    }
}