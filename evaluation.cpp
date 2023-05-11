//
// Created by Alex Tian on 9/29/2022.
//

#include "evaluation.h"
#include "move.h"
#include "see.h"


SCORE_TYPE evaluate(Position& position) {

    SCORE_TYPE material = 0;

    for (SQUARE_TYPE pos : position.white_pieces) {
        material += PIECE_VALUES[position.board[pos]];
    }

    for (SQUARE_TYPE pos : position.black_pieces) {
        material -= PIECE_VALUES[position.board[pos]];
    }

    return (position.side * -2 + 1) * material;
}


SCORE_TYPE score_move(const Engine& engine, Position& position, MOVE_TYPE move, MOVE_TYPE tt_move, MOVE_TYPE last_move) {

    if (move == tt_move) return 100000;

    SCORE_TYPE score = 0;

    PIECE_TYPE selected = get_selected(move);
    PIECE_TYPE occupied = get_occupied(move);

    short move_type = get_move_type(move);

    if (selected < BLACK_PAWN) {
        if (get_is_capture(move)) {
            score += 20000 * get_static_exchange_evaluation(position, move, SEE_MOVE_ORDERING_THRESHOLD);
            score += 2 * (MVV_LVA_VALUES[occupied - BLACK_PAWN] - MVV_LVA_VALUES[selected]);
            score += engine.capture_history[selected][occupied][MAILBOX_TO_STANDARD[get_target_square(move)]];
        }
        else {
            if (last_move != NO_MOVE &&
                engine.counter_moves[0][MAILBOX_TO_STANDARD[get_origin_square(last_move)]]
                                    [MAILBOX_TO_STANDARD[get_target_square(last_move)]] == move) score += 8000;

            // score 1st and 2nd killer move
            if (engine.killer_moves[0][engine.search_ply] == move) score += 12000;
            else if (engine.killer_moves[1][engine.search_ply] == move) score += 11000;
            else score += engine.history_moves
                     [selected][MAILBOX_TO_STANDARD[get_target_square(move)]];

            if (move_type == MOVE_TYPE_PROMOTION) {
                PIECE_TYPE promotion_piece = get_promotion_piece(move);
                if (promotion_piece == WHITE_QUEEN) {
                    score += 30000;
                } else {
                    score = score - 2000 + MVV_LVA_VALUES[promotion_piece];
                }
            }
            else if (move_type == MOVE_TYPE_EP) score += 20050;
            else if (move_type == MOVE_TYPE_CASTLE) score += 1200;
        }

        score += MO_PST[selected][MAILBOX_TO_STANDARD[get_target_square(move)]] -
                 MO_PST[selected][MAILBOX_TO_STANDARD[get_origin_square(move)]];
    }
    else {
        if (get_is_capture(move)) {
            score += 20000 * get_static_exchange_evaluation(position, move, SEE_MOVE_ORDERING_THRESHOLD);
            score += 2 * (MVV_LVA_VALUES[occupied] - MVV_LVA_VALUES[selected - BLACK_PAWN]);
            score += engine.capture_history[selected][occupied][MAILBOX_TO_STANDARD[get_target_square(move)]];
        }
        else {
            if (last_move != NO_MOVE &&
                engine.counter_moves[1][MAILBOX_TO_STANDARD[get_origin_square(last_move)]]
                                    [MAILBOX_TO_STANDARD[get_target_square(last_move)]] == move) score += 8000;

            // score 1st and 2nd killer move
            if (engine.killer_moves[0][engine.search_ply] == move) score += 12000;
            else if (engine.killer_moves[1][engine.search_ply] == move) score += 11000;
            else score += engine.history_moves[selected][MAILBOX_TO_STANDARD[get_target_square(move)]];

            if (move_type == MOVE_TYPE_PROMOTION) {
                PIECE_TYPE promotion_piece = get_promotion_piece(move) - BLACK_PAWN;
                if (promotion_piece == WHITE_QUEEN) {
                    score += 30000;
                } else {
                    score = score - 2000 + MVV_LVA_VALUES[promotion_piece];
                }
            }
            else if (move_type == MOVE_TYPE_EP) score += 20050;
            else if (move_type == MOVE_TYPE_CASTLE) score += 1200;
        }

        score += MO_PST[selected - BLACK_PAWN][MAILBOX_TO_STANDARD[get_target_square(move)] ^ 56] -
                 MO_PST[selected - BLACK_PAWN][MAILBOX_TO_STANDARD[get_origin_square(move)] ^ 56];
    }

    return score;
}


SCORE_TYPE score_capture(const Engine& engine, Position& position, MOVE_TYPE move, MOVE_TYPE tt_move) {

    if (move == tt_move) return 100000;

    SCORE_TYPE score = 0;

    PIECE_TYPE selected = get_selected(move);
    PIECE_TYPE occupied = get_occupied(move);

    score += 20000 * get_static_exchange_evaluation(position, move, SEE_MOVE_ORDERING_THRESHOLD);

    if (selected < BLACK_PAWN) {
        score += MVV_LVA_VALUES[occupied - BLACK_PAWN] - MVV_LVA_VALUES[selected];
    }
    else {
        score += MVV_LVA_VALUES[occupied] - MVV_LVA_VALUES[selected - BLACK_PAWN];
    }

    score += engine.capture_history[selected][occupied][MAILBOX_TO_STANDARD[get_target_square(move)]];

    return score;
}


void get_move_scores(const Engine& engine, Position& position, const std::vector<MOVE_TYPE>& moves, std::vector<SCORE_TYPE>& move_scores,
                     MOVE_TYPE tt_move, MOVE_TYPE last_move) {
    move_scores.clear();

    for (MOVE_TYPE move : moves) {
        move_scores.push_back(score_move(engine, position, move, tt_move, last_move));
    }
}


void get_capture_scores(const Engine& engine, Position& position, const std::vector<MOVE_TYPE>& moves, std::vector<SCORE_TYPE>& move_scores,
                        MOVE_TYPE tt_move) {
    move_scores.clear();

    for (MOVE_TYPE move : moves) {
        move_scores.push_back(score_capture(engine, position, move, tt_move));
    }
}


void sort_next_move(std::vector<MOVE_TYPE>& moves, std::vector<SCORE_TYPE>& move_scores, int current_count) {
    for (int next_count = current_count; next_count < static_cast<int>(moves.size()); next_count++) {
        if (move_scores[current_count] < move_scores[next_count]) {
            MOVE_TYPE current_move = moves[current_count];
            moves[current_count] = moves[next_count];
            moves[next_count] = current_move;

            SCORE_TYPE current_score = move_scores[current_count];
            move_scores[current_count] = move_scores[next_count];
            move_scores[next_count] = current_score;
        }
    }
}
