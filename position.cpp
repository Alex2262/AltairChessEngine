
#include <stdexcept>
#include <iostream>
#include <bitset>
#include <regex>
#include "position.h"
#include "useful.h"
#include "bitboard.h"
#include "attacks.h"
#include "zobrist.h"


void Position::clear_state_stack() {
    for (auto& state : state_stack) {
        state.in_check = -1;
        state.current_hash_key = 0ULL;
        state.move = NO_INFORMATIVE_MOVE;
        state.evaluation = NO_EVALUATION;
        state.current_ep_square = NO_SQUARE;
        state.current_castle_ability_bits = 0;
        state.current_fifty_move = 0;
        state.excluded_move = NO_MOVE;
    }
}

void Position::set_state(State_Struct& state_struct, PLY_TYPE fifty_move) const {
    state_struct.current_ep_square = ep_square;
    state_struct.current_castle_ability_bits = castle_ability_bits;
    state_struct.current_hash_key = hash_key;
    state_struct.current_fifty_move = fifty_move;
}

[[nodiscard]] BITBOARD Position::get_attacked_squares(Color color) const {
    BITBOARD attacks{};
    for (int piece = 0; piece < 6; piece++) {
        BITBOARD piece_bitboard = get_pieces(static_cast<PieceType>(piece), color);
        while (piece_bitboard) {
            Square square = poplsb(piece_bitboard);
            attacks |= get_piece_attacks(static_cast<Piece>(piece + COLOR_OFFSET * color), square,
                                         all_pieces & (~from_square(square)));
        }
    }

    attacks &= ~(color == side ? our_pieces : opp_pieces);
    return attacks;
}

Square Position::get_king_pos(Color color) const {
    return lsb(get_pieces(KING, color));
}

bool Position::is_attacked(Square square, Color color) const {
    BITBOARD occupancy = all_pieces & (~from_square(square));

    // Treat square like a pawn
    BITBOARD pawn_attacks = color == WHITE ? WHITE_PAWN_ATTACKS[square] : BLACK_PAWN_ATTACKS[square];
    if (pawn_attacks & get_pieces(PAWN, ~color)) return true;

    // Treat square like a knight
    BITBOARD knight_attacks = KNIGHT_ATTACKS[square];
    if (knight_attacks & get_pieces(KNIGHT, ~color)) return true;

    // Treat square like a bishop
    BITBOARD bishop_attacks = get_bishop_attacks(square, occupancy);
    if (bishop_attacks & (get_pieces(BISHOP, ~color) | get_pieces(QUEEN, ~color))) return true;

    // Treat square like a rook
    BITBOARD rook_attacks = get_rook_attacks(square, occupancy);
    if (rook_attacks & (get_pieces(ROOK, ~color) | get_pieces(QUEEN, ~color))) return true;

    // Treat square like a king
    BITBOARD king_attacks = KING_ATTACKS[square];
    if (king_attacks & (get_pieces(KING, ~color))) return true;

    return false;
}

uint32_t Position::get_non_pawn_material_count() const {
    return popcount(all_pieces ^
                    (get_pieces(PAWN, WHITE) | get_pieces(PAWN, BLACK) | get_pieces(KING, WHITE) | get_pieces(KING, BLACK)));
}

void Position::remove_piece(Piece piece, Square square) {
    pieces[piece] &= ~(1ULL << square);
    board[square] = EMPTY;
}

void Position::place_piece(Piece piece, Square square) {
    pieces[piece] |= (1ULL << square);
    board[square] = piece;
}

void Position::compute_hash_key() {
    hash_key = 0;

    for (int piece = 0; piece < static_cast<int>(EMPTY); piece++) {
        BITBOARD piece_bitboard = get_pieces(static_cast<Piece>(piece));
        while (piece_bitboard) {
            Square square = poplsb(piece_bitboard);
            hash_key ^= ZobristHashKeys.piece_hash_keys[piece][square];
        }
    }

    if (ep_square != NO_SQUARE) hash_key ^= ZobristHashKeys.ep_hash_keys[ep_square];

    hash_key ^= ZobristHashKeys.castle_hash_keys[castle_ability_bits];

    if (side) hash_key ^= ZobristHashKeys.side_hash_key;
}

