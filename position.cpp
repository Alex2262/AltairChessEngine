//
// Created by Alex Tian on 8/24/2022.
//

#include <iostream>
#include <algorithm>
#include <regex>
#include "position.h"
#include "useful.h"
#include "move.h"
#include "zobrist.h"


void Position::clear_movelist() {
    for (int i = 0; i < TOTAL_MAX_DEPTH; i++) {
        moves[i].clear();
    }
}


void Position::clear_state_stack() {
    for (auto& state : state_stack) {
        state.in_check = -1;
        state.current_hash_key = 0ULL;
        state.move = NO_MOVE;
        state.evaluation = NO_EVALUATION;
        state.current_ep_square = 0;
        state.current_castle_ability_bits = 0;
        state.current_fifty_move = 0;
        state.excluded_move = NO_MOVE;
    }
}


void Position::compute_hash_key() {
    hash_key = 0;

    for (int i = 0; i < 64; i++) {
        SQUARE_TYPE pos = STANDARD_TO_MAILBOX[i];

        if (board[pos] >= EMPTY) continue;

        hash_key ^= ZobristHashKeys.piece_hash_keys[board[pos]][i];
    }

    if (ep_square) hash_key ^= ZobristHashKeys.ep_hash_keys[MAILBOX_TO_STANDARD[ep_square]];

    hash_key ^= ZobristHashKeys.castle_hash_keys[castle_ability_bits];

    if (side) hash_key ^= ZobristHashKeys.side_hash_key;
}


PLY_TYPE Position::set_fen(const std::string& fen_string) {

    std::string reduced_fen_string = std::regex_replace(fen_string, std::regex("^ +| +$|( ) +"), "$1");

    std::vector<std::string> fen_tokens = split(reduced_fen_string, ' ');

    if (fen_tokens.size() < 4) {
        std::cout << "Fen String is invalid. " << fen_tokens.size()
                  << " Field(s) received, a minimum of 4 is required." << std::endl;
        return 0;
    }

    // Setting the padding around the 8x8 board inscribed within the 10x12 board
    SQUARE_TYPE pos = 0;

    white_pieces.clear();
    black_pieces.clear();

    non_pawn_material_count = 0;

    clear_movelist();

    for (SQUARE_TYPE& i : piece_list_index) {
        i = NO_PIECE_INDEX;
    }

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

            if (board[pos] != WHITE_PAWN && board[pos] != BLACK_PAWN &&
                board[pos] != WHITE_KING && board[pos] != BLACK_KING) non_pawn_material_count++;

            if (std::isupper(c)) {
                white_pieces.push_back(pos);
                piece_list_index[pos] = static_cast<SQUARE_TYPE>(white_pieces.size() - 1);
            }
            else {
                black_pieces.push_back(pos);
                piece_list_index[pos] = static_cast<SQUARE_TYPE>(black_pieces.size() - 1);
            }

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
        if (fischer_random_chess) {
            if (isupper(c)) {
                if (c == 'K') {
                    for (SQUARE_TYPE test_pos = king_positions[WHITE_COLOR] + 1; test_pos <= H1; test_pos++) {
                        if (board[test_pos] == WHITE_ROOK) {
                            starting_rook_pos[WHITE_COLOR][0] = test_pos;
                        }
                    }
                    castle_ability_bits |= 1;
                } else if (c == 'Q') {
                    for (SQUARE_TYPE test_pos = king_positions[WHITE_COLOR] - 1; test_pos >= A1; test_pos--) {
                        if (board[test_pos] == WHITE_ROOK) {
                            starting_rook_pos[WHITE_COLOR][1] = test_pos;
                        }
                    }
                    castle_ability_bits |= 2;
                } else {
                    int rook_col = c - 'A';
                    int king_col = MAILBOX_TO_STANDARD[king_positions[WHITE_COLOR]] % 8;

                    if (rook_col > king_col) {
                        castle_ability_bits |= 1;
                        starting_rook_pos[WHITE_COLOR][0] = STANDARD_TO_MAILBOX[rook_col + 56];
                    }
                    else {
                        castle_ability_bits |= 2;
                        starting_rook_pos[WHITE_COLOR][1] = STANDARD_TO_MAILBOX[rook_col + 56];
                    }
                }
            }

            else {
                if (c == 'k') {
                    for (SQUARE_TYPE test_pos = king_positions[BLACK_COLOR] + 1; test_pos <= H8; test_pos++) {
                        if (board[test_pos] == BLACK_ROOK) {
                            starting_rook_pos[BLACK_COLOR][0] = test_pos;
                        }
                    }
                    castle_ability_bits |= 4;
                } else if (c == 'q') {
                    for (SQUARE_TYPE test_pos = king_positions[BLACK_COLOR] - 1; test_pos >= A8; test_pos--) {
                        if (board[test_pos] == BLACK_ROOK) {
                            starting_rook_pos[BLACK_COLOR][1] = test_pos;
                        }
                    }
                    castle_ability_bits |= 8;
                } else {
                    int rook_col = c - 'a';
                    int king_col = MAILBOX_TO_STANDARD[king_positions[BLACK_COLOR]] % 8;

                    if (rook_col > king_col) {
                        castle_ability_bits |= 4;
                        starting_rook_pos[BLACK_COLOR][0] = STANDARD_TO_MAILBOX[rook_col];
                    }
                    else {
                        castle_ability_bits |= 8;
                        starting_rook_pos[BLACK_COLOR][1] = STANDARD_TO_MAILBOX[rook_col];
                    }
                }
            }
        }

        else {
            if (c == 'K') {
                castle_ability_bits |= 1;
                starting_rook_pos[WHITE_COLOR][0] = H1;
            }
            else if (c == 'Q') {
                castle_ability_bits |= 2;
                starting_rook_pos[WHITE_COLOR][1] = A1;
            }
            else if (c == 'k') {
                castle_ability_bits |= 4;
                starting_rook_pos[BLACK_COLOR][0] = H8;
            }
            else if (c == 'q') {
                castle_ability_bits |= 8;
                starting_rook_pos[BLACK_COLOR][1] = A8;
            }
        }
    }

    // std::cout << starting_rook_pos[WHITE_COLOR][0] << " " << starting_rook_pos[WHITE_COLOR][1] << " " <<
    //              starting_rook_pos[BLACK_COLOR][0] << " " << starting_rook_pos[BLACK_COLOR][1] << std::endl;

    if (fen_tokens[3].size() > 1) {
        auto square = static_cast<SQUARE_TYPE>((8 - (fen_tokens[3][1] - '0')) * 8 + fen_tokens[3][0] - 'a');
        ep_square = STANDARD_TO_MAILBOX[square];
    }
    else {
        ep_square = 0;
    }

    side = 0;
    if (fen_tokens[1] == "b") side = 1;

    compute_hash_key();

    if (fen_tokens.size() >= 5) {
        return static_cast<PLY_TYPE>(std::stoi(fen_tokens[4]));
    }
    else return 0;
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
              << " hash: " << hash_key << "\nking pos: " << king_positions[0] << " "
              << king_positions[1] << " white pieces: " << white_pieces.size()
              << " black pieces: " << black_pieces.size()
              << std::endl << std::endl;
}


