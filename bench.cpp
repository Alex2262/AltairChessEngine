//
// Created by Alexander Tian on 4/12/23.
//

#include <iostream>
#include <chrono>
#include "bench.h"

// A function for a 'bench' metric that calculates nps and nodes over
// a set of 50 pre-defined fens. Used to insure equality between machines, which is used
// during testing on an instance.

void run_bench(Engine& engine, PLY_TYPE depth) {

    // Save these variables to reset them after the bench has been run.
    Position& position = engine.thread_states[0].position;

    PLY_TYPE old_depth = engine.max_depth;
    uint64_t old_soft = engine.soft_time_limit;
    uint64_t old_hard = engine.hard_time_limit;

    // Set variables
    engine.max_depth = depth;
    engine.soft_time_limit = TIME_INF;
    engine.hard_time_limit = TIME_INF;

    // Calculate the starting time
    auto start_time = std::chrono::high_resolution_clock::now();
    engine.start_time = std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::time_point_cast<std::chrono::milliseconds>(start_time).time_since_epoch()).count();

    // Used for calculating statistics
    uint64_t total_nodes = 0;
    Search_Results bench_res{};

    // Loop through the 50 fens
    for (int fen_count = 0; fen_count < static_cast<int>(fens.size()); fen_count++) {

        std::string fen = fens[fen_count];
        std::cout << "running position #" << fen_count + 1 << " fen: " << fen << std::endl;

        engine.new_game();
        position.set_fen(fen);

        iterative_search(engine);

        lazy_smp_search(engine);
        total_nodes += engine.node_count;

        if (engine.show_stats) {
            for (int i = 0; i < FAIL_HIGH_STATS_COUNT; i++) {
                bench_res.qsearch_fail_highs[i] += engine.search_results.qsearch_fail_highs[i];
                bench_res.search_fail_highs[i] += engine.search_results.search_fail_highs[i];
            }

            for (int i = 0; i < 6; i++) {
                bench_res.search_fail_high_types[i] += engine.search_results.search_fail_high_types[i];
            }

            for (int i = 0; i < ALPHA_RAISE_STATS_COUNT; i++) {
                bench_res.search_alpha_raises[i] += engine.search_results.search_alpha_raises[i];
            }

            bench_res.alpha_raised_count += engine.search_results.alpha_raised_count;
        }
    }

    // Print certain statistics if instructed
    if (engine.show_stats) {
        bench_res.num_searches = fens.size();
        bench_res.node_count = total_nodes;
        bench_res.depth_reached = depth;

        print_statistics(bench_res);
    }

    // Calculate elapsed time and NPS
    auto end_time = std::chrono::high_resolution_clock::now();
    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(end_time
                                                                        - start_time);
    uint64_t elapsed_time = ms_int.count();
    elapsed_time = std::max<uint64_t>(elapsed_time, 1);

    std::cout << "info time " << elapsed_time << std::endl;
    std::cout << total_nodes << " nodes "
              << int(static_cast<double>(total_nodes) / (static_cast<double>(elapsed_time) / 1000.0))
              << " nps " << std::endl;

    // Reset variables
    engine.max_depth = old_depth;
    engine.soft_time_limit = old_soft;
    engine.hard_time_limit = old_hard;

    position.set_fen(START_FEN);
}