PLY_TYPE Position::set_fen(const std::string& fen_string) {

    std::string reduced_fen_string = std::regex_replace(fen_string, std::regex("^ +| +$|( ) +"), "$1");
    std::vector<std::string> fen_tokens = split(reduced_fen_string, ' ');

    if (fen_tokens.size() < 4) {
        throw std::invalid_argument("Fen is incorrect");
    }

    const std::string position = fen_tokens[0];
    const std::string player = fen_tokens[1];
    const std::string castling = fen_tokens[2];
    const std::string en_passant = fen_tokens[3];

    const std::string half_move_clock = fen_tokens.size() >= 5 ? fen_tokens[4] : "0";
    const std::string full_move_counter = fen_tokens.size() >= 6 ? fen_tokens[5] : "1";

    side = (player == "w") ? WHITE : BLACK;

    for (int piece = WHITE_PAWN; piece < static_cast<int>(EMPTY); piece++) {
        pieces[piece] = 0ULL;
    }

    for (auto & square : board) {
        square = EMPTY;
    }

    auto pos = static_cast<Square>(56);

    // Parsing the main 8x8 board part while adding appropriate padding
    for (char c : position) {
        if (c == '/' ) {
            pos = static_cast<Square>(pos - 16);
        } else if (std::isdigit(c)) {

            for (int empty_amt = 0; empty_amt < c - '0'; empty_amt++) {
                board[pos] = EMPTY;
                pos = static_cast<Square>(pos + 1);
            }

        }
        else if (std::isalpha(c)) {

            Piece piece = piece_to_num(c);
            place_piece(piece, pos);

            pos = static_cast<Square>(pos + 1);

        }
    }

    castle_ability_bits = 0;
    starting_rook_pos[WHITE][0] = h1;
    starting_rook_pos[WHITE][1] = a1;
    starting_rook_pos[BLACK][0] = h8;
    starting_rook_pos[BLACK][1] = a8;

    for (char c : castling) {
        if (fischer_random_chess) {

            Color castle_flag_color = isupper(c) ? WHITE : BLACK;
            char castle_flag = static_cast<char>(tolower(static_cast<char>(c)));

            if (castle_flag == 'k') {
                starting_rook_pos[castle_flag_color][0] = msb(get_pieces(ROOK, castle_flag_color));
                castle_ability_bits |= castle_flag_color == WHITE ? 1 : 4;
            }

            else if (castle_flag == 'q') {
                starting_rook_pos[castle_flag_color][1] = lsb(get_pieces(ROOK, castle_flag_color));
                castle_ability_bits |= castle_flag_color == WHITE ? 2 : 8;
            }

            else {
                int rook_file = castle_flag - 'a';
                int king_file = static_cast<int>(file_of(get_king_pos(castle_flag_color)));

                if (rook_file > king_file) {
                    starting_rook_pos[castle_flag_color][0] = static_cast<Square>(rook_file + 56 * castle_flag_color);
                    castle_ability_bits |= (castle_flag_color == WHITE) ? 1 : 4;
                }
                else {
                    starting_rook_pos[castle_flag_color][1] = static_cast<Square>(rook_file + 56 * castle_flag_color);
                    castle_ability_bits |= (castle_flag_color == WHITE) ? 2 : 8;
                }
            }
        }

        else {
            if (c == 'K') castle_ability_bits |= 1;
            else if (c == 'Q') castle_ability_bits |= 2;
            else if (c == 'k') castle_ability_bits |= 4;
            else if (c == 'q') castle_ability_bits |= 8;
        }
    }

    if (en_passant.size() > 1) {
        auto square = static_cast<Square>((en_passant[1] - '1') * 8 + en_passant[0] - 'a');
        ep_square = square;
    }
    else {
        ep_square = NO_SQUARE;
    }

    our_pieces = get_our_pieces();
    opp_pieces = get_opp_pieces();
    all_pieces = get_all_pieces();
    empty_squares = get_empty_squares();

    compute_hash_key();

    nnue_state.reset_nnue(*this);

    return static_cast<PLY_TYPE>(std::stoi(half_move_clock));
}

std::string Position::get_fen(PLY_TYPE fifty_move) {
    std::string fen;

    int empty = 0;
    for (int i = 0; i < 64; i++) {
        int square = i ^ 56;
        if (i != 0 && i % 8 == 0) {
            if (empty) fen += std::to_string(empty);
            empty = 0;
            fen += "/";
        }

        Piece piece = board[square];
        if (piece == EMPTY) empty++;
        else {
            if (empty) fen += std::to_string(empty);
            empty = 0;

            fen += PIECE_MATCHER[piece];
        }
    }

    fen += " ";
    fen += side == WHITE ? "w" : "b";

    fen += " ";

    if (castle_ability_bits == 0) fen += "-";
    if ((castle_ability_bits & 1) == 1) fen += "K";
    if ((castle_ability_bits & 2) == 2) fen += "Q";
    if ((castle_ability_bits & 4) == 4) fen += "k";
    if ((castle_ability_bits & 8) == 8) fen += "q";

    fen += " ";
    if (ep_square == NO_SQUARE) fen += "-";
    else {
        fen += char(ep_square % 8 + 'a');
        fen += char(ep_square / 8 + '1');
    }

    fen += " ";
    fen += std::to_string(fifty_move);

    return fen;
}