[[maybe_unused]] void Position::print_piece_index_board() {
    std::string new_board;

    for (SQUARE_TYPE pos : STANDARD_TO_MAILBOX) {
        if (MAILBOX_TO_STANDARD[pos] % 8 == 0) {
            new_board += '\n';
        }
        new_board += std::to_string(piece_list_index[pos]);
        new_board += " ";
    }

    std::cout << new_board << std::endl;
}


[[maybe_unused]] bool Position::check_valid(PLY_TYPE ply) {
    for (SQUARE_TYPE pos : STANDARD_TO_MAILBOX) {
        PIECE_TYPE piece = board[pos];

        if (piece == EMPTY) {
            if (piece_list_index[pos] != -1) {
                std::cout << "EMPTY PIECE EXPECTED " << -1 << " GOT " << piece_list_index[pos] << std::endl;
                std::cout << "Previous moves:" << std::endl;
                for (int test_ply = 0; test_ply <= ply; test_ply++) {
                    std::cout << get_uci_from_move(*this, state_stack[test_ply].move) << " ";
                }
                std::cout << std::endl;
                print_board();
                return false;
            }
        }

        else if (piece < BLACK_PAWN) {
            if (board[white_pieces[piece_list_index[pos]]] != piece) {
                std::cout << "NOT MATCHING WHITE PIECE EXPECTED " << piece << " GOT " <<
                             board[white_pieces[piece_list_index[pos]]]  << std::endl;
                std::cout << pos << " " << piece_list_index[pos] << " " << black_pieces[piece_list_index[pos]] << std::endl;

                std::cout << "Previous moves:" << std::endl;
                for (int test_ply = 0; test_ply <= ply; test_ply++) {
                    std::cout << get_uci_from_move(*this, state_stack[test_ply].move) << " ";
                }
                std::cout << std::endl;
                print_board();
                return false;
            }
        }

        else if (piece < EMPTY) {
            if (board[black_pieces[piece_list_index[pos]]] != piece) {
                std::cout << "NOT MATCHING BLACK PIECE EXPECTED " << piece << " GOT " <<
                          board[black_pieces[piece_list_index[pos]]]  << std::endl;
                std::cout << pos << " " << piece_list_index[pos] << " " << black_pieces[piece_list_index[pos]] << std::endl;

                std::cout << "Previous moves:" << std::endl;
                for (int test_ply = 0; test_ply <= ply; test_ply++) {
                    std::cout << get_uci_from_move(*this, state_stack[test_ply].move) << " ";
                }
                std::cout << std::endl;
                print_board();
                return false;
            }
        }
    }

    return true;
}


