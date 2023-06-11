//
// Created by Alex Tian on 9/29/2022.
//

#ifndef ANTARESCHESSENGINE_EVALUATION_H
#define ANTARESCHESSENGINE_EVALUATION_H

#include <iostream>
#include "constants.h"
#include "position.h"
#include "search.h"
#include "cmath"

struct Score_Struct {
    SCORE_TYPE mid;
    SCORE_TYPE end;
};

inline SCORE_TYPE get_manhattan_distance(SQUARE_TYPE square_1, SQUARE_TYPE square_2) {
    SQUARE_TYPE row_1 = 8 - square_1 / 8, col_1 = square_1 % 8;
    SQUARE_TYPE row_2 = 8 - square_2 / 8, col_2 = square_2 % 8;

    return abs(row_1 - row_2) + abs(col_1 - col_2);
}


inline SCORE_TYPE get_chebyshev_distance(SQUARE_TYPE square_1, SQUARE_TYPE square_2) {
    SQUARE_TYPE row_1 = 8 - square_1 / 8, col_1 = square_1 % 8;
    SQUARE_TYPE row_2 = 8 - square_2 / 8, col_2 = square_2 % 8;

    return std::max(abs(row_1 - row_2), abs(col_1 - col_2));
}


void evaluate_king_pawn(const Position& position, Score_Struct& scores, SQUARE_TYPE file, bool is_white);
void evaluate_pawn(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white);
void evaluate_knight(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white);
void evaluate_bishop(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white);
void evaluate_rook(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white);
void evaluate_queen(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white);
void evaluate_king(const Position& position, Score_Struct& scores, SQUARE_TYPE pos, bool is_white);

double evaluate_drawishness(const int white_piece_amounts[6], const int black_piece_amounts[6],
                            SCORE_TYPE white_material, SCORE_TYPE black_material, bool opp_colored_bishops);
SCORE_TYPE evaluate(Position& position);

SCORE_TYPE score_move(const Thread_State& thread_state, Position& position, MOVE_TYPE move, MOVE_TYPE tt_move, MOVE_TYPE last_move_one, MOVE_TYPE last_move_two);
SCORE_TYPE score_capture(const Thread_State& thread_state, Position& position, MOVE_TYPE move, MOVE_TYPE tt_move);

void get_move_scores(const Thread_State& thread_state, Position& position, std::vector<Move_Struct>& moves,
                     MOVE_TYPE tt_move, MOVE_TYPE last_move_one, MOVE_TYPE last_move_two);
void get_capture_scores(const Thread_State& thread_state, Position& position, std::vector<Move_Struct>& moves,
                        MOVE_TYPE tt_move);
void sort_next_move(std::vector<Move_Struct>& moves, int current_count);

template<int n>
struct KingRing {
    constexpr KingRing() : masks() {
        for (int rings = 1; rings <= n; rings++) {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    masks[rings-1][i * 8 + j] = 0ULL;
                    for (int y = i - rings; y <= i + rings; y++){
                        for (int x = j - rings; x <= j + rings; x++) {
                            if (y < 0 || y >= 8 || x < 0 || x >= 8) continue;
                            if (y == i - rings || y == i + rings || x == j - rings || x == j + rings) {
                                masks[rings-1][i * 8 + j] |= 1ULL << (y * 8 + x);
                            }
                        }
                    }
                    //std::cout << i * 8 + j << " " << masks[rings-1][i * 8 + j] << std::endl;
                }
            }
        }
    }

    uint64_t masks[n][64]{};
};

constexpr KingRing king_ring_zone = KingRing<2>();

#endif //ANTARESCHESSENGINE_EVALUATION_H
