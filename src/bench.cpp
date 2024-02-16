
#include <iostream>
#include <chrono>
#include "bench.h"

// A list of many fens that include famous positions from notable games, some of my personal games,
// and other chess studies.
constexpr std::array fens {

        // Positions from my own games
        "r1r3k1/pb1nbppp/4p3/1p1pP2P/3p1B2/3P2P1/qPP1QPBN/2R1R1K1 w - - 0 18",
        "r1b2rk1/1pqnbppp/p2ppn2/8/3NPP2/2NBBQ2/PPP3PP/3R1RK1 b - - 3 11",
        "5rk1/5ppp/p3p3/1pqp4/2n2P2/P1NB1N2/1PP3PP/2BR3K b - - 6 20",
        "r1b3k1/pp2b1pp/1q2prn1/2p4Q/2PpBP2/1N1P2PP/PP6/R1B1R1K1 w - - 5 18", // Nd2 was best, I played f5
        "r1br2k1/pp3pbp/1qn1p1pn/3pP3/3P2P1/2N2N1P/PP3PB1/R1BQR1K1 w - - 0 14",
        "3rb3/p1R4p/1p1qPkp1/3B1p2/3P4/1P5P/P2Q1P2/2R3K1 w - - 2 34", // Mate in 8
        "r1bq1rk1/pp1n1pp1/2pb1n1p/6B1/2BP4/2NQ1N1P/PP3PP1/R4RK1 w - - 0 14", // Bxh6 sacrifice
        "r2q1rk1/1b3p2/p1p2p2/1p3Np1/3P4/1Q5P/PP3PP1/R4RK1 w - - 8 27",
        "r1br2k1/ppq1bppp/4p3/4P3/1nP5/P4N2/4QPPP/R1B1RNK1 b - - 0 16",
        "r1b3k1/ppq2ppp/4p3/4P3/2P5/b4N2/4QPPP/3R1NK1 w - - 2 21",
        "r2q1rk1/pb2bppp/2n2n2/2pp4/8/1PN1PN2/PBB2PPP/R2Q1RK1 b - - 2 12",
        "r2q1rk1/pb3ppp/8/2Pp4/8/1P2PN2/2Q2PPP/Rn3RK1 b - - 0 18",
        "r6k/1p1bb1pq/p1nppr2/5p2/1PPN1P2/P3B2P/2Q1B1P1/3R1RK1 w - - 4 23",
        "r4rk1/pb3ppp/8/2Pq4/3N4/1P2P3/2Q2PPP/Rn3RK1 w - - 1 20",
        "r4rk1/3qbppp/b1n1p3/pp1pP3/3P1PP1/PP3N2/1B2NQ1P/2R1R1K1 b - - 1 21", // a4, b4 then Nxb4
        "2rn1rk1/bp1nq1p1/p3p2p/2ppP2N/3P4/4BN2/PP1Q1PPP/2R1R1K1 w - - 0 19", // Nxg7
        "1r2k2r/2qpbppp/p1b1pn2/8/3QP1P1/4BP2/NPP4P/2KR1B1R b k g3 0 15", // Nxg4
        "1r4k1/5ppp/pB1pp3/8/4b1P1/2Q5/q6P/2KR3R b - - 5 28", // h6
        "3r3k/2p1qp1p/1pnr1np1/p3p3/4P3/2P2NPP/PP2QP2/R2R1NK1 b - - 6 24", // Nxe4
        "4r1k1/pp3ppp/3q1n2/3pn3/3Q1N2/1NP4P/PP3PP1/R5K1 b - - 2 19",
        "r2nr1k1/1pp1qppp/p2pbn2/4p1N1/PPBPP3/1QP1P3/3N2PP/R4RK1 b - - 0 14",
        "rn2k2r/1p2bppp/1q2p3/pB1pP1B1/P2P4/5b2/1PP3PP/R2Q1RK1 b kq - 1 13",

        // Studies
        "r4bk1/pp4p1/2p5/4P1p1/4B3/2P1P2P/PP3K2/R7 w - - 0 1", // Bg6
        "r4rk1/1pq1bppp/p1bppn2/8/P3PP2/2NBB3/1PPQ2PP/R4R1K b - - 0 1", // b5
        "1B6/8/7P/4p3/3b3k/8/8/2K5 w - - 0 1", // Ba7

        // GM Games
        "3N4/5pk1/1p1Qpnpp/p1n5/5P2/3qP1PP/6BK/8 w - - 2 38", // Nxe6, Carlsen v Karjakin, 2016 WCC
        "r3k2r/1b1nqp1p/p1npp1p1/1p6/3NPP2/P1N1Q3/1PP1B2P/1K1R2R1 w kq - 0 1",
        "r1b2r1k/4qp1p/p2ppb1Q/4nP2/1p1NP3/2N5/PPP4P/2KR1BR1 w - - 4 18", // Nc6, Kholmov v Bronstein, Kiev 1964
        "8/pR4pk/1b2p3/2p3p1/N1p5/7P/PP1r2P1/6K1 b - - 2 31", // Rxb2, Sanz - Endgame Sacrifice
        "rn3rk1/pbppq1pp/1p2pb2/4N2Q/3PN3/3B4/PPP2PPP/R3K2R w KQ - 6 11", // Qxh7, Lasker v Thomas - King Hunt
        "r4rk1/pp2pp1p/3p2p1/6B1/3Q3P/1P6/1RPKnPP1/q6R w - - 0 1", // Qh8+, Bura -  Desperado
        "8/7p/5kp1/4p3/p3rPRP/3K2P1/8/8 b - - 1 43", // Kg7, Flohr v Geller, Moscow 1949
        "r4k1r/1b2bPR1/p4n2/3p4/4P2P/1q2B2B/PpP5/1K4R1 w - - 0 26", // Bh6, Vladimirov v Epishin
        "5rk1/pp4pp/4p3/2R3Q1/3n4/2q4r/P1P2PPP/5RK1 b - - 1 23", // Qg3, Levitsky v Marshall - Gold Coin Game
        "8/8/4kpp1/3p1b2/p6P/2B5/6P1/6K1 b - - 0 47", // Bh3, Topalov v Shirov, 1998

};