bool Position::is_attacked(SQUARE_TYPE pos) {

    if (!side) {
        // Check if pawns are attacking you
        if (board[pos - 11] == BLACK_PAWN || board[pos - 9] == BLACK_PAWN) return true;

        // Search with the increments of a knight to see if any opponent knights are attacking you
        for (int increment : BLACK_ATK_INCREMENTS[WHITE_KNIGHT]) {
            auto new_pos = static_cast<SQUARE_TYPE>(pos + increment);
            PIECE_TYPE occupied = board[new_pos];

            if (occupied == BLACK_KNIGHT) return true;
        }

        // Search with the increments of a queen to see if any opponent queens, bishops, or rooks are attacking you.
        for (int increment : BLACK_ATK_INCREMENTS[WHITE_QUEEN]) {
            SQUARE_TYPE new_pos = pos;

            while (true) {
                new_pos += increment;
                PIECE_TYPE occupied = board[new_pos];

                // Break if you hit your own piece or if you are out of bounds
                if (occupied == PADDING || occupied < BLACK_PAWN) break;
                if (occupied == EMPTY) continue;  // Continue if there is no piece on this square

                if (occupied == BLACK_QUEEN) return true;

                else if (occupied == BLACK_BISHOP) {
                    if (increment == -11 || increment == 11 || increment == 9 || increment == -9) return true;
                }

                else if (occupied == BLACK_ROOK) {
                    if (increment == -10 || increment == 1 || increment == 10 || increment == -1) return true;
                }

                else if (occupied == BLACK_KING) {
                    if (new_pos == pos + increment) return true;
                }

                break;

            }
        }
    }

    else {

        // Check if pawns are attacking you
        if (board[pos + 11] == WHITE_PAWN || board[pos + 9] == WHITE_PAWN) return true;

        // Search with the increments of a knight to see if any opponent knights are attacking you
        for (int increment : WHITE_ATK_INCREMENTS[WHITE_KNIGHT]) {
            SQUARE_TYPE new_pos = pos + increment;
            PIECE_TYPE occupied = board[new_pos];

            if (occupied == WHITE_KNIGHT) return true;
        }

        // Search with the increments of a queen to see if any opponent queens, bishops, or rooks are attacking you.
        for (int increment : WHITE_ATK_INCREMENTS[WHITE_QUEEN]) {
            SQUARE_TYPE new_pos = pos;

            while (true) {
                new_pos += increment;
                PIECE_TYPE occupied = board[new_pos];

                // Break if you hit your own piece or if you are out of bounds
                if (occupied != EMPTY && occupied > WHITE_KING) break;
                if (occupied == EMPTY) continue;  // Continue if there is no piece on this square

                if (occupied == WHITE_QUEEN) return true;

                else if (occupied == WHITE_BISHOP) {
                    if (increment == -11 || increment == 11 || increment == 9 || increment == -9) return true;
                }

                else if (occupied == WHITE_ROOK) {
                    if (increment == -10 || increment == 1 || increment == 10 || increment == -1) return true;
                }

                else if (occupied == WHITE_KING) {
                    if (new_pos == pos + increment) return true;
                }

                break;

            }
        }
    }

    return false;
}


void Position::set_state(PLY_TYPE search_ply, PLY_TYPE fifty_move) {
    state_stack[search_ply].current_ep_square = ep_square;
    state_stack[search_ply].current_fifty_move = fifty_move;
    state_stack[search_ply].current_hash_key = hash_key;
    state_stack[search_ply].current_castle_ability_bits = castle_ability_bits;
}


