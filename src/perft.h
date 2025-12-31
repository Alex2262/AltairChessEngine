
#pragma once

#include "position.h"

struct Perft_Result_Type {
    int total_amount;
    int capture_amount;
    int ep_amount;
    int promotion_amount;
    int castle_amount;
    int check_amount;
};

struct Perft {
    std::array<FixedVector<ScoredMove, MAX_MOVES>, TOTAL_MAX_DEPTH> scored_moves;
};

void debug_perft(Perft& perft, Position& position, Perft_Result_Type& res, Ply depth, Ply ply);

uint64_t fast_perft(Perft& perft, Position& position, Ply depth, Ply ply);

uint64_t uci_perft(Perft& perft, Position& position, Ply depth, Ply ply);