// A function for a 'bench' metric that calculates nps and nodes over
// a set of pre-defined fens. Used to insure equality between machines, which is used
// during testing on an instance.

void run_bench(Engine& engine, PLY_TYPE depth) {

    // Save these variables to reset them after the bench has been run.
    Position& position = engine.thread_states[0].position;

    PLY_TYPE old_depth = engine.max_depth;
    uint64_t old_soft = engine.soft_time_limit;
    uint64_t old_hard = engine.hard_time_limit;

    // Set variables
    engine.max_depth = depth;

    // Calculate the starting time
    auto start_time = std::chrono::high_resolution_clock::now();
    engine.start_time = std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::time_point_cast<std::chrono::milliseconds>(start_time).time_since_epoch()).count();

    // Used for calculating statistics
    uint64_t total_nodes = 0;

#ifdef SHOW_STATISTICS
    Search_Results bench_res{};
#endif

    // Loop through the 50 fens
    for (int fen_count = 0; fen_count < static_cast<int>(fens.size()); fen_count++) {

        std::string fen = fens[fen_count];
        std::cout << "running position #" << fen_count + 1 << " fen: " << fen << std::endl;

        engine.new_game();
        position.set_fen(fen);

        engine.soft_time_limit = TIME_INF;
        engine.hard_time_limit = TIME_INF;

        search(engine);

        for (Thread_State& thread_state_i : engine.thread_states) {
            total_nodes += thread_state_i.node_count;
        }

#ifdef SHOW_STATISTICS
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
#endif
    }

    // Print certain statistics if instructed
#ifdef SHOW_STATISTICS
    bench_res.num_searches = fens.size();
    bench_res.node_count = total_nodes;
    bench_res.depth_reached = depth;

    print_statistics(bench_res);
#endif

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