bool Position::make_move(MOVE_TYPE move, PLY_TYPE search_ply, PLY_TYPE& fifty_move) {

    // Get move info
    SQUARE_TYPE castled_pos[2] = {0};
    SQUARE_TYPE origin_square = get_origin_square(move);
    SQUARE_TYPE target_square = get_target_square(move);
    PIECE_TYPE selected = get_selected(move);
    PIECE_TYPE occupied = get_occupied(move);
    SQUARE_TYPE selected_index = piece_list_index[origin_square];
    SQUARE_TYPE occupied_index = piece_list_index[target_square];
    uint16_t move_type = get_move_type(move);

    state_stack[search_ply].move = move;

    bool legal = true;

    fifty_move++;

    if (move_type == MOVE_TYPE_NORMAL) {
        // Set the piece to the target square and hash it
        piece_list_index[target_square] = selected_index;
        board[target_square] = selected;
        hash_key ^= ZobristHashKeys.piece_hash_keys[selected][MAILBOX_TO_STANDARD[target_square]];
    }

    else if (move_type == MOVE_TYPE_EP) {
        // Set the piece to the target square and hash it
        piece_list_index[target_square] = selected_index;
        board[target_square] = selected;
        hash_key ^= ZobristHashKeys.piece_hash_keys[selected][MAILBOX_TO_STANDARD[target_square]];

        // Remove the en passant captured pawn and hash it
        if (!side) {
            board[target_square + 10] = EMPTY;
            hash_key ^= ZobristHashKeys.piece_hash_keys[BLACK_PAWN][MAILBOX_TO_STANDARD[target_square + 10]];

            black_pieces.erase(black_pieces.begin() + piece_list_index[target_square + 10]);
            update_piece_list_index(piece_list_index[target_square + 10], black_pieces.size(), BLACK_COLOR);

            piece_list_index[target_square + 10] = NO_PIECE_INDEX;
        } else {
            board[target_square - 10] = EMPTY;
            hash_key ^= ZobristHashKeys.piece_hash_keys[WHITE_PAWN][MAILBOX_TO_STANDARD[target_square - 10]];

            white_pieces.erase(white_pieces.begin() + piece_list_index[target_square - 10]);
            update_piece_list_index(piece_list_index[target_square - 10], white_pieces.size(), WHITE_COLOR);

            piece_list_index[target_square - 10] = NO_PIECE_INDEX;
        }
    }

    else if (move_type == MOVE_TYPE_CASTLE) {

        legal = !is_attacked(origin_square);

        // Queen side castling
        if (target_square == C1 || target_square == C8) {
            castled_pos[0] = starting_rook_pos[side][1];  // Rook origin square
            castled_pos[1] = target_square + 1;  // Rook target square
        }
        // King side castling
        else {
            castled_pos[0] = starting_rook_pos[side][0];  // Rook origin square
            castled_pos[1] = target_square - 1;  // Rook target square
        }

        if (castled_pos[0] != castled_pos[1]) {
            piece_list_index[castled_pos[1]] = piece_list_index[castled_pos[0]];

            // Move the rook and hash it
            if (!side) {
                board[castled_pos[1]] = WHITE_ROOK;
                hash_key ^= ZobristHashKeys.piece_hash_keys[WHITE_ROOK][MAILBOX_TO_STANDARD[castled_pos[1]]];

                board[castled_pos[0]] = EMPTY;
                hash_key ^= ZobristHashKeys.piece_hash_keys[WHITE_ROOK][MAILBOX_TO_STANDARD[castled_pos[0]]];

                white_pieces[piece_list_index[castled_pos[1]]] = castled_pos[1];
            } else {
                board[castled_pos[1]] = BLACK_ROOK;
                hash_key ^= ZobristHashKeys.piece_hash_keys[BLACK_ROOK][MAILBOX_TO_STANDARD[castled_pos[1]]];

                board[castled_pos[0]] = EMPTY;
                hash_key ^= ZobristHashKeys.piece_hash_keys[BLACK_ROOK][MAILBOX_TO_STANDARD[castled_pos[0]]];

                black_pieces[piece_list_index[castled_pos[1]]] = castled_pos[1];
            }

            piece_list_index[castled_pos[0]] = NO_PIECE_INDEX;
        }

        board[target_square] = selected;
        piece_list_index[target_square] = selected_index;
        hash_key ^= ZobristHashKeys.piece_hash_keys[selected][MAILBOX_TO_STANDARD[target_square]];
    }

    else if (move_type == MOVE_TYPE_PROMOTION) {
        PIECE_TYPE promotion_piece = get_promotion_piece(move);
        piece_list_index[target_square] = selected_index;
        board[target_square] = promotion_piece;
        hash_key ^= ZobristHashKeys.piece_hash_keys[promotion_piece][MAILBOX_TO_STANDARD[target_square]];
    }

    // Remove the piece from the source square except for some FRC edge cases
    if (target_square != origin_square && castled_pos[1] != origin_square) {
        board[origin_square] = EMPTY;
        hash_key ^= ZobristHashKeys.piece_hash_keys[selected][MAILBOX_TO_STANDARD[origin_square]];
    }

    // Update certain information for both sides in the case of capturing moves
    if (!side) {
        white_pieces[selected_index] = target_square;

        if (get_is_capture(move)) {
            fifty_move = 0;
            hash_key ^= ZobristHashKeys.piece_hash_keys[occupied][MAILBOX_TO_STANDARD[target_square]];
            black_pieces.erase(black_pieces.begin() + occupied_index);
            update_piece_list_index(occupied_index, black_pieces.size(), BLACK_COLOR);

            if (occupied != BLACK_PAWN) non_pawn_material_count--;
        }
    } else {
        black_pieces[selected_index] = target_square;

        if (get_is_capture(move)) {
            fifty_move = 0;
            hash_key ^= ZobristHashKeys.piece_hash_keys[occupied][MAILBOX_TO_STANDARD[target_square]];
            white_pieces.erase(white_pieces.begin() + occupied_index);
            update_piece_list_index(occupied_index, white_pieces.size(), WHITE_COLOR);

            if (occupied != WHITE_PAWN) non_pawn_material_count--;
        }
    }

    // Piece List Index updating except in the case of FRC edge cases
    if (target_square != origin_square && castled_pos[1] != origin_square) piece_list_index[origin_square] = NO_PIECE_INDEX;

    // Change the king position for check detection
    if (selected == WHITE_KING || selected == BLACK_KING) king_positions[side] = target_square;

    // Legal move checking.
    // Return False if we are in check after our move or castling isn't legal.

    if (!legal) return false;
    if (is_attacked(king_positions[side])) return false;
    if (castled_pos[0]) {
        // If we have castled, then we already checked to_square with is_attacked since the king moved.
        // We then check the position of where the rook would be, and where the king originally was
        if (target_square == C1 || target_square == C8) {
            for (SQUARE_TYPE temp_pos = origin_square - 1; temp_pos > target_square; temp_pos--) {
                if (is_attacked(temp_pos)) return false;
            }
        } else {
            for (SQUARE_TYPE temp_pos = origin_square + 1; temp_pos < target_square; temp_pos++) {
                if (is_attacked(temp_pos)) return false;
            }
        }
    }

    // --- The move is legal ---
    if (selected == WHITE_PAWN || selected == BLACK_PAWN) fifty_move = 0;

    // Double Pawn Push
    if ((selected == WHITE_PAWN || selected == BLACK_PAWN) && abs(target_square - origin_square) == 20) {
        // Reset the hashed ep square if it exists
        if (ep_square)  hash_key ^= ZobristHashKeys.ep_hash_keys[MAILBOX_TO_STANDARD[ep_square]];

        ep_square = target_square - side * 20 + 10;
        hash_key ^= ZobristHashKeys.ep_hash_keys[MAILBOX_TO_STANDARD[ep_square]];  // Set new EP hash
    } else {
        if (ep_square) {
            hash_key ^= ZobristHashKeys.ep_hash_keys[MAILBOX_TO_STANDARD[ep_square]];
            ep_square = 0;
        }
    }

    hash_key ^= ZobristHashKeys.castle_hash_keys[castle_ability_bits];

    // Update Castling Rights
    if (selected == WHITE_KING) {
        castle_ability_bits &= ~(1 << 0);
        castle_ability_bits &= ~(1 << 1);
    } else if (selected == BLACK_KING) {
        castle_ability_bits &= ~(1 << 2);
        castle_ability_bits &= ~(1 << 3);
    }

    if (origin_square == starting_rook_pos[WHITE_COLOR][0] ||
        target_square == starting_rook_pos[WHITE_COLOR][0]) castle_ability_bits &= ~(1 << 0);
    else if (origin_square == starting_rook_pos[WHITE_COLOR][1] ||
             target_square == starting_rook_pos[WHITE_COLOR][1]) castle_ability_bits &= ~(1 << 1);
    else if (origin_square == starting_rook_pos[BLACK_COLOR][0] ||
             target_square == starting_rook_pos[BLACK_COLOR][0]) castle_ability_bits &= ~(1 << 2);
    else if (origin_square == starting_rook_pos[BLACK_COLOR][1] ||
             target_square == starting_rook_pos[BLACK_COLOR][1]) castle_ability_bits &= ~(1 << 3);

    hash_key ^= ZobristHashKeys.castle_hash_keys[castle_ability_bits];

    // Switch hash side (actual side is switched in loop)
    hash_key ^= ZobristHashKeys.side_hash_key;

    return true;

}


