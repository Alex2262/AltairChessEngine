
#include <iostream>
#include "evaluation_constants.h"
#include "move_ordering.h"
#include "see.h"
#include "search.h"
#include "search_parameters.h"


Score score_all(Thread_State& thread_state, ScoredMove& scored_move, Move tt_move, InformativeMove last_moves[]) {
    Move move = scored_move.move;
    assert(move != NO_MOVE);

    if (move == tt_move) return static_cast<Score>(MO_Margin::TT);

    Score score = 0;

    Position& position = thread_state.position;

    Piece selected = position.board[move.origin()];
    Piece occupied = position.board[move.target()];

    auto selected_type = get_piece_type(selected, position.side);

    MoveType move_type = move.type();

    if (move_type == MOVE_TYPE_PROMOTION) {
        auto promotion_piece_type = static_cast<PieceType>(move.promotion_type() + 1);
        if (promotion_piece_type == QUEEN) score += static_cast<Score>(MO_Margin::queen_promotion);
        else score += static_cast<Score>(MO_Margin::other_promotion) + MVV_LVA_VALUES[promotion_piece_type];
    }

    else if (move_type == MOVE_TYPE_CASTLE) {
        score += static_cast<Score>(MO_Margin::castle);
    }

    if (move.is_capture(position) || move_type == MOVE_TYPE_EP) {
        bool winning_capture = get_static_exchange_evaluation(position, move, -search_params.SEE_MO_threshold.v);
        scored_move.winning_capture = winning_capture;

        if (winning_capture) score += static_cast<Score>(MO_Margin::winning_capture);
        else score += static_cast<Score>(MO_Margin::base_capture);

        score += thread_state.capture_history[false][selected][occupied][move.target()];

        if (move_type == MOVE_TYPE_EP) {
            score += static_cast<Score>(MO_Margin::capture_scale) * (MVV_LVA_VALUES[PAWN] / 2);
        } else {
            auto occupied_type = get_piece_type(occupied, ~position.side);
            score += static_cast<Score>(MO_Margin::capture_scale) * MVV_LVA_VALUES[occupied_type] -
                     MVV_LVA_VALUES[selected_type];
        }
    }

    else {
        InformativeMove informative_move = InformativeMove(move, selected, occupied);

        // score 1st and 2nd killer move
        if (thread_state.killer_moves[0][thread_state.search_ply] == informative_move) score += static_cast<Score>(MO_Margin::killer_1);
        else if (thread_state.killer_moves[1][thread_state.search_ply] == informative_move) score += static_cast<Score>(MO_Margin::killer_2);

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


Score score_q_bn(Thread_State& thread_state, Move move, Move tt_move,
                      InformativeMove last_moves[]) {
    assert(move != NO_MOVE);

    if (move == tt_move) return static_cast<Score>(MO_Margin::TT);

    Score score = 0;

    Position& position = thread_state.position;

    Piece selected = position.board[move.origin()];
    Piece occupied = position.board[move.target()];

    auto selected_type = get_piece_type(selected, position.side);

    MoveType move_type = move.type();

    if (move_type == MOVE_TYPE_PROMOTION) {
        auto promotion_piece_type = static_cast<PieceType>(move.promotion_type() + 1);
        if (promotion_piece_type == QUEEN) score += static_cast<Score>(MO_Margin::queen_promotion);
        else score += static_cast<Score>(MO_Margin::other_promotion) + MVV_LVA_VALUES[promotion_piece_type];
    }

    else if (move_type == MOVE_TYPE_CASTLE) {
        score += static_cast<Score>(MO_Margin::castle);
    }

    // No EP moves appear as Q_BN
    if (move.is_capture(position)) {
        auto occupied_type = get_piece_type(occupied, ~position.side);
        score += static_cast<Score>(MO_Margin::capture_scale) * MVV_LVA_VALUES[occupied_type] -
                 MVV_LVA_VALUES[selected_type];

        // All captures are not winning in Q_BN;
        score += thread_state.capture_history[false][selected][occupied][move.target()];
        score += static_cast<Score>(MO_Margin::base_capture);
    }

    else {

        InformativeMove informative_move = InformativeMove(move, selected, occupied);

        // score 1st and 2nd killer move
        if (thread_state.killer_moves[0][thread_state.search_ply] == informative_move) score +=
                static_cast<Score>(MO_Margin::killer_1);
        else if (thread_state.killer_moves[1][thread_state.search_ply] == informative_move) score +=
                static_cast<Score>(MO_Margin::killer_2);

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
Score score_capture(Thread_State& thread_state, ScoredMove& scored_move, Move tt_move, size_t& good_capture_count) {

    Move move = scored_move.move;

    assert(move != NO_MOVE);

    if (move == tt_move) return static_cast<Score>(MO_Margin::TT);

    Score score = 0;

    Position& position = thread_state.position;

    Piece selected = position.board[move.origin()];
    Piece occupied = position.board[move.target()];
    MoveType move_type = move.type();

    bool winning_capture = get_static_exchange_evaluation(position, move, -search_params.SEE_MO_threshold.v);

    if (winning_capture) {
        score += static_cast<Score>(MO_Margin::winning_capture);
        scored_move.winning_capture = true;
        good_capture_count++;
    }

    else {
        scored_move.winning_capture = false;
        if constexpr (!qsearch) return BAD_SCORE;  // Skip scoring the bad capture currently, as it will be scored fully later
    }

    score += thread_state.capture_history[winning_capture][selected][occupied][move.target()];

    if (move_type == MOVE_TYPE_EP) return score + static_cast<Score>(MO_Margin::capture_scale) * (MVV_LVA_VALUES[PAWN] / 2);

    auto selected_type = get_piece_type(selected, position.side);
    auto occupied_type = get_piece_type(occupied, ~position.side);

    if (move_type == MOVE_TYPE_PROMOTION) {
        auto promotion_piece_type = static_cast<PieceType>(move.promotion_type() + 1);
        if (promotion_piece_type == QUEEN) score += static_cast<Score>(MO_Margin::queen_promotion);
        else score += static_cast<Score>(MO_Margin::other_promotion) + MVV_LVA_VALUES[promotion_piece_type];
    }

    score += static_cast<Score>(MO_Margin::capture_scale) * MVV_LVA_VALUES[occupied_type] - MVV_LVA_VALUES[selected_type];

    return score;
}

template Score score_capture<true >(Thread_State& thread_state, ScoredMove& scored_move, Move tt_move, size_t& good_capture_count);
template Score score_capture<false>(Thread_State& thread_state, ScoredMove& scored_move, Move tt_move, size_t& good_capture_count);

void get_all_scores(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                    Move tt_move, InformativeMove last_moves[]) {
    for (int i = 0; i < static_cast<int>(current_scored_moves.size()); i++) {
        ScoredMove& scored_move = current_scored_moves[i];
        scored_move.score = score_all(thread_state, scored_move, tt_move, last_moves);
    }
}

void get_q_bn_scores(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                     Move tt_move, InformativeMove last_moves[], int start_index) {
    for (int i = start_index; i < static_cast<int>(current_scored_moves.size()); i++) {
        ScoredMove& scored_move = current_scored_moves[i];
        scored_move.score = score_q_bn(thread_state, scored_move.move, tt_move, last_moves);
    }
}

template<bool qsearch>
void get_capture_scores(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                        Move tt_move, size_t& good_capture_count) {
    for (ScoredMove& scored_move : current_scored_moves) {
        assert(scored_move.move.type() != MOVE_TYPE_CASTLE);
        scored_move.score = score_capture<qsearch>(thread_state, scored_move, tt_move, good_capture_count);
    }
}

template void get_capture_scores<true >(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                                        Move tt_move, size_t& good_capture_count);
template void get_capture_scores<false>(Thread_State& thread_state, FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves,
                                        Move tt_move, size_t& good_capture_count);


MaxHeap::MaxHeap() {
    ordered = false;
}

bool MaxHeap::comp(FixedVector<ScoredMove, MAX_MOVES>& scored_moves, int ind1, int ind2) {
    Score s1 = scored_moves[ind1].score;
    Score s2 = scored_moves[ind2].score;

    return s1 > s2 || (s1 == s2 && scored_moves[ind1].move.internal_move() < scored_moves[ind2].move.internal_move());
}

void MaxHeap::sift_down(FixedVector<ScoredMove, MAX_MOVES>& scored_moves, int parent) {
    while (true) {
        int largest = parent;
        int c1 = parent * 2 + 1;
        int c2 = parent * 2 + 2;

        if (c1 < current_size && comp(scored_moves, c1, largest)) largest = c1;
        if (c2 < current_size && comp(scored_moves, c2, largest)) largest = c2;

        if (largest == parent) break;

        std::swap(scored_moves[parent], scored_moves[largest]);
        parent = largest;
    }
}

void MaxHeap::heapify(FixedVector<ScoredMove, MAX_MOVES>& scored_moves) {
    current_size = scored_moves.size();
    for (int parent = current_size / 2 - 1; parent >= 0; parent--) {
        sift_down(scored_moves, parent);
    }
    ordered = true;
}

ScoredMove MaxHeap::extract(FixedVector<ScoredMove, MAX_MOVES>& scored_moves) {
    if (!ordered) {
        scored_moves[0] = scored_moves[current_size - 1];
        sift_down(scored_moves, 0);
        current_size--;
    }

    ordered = false;

    assert(current_size > 0);
    return scored_moves[0];
}


Generator::Generator(Thread_State& thread_state_passed) {
    thread_state = &thread_state_passed;
    position = &thread_state->position;
    scored_moves.clear();
    max_heap = MaxHeap();
}

void Generator::reset_qsearch(Move tt_move_passed) {
    stage = Stage::TT_probe;
    tt_move = tt_move_passed;
    gen_all = false;

    move_index = 0;
}

void Generator::reset_negamax(Move tt_move_passed, bool p_gen_all, InformativeMove last_moves_passed[]) {
    stage = Stage::TT_probe;
    tt_move = tt_move_passed;
    gen_all = p_gen_all;

    move_index = 0;

    for (int last_move_i = 0; last_move_i < LAST_MOVE_COUNTS; last_move_i++) {
        last_moves[last_move_i] = last_moves_passed[last_move_i];
    }
}