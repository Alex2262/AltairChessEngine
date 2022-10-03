//
// Created by Alex Tian on 8/24/2022.
//

#include <iostream>
#include <algorithm>
#include "position.h"
#include "useful.h"
#include "move.h"


void Position::clear_movelist() {
    for (int i = 0; i < TOTAL_MAX_DEPTH; i++) {
        moves[i].clear();
        move_scores[i].clear();
    }
}

void Position::set_fen(const std::string& fen_string) {

    std::vector<std::string> fen_tokens = split(fen_string, ' ');

    // Setting the padding around the 8x8 board inscribed within the 10x12 board
    SQUARE_TYPE pos = 0;

    white_pieces.clear();
    black_pieces.clear();

    clear_movelist();

    for (int i = 0; i < 21; i++) {
        board[pos++] = PADDING;
    }

    // Parsing the main 8x8 board part while adding appropriate padding
    for (char c : fen_tokens[0]) {

        if (c == '/') {

            board[pos++] = PADDING;
            board[pos++] = PADDING;

        }
        else if (std::isdigit(c)) {

            for (int empty_amt = 0; empty_amt < c - '0'; empty_amt++) {
                board[pos++] = EMPTY;
            }

        }
        else if (std::isalpha(c)) {

            board[pos] = piece_to_num(c);

            if (std::isupper(c)) white_pieces.push_back(pos);
            else black_pieces.push_back(pos);

            if (c == 'K') king_positions[0] = pos;
            else if (c == 'k') king_positions[1] = pos;

            pos++;

        }
    }

    for (int i = 0; i < 21; i++) {
        board[pos++] = PADDING;
    }

    castle_ability_bits = 0;
    for (char c : fen_tokens[2]) {

        if (c == 'K') castle_ability_bits |= 1;
        else if (c == 'Q') castle_ability_bits |= 2;
        else if (c == 'k') castle_ability_bits |= 4;
        else if (c == 'q') castle_ability_bits |= 8;

    }

    if (fen_tokens[3].size() > 1) {
        SQUARE_TYPE square = (8 - (fen_tokens[3][1] - '0')) * 8 + fen_tokens[3][0] - 'a';
        ep_square = STANDARD_TO_MAILBOX[square];
    }
    else {
        ep_square = 0;
    }

    side = 0;
    if (fen_tokens[1] == "b") side = 1;
}


void Position::print_board() {
    std::string new_board;

    for (SQUARE_TYPE pos : STANDARD_TO_MAILBOX) {

        if (MAILBOX_TO_STANDARD[pos] % 8 == 0) {
            new_board += '\n';
        }

        PIECE_TYPE piece = board[pos];
        if (piece == EMPTY) {
            new_board += ". ";
            continue;
        }

        new_board += PIECE_MATCHER[piece];
        new_board += ' ';

    }

    std::cout << new_board << std::endl << std::endl;
    std::cout << "side: " << side << " ep: " << ep_square << " castle: " << castle_ability_bits
              << "\nhash: " << hash_key << " king pos: " << king_positions[0] << " "
              << king_positions[1] << " white pieces: " << white_pieces.size()
              << " black pieces: " << black_pieces.size()
              << std::endl << std::endl;

}


