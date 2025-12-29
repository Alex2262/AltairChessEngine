
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

void debug_perft(Position& position, Perft_Result_Type& res, Ply depth, Ply ply);

long long fast_perft(Position& position, Ply depth, Ply ply);

long long uci_perft(Position& position, Ply depth, Ply ply);
