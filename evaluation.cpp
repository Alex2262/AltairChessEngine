//
// Created by Alex Tian on 9/29/2022.
//

#include "evaluation.h"
#include "move.h"
#include "see.h"


SCORE_TYPE evaluate(Position& position) {

    Score_Struct white_material{};
    Score_Struct white_scores{};

    Score_Struct black_material{};
    Score_Struct black_scores{};

    int game_phase = 0;

    for (SQUARE_TYPE pos : position.white_pieces) {
        PIECE_TYPE piece = position.board[pos];
        SQUARE_TYPE standard_pos = MAILBOX_TO_STANDARD[pos];

        game_phase += GAME_PHASE_SCORES[piece];

        white_material.mid += PIECE_VALUES_MID[piece];
        white_material.end += PIECE_VALUES_END[piece];
        // std::cout << piece << std::endl;

        // std::cout << white_scores.mid << " " << white_scores.end << std::endl;
        if (piece == WHITE_PAWN) {
            white_scores.mid += PAWN_PST_MID[standard_pos];
            white_scores.end += PAWN_PST_END[standard_pos];
        }
        else if (piece == WHITE_KNIGHT) {
            white_scores.mid += KNIGHT_PST_MID[standard_pos];
            white_scores.end += KNIGHT_PST_END[standard_pos];
        }
        else if (piece == WHITE_BISHOP) {
            white_scores.mid += BISHOP_PST_MID[standard_pos];
            white_scores.end += BISHOP_PST_END[standard_pos];
        }
        else if (piece == WHITE_ROOK) {
            white_scores.mid += ROOK_PST_MID[standard_pos];
            white_scores.end += ROOK_PST_END[standard_pos];
        }
        else if (piece == WHITE_QUEEN) {
            white_scores.mid += QUEEN_PST_MID[standard_pos];
            white_scores.end += QUEEN_PST_END[standard_pos];
        }
        else if (piece == WHITE_KING) {
            white_scores.mid += KING_PST_MID[standard_pos];
            white_scores.end += KING_PST_END[standard_pos];
        }

        // std::cout << white_scores.mid << " " << white_scores.end << std::endl;
    }

    for (SQUARE_TYPE pos : position.black_pieces) {
        PIECE_TYPE piece = position.board[pos];
        SQUARE_TYPE standard_pos = MAILBOX_TO_STANDARD[pos];

        game_phase += GAME_PHASE_SCORES[piece-6];

        black_material.mid += PIECE_VALUES_MID[piece - BLACK_PAWN];
        black_material.end += PIECE_VALUES_END[piece - BLACK_PAWN];
        // std::cout << piece << std::endl;

        // std::cout << black_scores.mid << " " << black_scores.end << std::endl;
        if (piece == BLACK_PAWN) {
            black_scores.mid += PAWN_PST_MID[standard_pos ^ 56];
            black_scores.end += PAWN_PST_END[standard_pos ^ 56];
        }
        else if (piece == BLACK_KNIGHT) {
            black_scores.mid += KNIGHT_PST_MID[standard_pos ^ 56];
            black_scores.end += KNIGHT_PST_END[standard_pos ^ 56];
        }
        else if (piece == BLACK_BISHOP) {
            black_scores.mid += BISHOP_PST_MID[standard_pos ^ 56];
            black_scores.end += BISHOP_PST_END[standard_pos ^ 56];
        }
        else if (piece == BLACK_ROOK) {
            black_scores.mid += ROOK_PST_MID[standard_pos ^ 56];
            black_scores.end += ROOK_PST_END[standard_pos ^ 56];
        }
        else if (piece == BLACK_QUEEN) {
            black_scores.mid += QUEEN_PST_MID[standard_pos ^ 56];
            black_scores.end += QUEEN_PST_END[standard_pos ^ 56];
        }
        else if (piece == BLACK_KING) {
            black_scores.mid += KING_PST_MID[standard_pos ^ 56];
            black_scores.end += KING_PST_END[standard_pos ^ 56];
        }

        // std::cout << black_scores.mid << " " << black_scores.end << std::endl;
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

    // std::cout << white_score << " " << black_score << std::endl;

    return (position.side * -2 + 1) * (white_score - black_score);
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
