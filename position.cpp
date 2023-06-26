//
// Created by Alex Tian on 8/24/2022.
//

#include <stdexcept>
#include <iostream>
#include <bitset>
#include "position.h"
#include "useful.h"
#include "bitboard.h"
#include "tables.h"

BITBOARD Position::get_pieces(Piece piece) {
    return pieces[piece];
}

BITBOARD Position::get_pieces(PieceType piece, Color color) {
    return pieces[piece + color * 6];
}

[[nodiscard]] BITBOARD Position::get_our_pieces() {
    return get_pieces(PAWN, side) |
           get_pieces(KNIGHT, side) |
           get_pieces(BISHOP, side) |
           get_pieces(ROOK, side) |
           get_pieces(QUEEN, side) |
           get_pieces(KING, side);
}

[[nodiscard]] BITBOARD Position::get_opp_pieces() {
    return get_pieces(PAWN, static_cast<Color>(~side)) |
           get_pieces(KNIGHT, static_cast<Color>(~side)) |
           get_pieces(BISHOP, static_cast<Color>(~side)) |
           get_pieces(ROOK, static_cast<Color>(~side)) |
           get_pieces(QUEEN, static_cast<Color>(~side)) |
           get_pieces(KING, static_cast<Color>(~side));
}

[[nodiscard]] BITBOARD Position::get_all_pieces() const {
    return our_pieces | opp_pieces;
}

[[nodiscard]] BITBOARD Position::get_empty_squares() const {
    return ~all_pieces;
}

Square Position::get_king_pos(Color color) {
    return lsb(get_pieces(KING, color));
}

void Position::remove_piece(Piece piece, Square square) {
    pieces[piece] &= ~(1ULL << square);
    board[square] = EMPTY;
}

void Position::place_piece(Piece piece, Square square) {
    pieces[piece] |= (1ULL << square);
    board[square] = piece;
}

