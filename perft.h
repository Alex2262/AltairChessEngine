//
// Created by Alex Tian on 9/18/2022.
//

#ifndef ANTARESCHESSENGINE_PERFT_H
#define ANTARESCHESSENGINE_PERFT_H

#include "position.h"

struct Perft_Result_Type {
    int total_amount;
    int capture_amount;
    int ep_amount;
    int promotion_amount;
    int castle_amount;
    int check_amount;
};

void debug_perft(Position& position, Perft_Result_Type& res, PLY_TYPE depth, PLY_TYPE ply);

long long fast_perft(Position& position, PLY_TYPE depth, PLY_TYPE ply);

long long uci_perft(Position& position, PLY_TYPE depth, PLY_TYPE ply);


#endif //ANTARESCHESSENGINE_PERFT_H