void Position::set_frc_side(Color color, int index) {

    // Based on the Scharnagl Numbering Scheme:
    // https://en.wikipedia.org/wiki/Fischer_random_chess_numbering_scheme

    std::vector<int> empty_back_rank;

    for (int i = 0; i < 8; i++) empty_back_rank.push_back(i ^ 56 * color);

    // Bishops
    Square bishop_1 = static_cast<Square>(bishop_ordering_1[color][index % 4]);
    index /= 4;

    Square bishop_2 = static_cast<Square>(bishop_ordering_2[color][index % 4]);
    index /= 4;

    place_piece(get_piece(BISHOP, color), bishop_1);
    place_piece(get_piece(BISHOP, color), bishop_2);

    empty_back_rank.erase(std::remove(empty_back_rank.begin(), empty_back_rank.end(), bishop_1));
    empty_back_rank.erase(std::remove(empty_back_rank.begin(), empty_back_rank.end(), bishop_2));

    // Queen
    place_piece(get_piece(QUEEN, color), static_cast<Square>(empty_back_rank[index % 6]));
    empty_back_rank.erase(empty_back_rank.begin() + (index % 6));

    index /= 6;

    // Knights
    for (int i = 4; i >= 1; i--) {
        if (index < i) {
            place_piece(get_piece(KNIGHT, color), static_cast<Square>(empty_back_rank[4 - i]));
            empty_back_rank.erase(empty_back_rank.begin() + (4 - i));

            place_piece(get_piece(KNIGHT, color), static_cast<Square>(empty_back_rank[index]));
            empty_back_rank.erase(empty_back_rank.begin() + (index));

            break;
        }
        index -= i;
    }

    place_piece(get_piece(ROOK, color), static_cast<Square>(empty_back_rank[0]));
    place_piece(get_piece(KING, color), static_cast<Square>(empty_back_rank[1]));
    place_piece(get_piece(ROOK, color), static_cast<Square>(empty_back_rank[2]));

}

void Position::set_dfrc(int index) {

    for (int piece = WHITE_PAWN; piece < static_cast<int>(EMPTY); piece++) {
        if (piece == WHITE_PAWN || piece == BLACK_PAWN) continue;
        pieces[piece] = 0ULL;
    }

    for (auto & square : board) {
        if (square == WHITE_PAWN || square == BLACK_PAWN) continue;
        square = EMPTY;
    }

    set_frc_side(WHITE, index % 960);
    set_frc_side(BLACK, index / 960);

    compute_hash_key();
    nnue_state.reset_nnue(*this);
}

std::ostream& operator << (std::ostream& os, const Position& position) {
    std::string new_board;

    auto pos = static_cast<Square>(56);
    for (int i = 0; i < 64; i++) {
        if (i != 0 && i % 8 == 0) {
            new_board += '\n';
            pos = static_cast<Square>(pos - 16);
        }

        Piece piece = position.board[pos];
        pos = static_cast<Square>(pos + 1);

        if (piece == EMPTY) {
            new_board += ". ";
            continue;
        }

        //assert((pieces[piece] & (1ULL << MAILBOX_TO_STANDARD[pos]) >> MAILBOX_TO_STANDARD[pos]) == 1);

        new_board += PIECE_MATCHER[piece];
        new_board += ' ';

    }

    os << new_board << std::endl << std::endl;
    os << "side: " << position.side << " ep: " << position.ep_square << " castle: " << position.castle_ability_bits
       << " hash: " << position.hash_key << std::endl << std::endl;

    /*
    for (int piece = WHITE_PAWN; piece < EMPTY; piece++) {
        os << "Piece: " << piece << " bitboard: \n";
        print_bitboard(position.pieces[piece]);
    }
    */

    return os;
}

void Position::get_pawn_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const {
    BITBOARD pawns = get_pieces(PAWN, side);
    BITBOARD pawn_forward_squares = side == WHITE ? shift<NORTH>(pawns) : shift<SOUTH>(pawns);
    pawn_forward_squares &= ~(MASK_RANK[RANK_1] | MASK_RANK[RANK_8]);

    BITBOARD west_attacks = shift<WEST>(pawn_forward_squares) & opp_pieces;
    BITBOARD east_attacks = shift<EAST>(pawn_forward_squares) & opp_pieces;

    Direction down = side == WHITE ? SOUTH : NORTH;

    while (west_attacks) {
        Square new_square = poplsb(west_attacks);
        current_scored_moves.push_back({
                                               Move(new_square + down + EAST, new_square),
                                               0
                                       });
    }

    while (east_attacks) {
        Square new_square = poplsb(east_attacks);
        current_scored_moves.push_back({
                                               Move(new_square + down + WEST, new_square),
                                               0
                                       });
    }
}

