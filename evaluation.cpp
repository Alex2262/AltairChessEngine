//
// Created by Alex Tian on 9/29/2022.
//

#include "evaluation.h"
#include "move.h"


void evaluate_pawn(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white) {

    SQUARE_TYPE i = MAILBOX_TO_STANDARD[pos];
    SQUARE_TYPE row = 8 - i / 8, col = i % 8 + 1;

    if (is_white) {
        // Doubled pawns. The pawn we are checking is higher in row compared to
        // the least advanced pawn in our column.
        if (row > position.pawn_rank[0][col]) {
            scores.mid -= DOUBLED_PAWN_PENALTY_MID;
            scores.end -= DOUBLED_PAWN_PENALTY_END;
        }

        // Isolated pawns. We do not have pawns on the columns next to our pawn.
        if (position.pawn_rank[0][col - 1] == 9 && position.pawn_rank[0][col + 1] == 9) {
            // If our opponent does not have a pawn in front of our pawn
            if (position.pawn_rank[1][col] == 0) {
                // The isolated pawn in the middle game is worse if the opponent
                // has the semi open file to attack it.
                scores.mid -= 1.5 * ISOLATED_PAWN_PENALTY_MID;

                // In the endgame it can be slightly better since it has the chance to become passed
                scores.end -= 0.8 * ISOLATED_PAWN_PENALTY_END;
            }
            else {
                scores.mid -= ISOLATED_PAWN_PENALTY_MID;
                scores.end -= ISOLATED_PAWN_PENALTY_END;
            }
        }

        // Backwards pawn
        else if (row < position.pawn_rank[0][col - 1] && row < position.pawn_rank[0][col + 1]) {
            // In the middle game it's worse to have a very backwards pawn
            // since then, the 'forwards' pawns won't be protected
            scores.mid -= BACKWARDS_PAWN_PENALTY_MID +
                          2 * (position.pawn_rank[0][col - 1] - row + position.pawn_rank[0][col + 1] - row - 2);

            // In the end game the backwards pawn should be worse, but if it's very backwards it's not awful.
            scores.end -= BACKWARDS_PAWN_PENALTY_END +
                          position.pawn_rank[0][col - 1] - row + position.pawn_rank[0][col + 1] - row - 2;

            // If there's no enemy pawn in front of our pawn then it's even worse, since
            // we allow outposts and pieces to attack us easily
            if (position.pawn_rank[1][col] == 0) scores.mid -= 3 * BACKWARDS_PAWN_PENALTY_MID;
        }

        // Passed Pawn Bonus
        if (row >= position.pawn_rank[1][col - 1] &&
            row >= position.pawn_rank[1][col] &&
            row >= position.pawn_rank[1][col + 1]) {

            scores.mid += row * PASSED_PAWN_BONUS_MID;
            scores.end += row * PASSED_PAWN_BONUS_END;
        }
    }

    else {
        // Doubled pawns. The pawn we are checking is higher in row compared to
        // the least advanced pawn in our column.
        if (row < position.pawn_rank[1][col]) {
            scores.mid -= DOUBLED_PAWN_PENALTY_MID;
            scores.end -= DOUBLED_PAWN_PENALTY_END;
        }

        // Isolated pawns. We do not have pawns on the columns next to our pawn.
        if (position.pawn_rank[1][col - 1] == 0 && position.pawn_rank[1][col + 1] == 0) {
            // If our opponent does not have a pawn in front of our pawn
            if (position.pawn_rank[0][col] == 9) {
                // The isolated pawn in the middle game is worse if the opponent
                // has the semi open file to attack it.
                scores.mid -= 1.5 * ISOLATED_PAWN_PENALTY_MID;

                // In the endgame it can be slightly better since it has the chance to become passed
                scores.end -= 0.8 * ISOLATED_PAWN_PENALTY_END;
            }
            else {
                scores.mid -= ISOLATED_PAWN_PENALTY_MID;
                scores.end -= ISOLATED_PAWN_PENALTY_END;
            }
        }

        // Backwards pawn
        else if (row > position.pawn_rank[1][col - 1] && row > position.pawn_rank[1][col + 1]) {
            // In the middle game it's worse to have a very backwards pawn
            // since then, the 'forwards' pawns won't be protected
            scores.mid -= BACKWARDS_PAWN_PENALTY_MID +
                          2 * (row - position.pawn_rank[1][col - 1] + row - position.pawn_rank[1][col + 1] - 2);

            // In the end game the backwards pawn should be worse, but if it's very backwards it's not awful.
            scores.end -= BACKWARDS_PAWN_PENALTY_END +
                          row - position.pawn_rank[1][col - 1] + row - position.pawn_rank[1][col + 1]- 2;

            // If there's no enemy pawn in front of our pawn then it's even worse, since
            // we allow outposts and pieces to attack us easily
            if (position.pawn_rank[0][col] == 9) scores.mid -= 3 * BACKWARDS_PAWN_PENALTY_MID;
        }

        // Passed Pawn Bonus
        if (row <= position.pawn_rank[0][col - 1] &&
            row <= position.pawn_rank[0][col] &&
            row <= position.pawn_rank[0][col + 1]) {

            scores.mid += (9 - row) * PASSED_PAWN_BONUS_MID;
            scores.end += (9 - row) * PASSED_PAWN_BONUS_END;
        }
    }

}


