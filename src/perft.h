
#pragma once

#include "position.h"

struct PerftResultType {
    int total_amount;
    int capture_amount;
    int ep_amount;
    int promotion_amount;
    int castle_amount;
    int check_amount;
};

struct Perft {
    std::vector<FixedVector<ScoredMove, MAX_MOVES>> scored_moves;

    Perft() : scored_moves(TOTAL_MAX_DEPTH) {}
};

void debug_perft(Perft& perft, Position& position, PerftResultType& res, Ply depth, Ply ply);

uint64_t fast_perft(Perft& perft, Position& position, Ply depth, Ply ply);

uint64_t uci_perft(Perft& perft, Position& position, Ply depth, Ply ply);
