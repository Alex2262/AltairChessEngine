

inline bool Position::is_attacked(Square square, Color color) const {
    const Bitboard occupancy = all_pieces & (~from_square(square));

    // Treat square like a pawn
    const Bitboard pawn_attacks = color == WHITE ? WHITE_PAWN_ATTACKS[square] : BLACK_PAWN_ATTACKS[square];
    if (pawn_attacks & get_pieces(PAWN, ~color)) return true;

    // Treat square like a knight
    const Bitboard knight_attacks = KNIGHT_ATTACKS[square];
    if (knight_attacks & get_pieces(KNIGHT, ~color)) return true;

    // Treat square like a king
    const Bitboard king_attacks = KING_ATTACKS[square];
    if (king_attacks & (get_pieces(KING, ~color))) return true;


    const Bitboard opp_queens = get_pieces(QUEEN, ~color);

    // Treat square like a bishop
    const Bitboard opp_diagonals = get_pieces(BISHOP, ~color) | opp_queens;
    if (opp_diagonals) {
        const Bitboard bishop_attacks = get_bishop_attacks(square, occupancy);
        if (bishop_attacks & opp_diagonals) return true;
    }

    // Treat square like a rook
    const Bitboard opp_orthogonals = get_pieces(ROOK, ~color) | opp_queens;
    if (opp_orthogonals) {
        const Bitboard rook_attacks = get_rook_attacks(square, occupancy);
        if (rook_attacks & opp_orthogonals) return true;
    }

    return false;
}


inline void Position::remove_piece(Piece piece, Square square) {
    pieces[piece] &= ~(1ULL << square);
    board[square] = EMPTY;
}

inline void Position::place_piece(Piece piece, Square square) {
    pieces[piece] |= (1ULL << square);
    board[square] = piece;
}


template<Movegen movegen>
void Position::get_pawn_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const {

    Bitboard pawns = get_pieces(PAWN, side);
    Bitboard pawn_forward_squares = side == WHITE ? shift<NORTH>(pawns) : shift<SOUTH>(pawns);
    const Direction down = side == WHITE ? SOUTH : NORTH;

    if constexpr (movegen == Movegen::Qsearch) {
        pawn_forward_squares &= ~(MASK_RANK[RANK_1] | MASK_RANK[RANK_8]);
    }

    Bitboard west_attacks = shift<WEST>(pawn_forward_squares) & opp_pieces;
    Bitboard east_attacks = shift<EAST>(pawn_forward_squares) & opp_pieces;

    if constexpr (movegen != Movegen::Quiet) {
        while (west_attacks) {
            const Square new_square = poplsb(west_attacks);

            // Promotion Captures
            if constexpr (movegen != Movegen::Qsearch) {
                const bool promotion = (side == WHITE && new_square >= 56) || (side == BLACK && new_square <= 7);

                if (promotion) {
                    for (PromotionType promotionType : {PROMOTION_KNIGHT, PROMOTION_BISHOP, PROMOTION_ROOK, PROMOTION_QUEEN}) {
                        current_scored_moves.push_back(
                                {Move(new_square + down + EAST, new_square, MOVE_TYPE_PROMOTION, promotionType), 0}
                        );
                    }

                    continue;
                }
            }

            // Regular Pawn Captures
            current_scored_moves.push_back({Move(new_square + down + EAST, new_square), 0});
        }

        while (east_attacks) {
            const Square new_square = poplsb(east_attacks);

            // Promotion Captures
            if constexpr (movegen != Movegen::Qsearch) {
                const bool promotion = (side == WHITE && new_square >= 56) || (side == BLACK && new_square <= 7);

                if (promotion) {
                    for (PromotionType promotionType: {PROMOTION_KNIGHT, PROMOTION_BISHOP, PROMOTION_ROOK,
                                                       PROMOTION_QUEEN}) {
                        current_scored_moves.push_back(
                                {Move(new_square + down + WEST, new_square, MOVE_TYPE_PROMOTION, promotionType), 0}
                        );
                    }

                    continue;
                }
            }

            // Regular Pawn Captures
            current_scored_moves.push_back({Move(new_square + down + WEST, new_square), 0});
        }

        // En passant code
        if constexpr (movegen != Movegen::Qsearch) {
            if (ep_square != NO_SQUARE) {
                Bitboard ep_pawns =
                        (side == WHITE ? BLACK_PAWN_ATTACKS[ep_square] : WHITE_PAWN_ATTACKS[ep_square]) & pawns;

                while (ep_pawns) {
                    const Square square = poplsb(ep_pawns);
                    current_scored_moves.push_back({Move(square, ep_square, MOVE_TYPE_EP), 0});
                }
            }
        }
    }

    if constexpr (movegen == Movegen::Noisy || movegen == Movegen::Qsearch) return;

    // Pawn Pushes
    Bitboard single_pushes = pawn_forward_squares & empty_squares;
    Bitboard double_pushes = (side == WHITE ? shift<NORTH>(single_pushes) & MASK_RANK[RANK_4]
                                            : shift<SOUTH>(single_pushes) & MASK_RANK[RANK_5]) & empty_squares;

    while (single_pushes) {
        const Square new_square = poplsb(single_pushes);
        const bool promotion = (side == WHITE && new_square >= 56) || (side == BLACK && new_square <= 7);

        // Single Push Promotions
        if (promotion) {
            for (PromotionType promotionType: {PROMOTION_KNIGHT, PROMOTION_BISHOP, PROMOTION_ROOK, PROMOTION_QUEEN}) {
                current_scored_moves.push_back({Move(new_square + down, new_square, MOVE_TYPE_PROMOTION, promotionType), 0});
            }
            continue;
        }

        // Single Pushes
        current_scored_moves.push_back({Move(new_square + down, new_square), 0});
    }

    while (double_pushes) {
        const Square new_square = poplsb(double_pushes);
        current_scored_moves.push_back({Move(new_square + down + down, new_square), 0});
    }

}