void Position::get_pawn_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const {

    BITBOARD pawns = get_pieces(PAWN, side);
    BITBOARD pawn_forward_squares = side == WHITE ? shift<NORTH>(pawns) : shift<SOUTH>(pawns);

    BITBOARD west_attacks = shift<WEST>(pawn_forward_squares) & opp_pieces;
    BITBOARD east_attacks = shift<EAST>(pawn_forward_squares) & opp_pieces;

    Direction down = side == WHITE ? SOUTH : NORTH;

    while (west_attacks) {
        Square new_square = poplsb(west_attacks);

        bool promotion = (side == WHITE && new_square >= 56) || (side == BLACK && new_square <= 7);

        if (promotion) {
            for (PromotionType promotionType : {PROMOTION_KNIGHT, PROMOTION_BISHOP, PROMOTION_ROOK, PROMOTION_QUEEN}) {
                current_scored_moves.push_back({
                                                       Move(new_square + down + EAST, new_square, MOVE_TYPE_PROMOTION, promotionType),
                                                       0
                                               });
            }

            continue;
        }

        current_scored_moves.push_back({
                                               Move(new_square + down + EAST, new_square),
                                               0
                                       });
    }

    while (east_attacks) {
        Square new_square = poplsb(east_attacks);

        bool promotion = (side == WHITE && new_square >= 56) || (side == BLACK && new_square <= 7);

        if (promotion) {
            for (PromotionType promotionType : {PROMOTION_KNIGHT, PROMOTION_BISHOP, PROMOTION_ROOK, PROMOTION_QUEEN}) {
                current_scored_moves.push_back({
                                                       Move(new_square + down + WEST, new_square, MOVE_TYPE_PROMOTION, promotionType),
                                                       0
                                               });
            }

            continue;
        }

        current_scored_moves.push_back({
                                               Move(new_square + down + WEST, new_square),
                                               0
                                       });
    }

    // En Passant Code
    if (ep_square != NO_SQUARE) {
        BITBOARD ep_pawns = (side == WHITE ? BLACK_PAWN_ATTACKS[ep_square] : WHITE_PAWN_ATTACKS[ep_square]) & pawns;

        while (ep_pawns) {
            Square square = poplsb(ep_pawns);
            current_scored_moves.push_back({
                                                   Move(square, ep_square, MOVE_TYPE_EP),
                                                   0
                                           });
        }
    }

    // Pawn Pushes
    BITBOARD single_pushes = pawn_forward_squares & empty_squares;
    BITBOARD double_pushes = (side == WHITE ? shift<NORTH>(single_pushes) & MASK_RANK[RANK_4]
                                            : shift<SOUTH>(single_pushes) & MASK_RANK[RANK_5]) & empty_squares;

    while (single_pushes) {
        Square new_square = poplsb(single_pushes);
        bool promotion = (side == WHITE && new_square >= 56) || (side == BLACK && new_square <= 7);

        // Single Push Promotions
        if (promotion) {
            for (PromotionType promotionType: {PROMOTION_KNIGHT, PROMOTION_BISHOP, PROMOTION_ROOK, PROMOTION_QUEEN}) {
                current_scored_moves.push_back({
                                                       Move(new_square + down, new_square, MOVE_TYPE_PROMOTION,
                                                            promotionType),
                                                       0
                                               });
            }
            continue;
        }

        // Single Pushes
        current_scored_moves.push_back({
                                               Move(new_square + down, new_square),
                                               0
                                       });
    }

    while (double_pushes) {
        Square new_square = poplsb(double_pushes);
        current_scored_moves.push_back({
                                               Move(new_square + down + down, new_square),
                                               0
                                       });

    }

}

void Position::get_knight_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const {
    BITBOARD knights = get_pieces(KNIGHT, side);

    while (knights) {
        Square square = poplsb(knights);

        BITBOARD bitboard = KNIGHT_ATTACKS[square] & opp_pieces;
        while (bitboard) {
            Square new_square = poplsb(bitboard);
            current_scored_moves.push_back({
                                                   Move(square, new_square),
                                                   0
                                           });
        }
    }
}

void Position::get_knight_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const {
    BITBOARD knights = get_pieces(KNIGHT, side);

    while (knights) {
        Square square = poplsb(knights);

        BITBOARD bitboard = KNIGHT_ATTACKS[square] & (~our_pieces);
        while (bitboard) {
            Square new_square = poplsb(bitboard);
            current_scored_moves.push_back({
                                                   Move(square, new_square),
                                                   0
                                           });
        }
    }
}