bool Position::is_attacked(SQUARE_TYPE pos) {

    if (!side) {
        for (PIECE_TYPE piece : {WHITE_QUEEN, WHITE_KNIGHT}) {
            for (int increment : BLACK_ATK_INCREMENTS[piece]) {
                if (!increment) break;

                SQUARE_TYPE new_pos = pos;

                while (true) {
                    new_pos += increment;
                    PIECE_TYPE occupied = board[new_pos];

                    if (occupied == PADDING || occupied < BLACK_PAWN) break;

                    if (occupied < EMPTY) {
                        if (piece == occupied - BLACK_PAWN) return true;
                        if (piece == WHITE_KNIGHT) break;

                        if (occupied == BLACK_KNIGHT) break;

                        if (occupied == BLACK_KING) {
                            if (new_pos == pos + increment) return true;
                            break;
                        }

                        if (occupied == BLACK_PAWN) {
                            if (new_pos == pos - 11 || new_pos == pos - 9) return true;
                            break;
                        }

                        if (occupied == BLACK_BISHOP) {
                            if (increment == -11 || increment == 11 ||
                                increment == 9 || increment == -9) return true;
                            break;
                        }

                        if (occupied == BLACK_ROOK) {
                            if (increment == -10 || increment == 1 ||
                                increment == 10 || increment == -1) return true;
                            break;
                        }
                    }

                    if (piece == WHITE_KNIGHT) break;
                }
            }
        }
    }

    else {
        for (PIECE_TYPE piece : {BLACK_QUEEN, BLACK_KNIGHT}) {
            for (int increment : WHITE_ATK_INCREMENTS[piece - BLACK_PAWN]) {
                if (!increment) break;

                SQUARE_TYPE new_pos = pos;

                while (true) {
                    new_pos += increment;
                    PIECE_TYPE occupied = board[new_pos];

                    if (occupied != EMPTY && occupied > WHITE_KING) break;

                    if (occupied < BLACK_PAWN) {
                        if (piece == occupied + BLACK_PAWN) return true;
                        if (piece == BLACK_KNIGHT) break;

                        if (occupied == WHITE_KNIGHT) break;

                        if (occupied == WHITE_KING) {
                            if (new_pos == pos + increment) return true;
                            break;
                        }

                        if (occupied == WHITE_PAWN) {
                            if (new_pos == pos + 11 || new_pos == pos + 9) return true;
                            break;
                        }

                        if (occupied == WHITE_BISHOP) {
                            if (increment == -11 || increment == 11 ||
                                increment == 9 || increment == -9) return true;
                            break;
                        }

                        if (occupied == WHITE_ROOK) {
                            if (increment == -10 || increment == 1 ||
                                increment == 10 || increment == -1) return true;
                            break;
                        }
                    }

                    if (piece == BLACK_KNIGHT) break;
                }
            }
        }
    }

    return false;
}