SCORE_TYPE evaluate(Position& position) {

    Score_Struct white_material{};
    Score_Struct white_scores{};

    Score_Struct black_material{};
    Score_Struct black_scores{};

    int game_phase = 0;

    // We make a 10 size array for each side, and eight of them are used for storing
    // the least advanced pawn. Storing this allows us to check for passed pawns,
    // backwards pawns, isolated pawns and whatnot.
    // Having a ten element array gives padding on the side to prevent out of bounds exceptions.

    for (int i = 0; i < 10; i++) {
        position.pawn_rank[0][i] = 9;
        position.pawn_rank[1][i] = 0;
    }

    for (SQUARE_TYPE pos : position.white_pieces) {
        PIECE_TYPE piece = position.board[pos];
        SQUARE_TYPE i = MAILBOX_TO_STANDARD[pos];
        SQUARE_TYPE row = 8 - i / 8, col = i % 8 + 1;

        if (piece == WHITE_PAWN && row < position.pawn_rank[0][col]) position.pawn_rank[0][col] = row;
    }

    for (SQUARE_TYPE pos : position.black_pieces) {
        PIECE_TYPE piece = position.board[pos];
        SQUARE_TYPE i = MAILBOX_TO_STANDARD[pos];
        SQUARE_TYPE row = 8 - i / 8, col = i % 8 + 1;

        if (piece == BLACK_PAWN && row > position.pawn_rank[1][col]) position.pawn_rank[1][col] = row;
    }

    for (SQUARE_TYPE pos : position.white_pieces) {
        PIECE_TYPE piece = position.board[pos];

        game_phase += GAME_PHASE_SCORES[piece];

        white_material.mid += PIECE_VALUES_MID[piece];
        white_material.end += PIECE_VALUES_END[piece];

        white_scores.mid += PST_MID[piece][MAILBOX_TO_STANDARD[pos]];
        white_scores.end += PST_END[piece][MAILBOX_TO_STANDARD[pos]];

        if (piece == WHITE_PAWN) evaluate_pawn(position, white_scores, pos, true);
    }

    for (SQUARE_TYPE pos : position.black_pieces) {
        PIECE_TYPE piece = position.board[pos];

        game_phase += GAME_PHASE_SCORES[piece-6];

        black_material.mid += PIECE_VALUES_MID[piece - BLACK_PAWN];
        black_material.end += PIECE_VALUES_END[piece - BLACK_PAWN];

        black_scores.mid += PST_MID[piece - BLACK_PAWN][MAILBOX_TO_STANDARD[pos] ^ 56];
        black_scores.end += PST_END[piece - BLACK_PAWN][MAILBOX_TO_STANDARD[pos] ^ 56];

        if (piece == BLACK_PAWN) evaluate_pawn(position, black_scores, pos, false);
    }

    white_scores.mid += white_material.mid;
    white_scores.end += white_material.end;

    black_scores.mid += black_material.mid;
    black_scores.end += black_material.end;

    if (game_phase > 24) game_phase = 24; // In case of early promotions
    SCORE_TYPE white_score = (white_scores.mid * game_phase +
                              (24 - game_phase) * white_scores.end) / 24;

    SCORE_TYPE black_score = (black_scores.mid * game_phase +
                              (24 - game_phase) * black_scores.end) / 24;


    return (position.side * -2 + 1) * (white_score - black_score) + TEMPO_BONUS;
}


SCORE_TYPE score_move(Engine& engine, MOVE_TYPE move, MOVE_TYPE tt_move, MOVE_TYPE last_move) {

    if (move == tt_move) return 100000;

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
            if (last_move != NO_MOVE &&
                engine.counter_moves[get_selected(last_move)][get_target_square(last_move)] == move) score += 1000;

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
            if (last_move != NO_MOVE &&
                engine.counter_moves[get_selected(last_move)][get_target_square(last_move)] == move) score += 1000;

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


SCORE_TYPE score_capture(MOVE_TYPE move, MOVE_TYPE tt_move) {

    if (move == tt_move) return 100000;

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


void get_move_scores(Engine& engine, const std::vector<MOVE_TYPE>& moves, std::vector<SCORE_TYPE>& move_scores,
                     MOVE_TYPE tt_move, MOVE_TYPE last_move) {
    move_scores.clear();

    for (MOVE_TYPE move : moves) {
        move_scores.push_back(score_move(engine, move, tt_move, last_move));
    }
}


void get_capture_scores(const std::vector<MOVE_TYPE>& moves, std::vector<SCORE_TYPE>& move_scores, MOVE_TYPE tt_move) {
    move_scores.clear();

    for (MOVE_TYPE move : moves) {
        move_scores.push_back(score_capture(move, tt_move));
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
