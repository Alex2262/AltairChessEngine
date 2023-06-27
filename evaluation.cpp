//
// Created by Alexander Tian on 6/26/23.
//

#include "evaluation.h"
#include "evaluation_constants.h"

SCORE_TYPE evaluate(Position& position) {
    uint32_t white_pawn_count = popcount(position.get_pieces(WHITE_PAWN));
    uint32_t white_knight_count = popcount(position.get_pieces(WHITE_KNIGHT));
    uint32_t white_bishop_count = popcount(position.get_pieces(WHITE_BISHOP));
    uint32_t white_rook_count = popcount(position.get_pieces(WHITE_ROOK));
    uint32_t white_queen_count = popcount(position.get_pieces(WHITE_QUEEN));

    uint32_t black_pawn_count = popcount(position.get_pieces(BLACK_PAWN));
    uint32_t black_knight_count = popcount(position.get_pieces(BLACK_KNIGHT));
    uint32_t black_bishop_count = popcount(position.get_pieces(BLACK_BISHOP));
    uint32_t black_rook_count = popcount(position.get_pieces(BLACK_ROOK));
    uint32_t black_queen_count = popcount(position.get_pieces(BLACK_QUEEN));

    SCORE_TYPE white_material_mid = PIECE_VALUES_MID[PAWN] * white_pawn_count +
                                    PIECE_VALUES_MID[KNIGHT] * white_knight_count +
                                    PIECE_VALUES_MID[BISHOP] * white_bishop_count +
                                    PIECE_VALUES_MID[ROOK] * white_rook_count +
                                    PIECE_VALUES_MID[QUEEN] * white_queen_count;

    SCORE_TYPE black_material_mid = PIECE_VALUES_MID[PAWN] * black_pawn_count +
                                    PIECE_VALUES_MID[KNIGHT] * black_knight_count +
                                    PIECE_VALUES_MID[BISHOP] * black_bishop_count +
                                    PIECE_VALUES_MID[ROOK] * black_rook_count +
                                    PIECE_VALUES_MID[QUEEN] * black_queen_count;

    SCORE_TYPE white_material_end = PIECE_VALUES_END[PAWN] * white_pawn_count +
                                    PIECE_VALUES_END[KNIGHT] * white_knight_count +
                                    PIECE_VALUES_END[BISHOP] * white_bishop_count +
                                    PIECE_VALUES_END[ROOK] * white_rook_count +
                                    PIECE_VALUES_END[QUEEN] * white_queen_count;

    SCORE_TYPE black_material_end = PIECE_VALUES_END[PAWN] * black_pawn_count +
                                    PIECE_VALUES_END[KNIGHT] * black_knight_count +
                                    PIECE_VALUES_END[BISHOP] * black_bishop_count +
                                    PIECE_VALUES_END[ROOK] * black_rook_count +
                                    PIECE_VALUES_END[QUEEN] * black_queen_count;

    SCORE_TYPE material_mid = white_material_mid - black_material_mid;
    SCORE_TYPE material_end = white_material_end - black_material_end;

    int game_phase = GAME_PHASE_SCORES[PAWN] * (white_pawn_count + black_pawn_count) +
                     GAME_PHASE_SCORES[KNIGHT] * (white_knight_count + black_knight_count) +
                     GAME_PHASE_SCORES[BISHOP] * (white_bishop_count + black_bishop_count) +
                     GAME_PHASE_SCORES[ROOK] * (white_rook_count + black_rook_count) +
                     GAME_PHASE_SCORES[QUEEN] * (white_queen_count + black_queen_count);

    game_phase = std::min(game_phase, 24);

    SCORE_TYPE evaluation = (material_mid * game_phase + material_end * (24 - game_phase)) / 24;

    return (position.side * -2 + 1) * evaluation;
}