bool Position::make_move(MOVE_TYPE move) {

    // Get move info
    SQUARE_TYPE castled_pos[2] = {0};
    SQUARE_TYPE origin_square = get_origin_square(move);
    SQUARE_TYPE target_square = get_target_square(move);
    PIECE_TYPE selected = get_selected(move);
    uint16_t move_type = get_move_type(move);

    if (move_type == MOVE_TYPE_NORMAL) {
        board[target_square] = selected;
    }

    else if (move_type == MOVE_TYPE_EP) {
        board[target_square] = selected;

        if (!side) {
            board[target_square + 10] = EMPTY;
            auto it = std::find(std::begin(black_pieces), std::end(black_pieces), target_square + 10);
            black_pieces.erase(it);
        } else {
            board[target_square - 10] = EMPTY;
            auto it = std::find(std::begin(white_pieces), std::end(white_pieces), target_square - 10);
            white_pieces.erase(it);
        }
    }

    else if (move_type == MOVE_TYPE_CASTLE) {
        board[target_square] = selected;

        if (target_square < origin_square) {
            castled_pos[0] = target_square - 2;
            castled_pos[1] = target_square + 1;
        } else {
            castled_pos[0] = target_square + 1;
            castled_pos[1] = target_square - 1;
        }

        if (!side) {
            board[castled_pos[1]] = WHITE_ROOK;

            board[castled_pos[0]] = EMPTY;

            auto it = std::find(std::begin(white_pieces), std::end(white_pieces), castled_pos[0]);
            white_pieces[it - std::begin(white_pieces)] = castled_pos[1];
        } else {
            board[castled_pos[1]] = BLACK_ROOK;

            board[castled_pos[0]] = EMPTY;

            auto it = std::find(std::begin(black_pieces), std::end(black_pieces), castled_pos[0]);
            black_pieces[it - std::begin(black_pieces)] = castled_pos[1];
        }
    }

    else if (move_type == MOVE_TYPE_PROMOTION) {
        PIECE_TYPE promotion_piece = get_promotion_piece(move);
        board[target_square] = promotion_piece;
    }

    // Remove the piece from the source square
    board[origin_square] = EMPTY;

    if (!side) {
        auto it_1 = std::find(std::begin(white_pieces), std::end(white_pieces), origin_square);
        white_pieces[it_1 - std::begin(white_pieces)] = target_square;

        if (get_is_capture(move)) {
            auto it_2 = std::find(std::begin(black_pieces), std::end(black_pieces), target_square);
            black_pieces.erase(it_2);
        }
    } else {
        auto it_1 = std::find(std::begin(black_pieces), std::end(black_pieces), origin_square);
        black_pieces[it_1 - std::begin(black_pieces)] = target_square;

        if (get_is_capture(move)) {
            auto it_2 = std::find(std::begin(white_pieces), std::end(white_pieces), target_square);
            white_pieces.erase(it_2);
        }
    }

    // Change the king position for check detection
    if (selected == WHITE_KING || selected == BLACK_KING) king_positions[side] = target_square;

    // Legal move checking.
    // Return False if we are in check after our move or castling isn't legal.

    if (is_attacked(king_positions[side])) return false;
    if (castled_pos[0]) {
        // If we have castled, then we already checked to_square with is_attacked since the king moved.
        // We then check the position of where the rook would be, and where the king originally was
        if (is_attacked(castled_pos[1])) return false;
        if (is_attacked(origin_square)) return false;
    }

    // --- The move is legal ---

    // Double Pawn Push
    if ((selected == WHITE_PAWN || selected == BLACK_PAWN) && abs(target_square - origin_square) == 20) {
        // if (ep_square)
        ep_square = target_square - side * 20 + 10;  // 119 - (target_square + 10)
    } else {
        if (ep_square) {
            ep_square = 0;
        }
    }

    if (selected == WHITE_KING) {
        castle_ability_bits &= ~(1 << 0);
        castle_ability_bits &= ~(1 << 1);
    } else if (selected == BLACK_KING) {
        castle_ability_bits &= ~(1 << 2);
        castle_ability_bits &= ~(1 << 3);
    }

    if (origin_square == H1) castle_ability_bits &= ~(1 << 0);
    else if (origin_square == A1) castle_ability_bits &= ~(1 << 1);

    if (target_square == H8) castle_ability_bits &= ~(1 << 2);
    else if (target_square == A8) castle_ability_bits &= ~(1 << 3);

    return true;

}


void Position::undo_move(MOVE_TYPE move, SQUARE_TYPE current_ep,
               uint16_t current_castle_ability_bits, uint64_t current_hash_key) {

    hash_key = current_hash_key;

    // Get move info
    SQUARE_TYPE origin_square = get_origin_square(move);
    SQUARE_TYPE target_square = get_target_square(move);
    PIECE_TYPE selected = get_selected(move);
    PIECE_TYPE occupied = get_occupied(move);
    uint16_t move_type = get_move_type(move);

    if (move_type == MOVE_TYPE_EP) {
        if (!side) {
            board[target_square + 10] = BLACK_PAWN;
            black_pieces.push_back(target_square + 10);
        } else {
            board[target_square - 10] = WHITE_PAWN;
            white_pieces.push_back(target_square - 10);
        }
    }

    else if (move_type == MOVE_TYPE_CASTLE) {

        SQUARE_TYPE castled_pos[2];
        if (target_square < origin_square) {
            castled_pos[0] = origin_square - 1;
            castled_pos[1] = target_square - 2;
        } else {
            castled_pos[0] = origin_square + 1;
            castled_pos[1] = target_square + 1;
        }

        board[castled_pos[0]] = EMPTY;
        if (!side) {
            board[castled_pos[1]] = WHITE_ROOK;
            auto it = std::find(std::begin(white_pieces), std::end(white_pieces), castled_pos[0]);
            white_pieces[it - std::begin(white_pieces)] = castled_pos[1];
        } else {
            board[castled_pos[1]] = BLACK_ROOK;
            auto it = std::find(std::begin(black_pieces), std::end(black_pieces), castled_pos[0]);
            black_pieces[it - std::begin(black_pieces)] = castled_pos[1];
        }

    }

    if (!side) {
        auto it_1 = std::find(std::begin(white_pieces), std::end(white_pieces), target_square);
        white_pieces[it_1 - std::begin(white_pieces)] = origin_square;

        if (get_is_capture(move)) {
            black_pieces.push_back(target_square);
        }
    } else {
        auto it_1 = std::find(std::begin(black_pieces), std::end(black_pieces), target_square);
        black_pieces[it_1 - std::begin(black_pieces)] = origin_square;

        if (get_is_capture(move)) {
            white_pieces.push_back(target_square);
        }
    }

    board[target_square] = occupied;
    board[origin_square] = selected;

    if (ep_square != current_ep) ep_square = current_ep;

    castle_ability_bits = current_castle_ability_bits;

    if (selected == WHITE_KING || selected == BLACK_KING) king_positions[side] = origin_square;
}