void Position::undo_move(MOVE_TYPE move, PLY_TYPE search_ply, PLY_TYPE& fifty_move) {

    hash_key = state_stack[search_ply].current_hash_key;
    fifty_move = state_stack[search_ply].current_fifty_move;

    SQUARE_TYPE castled_pos[2]{};

    // Get move info
    SQUARE_TYPE origin_square = get_origin_square(move);
    SQUARE_TYPE target_square = get_target_square(move);
    PIECE_TYPE selected = get_selected(move);
    PIECE_TYPE occupied = get_occupied(move);
    SQUARE_TYPE occupied_index = piece_list_index[target_square];
    uint16_t move_type = get_move_type(move);

    if (move_type == MOVE_TYPE_EP) {
        if (!side) {
            board[target_square + 10] = BLACK_PAWN;
            black_pieces.push_back(target_square + 10);
            piece_list_index[target_square + 10] = black_pieces.size() - 1;
        } else {
            board[target_square - 10] = WHITE_PAWN;
            white_pieces.push_back(target_square - 10);
            piece_list_index[target_square - 10] = white_pieces.size() - 1;
        }
    }

    else if (move_type == MOVE_TYPE_CASTLE) {
        if (target_square == C1 || target_square == C8) {
            castled_pos[0] = target_square + 1;  // Current rook square
            castled_pos[1] = starting_rook_pos[side][1];  // Old rook square
        } else {
            castled_pos[0] = target_square - 1;  // Current rook square
            castled_pos[1] = starting_rook_pos[side][0];  // Old rook square
        }

        if (castled_pos[0] != castled_pos[1]) {
            piece_list_index[castled_pos[1]] = piece_list_index[castled_pos[0]];

            if (!side) {
                board[castled_pos[1]] = WHITE_ROOK;
                white_pieces[piece_list_index[castled_pos[0]]] = castled_pos[1];
            } else {
                board[castled_pos[1]] = BLACK_ROOK;
                black_pieces[piece_list_index[castled_pos[0]]] = castled_pos[1];
            }

            board[castled_pos[0]] = EMPTY;
            piece_list_index[castled_pos[0]] = NO_PIECE_INDEX;
        }
    }

    // Set the occupied piece back except in FRC edge cases
    if (castled_pos[1] != target_square) board[target_square] = occupied;
    board[origin_square] = selected;

    piece_list_index[origin_square] = occupied_index;

    // Reset the piece list index target square except in FRC edge cases
    if (target_square != origin_square && castled_pos[1] != target_square) piece_list_index[target_square] = NO_PIECE_INDEX;

    if (!side) {
        white_pieces[piece_list_index[origin_square]] = origin_square;

        if (get_is_capture(move)) {
            black_pieces.push_back(target_square);
            piece_list_index[target_square] = black_pieces.size() - 1;
            if (occupied != BLACK_PAWN) non_pawn_material_count++;
        }
    } else {
        black_pieces[piece_list_index[origin_square]] = origin_square;

        if (get_is_capture(move)) {
            white_pieces.push_back(target_square);
            piece_list_index[target_square] = white_pieces.size() - 1;
            if (occupied != WHITE_PAWN) non_pawn_material_count++;
        }
    }

    if (ep_square != state_stack[search_ply].current_ep_square)
        ep_square = state_stack[search_ply].current_ep_square;

    castle_ability_bits = state_stack[search_ply].current_castle_ability_bits;

    if (selected == WHITE_KING || selected == BLACK_KING) king_positions[side] = origin_square;
}


