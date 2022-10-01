
#include <iostream>
#include "move.h"

std::string get_uci_from_move(MOVE_TYPE move) {

    std::string uci_move;

    SQUARE_TYPE origin_square = MAILBOX_TO_STANDARD[get_origin_square(move)];
    SQUARE_TYPE target_square = MAILBOX_TO_STANDARD[get_target_square(move)];

    uint16_t move_type = get_move_type(move);

    uci_move += char(origin_square % 8 + 'a');
    uci_move += char((8 - origin_square / 8) + '0');

    uci_move += char(target_square % 8 + 'a');
    uci_move += char((8 - target_square / 8) + '0');

    if (move_type == MOVE_TYPE_PROMOTION) {
        PIECE_TYPE promotion_piece = get_promotion_piece(move);
        if (promotion_piece % BLACK_PAWN == WHITE_QUEEN) uci_move += 'q';
        else if (promotion_piece % BLACK_PAWN == WHITE_ROOK) uci_move += 'r';
        else if (promotion_piece % BLACK_PAWN == WHITE_BISHOP) uci_move += 'b';
        else if (promotion_piece % BLACK_PAWN == WHITE_KNIGHT) uci_move += 'n';
    }

    return uci_move;
}

MOVE_TYPE get_move_from_uci(const Position& position, std::string uci) {

    PIECE_TYPE promotion_piece = 0;
    if (uci.length() == 5) {

        if (uci[4] == 'q') promotion_piece = 4;
        else if (uci[4] == 'r') promotion_piece = 3;
        else if (uci[4] == 'b') promotion_piece = 2;
        else if (uci[4] == 'n') promotion_piece = 1;

        promotion_piece += position.side * BLACK_PAWN;

    }

    SQUARE_TYPE origin_square = STANDARD_TO_MAILBOX[(8 - (uci[1] - '0')) * 8 + (uci[0] - 'a')];
    SQUARE_TYPE target_square = STANDARD_TO_MAILBOX[(8 - (uci[3] - '0')) * 8 + (uci[2] - 'a')];

    PIECE_TYPE selected = position.board[origin_square];
    PIECE_TYPE occupied = position.board[target_square];

    uint16_t move_type = 0;

    if (selected % BLACK_PAWN == WHITE_PAWN) {
        if ((21 <= target_square && target_square <= 28) ||
             91 <= target_square && target_square <= 98) move_type = 3;
        else if (target_square == position.ep_square) move_type = 1;
    }

    else if (selected % BLACK_PAWN == WHITE_KING) {
        if (abs(target_square - origin_square) == 2) move_type = 2;
    }

    bool is_capture = occupied < EMPTY;
    MOVE_TYPE move = encode_move(origin_square, target_square, selected, occupied,
                                 move_type, promotion_piece, is_capture);

    return move;
}