void Position::get_bishop_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const {
    BITBOARD bishops = get_pieces(BISHOP, side);

    while (bishops) {
        Square square = poplsb(bishops);

        BITBOARD bishop_captures = get_bishop_attacks(square, all_pieces) & opp_pieces;

        while (bishop_captures) {
            Square new_square = poplsb(bishop_captures);
            current_scored_moves.push_back({
                                                   Move(square, new_square),
                                                   0
                                           });
        }
    }
}

void Position::get_bishop_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const {
    BITBOARD bishops = get_pieces(BISHOP, side);

    while (bishops) {
        Square square = poplsb(bishops);

        BITBOARD bishop_attacks = get_bishop_attacks(square, all_pieces);
        BITBOARD bishop_moves = bishop_attacks & (~our_pieces);

        while (bishop_moves) {
            Square new_square = poplsb(bishop_moves);
            current_scored_moves.push_back({
                                                   Move(square, new_square),
                                                   0
                                           });
        }
    }
}

void Position::get_rook_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const {
    BITBOARD rooks = get_pieces(ROOK, side);

    while (rooks) {
        Square square = poplsb(rooks);

        BITBOARD rook_attacks = get_rook_attacks(square, all_pieces) & opp_pieces;

        while (rook_attacks) {
            Square new_square = poplsb(rook_attacks);
            current_scored_moves.push_back({
                                                   Move(square, new_square),
                                                   0
                                           });
        }
    }
}

void Position::get_rook_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const {
    BITBOARD rooks = get_pieces(ROOK, side);
    Square king_pos = get_king_pos(side);

    while (rooks) {
        Square square = poplsb(rooks);

        BITBOARD rook_attacks = get_rook_attacks(square, all_pieces);
        BITBOARD rook_moves = rook_attacks & (~our_pieces);

        while (rook_moves) {
            Square new_square = poplsb(rook_moves);
            current_scored_moves.push_back({
                                                   Move(square, new_square),
                                                   0
                                           });
        }

        // -- Generate Castling moves --
        if (!(rook_attacks & get_pieces(KING, side))) continue;  // Guard clause

        Square starting_rook_pos_k = starting_rook_pos[side][0];
        Square starting_rook_pos_q = starting_rook_pos[side][1];

        Square target_pos_k = side == WHITE ? g1 : g8;
        Square target_pos_q = side == WHITE ? c1 : c8;

        Square important_pos_k = target_pos_k + WEST;  // F1 square for FRC (the square the rook will go to)
        Square important_pos_q = target_pos_q + EAST;  // D1 square for FRC (the square the rook will go to)

        // King side Castling

        if (((side == WHITE && (castle_ability_bits & 1) == 1) || (side == BLACK && (castle_ability_bits & 4) == 4))
            && square == starting_rook_pos_k) {
            if (fischer_random_chess) {
                // The rook is to the right of the F1 square
                if (king_pos > important_pos_k) {
                    // Ensure that the rook can go to the F1 square
                    if (board[important_pos_k] != EMPTY) continue;
                }

                    // The rook is to the left of the F1 square
                else if (king_pos < important_pos_k) {
                    // Ensure that all the squares between the rook's square,
                    // and its current square are empty
                    bool flag = false;
                    for (int temp_square = target_pos_k; temp_square > static_cast<int>(square); temp_square--) {
                        if (board[temp_square] != EMPTY) {
                            flag = true;
                            break;
                        }
                    }

                    if (flag) continue;
                }
            }
            current_scored_moves.push_back({
                                                   Move(king_pos, target_pos_k, MOVE_TYPE_CASTLE),
                                                   0
                                           });
        }

            // Queen side Castling
        else if (((side == WHITE && (castle_ability_bits & 2) == 2) || (side == BLACK && (castle_ability_bits & 8) == 8))
                 && square == starting_rook_pos_q) {

            // FRC Castling Cases
            if (fischer_random_chess) {

                // The rook is to the left of the D1 square
                if (king_pos < important_pos_q) {
                    // Guard certain cases
                    if (board[target_pos_q] != EMPTY && board[target_pos_q] != WHITE_KING) continue;
                    if (board[important_pos_q] != EMPTY) continue;
                }

                    // The rook is to the right of the D1 square
                else if (king_pos > important_pos_q){
                    // Ensure that all the squares between the rook's square,
                    // and its current square are empty
                    bool flag = false;
                    for (int temp_square = target_pos_q; temp_square < static_cast<int>(square); temp_square++) {
                        if (board[temp_square] != EMPTY) {
                            flag = true;
                            break;
                        }
                    }

                    if (flag) continue;
                }
            }

            current_scored_moves.push_back({
                                                   Move(king_pos, target_pos_q, MOVE_TYPE_CASTLE),
                                                   0
                                           });
        }
    }
}