void Position::make_null_move(PLY_TYPE search_ply, PLY_TYPE& fifty_move) {

    side ^= 1;
    hash_key ^= ZobristHashKeys.side_hash_key;

    state_stack[search_ply].move = NO_MOVE;

    if (ep_square) {
        hash_key ^= ZobristHashKeys.ep_hash_keys[MAILBOX_TO_STANDARD[ep_square]];
        ep_square = 0;
    }

    fifty_move = 0;
}


void Position::undo_null_move(PLY_TYPE search_ply, PLY_TYPE& fifty_move) {
    side ^= 1;
    ep_square = state_stack[search_ply].current_ep_square;
    hash_key = state_stack[search_ply].current_hash_key;
    fifty_move = state_stack[search_ply].current_fifty_move;
}


void Position::get_pseudo_legal_moves(PLY_TYPE ply) {

    moves[ply].clear();

    // Pseudo legals for White
    if (!side) {

        // Loop through the white pieces
        for (SQUARE_TYPE pos : white_pieces) {
            PIECE_TYPE piece = board[pos];

            // Generate the directions for the piece to move in
            for (short increment : WHITE_INCREMENTS[piece]) {
                if (!increment) break;

                SQUARE_TYPE new_pos = pos;

                while (true) {
                    new_pos += increment;

                    PIECE_TYPE occupied = board[new_pos];

                    if (occupied == PADDING || occupied < BLACK_PAWN) {

                        // Castling
                        if (piece == WHITE_ROOK && board[new_pos] == WHITE_KING) {

                            // King side castling
                            if ((castle_ability_bits & 1) == 1 && pos == starting_rook_pos[WHITE_COLOR][0]) {

                                // FRC Castling Cases
                                if (fischer_random_chess) {

                                    // The rook is to the right of the F1 square (the square it will go to)
                                    if (new_pos > F1) {
                                        // Ensure that the rook can go to the F1 square
                                        if (board[F1] != EMPTY) break;
                                    }

                                    // The rook is to the left of the F1 square (the square it will go to)
                                    else if (new_pos < F1) {
                                        // Ensure that all the squares between the king's square,
                                        // and its current square are empty
                                        bool flag = true;
                                        for (SQUARE_TYPE temp_pos = G1; temp_pos > pos; temp_pos--) {
                                            if (board[temp_pos] != EMPTY) {
                                                flag = false;
                                                break;
                                            }
                                        }

                                        if (!flag) break;
                                    }
                                }

                                // Add the castling move
                                moves[ply].push_back(
                                        Move_Struct{encode_move(new_pos, G1, WHITE_KING,
                                                    EMPTY, MOVE_TYPE_CASTLE, 0, false),
                                                    0,
                                                    false}
                                );
                            }

                            // Queen side castling
                            else if ((castle_ability_bits & 2) == 2 && pos == starting_rook_pos[WHITE_COLOR][1]) {

                                // FRC Castling Cases
                                if (fischer_random_chess) {

                                    // The rook is to the left of the D1 square (the square it will go to)
                                    if (new_pos < D1) {
                                        // Guard certain cases
                                        if (board[C1] != EMPTY && board[C1] != WHITE_KING) break;
                                        if (board[D1] != EMPTY) break;
                                    }

                                    // The rook is to the right of the D1 square (the square it will go to)
                                    else if (new_pos > D1){
                                        // Ensure that all the squares between the king's square,
                                        // and its current square are empty
                                        bool flag = true;
                                        for (SQUARE_TYPE temp_pos = C1; temp_pos < pos; temp_pos++) {
                                            if (board[temp_pos] != EMPTY) {
                                                flag = false;
                                                break;
                                            }
                                        }

                                        if (!flag) break;
                                    }
                                }

                                // Add the castling move
                                moves[ply].push_back(
                                        Move_Struct{encode_move(new_pos, C1, WHITE_KING,
                                                    EMPTY, MOVE_TYPE_CASTLE, 0, false),
                                                    0,
                                                    false}
                                );
                            }

                        }

                        break;
                    }

                    if (piece == WHITE_PAWN && (increment == -10 || increment == -20) &&
                        board[pos - 10] != EMPTY) break;
                    if (piece == WHITE_PAWN && increment == -20 && (pos < 81 || occupied != EMPTY)) break;

                    // En Passant
                    if (piece == WHITE_PAWN && (increment == -11 || increment == -9) && occupied == EMPTY) {
                        if (new_pos == ep_square) {
                            moves[ply].push_back(Move_Struct{encode_move(pos, new_pos,
                                                                 WHITE_PAWN, EMPTY,
                                                                 MOVE_TYPE_EP, 0, false),
                                                             0,
                                                             false});
                        }

                        break;
                    }

                    // Promotion
                    if (piece == WHITE_PAWN && new_pos < 31) {
                        for (PIECE_TYPE new_piece = WHITE_KNIGHT; new_piece < WHITE_KING; new_piece++) {
                            moves[ply].push_back(Move_Struct{encode_move(pos, new_pos,
                                                                 WHITE_PAWN, occupied,
                                                                 MOVE_TYPE_PROMOTION, new_piece,
                                                                 occupied < EMPTY),
                                                             0,
                                                             false});
                        }

                        break;
                    }

                    // Captures
                    if (occupied < EMPTY) {
                        moves[ply].push_back(Move_Struct{encode_move(pos, new_pos,
                                                             piece, occupied,
                                                             MOVE_TYPE_NORMAL, 0, true),
                                                         0,
                                                         false});

                        break;
                    }

                    // Ordinary moves
                    moves[ply].push_back(Move_Struct{encode_move(pos, new_pos,
                                                         piece, EMPTY,
                                                         MOVE_TYPE_NORMAL, 0, false),
                                                     0,
                                                     false});

                    if (piece == WHITE_PAWN || piece == WHITE_KNIGHT || piece == WHITE_KING) break;
                }
            }
        }
    }

    // Pseudo legals for Black
    else {

        // Loop through the black pieces
        for (SQUARE_TYPE pos : black_pieces) {
            PIECE_TYPE piece = board[pos];

            // Generate the directions for the piece to move in
            for (short increment : BLACK_INCREMENTS[piece - BLACK_PAWN]) {
                if (!increment) break;

                SQUARE_TYPE new_pos = pos;

                while (true) {
                    new_pos += increment;

                    PIECE_TYPE occupied = board[new_pos];

                    if (occupied != EMPTY && occupied > WHITE_KING) {

                        // Castling
                        if (piece == BLACK_ROOK && board[new_pos] == BLACK_KING) {

                            // King side castling
                            if ((castle_ability_bits & 4) == 4 && pos == starting_rook_pos[BLACK_COLOR][0]) {

                                // FRC Castling Cases
                                if (fischer_random_chess) {

                                    // The rook is to the right of the F8 square (the square it will go to)
                                    if (new_pos > F8) {
                                        // Ensure that the rook can go to the F1 square
                                        if (board[F8] != EMPTY) break;
                                    }

                                    // The rook is to the left of the F8 square (the square it will go to)
                                    else if (new_pos < F8) {
                                        // Ensure that all the squares between the king's square,
                                        // and its current square are empty
                                        bool flag = true;
                                        for (SQUARE_TYPE temp_pos = G8; temp_pos > pos; temp_pos--) {
                                            if (board[temp_pos] != EMPTY) {
                                                flag = false;
                                                break;
                                            }
                                        }

                                        if (!flag) break;
                                    }
                                }

                                // Add the castling move
                                moves[ply].push_back(
                                        Move_Struct{encode_move(new_pos, G8, BLACK_KING,
                                                    EMPTY, MOVE_TYPE_CASTLE, 0, false),
                                                    0,
                                                    false}
                                );
                            }


                            else if ((castle_ability_bits & 8) == 8 && pos == starting_rook_pos[BLACK_COLOR][1]) {

                                // FRC Castling Cases
                                if (fischer_random_chess) {

                                    // The rook is to the left of the D8 square (the square it will go to)
                                    if (new_pos < D8) {
                                        // Guard certain cases
                                        if (board[C8] != EMPTY && board[C8] != WHITE_KING) break;
                                        if (board[D8] != EMPTY) break;
                                    }

                                    // The rook is to the right of the D8 square (the square it will go to)
                                    else if (new_pos > D8){
                                        // Ensure that all the squares between the king's square,
                                        // and its current square are empty
                                        bool flag = true;
                                        for (SQUARE_TYPE temp_pos = C8; temp_pos < pos; temp_pos++) {
                                            if (board[temp_pos] != EMPTY) {
                                                flag = false;
                                                break;
                                            }
                                        }

                                        if (!flag) break;
                                    }
                                }

                                // Add the castling move
                                moves[ply].push_back(
                                        Move_Struct{encode_move(new_pos, C8, BLACK_KING,
                                                    EMPTY, MOVE_TYPE_CASTLE, 0, false),
                                                    0,
                                                    false}
                                );
                            }

                        }
                        break;
                    }

                    if (piece == BLACK_PAWN && (increment == 10 || increment == 20) &&
                        board[pos + 10] != EMPTY) break;
                    if (piece == BLACK_PAWN && increment == 20 && (pos > 38 || occupied != EMPTY)) break;

                    // En Passant
                    if (piece == BLACK_PAWN && (increment == 11 || increment == 9) && occupied == EMPTY) {
                        if (new_pos == ep_square) {
                            moves[ply].push_back(Move_Struct{encode_move(pos, new_pos,
                                                                 BLACK_PAWN, EMPTY,
                                                                 MOVE_TYPE_EP, 0, false),
                                                             0,
                                                             false});
                        }

                        break;
                    }

                    // Promotion
                    if (piece == BLACK_PAWN && new_pos > 88) {
                        for (PIECE_TYPE new_piece = BLACK_KNIGHT; new_piece <= BLACK_QUEEN; new_piece++) {
                            moves[ply].push_back(Move_Struct{encode_move(pos, new_pos,
                                                                 BLACK_PAWN, occupied,
                                                                 MOVE_TYPE_PROMOTION, new_piece,
                                                                 occupied < BLACK_PAWN),
                                                             0,
                                                             false});
                        }

                        break;
                    }

                    // Captures
                    if (occupied < BLACK_PAWN) {
                        moves[ply].push_back(Move_Struct{encode_move(pos, new_pos,
                                                             piece, occupied,
                                                             MOVE_TYPE_NORMAL, 0, true),
                                                         0,
                                                         false});

                        break;
                    }

                    // Ordinary moves
                    moves[ply].push_back(Move_Struct{encode_move(pos, new_pos,
                                                         piece, EMPTY,
                                                         MOVE_TYPE_NORMAL, 0, false),
                                                     0,
                                                     false});

                    if (piece == BLACK_PAWN || piece == BLACK_KNIGHT || piece == BLACK_KING) break;
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

            for (short increment : WHITE_ATK_INCREMENTS[piece]) {
                if (!increment) break;

                SQUARE_TYPE new_pos = pos;

                while (true) {
                    new_pos += increment;
                    PIECE_TYPE occupied = board[new_pos];

                    if (occupied == PADDING || occupied < BLACK_PAWN) break;

                    if (occupied < EMPTY) {
                        moves[ply].push_back(Move_Struct{encode_move(pos, new_pos,
                                                             piece, occupied,
                                                             MOVE_TYPE_NORMAL, 0, true),
                                                         0,
                                                         false});

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

            for (short increment : BLACK_ATK_INCREMENTS[piece - BLACK_PAWN]) {
                if (!increment) break;

                SQUARE_TYPE new_pos = pos;

                while (true) {
                    new_pos += increment;
                    PIECE_TYPE occupied = board[new_pos];

                    if (occupied != EMPTY && occupied > WHITE_KING) break;

                    if (occupied < BLACK_PAWN) {
                        moves[ply].push_back(Move_Struct{encode_move(pos, new_pos,
                                                             piece, occupied,
                                                             MOVE_TYPE_NORMAL, 0, true),
                                                         0,
                                                         false});

                        break;
                    }

                    if (piece == BLACK_PAWN || piece == BLACK_KNIGHT || piece == BLACK_KING) break;
                }
            }
        }
    }
}


bool Position::get_is_pseudo_legal(MOVE_TYPE move) {
    if (get_selected(move) != board[get_origin_square(move)]) return false;
    if (get_occupied(move) != board[get_target_square(move)]) return false;

    return true;
}