void Position::set_fen(const std::string& fen_string) {

    std::vector<std::string> fen_tokens = split(fen_string, ' ');

    if (fen_tokens.size() < 4) {
        throw std::invalid_argument( "Fen is incorrect" );
    }

    const std::string position = fen_tokens[0];
    const std::string player = fen_tokens[1];
    const std::string castling = fen_tokens[2];
    const std::string en_passant = fen_tokens[3];

    const std::string half_move_clock = fen_tokens.size() > 4 ? fen_tokens[4] : "0";
    const std::string full_move_counter = fen_tokens.size() > 4 ? fen_tokens[5] : "1";

    side = (player == "w") ? WHITE : BLACK;

    for (int piece = WHITE_PAWN; piece != EMPTY; piece++) {
        pieces[piece] = 0ULL;
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
    for (char c : castling) {

        if (c == 'K') castle_ability_bits |= 1;
        else if (c == 'Q') castle_ability_bits |= 2;
        else if (c == 'k') castle_ability_bits |= 4;
        else if (c == 'q') castle_ability_bits |= 8;

    }

    if (en_passant.size() > 1) {
        auto square = static_cast<Square>((8 - (en_passant[1] - '0')) * 8 + en_passant[0] - 'a');
        ep_square = square;
    }
    else {
        ep_square = NO_SQUARE;
    }
}

std::ostream& operator << (std::ostream& os, const Position& p) {
    std::string new_board;

    auto pos = static_cast<Square>(56);
    for (int i = 0; i < 64; i++) {
        if (i != 0 && i % 8 == 0) {
            new_board += '\n';
            pos = static_cast<Square>(pos - 16);
        }

        Piece piece = p.board[pos];
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
    os << "side: " << p.side << " ep: " << p.ep_square << " castle: " << p.castle_ability_bits
       << " hash: " << p.hash_key << std::endl << std::endl;

    for (int piece = WHITE_PAWN; piece < EMPTY; piece++) {
        os << "Piece: " << piece << " bitboard: \n";
        print_bitboard(p.pieces[piece]);
    }
    return os;
}

bool Position::get_is_capture(Move move) {
    return board[move.to()] < EMPTY;
}

void Position::get_pawn_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const {
    BITBOARD bitboard = (side == WHITE ? WHITE_PAWN_ATTACKS[square] : BLACK_PAWN_ATTACKS[square]) & opp_pieces;
    while (bitboard) {
        Square new_square = poplsb(bitboard);
        current_scored_moves.push_back({
            Move(square, new_square),
            0
        });
    }
}

void Position::get_pawn_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) {
    bool promotion = (side == WHITE && square >= 48) || (side == BLACK && square <= 15);

    // Get Attacks with consideration of promotions and en-passant
    BITBOARD attack_bitboard = (side == WHITE ? WHITE_PAWN_ATTACKS[square] : BLACK_PAWN_ATTACKS[square]) & opp_pieces;
    while (attack_bitboard) {
        Square new_square = poplsb(attack_bitboard);
        if (promotion) {
            for (PromotionType promotionType : {PROMOTION_KNIGHT, PROMOTION_BISHOP, PROMOTION_ROOK, PROMOTION_QUEEN}) {
                current_scored_moves.push_back({
                        Move(square, new_square, MOVE_TYPE_PROMOTION, promotionType),
                        0
                });
            }

            continue;
        }

        current_scored_moves.push_back({
            Move(square, new_square),
            0
        });

    }

    // En Passant Code
    BITBOARD ep_bitboard = (side == WHITE ? WHITE_PAWN_ATTACKS[square] : BLACK_PAWN_ATTACKS[square]) &
            from_square(ep_square);

    while (ep_bitboard) {
        Square new_square = poplsb(ep_bitboard);
        current_scored_moves.push_back({
                Move(square, new_square, MOVE_TYPE_EP),
                0
        });
    }

    // Pawn Pushes
    const auto single_push_square = static_cast<Square>(square + static_cast<Square>(side == WHITE ? NORTH : SOUTH));

    if (board[single_push_square] == EMPTY) {

        // Single Push Promotions
        if (promotion) {
            for (PromotionType promotionType : {PROMOTION_KNIGHT, PROMOTION_BISHOP, PROMOTION_ROOK, PROMOTION_QUEEN}) {
                current_scored_moves.push_back({
                        Move(square, single_push_square, MOVE_TYPE_PROMOTION,
                             promotionType),
                        0
                });
            }
        }

        // Single & Double Pushes
        else {

            // Single Pushes
            current_scored_moves.push_back({
                    Move(square, single_push_square),
                    0
            });

            // Double Pushes
            const auto double_push_square = static_cast<Square>(square +
                    static_cast<Square>(side == WHITE ? NORTH_NORTH : SOUTH_SOUTH));

            bool double_push_possible = (side == WHITE && square <= 15) || (side == BLACK && square >= 48);
            if (double_push_possible && board[double_push_square] == EMPTY) {
                current_scored_moves.push_back({
                        Move(square, single_push_square),
                        0
                });
            }
        }
    }

}

void Position::get_knight_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const {
    BITBOARD bitboard = KNIGHT_ATTACKS[square] & opp_pieces;
    while (bitboard) {
        Square new_square = poplsb(bitboard);
        current_scored_moves.push_back({
                Move(square, new_square),
                0
        });
    }
}

void Position::get_knight_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const {
    BITBOARD bitboard = KNIGHT_ATTACKS[square] & (~our_pieces);
    while (bitboard) {
        Square new_square = poplsb(bitboard);
        current_scored_moves.push_back({
                Move(square, new_square),
                0
        });
    }
}

void Position::get_bishop_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const {
    BITBOARD other_pieces = all_pieces & (~from_square(square));
    BITBOARD bishop_attacks = get_bishop_attacks(square, other_pieces);
    BITBOARD bishop_moves = bishop_attacks & opp_pieces;

    while (bishop_moves) {
        Square new_square = poplsb(bishop_moves);
        current_scored_moves.push_back({
            Move(square, new_square),
            0
        });
    }
}

void Position::get_bishop_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const {
    BITBOARD other_pieces = all_pieces & (~from_square(square));
    BITBOARD bishop_attacks = get_bishop_attacks(square, other_pieces);
    BITBOARD bishop_moves = bishop_attacks & (~our_pieces);

    while (bishop_moves) {
        Square new_square = poplsb(bishop_moves);
        current_scored_moves.push_back({
            Move(square, new_square),
            0
        });
    }
}

void Position::get_rook_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const {
    BITBOARD other_pieces = all_pieces & (~from_square(square));
    BITBOARD rook_attacks = get_rook_attacks(square, other_pieces);
    BITBOARD rook_moves = rook_attacks & opp_pieces;

    while (rook_moves) {
        Square new_square = poplsb(rook_moves);
        current_scored_moves.push_back({
            Move(square, new_square),
            0
        });
    }
}

void Position::get_rook_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const {
    BITBOARD other_pieces = all_pieces & (~from_square(square));
    BITBOARD rook_attacks = get_rook_attacks(square, other_pieces);
    BITBOARD rook_moves = rook_attacks & (~our_pieces);

    while (rook_moves) {
        Square new_square = poplsb(rook_moves);
        current_scored_moves.push_back({
            Move(square, new_square),
            0
        });
    }
}

void Position::get_queen_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const {
    BITBOARD other_pieces = all_pieces & (~from_square(square));
    BITBOARD queen_attacks = get_queen_attacks(square, other_pieces);
    BITBOARD queen_moves = queen_attacks & opp_pieces;

    while (queen_moves) {
        Square new_square = poplsb(queen_moves);
        current_scored_moves.push_back({
            Move(square, new_square),
            0
        });
    }
}

void Position::get_queen_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const {
    BITBOARD other_pieces = all_pieces & (~from_square(square));
    BITBOARD queen_attacks = get_queen_attacks(square, other_pieces);
    BITBOARD queen_moves = queen_attacks & (~our_pieces);

    while (queen_moves) {
        Square new_square = poplsb(queen_moves);
        current_scored_moves.push_back({
            Move(square, new_square),
            0
        });
    }
}

void Position::get_king_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const {
    BITBOARD bitboard = KING_ATTACKS[square] & opp_pieces;
    while (bitboard) {
        Square new_square = poplsb(bitboard);
        current_scored_moves.push_back({
                Move(square, new_square),
                0
        });
    }
}

void Position::get_king_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, Square square) const {
    BITBOARD bitboard = KING_ATTACKS[square] & (~our_pieces);
    while (bitboard) {
        Square new_square = poplsb(bitboard);
        current_scored_moves.push_back({
                Move(square, new_square),
                0
        });
    }
}

