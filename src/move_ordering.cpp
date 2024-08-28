
#include <iostream>
#include "evaluation_constants.h"
#include "move_ordering.h"
#include "see.h"
#include "search.h"

SCORE_TYPE score_q_bn(Thread_State& thread_state, Move move, Move tt_move,
                      InformativeMove last_moves[]) {
    assert(move != NO_MOVE);

    if (move == tt_move) return static_cast<SCORE_TYPE>(MO_Margin::TT);

    SCORE_TYPE score = 0;

    Position& position = thread_state.position;

    Piece selected = position.board[move.origin()];
    Piece occupied = position.board[move.target()];

    auto selected_type = get_piece_type(selected, position.side);

    MoveType move_type = move.type();

    if (move_type == MOVE_TYPE_PROMOTION) {
        auto promotion_piece_type = static_cast<PieceType>(move.promotion_type() + 1);
        if (promotion_piece_type == QUEEN) score += static_cast<SCORE_TYPE>(MO_Margin::queen_promotion);
        else score += static_cast<SCORE_TYPE>(MO_Margin::other_promotion) + MVV_LVA_VALUES[promotion_piece_type];
    }

    else if (move_type == MOVE_TYPE_CASTLE) {
        score += static_cast<SCORE_TYPE>(MO_Margin::castle);
    }

    // No EP moves appear as Q_BN

    if (move.is_capture(position)) {
        auto occupied_type = get_piece_type(occupied, ~position.side);
        score += static_cast<SCORE_TYPE>(MO_Margin::capture_scale) * MVV_LVA_VALUES[occupied_type] -
                 MVV_LVA_VALUES[selected_type];

        // All captures are not winning in Q_BN;
        score += thread_state.capture_history[false][selected][occupied][move.target()];
        score += static_cast<SCORE_TYPE>(MO_Margin::base_capture);
    }

    else {

        InformativeMove informative_move = InformativeMove(move, selected, occupied);

        // score 1st and 2nd killer move
        if (thread_state.killer_moves[0][thread_state.search_ply] == informative_move) score +=
                static_cast<SCORE_TYPE>(MO_Margin::killer_1);
        else if (thread_state.killer_moves[1][thread_state.search_ply] == informative_move) score +=
                static_cast<SCORE_TYPE>(MO_Margin::killer_2);

        score += thread_state.history_moves[selected][move.target()]
                                           [(position.threats >> move.origin()) & 1]
                                           [(position.threats >> move.target()) & 1];

        for (int last_move_index = 0; last_move_index < LAST_MOVE_COUNTS; last_move_index++) {
            if (last_moves[last_move_index] != NO_INFORMATIVE_MOVE) {
                score += thread_state.get_continuation_history_entry(last_moves[last_move_index], informative_move);
            }
        }
    }

    return score;
}

template<bool qsearch>
SCORE_TYPE score_capture(Thread_State& thread_state, ScoredMove& scored_move, Move tt_move, int& good_capture_count) {

    Move move = scored_move.move;

    assert(move != NO_MOVE);

    if (move == tt_move) return static_cast<SCORE_TYPE>(MO_Margin::TT);

    SCORE_TYPE score = 0;

    Position& position = thread_state.position;

    Piece selected = position.board[move.origin()];
    Piece occupied = position.board[move.target()];
    MoveType move_type = move.type();

    bool winning_capture = get_static_exchange_evaluation(position, move, -search_params.SEE_MO_threshold.v);

    if (winning_capture) {
        score += static_cast<SCORE_TYPE>(MO_Margin::winning_capture);
        scored_move.winning_capture = true;
        good_capture_count++;
    }

    else {
        scored_move.winning_capture = false;
        if constexpr (!qsearch) return -1000000;  // Skip scoring the bad capture currently, as it will be scored fully later
    }

    score += thread_state.capture_history[winning_capture][selected][occupied][move.target()];

    if (move_type == MOVE_TYPE_EP) return score +
        static_cast<SCORE_TYPE>(MO_Margin::winning_capture) +
        static_cast<SCORE_TYPE>(MO_Margin::capture_scale) * (MVV_LVA_VALUES[PAWN] / 2);

    auto selected_type = get_piece_type(selected, position.side);
    auto occupied_type = get_piece_type(occupied, ~position.side);

    if (move_type == MOVE_TYPE_PROMOTION) {
        auto promotion_piece_type = static_cast<PieceType>(move.promotion_type() + 1);
        if (promotion_piece_type == QUEEN) score += static_cast<SCORE_TYPE>(MO_Margin::queen_promotion);
        else score += static_cast<SCORE_TYPE>(MO_Margin::other_promotion) + MVV_LVA_VALUES[promotion_piece_type];
    }

    score += static_cast<SCORE_TYPE>(MO_Margin::capture_scale) * MVV_LVA_VALUES[occupied_type] - MVV_LVA_VALUES[selected_type];

    score += static_cast<SCORE_TYPE>(MO_Margin::base_capture);

    return score;
}

template SCORE_TYPE score_capture<true >(Thread_State& thread_state, ScoredMove& scored_move, Move tt_move, int& good_capture_count);
template SCORE_TYPE score_capture<false>(Thread_State& thread_state, ScoredMove& scored_move, Move tt_move, int& good_capture_count);

void get_q_bn_scores(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                     Move tt_move, InformativeMove last_moves[], int start_index) {
    for (int i = start_index; i < static_cast<int>(current_scored_moves.size()); i++) {
        ScoredMove& scored_move = current_scored_moves[i];
        scored_move.score = score_q_bn(thread_state, scored_move.move, tt_move, last_moves);
    }
}

template<bool qsearch>
void get_capture_scores(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                        Move tt_move, int& good_capture_count) {
    for (ScoredMove& scored_move : current_scored_moves) {
        assert(scored_move.move.type() != MOVE_TYPE_CASTLE);
        scored_move.score = score_capture<qsearch>(thread_state, scored_move, tt_move, good_capture_count);
    }
}

template void get_capture_scores<true >(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                                        Move tt_move, int& good_capture_count);
template void get_capture_scores<false>(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                                        Move tt_move, int& good_capture_count);

Generator::Generator(Thread_State& thread_state_passed) {
    thread_state = &thread_state_passed;
    position = &thread_state->position;
}

void Generator::reset_qsearch(Move tt_move_passed) {

    stage = Stage::TT_probe;
    tt_move = tt_move_passed;

    move_index = 0;
}

void Generator::reset_negamax(Move tt_move_passed, InformativeMove last_moves_passed[]) {

    stage = Stage::TT_probe;
    tt_move = tt_move_passed;

    move_index = 0;

    for (int last_move_i = 0; last_move_i < LAST_MOVE_COUNTS; last_move_i++) {
        last_moves[last_move_i] = last_moves_passed[last_move_i];
    }
}