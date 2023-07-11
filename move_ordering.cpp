//
// Created by Alexander Tian on 6/26/23.
//

#include <iostream>
#include "evaluation_constants.h"
#include "move_ordering.h"
#include "see.h"

SCORE_TYPE score_move(Thread_State& thread_state, Move move, Move tt_move,
                      InformativeMove last_move_one, InformativeMove last_move_two) {
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
        
        score += thread_state.capture_history[selected][occupied][move.target()];
        score += thread_state.move_ordering_parameters.capture_scale * MVV_LVA_VALUES[occupied_type]
                - MVV_LVA_VALUES[selected_type];

        // Only Use SEE under certain conditions since it is expensive
        if (score >= -3000) {
            if (score >= 3000 ||
                get_static_exchange_evaluation(position, move, SEE_MOVE_ORDERING_THRESHOLD))
                score += thread_state.move_ordering_parameters.winning_capture_margin;
        }

        score += thread_state.move_ordering_parameters.base_capture_margin;
    }

    else {
        // score 1st and 2nd killer move
        if (thread_state.killer_moves[0][thread_state.search_ply] == informative_move) score +=
                thread_state.move_ordering_parameters.first_killer_margin;
        else if (thread_state.killer_moves[1][thread_state.search_ply] == informative_move) score +=
                thread_state.move_ordering_parameters.second_killer_margin;

        score += thread_state.history_moves[selected][move.target()];

        if (last_move_one != NO_INFORMATIVE_MOVE) {
            score += thread_state.continuation_history[last_move_one.selected()]
            [last_move_one.target()][selected][move.target()];
        }

        if (last_move_two != NO_INFORMATIVE_MOVE) {
            score += thread_state.continuation_history[last_move_two.selected()]
            [last_move_two.target()][selected][move.target()];
        }

        if (move_type == MOVE_TYPE_EP) score += thread_state.move_ordering_parameters.winning_capture_margin +
                thread_state.move_ordering_parameters.capture_scale * (MVV_LVA_VALUES[PAWN] / 2);
        else if (move_type == MOVE_TYPE_CASTLE) score += thread_state.move_ordering_parameters.castle_margin;
    }

    return score;
}

SCORE_TYPE score_capture(Thread_State& thread_state, Move move, Move tt_move) {
    if (move == tt_move) return 100000;

    SCORE_TYPE score = 0;

    Position& position = thread_state.position;

    Piece selected = position.board[move.origin()];
    Piece occupied = position.board[move.target()];

    score += thread_state.capture_history[selected][occupied][move.target()];

    if (score >= -3000) {
        if (score >= 3000 || get_static_exchange_evaluation(position, move, SEE_MOVE_ORDERING_THRESHOLD))
            score += thread_state.move_ordering_parameters.winning_capture_margin;
    }

    if (selected < BLACK_PAWN) score += MVV_LVA_VALUES[occupied - BLACK_PAWN] - MVV_LVA_VALUES[selected];
    else score += MVV_LVA_VALUES[occupied] - MVV_LVA_VALUES[selected - BLACK_PAWN];

    return score;
}

void get_move_scores(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                     Move tt_move, InformativeMove last_move_one, InformativeMove last_move_two) {
    for (ScoredMove& scored_move : current_scored_moves) {
        scored_move.score = score_move(thread_state, scored_move.move, tt_move, last_move_one, last_move_two);
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