void Position::get_queen_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const {
    BITBOARD queens = get_pieces(QUEEN, side);
    while (queens) {
        Square square = poplsb(queens);
        BITBOARD queen_captures = get_queen_attacks(square, all_pieces) & opp_pieces;

        while (queen_captures) {
            Square new_square = poplsb(queen_captures);
            current_scored_moves.push_back({
                                                   Move(square, new_square),
                                                   0
                                           });
        }
    }
}

void Position::get_queen_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const {
    BITBOARD queens = get_pieces(QUEEN, side);
    while (queens) {
        Square square = poplsb(queens);

        BITBOARD queen_attacks = get_queen_attacks(square, all_pieces);
        BITBOARD queen_moves = queen_attacks & (~our_pieces);

        while (queen_moves) {
            Square new_square = poplsb(queen_moves);
            current_scored_moves.push_back({
                                                   Move(square, new_square),
                                                   0
                                           });
        }
    }
}

void Position::get_king_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const {
    Square square = get_king_pos(side);
    BITBOARD king_captures = KING_ATTACKS[square] & opp_pieces;
    while (king_captures) {
        Square new_square = poplsb(king_captures);
        current_scored_moves.push_back({
                                               Move(square, new_square),
                                               0
                                       });
    }
}

void Position::get_king_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const {
    Square square = get_king_pos(side);
    BITBOARD king_moves = KING_ATTACKS[square] & (~our_pieces);
    while (king_moves) {
        Square new_square = poplsb(king_moves);
        current_scored_moves.push_back({
                                               Move(square, new_square),
                                               0
                                       });
    }
}

void Position::get_pseudo_legal_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const {
    current_scored_moves.clear();
    get_pawn_captures(current_scored_moves);
    get_knight_captures(current_scored_moves);
    get_bishop_captures(current_scored_moves);
    get_rook_captures(current_scored_moves);
    get_queen_captures(current_scored_moves);
    get_king_captures(current_scored_moves);
}

void Position::get_pseudo_legal_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const {
    current_scored_moves.clear();
    get_pawn_moves(current_scored_moves);
    get_knight_moves(current_scored_moves);
    get_bishop_moves(current_scored_moves);
    get_rook_moves(current_scored_moves);
    get_queen_moves(current_scored_moves);
    get_king_moves(current_scored_moves);
}

