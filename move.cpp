
#include <iostream>
#include "position.h"
#include "move.h"

bool Move::is_capture(const Position& position) const {
    Color side_to_move = get_color(position.board[origin()]);
    return ~side_to_move * 6        <= static_cast<int>(position.board[target()]) &&
           ~side_to_move * 6 + 6     > static_cast<int>(position.board[target()]);
}

std::string Move::get_uci(const Position& position) const {

    std::string uci_move;

    Square origin_square = origin();
    Square target_square = target();

    MoveType move_type = type();

    if (move_type == MOVE_TYPE_CASTLE && position.fischer_random_chess) {
        if (target_square == c1 || target_square == c8) target_square = position.starting_rook_pos[position.side][1];
        else if (target_square == g1 || target_square == g8) target_square = position.starting_rook_pos[position.side][0];
    }

    uci_move += char(origin_square % 8 + 'a');
    uci_move += char(origin_square / 8 + '1');

    uci_move += char(target_square % 8 + 'a');
    uci_move += char(target_square / 8 + '1');

    if (move_type == MOVE_TYPE_PROMOTION) {
        PromotionType promotion_type = this->promotion_type();
        if (promotion_type == PROMOTION_QUEEN) uci_move += 'q';
        else if (promotion_type == PROMOTION_ROOK) uci_move += 'r';
        else if (promotion_type == PROMOTION_BISHOP) uci_move += 'b';
        else if (promotion_type == PROMOTION_KNIGHT) uci_move += 'n';
    }

    return uci_move;
}


Move::Move(const Position& position, std::string uci) {
    MoveType move_type = MOVE_TYPE_NORMAL;
    PromotionType promotion_type;

    if (uci.length() == 5) {
        move_type = MOVE_TYPE_PROMOTION;
        if (uci[4] == 'q') promotion_type = PROMOTION_QUEEN;
        else if (uci[4] == 'r') promotion_type = PROMOTION_ROOK;
        else if (uci[4] == 'b') promotion_type = PROMOTION_BISHOP;
        else if (uci[4] == 'n') promotion_type = PROMOTION_KNIGHT;
    }

    auto origin_square = static_cast<Square>((uci[1] - '1') * 8 + (uci[0] - 'a'));
    auto target_square = static_cast<Square>((uci[3] - '1') * 8 + (uci[2] - 'a'));

    auto selected = static_cast<Piece>(position.board[origin_square]);
    auto occupied = static_cast<Piece>(position.board[target_square]);

    auto selected_type = static_cast<PieceType>(static_cast<int>(selected) % COLOR_OFFSET);
    auto occupied_type = static_cast<PieceType>(static_cast<int>(occupied) % COLOR_OFFSET);

    bool castle_move = selected_type == KING && (abs(static_cast<int>(target_square - origin_square)) == 2);
    if (position.fischer_random_chess) {
        if (selected_type == KING && occupied_type == ROOK && get_color(selected) == get_color(occupied)) {
            castle_move = true;

            if (target_square == position.starting_rook_pos[WHITE][0]) target_square = g1;
            else if (target_square == position.starting_rook_pos[WHITE][1]) target_square = c1;
            else if (target_square == position.starting_rook_pos[BLACK][0]) target_square = g8;
            else if (target_square == position.starting_rook_pos[BLACK][1]) target_square = c8;
        }
    }

    if (selected_type == PAWN && target_square == position.ep_square) move_type = MOVE_TYPE_EP;
    else if (castle_move) move_type = MOVE_TYPE_CASTLE;

    move = (move_type << 12) | (origin_square << 6) | target_square;
    if (move_type == MOVE_TYPE_PROMOTION) move |= promotion_type << 14;

}