template<Movegen movegen>
void Position::get_knight_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const {
    Bitboard knights = get_pieces(KNIGHT, side);

    const Bitboard mask = [this]() -> Bitboard {
        if constexpr (movegen == Movegen::Quiet) return empty_squares;
        else if constexpr (movegen == Movegen::All) return ~(our_pieces);
        return opp_pieces;
    }();

    while (knights) {
        const Square square = poplsb(knights);

        Bitboard bitboard = KNIGHT_ATTACKS[square] & mask;

        while (bitboard) {
            const Square new_square = poplsb(bitboard);
            current_scored_moves.push_back({Move(square, new_square), 0});
        }
    }
}

template<Movegen movegen>
void Position::get_bishop_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const {
    Bitboard bishops = get_pieces(BISHOP, side);

    const Bitboard mask = [this]() -> Bitboard {
        if constexpr (movegen == Movegen::Quiet) return empty_squares;
        else if constexpr (movegen == Movegen::All) return ~(our_pieces);
        return opp_pieces;
    }();

    while (bishops) {
        const Square square = poplsb(bishops);

        Bitboard bishop_attacks = get_bishop_attacks(square, all_pieces);
        Bitboard bishop_moves = bishop_attacks & mask;

        while (bishop_moves) {
            const Square new_square = poplsb(bishop_moves);
            current_scored_moves.push_back({Move(square, new_square), 0});
        }
    }
}

template<Movegen movegen>
void Position::get_rook_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const {
    Bitboard rooks = get_pieces(ROOK, side);
    const Square king_pos = get_king_pos(side);

    const Bitboard mask = [this]() -> Bitboard {
        if constexpr (movegen == Movegen::Quiet) return empty_squares;
        else if constexpr (movegen == Movegen::All) return ~(our_pieces);
        return opp_pieces;
    }();

    while (rooks) {
        const Square square = poplsb(rooks);

        Bitboard rook_attacks = get_rook_attacks(square, all_pieces);
        Bitboard rook_moves = rook_attacks & mask;

        while (rook_moves) {
            const Square new_square = poplsb(rook_moves);
            current_scored_moves.push_back({Move(square, new_square), 0});
        }

        if constexpr (movegen == Movegen::Qsearch || movegen == Movegen::Noisy) continue;

        // -- Generate Castling moves --
        if (!(rook_attacks & get_pieces(KING, side))) continue;  // Guard clause

        const Square starting_rook_pos_k = starting_rook_pos[side][0];
        const Square starting_rook_pos_q = starting_rook_pos[side][1];

        const Square target_pos_k = side == WHITE ? g1 : g8;
        const Square target_pos_q = side == WHITE ? c1 : c8;

        const Square important_pos_k = target_pos_k + WEST;  // F1 square for FRC (the square the rook will go to)
        const Square important_pos_q = target_pos_q + EAST;  // D1 square for FRC (the square the rook will go to)

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

            current_scored_moves.push_back({Move(king_pos, target_pos_k, MOVE_TYPE_CASTLE), 0});
        }

        // Queen side Castling
        else if (((side == WHITE && (castle_ability_bits & 2) == 2) || (side == BLACK && (castle_ability_bits & 8) == 8))
                 && square == starting_rook_pos_q) {
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

            current_scored_moves.push_back({Move(king_pos, target_pos_q, MOVE_TYPE_CASTLE), 0});
        }
    }
}

template<Movegen movegen>
void Position::get_queen_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const {
    Bitboard queens = get_pieces(QUEEN, side);

    const Bitboard mask = [this]() -> Bitboard {
        if constexpr (movegen == Movegen::Quiet) return empty_squares;
        else if constexpr (movegen == Movegen::All) return ~(our_pieces);
        return opp_pieces;
    }();

    while (queens) {
        const Square square = poplsb(queens);

        Bitboard queen_attacks = get_queen_attacks(square, all_pieces);
        Bitboard queen_moves = queen_attacks & mask;

        while (queen_moves) {
            const Square new_square = poplsb(queen_moves);
            current_scored_moves.push_back({Move(square, new_square), 0});
        }
    }
}

template<Movegen movegen>
void Position::get_king_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const {
    const Square square = get_king_pos(side);

    const Bitboard mask = [this]() -> Bitboard {
        if constexpr (movegen == Movegen::Quiet) return empty_squares;
        else if constexpr (movegen == Movegen::All) return ~(our_pieces);
        return opp_pieces;
    }();

    Bitboard king_moves = KING_ATTACKS[square] & mask;
    while (king_moves) {
        const Square new_square = poplsb(king_moves);
        current_scored_moves.push_back({Move(square, new_square), 0});
    }
}

template<Movegen movegen, bool clear>
void Position::get_pseudo_legal_moves(FixedVector<ScoredMove, MAX_MOVES>& current_scored_moves) const {
    if constexpr (clear) current_scored_moves.clear();

    get_pawn_moves<movegen>(current_scored_moves);
    get_knight_moves<movegen>(current_scored_moves);
    get_bishop_moves<movegen>(current_scored_moves);
    get_rook_moves<movegen>(current_scored_moves);
    get_queen_moves<movegen>(current_scored_moves);
    get_king_moves<movegen>(current_scored_moves);
}