void Position::get_piece_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, PieceType piece, Square square) const {
    if (piece == PAWN) get_pawn_captures(current_scored_moves, square);
    else if (piece == KNIGHT) get_knight_captures(current_scored_moves, square);
    else if (piece == BISHOP) get_bishop_captures(current_scored_moves, square);
    else if (piece == ROOK) get_rook_captures(current_scored_moves, square);
    else if (piece == QUEEN) get_queen_captures(current_scored_moves, square);
    else if (piece == KING) get_king_captures(current_scored_moves, square);
}

void Position::get_piece_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves, PieceType piece, Square square) {
    if (piece == PAWN) get_pawn_moves(current_scored_moves, square);
    else if (piece == KNIGHT) get_knight_moves(current_scored_moves, square);
    else if (piece == BISHOP) get_bishop_moves(current_scored_moves, square);
    else if (piece == ROOK) get_rook_moves(current_scored_moves, square);
    else if (piece == QUEEN) get_queen_moves(current_scored_moves, square);
    else if (piece == KING) get_king_moves(current_scored_moves, square);
}

void Position::get_pseudo_legal_captures(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) {
    current_scored_moves.clear();

    for (int piece = 0; piece < 6; piece++) {
        BITBOARD piece_bitboard = pieces[piece + side * COLOR_OFFSET];
        while (piece_bitboard) {
            Square square = poplsb(piece_bitboard);
            get_piece_captures(current_scored_moves, static_cast<PieceType>(piece), square);
        }
    }
}

void Position::get_pseudo_legal_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) {
    current_scored_moves.clear();

    for (int piece = 0; piece < 6; piece++) {
        BITBOARD piece_bitboard = pieces[piece + side * COLOR_OFFSET];
        while (piece_bitboard) {
            Square square = poplsb(piece_bitboard);
            get_piece_moves(current_scored_moves, static_cast<PieceType>(piece), square);
        }
    }
}