void Position::get_pseudo_legal_moves(PLY_TYPE ply) {

    moves[ply].clear();

    if (!side) {

        for (SQUARE_TYPE pos : white_pieces) {
            PIECE_TYPE piece = board[pos];

            for (int increment : WHITE_INCREMENTS[piece]) {
                if (!increment) break;

                SQUARE_TYPE new_pos = pos;

                while (true) {
                    new_pos += increment;

                    PIECE_TYPE occupied = board[new_pos];

                    if (occupied == PADDING || occupied < BLACK_PAWN) break;
                    if (piece == WHITE_PAWN && (increment == -10 || increment == -20) &&
                        board[pos - 10] != EMPTY) break;
                    if (piece == WHITE_PAWN && increment == -20 && (pos < 81 || occupied != EMPTY)) break;

                    // En Passant
                    if (piece == WHITE_PAWN && (increment == -11 || increment == -9) and occupied == EMPTY) {
                        if (new_pos == ep_square) {
                            moves[ply].push_back(encode_move(pos, new_pos,
                                                                 WHITE_PAWN, EMPTY,
                                                                 MOVE_TYPE_EP, 0, false));
                        }

                        break;
                    }

                    // Promotion
                    if (piece == WHITE_PAWN && new_pos < 31) {
                        for (PIECE_TYPE new_piece = WHITE_KNIGHT; new_piece < WHITE_KING; new_piece++) {
                            moves[ply].push_back(encode_move(pos, new_pos,
                                                                 WHITE_PAWN, occupied,
                                                                 MOVE_TYPE_PROMOTION, new_piece,
                                                                 occupied < EMPTY));
                        }

                        break;
                    }

                    // Captures
                    if (occupied < EMPTY) {
                        moves[ply].push_back(encode_move(pos, new_pos,
                                                             piece, occupied,
                                                             MOVE_TYPE_NORMAL, 0, true));

                        break;
                    }

                    moves[ply].push_back(encode_move(pos, new_pos,
                                                         piece, EMPTY,
                                                         MOVE_TYPE_NORMAL, 0, false));

                    if (piece == WHITE_PAWN || piece == WHITE_KNIGHT || piece == WHITE_KING) break;

                    if ((castle_ability_bits & 1) == 1 && pos == H1 &&
                        board[new_pos - 1] == WHITE_KING) moves[ply].push_back(
                                encode_move(E1, G1, WHITE_KING,
                                            EMPTY, MOVE_TYPE_CASTLE, 0, false)
                        );

                    else if ((castle_ability_bits & 2) == 2 && pos == A1 &&
                             board[new_pos + 1] == WHITE_KING) moves[ply].push_back(
                                encode_move(E1, C1, WHITE_KING,
                                            EMPTY, MOVE_TYPE_CASTLE, 0, false)
                        );
                }
            }
        }
    }

    else {

        for (SQUARE_TYPE pos : black_pieces) {
            PIECE_TYPE piece = board[pos];

            for (int increment : BLACK_INCREMENTS[piece - BLACK_PAWN]) {
                if (!increment) break;

                SQUARE_TYPE new_pos = pos;

                while (true) {
                    new_pos += increment;

                    PIECE_TYPE occupied = board[new_pos];

                    if (occupied != EMPTY && occupied > WHITE_KING) break;
                    if (piece == BLACK_PAWN && (increment == 10 || increment == 20) &&
                        board[pos + 10] != EMPTY) break;
                    if (piece == BLACK_PAWN && increment == 20 && (pos > 38 || occupied != EMPTY)) break;

                    // En Passant
                    if (piece == BLACK_PAWN && (increment == 11 || increment == 9) and occupied == EMPTY) {
                        if (new_pos == ep_square) {
                            moves[ply].push_back(encode_move(pos, new_pos,
                                                                 BLACK_PAWN, EMPTY,
                                                                 MOVE_TYPE_EP, 0, false));
                        }

                        break;
                    }

                    // Promotion
                    if (piece == BLACK_PAWN && new_pos > 88) {
                        for (PIECE_TYPE new_piece = BLACK_KNIGHT; new_piece <= BLACK_QUEEN; new_piece++) {
                            moves[ply].push_back(encode_move(pos, new_pos,
                                                                 BLACK_PAWN, occupied,
                                                                 MOVE_TYPE_PROMOTION, new_piece,
                                                                 occupied < BLACK_PAWN));
                        }

                        break;
                    }

                    // Captures
                    if (occupied < BLACK_PAWN) {
                        moves[ply].push_back(encode_move(pos, new_pos,
                                                             piece, occupied,
                                                             MOVE_TYPE_NORMAL, 0, true));

                        break;
                    }

                    moves[ply].push_back(encode_move(pos, new_pos,
                                                         piece, EMPTY,
                                                         MOVE_TYPE_NORMAL, 0, false));

                    if (piece == BLACK_PAWN || piece == BLACK_KNIGHT || piece == BLACK_KING) break;

                    if ((castle_ability_bits & 4) == 4 && pos == H8 &&
                        board[new_pos - 1] == BLACK_KING) moves[ply].push_back(
                                encode_move(E8, G8, BLACK_KING,
                                            EMPTY, MOVE_TYPE_CASTLE, 0, false)
                        );

                    else if ((castle_ability_bits & 8) == 8 && pos == A8 &&
                             board[new_pos + 1] == BLACK_KING) moves[ply].push_back(
                                encode_move(E8, C8, BLACK_KING,
                                            EMPTY, MOVE_TYPE_CASTLE, 0, false)
                        );
                }
            }
        }
    }
}