bool Position::make_move(Move move, State_Struct& state_struct, PLY_TYPE& fifty_move) {

    Square castled_pos[2] = {NO_SQUARE, NO_SQUARE};

    // Get move info
    Square origin_square = move.origin();
    Square target_square = move.target();
    Piece selected = board[origin_square];
    Piece occupied = board[target_square];
    MoveType move_type = move.type();

    state_struct.move = InformativeMove(move, selected, occupied);

    bool legal = true;

    fifty_move++;

    nnue_state.push();

    // Handle captures
    if (move.is_capture(*this)) {
        remove_piece(occupied, target_square);
        nnue_state.update_feature<false>(occupied, target_square);
        hash_key ^= ZobristHashKeys.piece_hash_keys[occupied][target_square];
        fifty_move = 0;
    }

    // -- Make the actual pseudo-legal move --
    if (move_type == MOVE_TYPE_NORMAL) {
        place_piece(selected, target_square);
        nnue_state.update_feature<true>(selected, target_square);
        hash_key ^= ZobristHashKeys.piece_hash_keys[selected][target_square];
    }

    else if (move_type == MOVE_TYPE_EP) {
        place_piece(selected, target_square);
        nnue_state.update_feature<true>(selected, target_square);
        hash_key ^= ZobristHashKeys.piece_hash_keys[selected][target_square];

        // Find and remove the captured EP pawn
        auto captured_square = static_cast<Square>(target_square + static_cast<Square>(side == WHITE ? SOUTH : NORTH));
        nnue_state.update_feature<false>(board[captured_square], captured_square);
        hash_key ^= ZobristHashKeys.piece_hash_keys[board[captured_square]][captured_square];
        remove_piece(board[captured_square], captured_square);
    }

    else if (move_type == MOVE_TYPE_CASTLE) {
        legal = !is_attacked(get_king_pos(side), side);

        // Get rook locations
        if (target_square == c1 || target_square == c8) {   // Queen side
            castled_pos[0] = starting_rook_pos[side][1];                // Rook origin square
            castled_pos[1] = static_cast<Square>(target_square + 1);    // Rook target square
        } else {                                            // King side
            castled_pos[0] = starting_rook_pos[side][0];                // Rook origin square
            castled_pos[1] = static_cast<Square>(target_square - 1);    // Rook target square
        }

        // Move the Rook
        nnue_state.update_feature<false>(board[castled_pos[0]], castled_pos[0]);
        nnue_state.update_feature<true>(board[castled_pos[0]], castled_pos[1]);
        hash_key ^= ZobristHashKeys.piece_hash_keys[board[castled_pos[0]]][castled_pos[0]];
        hash_key ^= ZobristHashKeys.piece_hash_keys[board[castled_pos[0]]][castled_pos[1]];
        remove_piece(board[castled_pos[0]], castled_pos[0]);
        place_piece(get_piece(ROOK, side), castled_pos[1]);

        // Move the king now (after moving the rook due to FRC edge-cases where the king and rook swap places)
        place_piece(selected, target_square);
        nnue_state.update_feature<true>(selected, target_square);
        hash_key ^= ZobristHashKeys.piece_hash_keys[selected][target_square];
    }

    else if (move_type == MOVE_TYPE_PROMOTION) {
        auto promotion_piece = static_cast<Piece>(move.promotion_type() + 1 + side * COLOR_OFFSET);
        place_piece(promotion_piece, target_square);
        nnue_state.update_feature<true>(promotion_piece, target_square);
        hash_key ^= ZobristHashKeys.piece_hash_keys[promotion_piece][target_square];
    }

    // Remove the piece from the source square except for some FRC edge cases
    // (If the king goes is castling to the same location then no need to change anything)
    if (target_square != origin_square) {

        // The rook and king have swapped in FRC, and the rook has been placed in this square; however,
        // the king in the bitboard hasn't been removed yet and must be removed.
        if (castled_pos[1] == origin_square) pieces[selected] &= ~(1ULL << origin_square);
        else remove_piece(selected, origin_square);

        nnue_state.update_feature<false>(selected, origin_square);
        hash_key ^= ZobristHashKeys.piece_hash_keys[selected][origin_square];
    }

    // -- Legal move checking --
    // Return False if we are in check after our move or castling isn't legal.
    if (!legal) return false;

    // Update information for getting attacked squares
    our_pieces = get_our_pieces();
    opp_pieces = get_opp_pieces();
    all_pieces = get_all_pieces();
    empty_squares = get_empty_squares();

    // Continue legal move checking
    if (is_attacked(get_king_pos(side), side)) return false;
    if (castled_pos[0] != NO_SQUARE) {
        // We need to check all the squares in between the king's destination square and original square, excluding
        // the original square since we already checked that earlier.
        if (target_square == c1 || target_square == c8) {  // Queen side castling
            for (int temp_pos = static_cast<int>(origin_square) - 1; temp_pos > static_cast<int>(target_square); temp_pos--) {
                if (is_attacked(static_cast<Square>(temp_pos), side)) return false;
            }
        } else {                                           // King side castling
            for (int temp_pos = static_cast<int>(origin_square) + 1; temp_pos < static_cast<int>(target_square); temp_pos++) {
                if (is_attacked(static_cast<Square>(temp_pos), side)) return false;
            }
        }
    }

    // --- The move is legal ---
    if (selected == WHITE_PAWN || selected == BLACK_PAWN) fifty_move = 0;

    // -- En Passant Resetting --
    // Double Pawn Push
    if ((selected == WHITE_PAWN || selected == BLACK_PAWN) && abs(static_cast<int>(target_square - origin_square)) == NORTH_NORTH) {
        // Reset the previously hashed ep square if it exists
        if (ep_square != NO_SQUARE) hash_key ^= ZobristHashKeys.ep_hash_keys[ep_square];

        ep_square = static_cast<Square>(target_square + static_cast<Square>(side == WHITE ? SOUTH : NORTH));
        hash_key ^= ZobristHashKeys.ep_hash_keys[ep_square];  // Set new EP hash
    }

        // If it is not a double pawn push then we must reset it if there was a previous EP
    else if (ep_square != NO_SQUARE) {
        hash_key ^= ZobristHashKeys.ep_hash_keys[ep_square];
        ep_square = NO_SQUARE;
    }

    // -- Update Castling Rights --
    // Reset the castling rights first
    hash_key ^= ZobristHashKeys.castle_hash_keys[castle_ability_bits];

    // King moves
    if (selected == WHITE_KING) {
        castle_ability_bits &= ~(1 << 0);
        castle_ability_bits &= ~(1 << 1);
    } else if (selected == BLACK_KING) {
        castle_ability_bits &= ~(1 << 2);
        castle_ability_bits &= ~(1 << 3);
    }

    // Rook moves or is captured
    if (origin_square == starting_rook_pos[WHITE][0] ||
        target_square == starting_rook_pos[WHITE][0]) castle_ability_bits &= ~(1 << 0);
    else if (origin_square == starting_rook_pos[WHITE][1] ||
             target_square == starting_rook_pos[WHITE][1]) castle_ability_bits &= ~(1 << 1);
    else if (origin_square == starting_rook_pos[BLACK][0] ||
             target_square == starting_rook_pos[BLACK][0]) castle_ability_bits &= ~(1 << 2);
    else if (origin_square == starting_rook_pos[BLACK][1] ||
             target_square == starting_rook_pos[BLACK][1]) castle_ability_bits &= ~(1 << 3);

    // Hash it back
    hash_key ^= ZobristHashKeys.castle_hash_keys[castle_ability_bits];

    hash_key ^= ZobristHashKeys.side_hash_key;
    side = ~side;

    BITBOARD temp_our_pieces = our_pieces;
    our_pieces = opp_pieces;
    opp_pieces = temp_our_pieces;

    return true;
}

