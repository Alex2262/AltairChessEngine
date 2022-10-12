//
// Created by Alex Tian on 9/29/2022.
//

#include "evaluation.h"
#include "move.h"


SCORE_TYPE evaluate_king_pawn(const Position& position, SQUARE_TYPE file, bool is_white) {
    SCORE_TYPE score = 0;

    if (is_white) {
        if (position.pawn_rank[0][file] == 3) score -= 6;  // Pawn moved one square
        else if (position.pawn_rank[0][file] == 4) score -= 14;  // Pawn moved two squares
        else if (position.pawn_rank[0][file] != 2) score -= 23;  // Pawn moved > 2 squares, or it doesn't exist

        if (position.pawn_rank[1][file] == 0) score -= 19;  // No enemy pawn on this file
        else if (position.pawn_rank[1][file] == 4) score -= 8;  // Enemy pawn is on the 4th rank
        else if (position.pawn_rank[1][file] != 3) score -= 16;  // Enemy pawn is on the 3rd rank
    }

    else {
        if (position.pawn_rank[1][file] == 6) score -= 6;  // Pawn moved one square
        else if (position.pawn_rank[1][file] == 5) score -= 14;  // Pawn moved two squares
        else if (position.pawn_rank[1][file] != 7) score -= 23;  // Pawn moved > 2 squares, or it doesn't exist

        if (position.pawn_rank[0][file] == 9) score -= 19;  // No enemy pawn on this file
        else if (position.pawn_rank[0][file] == 5) score -= 8;  // Enemy pawn is on the 5th rank
        else if (position.pawn_rank[0][file] != 6) score -= 16;  // Enemy pawn is on the 6th rank
    }

    return score;
}
void evaluate_pawn(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white) {

    SQUARE_TYPE i = MAILBOX_TO_STANDARD[pos];
    SQUARE_TYPE row = 8 - i / 8, col = i % 8 + 1;

    if (is_white) {

        scores.mid += PAWN_PST_MID[i];
        scores.end += PAWN_PST_END[i];

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

        scores.mid += PAWN_PST_MID[i ^ 56];
        scores.end += PAWN_PST_END[i ^ 56];

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


void evaluate_knight(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white) {
    SQUARE_TYPE i = MAILBOX_TO_STANDARD[pos];

    if (is_white) {
        scores.mid += KNIGHT_PST_MID[i];
        scores.end += KNIGHT_PST_END[i];
    }
    else {
        scores.mid += KNIGHT_PST_MID[i ^ 56];
        scores.end += KNIGHT_PST_END[i ^ 56];
    }
}


void evaluate_bishop(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white) {
    SQUARE_TYPE i = MAILBOX_TO_STANDARD[pos];

    if (is_white) {
        scores.mid += BISHOP_PST_MID[i];
        scores.end += BISHOP_PST_END[i];
    }
    else {
        scores.mid += BISHOP_PST_MID[i ^ 56];
        scores.end += BISHOP_PST_END[i ^ 56];
    }
}


void evaluate_rook(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white) {
    SQUARE_TYPE i = MAILBOX_TO_STANDARD[pos];
    SQUARE_TYPE col = i % 8 + 1;

    if (is_white) {
        scores.mid += ROOK_PST_MID[i];
        scores.end += ROOK_PST_END[i];

        if (position.pawn_rank[0][col] == 9) {
            if (position.pawn_rank[1][col] == 0) {
                scores.mid += ROOK_OPEN_FILE_BONUS_MID;
                scores.end += ROOK_OPEN_FILE_BONUS_END;
            }
            else {
                scores.mid += ROOK_SEMI_OPEN_FILE_BONUS_MID;
                scores.end += ROOK_SEMI_OPEN_FILE_BONUS_END;
            }
        }
    }
    else {
        scores.mid += ROOK_PST_MID[i ^ 56];
        scores.end += ROOK_PST_END[i ^ 56];

        if (position.pawn_rank[1][col] == 0) {
            if (position.pawn_rank[0][col] == 9) {
                scores.mid += ROOK_OPEN_FILE_BONUS_MID;
                scores.end += ROOK_OPEN_FILE_BONUS_END;
            }
            else {
                scores.mid += ROOK_SEMI_OPEN_FILE_BONUS_MID;
                scores.end += ROOK_SEMI_OPEN_FILE_BONUS_END;
            }
        }
    }
}


void evaluate_queen(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white) {
    SQUARE_TYPE i = MAILBOX_TO_STANDARD[pos];
    SQUARE_TYPE col = i % 8 + 1;

    if (is_white) {
        scores.mid += QUEEN_PST_MID[i];
        scores.end += QUEEN_PST_END[i];

        if (position.pawn_rank[0][col] == 9) {
            if (position.pawn_rank[1][col] == 0) {
                scores.mid += QUEEN_OPEN_FILE_BONUS_MID;
                scores.end += QUEEN_OPEN_FILE_BONUS_END;
            }
            else {
                scores.mid += QUEEN_SEMI_OPEN_FILE_BONUS_MID;
                scores.end += QUEEN_SEMI_OPEN_FILE_BONUS_END;
            }
        }
    }
    else {
        scores.mid += QUEEN_PST_MID[i ^ 56];
        scores.end += QUEEN_PST_END[i ^ 56];

        if (position.pawn_rank[1][col] == 0) {
            if (position.pawn_rank[0][col] == 9) {
                scores.mid += QUEEN_OPEN_FILE_BONUS_MID;
                scores.end += QUEEN_OPEN_FILE_BONUS_END;
            }
            else {
                scores.mid += QUEEN_SEMI_OPEN_FILE_BONUS_MID;
                scores.end += QUEEN_SEMI_OPEN_FILE_BONUS_END;
            }
        }
    }
}

void evaluate_king(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white) {
    SQUARE_TYPE i = MAILBOX_TO_STANDARD[pos];
    SQUARE_TYPE col = i % 8 + 1;

    if (is_white) {
        scores.mid += KING_PST_MID[i];
        scores.end += KING_PST_END[i];

        if (col < 4) {  // Queen side
            scores.mid += evaluate_king_pawn(position, 1, true) * 0.8; // A file pawn
            scores.mid += evaluate_king_pawn(position, 2, true);
            scores.mid += evaluate_king_pawn(position, 3, true) * 0.6; // C file pawn
        }
        else if (col > 5) {
            scores.mid += evaluate_king_pawn(position, 8, true) * 0.5; // H file pawn
            scores.mid += evaluate_king_pawn(position, 7, true);
            scores.mid += evaluate_king_pawn(position, 6, true) * 0.3; // F file pawn
        }
        else {
            for (SQUARE_TYPE pawn_file = col - 1; pawn_file < col + 2; pawn_file++) {
                if (position.pawn_rank[0][pawn_file] == 9) {
                    scores.mid -= 6;
                    if (position.pawn_rank[1][pawn_file] == 0) {
                        scores.mid -= 13;
                    }
                }
            }
        }
    }
    else {
        scores.mid += KING_PST_MID[i ^ 56];
        scores.end += KING_PST_END[i ^ 56];

        if (col < 4) {  // Queen side
            scores.mid += evaluate_king_pawn(position, 1, false) * 0.8; // A file pawn
            scores.mid += evaluate_king_pawn(position, 2, false);
            scores.mid += evaluate_king_pawn(position, 3, false) * 0.6; // C file pawn
        }
        else if (col > 5) {
            scores.mid += evaluate_king_pawn(position, 8, false) * 0.5; // H file pawn
            scores.mid += evaluate_king_pawn(position, 7, false);
            scores.mid += evaluate_king_pawn(position, 6, false) * 0.3; // F file pawn
        }
        else {
            for (SQUARE_TYPE pawn_file = col - 1; pawn_file < col + 2; pawn_file++) {
                if (position.pawn_rank[1][pawn_file] == 0) {
                    scores.mid -= 6;
                    if (position.pawn_rank[0][pawn_file] == 9) {
                        scores.mid -= 13;
                    }
                }
            }
        }
    }
}


double evaluate_drawishness(const int white_piece_amounts[6], const int black_piece_amounts[6],
                            SCORE_TYPE white_material, SCORE_TYPE black_material, bool opp_colored_bishops) {

    // return a decimal from 0.0 - 1.0 that will multiply the eval by

    if (white_piece_amounts[WHITE_QUEEN] + black_piece_amounts[WHITE_QUEEN] > 0) return 1.0;
    if (white_piece_amounts[WHITE_ROOK] + black_piece_amounts[WHITE_ROOK] >= 2) return 1.0;
    if (white_piece_amounts[WHITE_PAWN] + black_piece_amounts[WHITE_PAWN] >= 1) {
        if (white_piece_amounts[1] + white_piece_amounts[3] +
            black_piece_amounts[1] + black_piece_amounts[3] >= 1) return 1.0;
        if (white_piece_amounts[2] == 1 && black_piece_amounts[2] == 1 && opp_colored_bishops)
            return 0.25 + abs(white_piece_amounts[0] - black_piece_amounts[0]) * 0.2;
        return 1.0;
    }
    if (white_material <= PIECE_VALUES_MID[WHITE_BISHOP] && black_material <= PIECE_VALUES_MID[WHITE_BISHOP])
        return 0.0;
    if (white_material <= 2 * PIECE_VALUES_MID[WHITE_BISHOP] && black_material <= 2 * PIECE_VALUES_MID[WHITE_BISHOP]) {

        // With only 2 knights, it's impossible to checkmate
        if (white_piece_amounts[WHITE_KNIGHT] == 2 || black_piece_amounts[WHITE_KNIGHT] == 2)
            return 0.0;

        // If one of them has 0 pieces we know that due to the check above, at least one of has more than
        // a bishop's worth of material, or else it would have returned 0.0, and thus it would be a win.
        // Either the player that doesn't have 0 material has two bishops, a bishop and knight, or a rook.
        // All of these are wins.
        if (white_material == 0 || black_material == 0) {
            return 1.0;
        }

        // Here we know they both do not have 0 material, and they cannot have pawns or queens,
        // this means they either have a rook, and the other player has a minor piece,
        // or this means one player has two minor pieces, and the other players has one minor piece.

        return 0.6;
    }

    return 1.0;

}


SCORE_TYPE evaluate(Position& position) {

    Score_Struct white_material{};
    Score_Struct white_scores{};

    Score_Struct black_material{};
    Score_Struct black_scores{};

    int game_phase = 0;
    int white_piece_amounts[6] = {0};
    int black_piece_amounts[6] = {0};
    int bishop_colors[2] = {0};

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
        SQUARE_TYPE standard_pos = MAILBOX_TO_STANDARD[pos];

        game_phase += GAME_PHASE_SCORES[piece];
        white_piece_amounts[piece]++;

        white_material.mid += PIECE_VALUES_MID[piece];
        white_material.end += PIECE_VALUES_END[piece];

        if (piece == WHITE_PAWN) evaluate_pawn(position, white_scores, pos, true);
        else if (piece == WHITE_KNIGHT) evaluate_knight(position, white_scores, pos, true);
        else if (piece == WHITE_BISHOP) {
            bishop_colors[0] = SQUARE_COLOR[standard_pos];
            evaluate_bishop(position, white_scores, pos, true);
        }
        else if (piece == WHITE_ROOK) evaluate_rook(position, white_scores, pos, true);
        else if (piece == WHITE_QUEEN) evaluate_queen(position, white_scores, pos, true);
        else if (piece == WHITE_KING) evaluate_king(position, white_scores, pos, true);
    }

    for (SQUARE_TYPE pos : position.black_pieces) {
        PIECE_TYPE piece = position.board[pos];
        SQUARE_TYPE standard_pos = MAILBOX_TO_STANDARD[pos];

        game_phase += GAME_PHASE_SCORES[piece-6];
        black_piece_amounts[piece-6]++;

        black_material.mid += PIECE_VALUES_MID[piece - BLACK_PAWN];
        black_material.end += PIECE_VALUES_END[piece - BLACK_PAWN];

        if (piece == BLACK_PAWN) evaluate_pawn(position, black_scores, pos, false);
        else if (piece == BLACK_KNIGHT) evaluate_knight(position, black_scores, pos, false);
        else if (piece == BLACK_BISHOP) {
            bishop_colors[1] = SQUARE_COLOR[standard_pos];
            evaluate_bishop(position, black_scores, pos, false);
        }
        else if (piece == BLACK_ROOK) evaluate_rook(position, black_scores, pos, false);
        else if (piece == BLACK_QUEEN) evaluate_queen(position, black_scores, pos, false);
        else if (piece == BLACK_KING) evaluate_king(position, black_scores, pos, false);
    }

    if (white_piece_amounts[WHITE_BISHOP] >= 2) {
        white_scores.mid += BISHOP_PAIR_BONUS_MID;
        white_scores.end += BISHOP_PAIR_BONUS_END;
    }

    if (black_piece_amounts[WHITE_BISHOP] >= 2) {
        black_scores.mid += BISHOP_PAIR_BONUS_MID;
        black_scores.end += BISHOP_PAIR_BONUS_END;
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

    double drawishness = evaluate_drawishness(white_piece_amounts, black_piece_amounts,
                                              white_material.mid, black_material.mid,
                                              bishop_colors[0] == bishop_colors[1]);

    white_score *= drawishness;
    black_score *= drawishness;

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
            score += 20000;
            score += 2 * (PIECE_VALUES_MID[occupied - BLACK_PAWN] - PIECE_VALUES_MID[selected]);
        }
        else {
            if (last_move != NO_MOVE &&
                engine.counter_moves[get_selected(last_move)]
                                    [MAILBOX_TO_STANDARD[get_target_square(last_move)]] == move) score += 620;

            // score 1st and 2nd killer move
            if (engine.killer_moves[0][engine.search_ply] == move) score += 12000;
            else if (engine.killer_moves[1][engine.search_ply] == move) score += 11000;
            else score += engine.history_moves[selected][MAILBOX_TO_STANDARD[get_target_square(move)]];
        }

        if (move_type == MOVE_TYPE_PROMOTION) score += 18000 + 5 * PIECE_VALUES_MID[get_promotion_piece(move)];
        else if (move_type == MOVE_TYPE_EP) score += 21000;
        else if (move_type == MOVE_TYPE_CASTLE) score += 800;
    }
    else {
        if (get_is_capture(move)) {
            score += 20000;
            score += 2 * (PIECE_VALUES_MID[occupied] - PIECE_VALUES_MID[selected - BLACK_PAWN]);
        }
        else {
            if (last_move != NO_MOVE &&
                engine.counter_moves[get_selected(last_move)]
                                    [MAILBOX_TO_STANDARD[get_target_square(last_move)]] == move) score += 620;

            // score 1st and 2nd killer move
            if (engine.killer_moves[0][engine.search_ply] == move) score += 12000;
            else if (engine.killer_moves[1][engine.search_ply] == move) score += 11000;
            else score += engine.history_moves[selected][MAILBOX_TO_STANDARD[get_target_square(move)]];
        }

        if (move_type == MOVE_TYPE_PROMOTION) score += 18000 +
                                                       5 * PIECE_VALUES_MID[get_promotion_piece(move) - BLACK_PAWN];
        else if (move_type == MOVE_TYPE_CASTLE) score += 21000;
        else if (move_type == MOVE_TYPE_EP) score += 800;
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
