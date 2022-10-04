//
// Created by Alex Tian on 9/22/2022.
//

#ifndef ANTARESCHESSENGINE_SEARCH_H
#define ANTARESCHESSENGINE_SEARCH_H

#include "position.h"

class Engine {

public:

    Engine() = default;

    PLY_TYPE max_depth = 64;
    PLY_TYPE max_q_depth = 64;
    PLY_TYPE min_depth = 2;
    PLY_TYPE current_search_depth = 0;
    PLY_TYPE search_ply = 0;

    long max_time = 60000;
    long start_time = 0;

    long long node_count = 0;

    MOVE_TYPE pv_table[64][64] = {0};
    unsigned short pv_length[65] = {0};

    MOVE_TYPE killer_moves[2][64] = {0};  // # of killer moves (2) | max_depth (64)
    SCORE_TYPE history_moves[12][64] = {0}; // # piece | square

    bool stopped = true;

    void reset();


};

SCORE_TYPE qsearch(Engine& engine, Position& position, SCORE_TYPE alpha, SCORE_TYPE beta, PLY_TYPE depth);
SCORE_TYPE negamax(Engine& engine, Position& position, SCORE_TYPE alpha, SCORE_TYPE beta, PLY_TYPE depth);

void iterative_search(Engine& engine, Position& position);

#endif //ANTARESCHESSENGINE_SEARCH_H
