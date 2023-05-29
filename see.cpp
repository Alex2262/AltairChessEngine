//
// Created by Alexander Tian on 5/4/23.
//

#include <vector>
#include <utility>
#include <iostream>
#include "see.h"

SQUARE_TYPE get_cheapest_attacker(Position& position, SQUARE_TYPE pos) {
    SQUARE_TYPE cheapest_piece_square = 0;

    if (!position.side) {
        // Check if pawns are attacking you
        if (position.board[pos - 11] == BLACK_PAWN) return pos - 11;
        if (position.board[pos -  9] == BLACK_PAWN) return pos - 9;

        // Search with the increments of a knight to see if any opponent knights are attacking you
        for (int increment : BLACK_ATK_INCREMENTS[WHITE_KNIGHT]) {
            SQUARE_TYPE new_pos = pos + increment;
            PIECE_TYPE occupied = position.board[new_pos];

            if (occupied == BLACK_KNIGHT) return new_pos;
        }

        // Search with the increments of a queen to see if any opponent queens, bishops, or rooks are attacking you.
        for (int increment : BLACK_ATK_INCREMENTS[WHITE_QUEEN]) {
            SQUARE_TYPE new_pos = pos;

            while (true) {
                new_pos += increment;
                PIECE_TYPE occupied = position.board[new_pos];

                // Break if you hit your own piece or if you are out of bounds
                if (occupied == PADDING || occupied < BLACK_PAWN) break;
                if (occupied == EMPTY) continue;  // Continue if there is no piece on this square

                // Can return immediately since the Bishop is the cheapest out of the sliding pieces
                if (occupied == BLACK_BISHOP) {
                    if (increment == -11 || increment == 11 || increment == 9 || increment == -9) return new_pos;
                }

                    // Can return immediately since the horizontal/vertical increments are searched after
                    // diagonal increments, and thus if a rook is found no bishop will be found after meaning it will be
                    // the cheapest piece.
                else if (occupied == BLACK_ROOK) {
                    if (increment == -10 || increment == 1 || increment == 10 || increment == -1) return new_pos;
                }

                else if (occupied == BLACK_QUEEN && (cheapest_piece_square == 0 ||
                                                     BLACK_QUEEN < position.board[cheapest_piece_square])) cheapest_piece_square = new_pos;

                else if (occupied == BLACK_KING && cheapest_piece_square == 0) {
                    if (new_pos == pos + increment) cheapest_piece_square = new_pos;
                }

                break;

            }
        }
    }

    else {

        // Check if pawns are attacking you
        if (position.board[pos + 11] == WHITE_PAWN) return pos + 11;
        if (position.board[pos +  9] == WHITE_PAWN) return pos + 9;

        // Search with the increments of a knight to see if any opponent knights are attacking you
        for (int increment : WHITE_ATK_INCREMENTS[WHITE_KNIGHT]) {
            SQUARE_TYPE new_pos = pos + increment;
            PIECE_TYPE occupied = position.board[new_pos];

            if (occupied == WHITE_KNIGHT) return new_pos;
        }

        // Search with the increments of a queen to see if any opponent queens, bishops, or rooks are attacking you.
        for (int increment : WHITE_ATK_INCREMENTS[WHITE_QUEEN]) {
            SQUARE_TYPE new_pos = pos;

            while (true) {
                new_pos += increment;
                PIECE_TYPE occupied = position.board[new_pos];

                // Break if you hit your own piece or if you are out of bounds
                if (occupied != EMPTY && occupied > WHITE_KING) break;
                if (occupied == EMPTY) continue;  // Continue if there is no piece on this square

                // Can return immediately since the Bishop is the cheapest out of the sliding pieces
                if (occupied == WHITE_BISHOP) {
                    if (increment == -11 || increment == 11 || increment == 9 || increment == -9) return new_pos;
                }

                    // Can return immediately since the horizontal/vertical increments are searched after
                    // diagonal increments, and thus if a rook is found no bishop will be found after meaning it will be
                    // the cheapest piece.
                else if (occupied == WHITE_ROOK) {
                    if (increment == -10 || increment == 1 || increment == 10 || increment == -1) return new_pos;
                }

                else if (occupied == WHITE_QUEEN && (cheapest_piece_square == 0 ||
                                                     WHITE_QUEEN < position.board[cheapest_piece_square])) cheapest_piece_square = new_pos;

                else if (occupied == WHITE_KING && cheapest_piece_square == 0) {
                    if (new_pos == pos + increment) return new_pos;
                }

                break;

            }
        }
    }

    return cheapest_piece_square;
}


SCORE_TYPE get_static_exchange_evaluation(Position& position, MOVE_TYPE move, SCORE_TYPE threshold) {
    uint16_t move_type = get_move_type(move);
    if (move_type == MOVE_TYPE_CASTLE) return true;
    if (move_type == MOVE_TYPE_PROMOTION) return true;
    if (move_type == MOVE_TYPE_EP) return true;

    SQUARE_TYPE target_square = get_target_square(move);

    PIECE_TYPE selected = get_selected(move);
    PIECE_TYPE occupied = get_occupied(move);

    SCORE_TYPE exchange_value = SEE_values[occupied] - threshold;
    if (exchange_value < 0) return false; // If taking the opponent's piece without any risk is still negative

    exchange_value -= SEE_values[selected];
    if (exchange_value >= 0) return true; // If we risk our piece being fully lost and the exchange value is still >= 0

    std::vector<std::pair<SQUARE_TYPE, PIECE_TYPE>> removed_pieces;

    position.board[target_square] = EMPTY;
    removed_pieces.emplace_back(target_square, occupied);

    SQUARE_TYPE original_side = position.side;

    while (true) {
        SQUARE_TYPE cheapest_attacker_square = get_cheapest_attacker(position, target_square);
        if (cheapest_attacker_square == 0) break; // No attacking piece was found

        position.side ^= 1;

        PIECE_TYPE cheapest_attacker = position.board[cheapest_attacker_square];

        exchange_value = -exchange_value - 1 - SEE_values[cheapest_attacker];
        if (exchange_value >= 0) {
            break;
        }

        position.board[cheapest_attacker_square] = EMPTY;
        removed_pieces.emplace_back(cheapest_attacker_square, cheapest_attacker);
    }

    for (auto removed : removed_pieces) {
        position.board[removed.first] = removed.second;
    }

    bool exchange_flag = position.side == original_side;

    position.side = original_side;

    return exchange_flag;


}