void Position::undo_move(Move move, State_Struct& state_struct, PLY_TYPE& fifty_move) {

    Square castled_pos[2] = {NO_SQUARE, NO_SQUARE};

    // Get move info
    Square origin_square = move.origin();
    Square target_square = move.target();
    Piece selected = state_struct.move.selected();
    Piece occupied = state_struct.move.occupied();
    MoveType move_type = move.type();

    nnue_state.pop();

    // Reset certain information
    side = static_cast<Color>(selected >= BLACK_PAWN);
    hash_key = state_struct.current_hash_key;
    fifty_move = state_struct.current_fifty_move;
    ep_square = state_struct.current_ep_square;
    castle_ability_bits = state_struct.current_castle_ability_bits;

    if (move_type == MOVE_TYPE_EP) {
        // Find and replace the captured EP pawn
        auto captured_square = static_cast<Square>(target_square + static_cast<Square>(side == WHITE ? SOUTH : NORTH));
        place_piece(side == WHITE ? BLACK_PAWN : WHITE_PAWN, captured_square);
    }

    else if (move_type == MOVE_TYPE_CASTLE) {
        // Get rook locations
        if (target_square == c1 || target_square == c8) {   // Queen side
            castled_pos[0] = starting_rook_pos[side][1];                // Rook origin square
            castled_pos[1] = static_cast<Square>(target_square + 1);    // Rook target square
        } else {                                            // King side
            castled_pos[0] = starting_rook_pos[side][0];                // Rook origin square
            castled_pos[1] = static_cast<Square>(target_square - 1);    // Rook target square
        }

        // Move the Rook back
        remove_piece(board[castled_pos[1]], castled_pos[1]);
        place_piece(get_piece(ROOK, side), castled_pos[0]);
    }

    // Set the occupied piece back except in FRC edge cases
    if (castled_pos[0] == target_square) {
        // The rook and king have swapped in FRC, and the rook has been placed in this square; however,
        // the king in the bitboard hasn't been removed yet and must be removed.
        pieces[selected] &= ~(1ULL << target_square);
    } else {
        remove_piece(board[target_square], target_square);
        if (occupied < EMPTY) place_piece(occupied, target_square);
    }

    place_piece(selected, origin_square);

    our_pieces = get_our_pieces();
    opp_pieces = get_opp_pieces();
    all_pieces = get_all_pieces();
    empty_squares = get_empty_squares();
}

void Position::make_null_move(State_Struct& state_struct, PLY_TYPE& fifty_move) {
    side = ~side;
    hash_key ^= ZobristHashKeys.side_hash_key;
    state_struct.move = NO_INFORMATIVE_MOVE;

    if (ep_square != NO_SQUARE) {
        hash_key ^= ZobristHashKeys.ep_hash_keys[ep_square];
        ep_square = NO_SQUARE;
    }

    fifty_move = 0;

    BITBOARD temp_our_pieces = our_pieces;
    our_pieces = opp_pieces;
    opp_pieces = temp_our_pieces;
}

void Position::undo_null_move(State_Struct& state_struct, PLY_TYPE& fifty_move) {
    side = ~side;
    ep_square = state_struct.current_ep_square;
    hash_key = state_struct.current_hash_key;
    fifty_move = state_struct.current_fifty_move;

    BITBOARD temp_our_pieces = our_pieces;
    our_pieces = opp_pieces;
    opp_pieces = temp_our_pieces;
}