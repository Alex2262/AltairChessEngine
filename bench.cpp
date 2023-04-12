//
// Created by Alexander Tian on 4/12/23.
//

#include <iostream>
#include <chrono>
#include <cstring>
#include "bench.h"


void run_bench(Engine& engine, Position& position, PLY_TYPE depth) {
    PLY_TYPE old_depth = engine.max_depth;
    uint64_t old_soft = engine.soft_time_limit;
    uint64_t old_hard = engine.hard_time_limit;

    engine.max_depth = depth;
    engine.soft_time_limit = TIME_INF;
    engine.hard_time_limit = TIME_INF;

    auto start_time = std::chrono::high_resolution_clock::now();
    engine.start_time = std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::time_point_cast<std::chrono::milliseconds>(start_time).time_since_epoch()).count();

    uint64_t total_nodes = 0;
    for (std::string fen : fens) {
        std::cout << "running fen: " << fen << std::endl;
        position.set_fen(fen);
        iterative_search(engine, position);

        total_nodes += engine.node_count;
    }

    auto end_time = std::chrono::high_resolution_clock::now();

    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(end_time
                                                                        - start_time);
    long elapsed_time = ms_int.count();
    elapsed_time = std::max(elapsed_time, 1L);

    std::cout << "info time " << elapsed_time << std::endl;
    std::cout << total_nodes << " nodes " << int(total_nodes / (elapsed_time / 1000.0)) << " nps " << std::endl;

    engine.max_depth = old_depth;
    engine.soft_time_limit = old_soft;
    engine.hard_time_limit = old_hard;

    position.set_fen(START_FEN);
}