void Position::get_pseudo_legal_captures(PLY_TYPE ply) {

    moves[ply].clear();

    if (!side) {

        for (SQUARE_TYPE pos : white_pieces) {
            PIECE_TYPE piece = board[pos];

            for (int increment : WHITE_ATK_INCREMENTS[piece]) {
                if (!increment) break;

                SQUARE_TYPE new_pos = pos;

                while (true) {
                    new_pos += increment;
                    PIECE_TYPE occupied = board[new_pos];

                    if (occupied == PADDING || occupied < BLACK_PAWN) break;

                    if (occupied < EMPTY) {
                        moves[ply].push_back(encode_move(pos, new_pos,
                                                             piece, occupied,
                                                             MOVE_TYPE_NORMAL, 0, true));

                        break;
                    }

                    if (piece == WHITE_PAWN || piece == WHITE_KNIGHT || piece == WHITE_KING) break;
                }
            }
        }
    }

    else {

        for (SQUARE_TYPE pos : black_pieces) {
            PIECE_TYPE piece = board[pos];

            for (int increment : BLACK_ATK_INCREMENTS[piece - BLACK_PAWN]) {
                if (!increment) break;

                SQUARE_TYPE new_pos = pos;

                while (true) {
                    new_pos += increment;
                    PIECE_TYPE occupied = board[new_pos];

                    if (occupied != EMPTY && occupied > WHITE_KING) break;

                    if (occupied < BLACK_PAWN) {
                        moves[ply].push_back(encode_move(pos, new_pos,
                                                             piece, occupied,
                                                             MOVE_TYPE_NORMAL, 0, true));

                        break;
                    }

                    if (piece == BLACK_PAWN || piece == BLACK_KNIGHT || piece == BLACK_KING) break;
                }
            }
        }
    }
}


