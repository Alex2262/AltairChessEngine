//
// Created by Alex Tian on 9/29/2022.
//

#include "evaluation.h"
#include "move.h"

SCORE_TYPE evaluate(const Position& position) {

    SCORE_TYPE white_mid_material = 0;
    SCORE_TYPE white_end_material = 0;

    SCORE_TYPE white_mid_scores = 0;
    SCORE_TYPE white_end_scores = 0;

    SCORE_TYPE black_mid_material = 0;
    SCORE_TYPE black_end_material = 0;

    SCORE_TYPE black_mid_scores = 0;
    SCORE_TYPE black_end_scores = 0;

    int game_phase = 0;

    for (SQUARE_TYPE pos : position.white_pieces) {
        PIECE_TYPE piece = position.board[pos];

        game_phase += GAME_PHASE_SCORES[piece];

        white_mid_material += PIECE_VALUES_MID[piece];
        white_end_material += PIECE_VALUES_END[piece];

        white_mid_scores += PST_MID[piece][MAILBOX_TO_STANDARD[pos]];
        white_end_scores += PST_END[piece][MAILBOX_TO_STANDARD[pos]];
    }

    for (SQUARE_TYPE pos : position.black_pieces) {
        PIECE_TYPE piece = position.board[pos];

        game_phase += GAME_PHASE_SCORES[piece-6];

        black_mid_material += PIECE_VALUES_MID[piece - BLACK_PAWN];
        black_end_material += PIECE_VALUES_END[piece - BLACK_PAWN];

        black_mid_scores += PST_MID[piece - BLACK_PAWN][MAILBOX_TO_STANDARD[pos] ^ 56];
        black_end_scores += PST_END[piece - BLACK_PAWN][MAILBOX_TO_STANDARD[pos] ^ 56];
    }

    white_mid_scores += white_mid_material;
    white_end_scores += white_end_material;

    black_mid_scores += black_mid_material;
    black_end_scores += black_end_material;

    if (game_phase > 24) game_phase = 24; // In case of early promotions
    SCORE_TYPE white_score = (white_mid_scores * game_phase +
                              (24 - game_phase) * white_end_scores) / 24;

    SCORE_TYPE black_score = (black_mid_scores * game_phase +
                              (24 - game_phase) * black_end_scores) / 24;


    return (position.side * -2 + 1) * (white_score - black_score) + TEMPO_BONUS;
}


SCORE_TYPE score_move(Engine& engine, MOVE_TYPE move) {
    SCORE_TYPE score = 0;

    PIECE_TYPE selected = get_selected(move);
    PIECE_TYPE occupied = get_occupied(move);

    short move_type = get_move_type(move);

    if (selected < BLACK_PAWN) {
        if (get_is_capture(move)) {
            score += 10000;
            score += 2 * (PIECE_VALUES_MID[occupied - BLACK_PAWN] - PIECE_VALUES_MID[selected]);
        }
        else {
            // score 1st and 2nd killer move
            if (engine.killer_moves[0][engine.search_ply] == move) score += 9000;
            else if (engine.killer_moves[1][engine.search_ply] == move) score += 8000;
            else score += engine.history_moves[selected][MAILBOX_TO_STANDARD[get_target_square(move)]];
        }

        if (move_type == MOVE_TYPE_PROMOTION) score += 15000 + PIECE_VALUES_MID[get_promotion_piece(move)];
        else if (move_type == MOVE_TYPE_CASTLE) score += 1000;
        else if (move_type == MOVE_TYPE_EP) score += 2000;
    }
    else {
        if (get_is_capture(move)) {
            score += 10000;
            score += 2 * (PIECE_VALUES_MID[occupied] - PIECE_VALUES_MID[selected - BLACK_PAWN]);
        }
        else {
            // score 1st and 2nd killer move
            if (engine.killer_moves[0][engine.search_ply] == move) score += 9000;
            else if (engine.killer_moves[1][engine.search_ply] == move) score += 8000;
            else score += engine.history_moves[selected][MAILBOX_TO_STANDARD[get_target_square(move)]];
        }

        if (move_type == MOVE_TYPE_PROMOTION) score += 15000 + PIECE_VALUES_MID[get_promotion_piece(move) - BLACK_PAWN];
        else if (move_type == MOVE_TYPE_CASTLE) score += 1000;
        else if (move_type == MOVE_TYPE_EP) score += 2000;
    }

    return score;
}


SCORE_TYPE score_capture(MOVE_TYPE move) {
    SCORE_TYPE score = 0;

    PIECE_TYPE selected = get_selected(move);
    PIECE_TYPE occupied = get_occupied(move);

    if (selected < BLACK_PAWN) {
        score += PIECE_VALUES_MID[occupied - BLACK_PAWN] - PIECE_VALUES_MID[selected];
    }
    else {
        score += PIECE_VALUES_MID[occupied] - PIECE_VALUES_MID[selected - BLACK_PAWN];
    }

    return score;
}


void get_move_scores(Engine& engine, const std::vector<MOVE_TYPE>& moves, std::vector<SCORE_TYPE>& move_scores) {
    move_scores.clear();

    for (MOVE_TYPE move : moves) {
        move_scores.push_back(score_move(engine, move));
    }
}


void get_capture_scores(const std::vector<MOVE_TYPE>& moves, std::vector<SCORE_TYPE>& move_scores) {
    move_scores.clear();

    for (MOVE_TYPE move : moves) {
        move_scores.push_back(score_capture(move));
    }
}


void sort_next_move(std::vector<MOVE_TYPE>& moves, std::vector<SCORE_TYPE>& move_scores, int current_count) {
    for (int next_count = current_count; next_count < moves.size(); next_count++) {
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
