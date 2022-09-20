//
// Created by Alex Tian on 9/12/2022.
//

#include "move_generator.h"
#include "move.h"


std::vector<MOVE_TYPE> get_pseudo_legal_moves(Position& position) {

    std::vector<MOVE_TYPE> moves;

    if (!position.side) {

        for (SQUARE_TYPE pos : position.white_pieces) {
            PIECE_TYPE piece = position.board[pos];

            for (int increment : WHITE_INCREMENTS[piece]) {
                if (!increment) break;

                SQUARE_TYPE new_pos = pos;

                while (true) {
                    new_pos += increment;

                    PIECE_TYPE occupied = position.board[new_pos];

                    if (occupied == PADDING || occupied < BLACK_PAWN) break;
                    if (piece == WHITE_PAWN && (increment == -10 || increment == -20) &&
                        position.board[pos - 10] != EMPTY) break;
                    if (piece == WHITE_PAWN && increment == -20 && (pos < 81 || occupied != EMPTY)) break;

                    // En Passant
                    if (piece == WHITE_PAWN && (increment == -11 || increment == -9) and occupied == EMPTY) {
                        if (new_pos == position.ep_square) {
                            moves.push_back(encode_move(pos, new_pos,
                                                        WHITE_PAWN, EMPTY,
                                                        MOVE_TYPE_EP, 0, false));
                        }

                        break;
                    }

                    // Promotion
                    if (piece == WHITE_PAWN && new_pos < 31) {
                        for (PIECE_TYPE new_piece = WHITE_KNIGHT; new_piece < WHITE_KING; new_piece++) {
                            moves.push_back(encode_move(pos, new_pos,
                                                        WHITE_PAWN, occupied,
                                                        MOVE_TYPE_PROMOTION, new_piece,
                                                        occupied < EMPTY));
                        }

                        break;
                    }

                    // Captures
                    if (occupied < EMPTY) {
                        moves.push_back(encode_move(pos, new_pos,
                                                    piece, occupied,
                                                    MOVE_TYPE_NORMAL, 0, true));

                        break;
                    }

                    moves.push_back(encode_move(pos, new_pos,
                                                piece, EMPTY,
                                                MOVE_TYPE_NORMAL, 0, false));

                    if (piece == WHITE_PAWN || piece == WHITE_KNIGHT || piece == WHITE_KING) break;

                    if ((position.castle_ability_bits & 1) == 1 && pos == H1 &&
                        position.board[new_pos - 1] == WHITE_KING) moves.push_back(
                                encode_move(E1, G1, WHITE_KING,
                                            EMPTY, MOVE_TYPE_CASTLE, 0, false)
                                            );

                    else if ((position.castle_ability_bits & 2) == 2 && pos == A1 &&
                        position.board[new_pos + 1] == WHITE_KING) moves.push_back(
                                encode_move(E1, C1, WHITE_KING,
                                            EMPTY, MOVE_TYPE_CASTLE, 0, false)
                                            );
                }
            }
        }
    }

    else {

        for (SQUARE_TYPE pos : position.black_pieces) {
            PIECE_TYPE piece = position.board[pos];

            for (int increment : BLACK_INCREMENTS[piece - BLACK_PAWN]) {
                if (!increment) break;

                SQUARE_TYPE new_pos = pos;

                while (true) {
                    new_pos += increment;

                    PIECE_TYPE occupied = position.board[new_pos];

                    if (occupied != EMPTY && occupied > WHITE_KING) break;
                    if (piece == BLACK_PAWN && (increment == 10 || increment == 20) &&
                        position.board[pos + 10] != EMPTY) break;
                    if (piece == BLACK_PAWN && increment == 20 && (pos > 38 || occupied != EMPTY)) break;

                    // En Passant
                    if (piece == BLACK_PAWN && (increment == 11 || increment == 9) and occupied == EMPTY) {
                        if (new_pos == position.ep_square) {
                            moves.push_back(encode_move(pos, new_pos,
                                                        BLACK_PAWN, EMPTY,
                                                        MOVE_TYPE_EP, 0, false));
                        }

                        break;
                    }

                    // Promotion
                    if (piece == BLACK_PAWN && new_pos > 88) {
                        for (PIECE_TYPE new_piece = BLACK_KNIGHT; new_piece <= BLACK_QUEEN; new_piece++) {
                            moves.push_back(encode_move(pos, new_pos,
                                                        BLACK_PAWN, occupied,
                                                        MOVE_TYPE_PROMOTION, new_piece,
                                                        occupied < BLACK_PAWN));
                        }

                        break;
                    }

                    // Captures
                    if (occupied < BLACK_PAWN) {
                        moves.push_back(encode_move(pos, new_pos,
                                                    piece, occupied,
                                                    MOVE_TYPE_NORMAL, 0, true));

                        break;
                    }

                    moves.push_back(encode_move(pos, new_pos,
                                                piece, EMPTY,
                                                MOVE_TYPE_NORMAL, 0, false));

                    if (piece == BLACK_PAWN || piece == BLACK_KNIGHT || piece == BLACK_KING) break;

                    if ((position.castle_ability_bits & 4) == 4 && pos == H8 &&
                        position.board[new_pos - 1] == BLACK_KING) moves.push_back(
                                encode_move(E8, G8, BLACK_KING,
                                            EMPTY, MOVE_TYPE_CASTLE, 0, false)
                        );

                    else if ((position.castle_ability_bits & 8) == 8 && pos == A8 &&
                             position.board[new_pos + 1] == BLACK_KING) moves.push_back(
                                encode_move(E8, C8, BLACK_KING,
                                            EMPTY, MOVE_TYPE_CASTLE, 0, false)
                        );
                }
            }
        }
    }

    return moves;
}
