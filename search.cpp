//
// Created by Alex Tian on 9/22/2022.
//

#include <chrono>
#include <iostream>
#include <cstring>
#include "search.h"
#include "evaluation.h"
#include "move.h"
#include "useful.h"



void Engine::reset() {
    node_count = 0;

    current_search_depth = 0;
    search_ply = 0;

    std::memset(pv_length, 0, sizeof(pv_length));
    std::memset(pv_table, 0, sizeof(pv_table));

    std::memset(killer_moves, 0, sizeof(killer_moves));
}


SCORE_TYPE qsearch(Engine& engine, Position& position, SCORE_TYPE alpha, SCORE_TYPE beta, PLY_TYPE depth) {

    // position.print_board();
    engine.node_count++;

    if (engine.current_search_depth >= engine.min_depth && (engine.node_count & 2047) == 0) {
        auto time = std::chrono::high_resolution_clock::now();
        long current_time = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::time_point_cast<std::chrono::milliseconds>(time).time_since_epoch()).count();

        if (current_time - engine.start_time >= engine.max_time) engine.stopped = true;
    }

    if (engine.stopped) return 0;

    SCORE_TYPE static_eval = evaluate(position);

    if (depth == 0 || static_eval >= beta) return static_eval;

    alpha = (static_eval > alpha) ? static_eval : alpha;

    position.get_pseudo_legal_captures(engine.search_ply);
    get_capture_scores(position.moves[engine.search_ply], position.move_scores[engine.search_ply]);

    SQUARE_TYPE current_ep_square = position.ep_square;
    uint16_t current_castle_ability_bits = position.castle_ability_bits;
    uint64_t current_hash_key = position.hash_key;

    SCORE_TYPE best_score = static_eval;
    // MOVE_TYPE best_move = NO_MOVE;

    for (int move_index = 0; move_index < position.moves[engine.search_ply].size(); move_index++) {

        sort_next_move(position.moves[engine.search_ply], position.move_scores[engine.search_ply], move_index);
        MOVE_TYPE move = position.moves[engine.search_ply][move_index];

        bool attempt = position.make_move(move);

        if (!attempt) {
            position.undo_move(move, current_ep_square, current_castle_ability_bits, current_hash_key);
            continue;
        }

        engine.search_ply++;
        position.side ^= 1;

        SCORE_TYPE return_eval = -qsearch(engine, position, -beta, -alpha, depth - 1);

        position.side ^= 1;
        engine.search_ply--;

        position.undo_move(move, current_ep_square, current_castle_ability_bits, current_hash_key);

        if (return_eval > best_score) {
            best_score = return_eval;

            if (return_eval > alpha) {
                alpha = return_eval;

                if (return_eval >= beta) {
                    return best_score;
                }
            }
        }

    }

    return best_score;
}


SCORE_TYPE negamax(Engine& engine, Position& position, SCORE_TYPE alpha, SCORE_TYPE beta, PLY_TYPE depth) {

    engine.pv_length[engine.search_ply] = engine.search_ply;

    if (depth == 0) {
        return qsearch(engine, position, alpha, beta, engine.max_q_depth);
    }

    if (engine.stopped) return 0;

    engine.node_count++;

    position.get_pseudo_legal_moves(engine.search_ply);
    get_move_scores(engine, position.moves[engine.search_ply], position.move_scores[engine.search_ply]);

    SQUARE_TYPE current_ep_square = position.ep_square;
    uint16_t current_castle_ability_bits = position.castle_ability_bits;
    uint64_t current_hash_key = position.hash_key;

    bool in_check = position.is_attacked(position.king_positions[position.side]);
    if (in_check) depth++;

    int legal_moves = 0;

    SCORE_TYPE best_score = -SCORE_INF;
    // MOVE_TYPE best_move = NO_MOVE;

    for (int move_index = 0; move_index < position.moves[engine.search_ply].size(); move_index++) {

        sort_next_move(position.moves[engine.search_ply], position.move_scores[engine.search_ply], move_index);
        MOVE_TYPE move = position.moves[engine.search_ply][move_index];

        bool attempt = position.make_move(move);

        if (!attempt) {
            position.undo_move(move, current_ep_square, current_castle_ability_bits, current_hash_key);
            continue;
        }

        engine.search_ply++;
        position.side ^= 1;

        SCORE_TYPE return_eval = -negamax(engine, position, -beta, -alpha, depth - 1);

        position.side ^= 1;
        engine.search_ply--;
        position.undo_move(move, current_ep_square, current_castle_ability_bits, current_hash_key);

        if (return_eval > best_score) {
            best_score = return_eval;

            engine.pv_table[engine.search_ply][engine.search_ply] = move;
            for (int next_ply = engine.search_ply+1; next_ply < engine.pv_length[engine.search_ply+1]; next_ply++) {
                engine.pv_table[engine.search_ply][next_ply] = engine.pv_table[engine.search_ply + 1][next_ply];
            }

            engine.pv_length[engine.search_ply] = engine.pv_length[engine.search_ply + 1];

            if (return_eval > alpha) {
                alpha = return_eval;

                if (return_eval >= beta) {

                    if (!get_is_capture(move)) {
                        engine.killer_moves[1][engine.search_ply] = engine.killer_moves[0][engine.search_ply];
                        engine.killer_moves[0][engine.search_ply] = move;
                    }
                    return best_score;
                }
            }
        }

        legal_moves++;
    }

    if (legal_moves == 0 && !in_check) return 0;
    else if (legal_moves == 0) return -MATE_SCORE - depth;

    return best_score;
}


void iterative_search(Engine& engine, Position& position) {

    engine.stopped = false;
    position.clear_movelist();

    engine.reset();

    auto start_time = std::chrono::high_resolution_clock::now();
    engine.start_time = std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::time_point_cast<std::chrono::milliseconds>(start_time).time_since_epoch()).count();

    int original_side = position.side;

    SCORE_TYPE alpha = -SCORE_INF;
    SCORE_TYPE beta = SCORE_INF;

    PLY_TYPE running_depth = 1;

    std::string best_pv;
    SCORE_TYPE best_score = 0;

    while (running_depth < engine.max_depth) {
        engine.current_search_depth = running_depth;

        SCORE_TYPE return_eval = negamax(engine, position, alpha, beta, running_depth);

        std::string pv_line;
        for (int c = 0; c < engine.pv_length[0]; c++) {
            pv_line += get_uci_from_move(engine.pv_table[0][c]);
            pv_line += " ";
            position.side ^= 1;
        }

        position.side = original_side;

        if (not engine.stopped) {
            best_pv = pv_line;
            best_score = return_eval;
        }
        else running_depth--;

        auto end_time = std::chrono::high_resolution_clock::now();

        auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(end_time
                                                                                                        - start_time);
        double elapsed_time = ms_int.count();
        if (elapsed_time == 0) elapsed_time = 0.1;

        std::cout << "info depth " << running_depth << " score cp " << best_score << " time " << int(elapsed_time)
                  << " nodes " << engine.node_count << " nps " << int(engine.node_count / (elapsed_time / 1000))
                  << " pv " << best_pv << std::endl;

        if (engine.stopped) {
            std::cout << "bestmove " << split(best_pv, ' ')[0] << std::endl;
            break;
        }

        running_depth++;
    }
}


/*
Bare a/b negamax with PST eval
info depth 1 score cp 58 time 0 nodes 21 nps 210000 pv b1c3
info depth 2 score cp 0 time 1 nodes 127 nps 127000 pv b1c3 g8f6
info depth 3 score cp 58 time 3 nodes 1246 nps 415333 pv b1c3 g8f6 g1f3
info depth 4 score cp 0 time 6 nodes 8680 nps 1446666 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 55 time 41 nodes 184415 nps 4497926 pv e2e4 b8c6 f1b5 c6e5 b5d7
info depth 6 score cp -30 time 274 nodes 1326069 nps 4839667 pv b1c3 e7e5 e2e3 f8b4 c3d5 b4d2
info depth 7 score cp 98 time 3277 nodes 17673132 nps 5393082 pv e2e3 b8c6 b1c3 c6b4 f1c4 g8f6 c4f7
info depth 8 score cp -63 time 41540 nodes 213790795 nps 5146624 pv b1c3 b8c6 e2e3 e7e5 f1b5 f8b4 c3d5 b4d2
info depth 8 score cp -63 time 44999 nodes 231026698 nps 5134040 pv b1c3 b8c6 e2e3 e7e5 f1b5 f8b4 c3d5 b4d2
bestmove b1c3



Qsearch + pre-allocating move vectors
info depth 1 score cp 58 time 0 nodes 21 nps 210000 pv b1c3
info depth 2 score cp 0 time 2 nodes 157 nps 78500 pv b1c3 b8c6
info depth 3 score cp 58 time 4 nodes 2362 nps 590500 pv b1c3 g8f6 g1f3
info depth 4 score cp 0 time 7 nodes 14721 nps 2103000 pv g1f3 g8f6 b1c3 b8c6
info depth 5 score cp 41 time 35 nodes 157226 nps 4492171 pv b1c3 g8f6 g1f3 b8c6 d2d4
info depth 6 score cp 0 time 412 nodes 1765136 nps 4284310 pv b1c3 b8c6 g1f3 g8f6 e2e4 d7d5
info depth 7 score cp 30 time 7861 nodes 31894942 nps 4057364 pv e2e4 b8c6 g1f3 g8f6 e4e5 f6e4 b1c3
info depth 7 score cp 30 time 45000 nodes 146612255 nps 3258050 pv e2e4 b8c6 g1f3 g8f6 e4e5 f6e4 b1c3
bestmove e2e4

Score of AntaresCpp0.01 vs AntaresCpp0.00: 54 - 5 - 41 [0.745]
...      AntaresCpp0.01 playing White: 23 - 1 - 26  [0.720] 50
...      AntaresCpp0.01 playing Black: 31 - 4 - 15  [0.770] 50
...      White vs Black: 27 - 32 - 41  [0.475] 100
Elo difference: 186.2 +/- 53.7, LOS: 100.0 %, DrawRatio: 41.0 %

Score of AntaresCpp0.01 vs SebLagueEngine0.1: 6 - 18 - 5 [0.293]
...      AntaresCpp0.01 playing White: 3 - 9 - 3  [0.300] 15
...      AntaresCpp0.01 playing Black: 3 - 9 - 2  [0.286] 14
...      White vs Black: 12 - 12 - 5  [0.500] 29
Elo difference: -152.9 +/- 132.7, LOS: 0.7 %, DrawRatio: 17.2 %



In check extensions
info depth 1 score cp 58 time 0 nodes 21 nps 210000 pv b1c3
info depth 2 score cp 0 time 1 nodes 157 nps 157000 pv b1c3 b8c6
info depth 3 score cp 58 time 2 nodes 2362 nps 1181000 pv b1c3 g8f6 g1f3
info depth 4 score cp 0 time 5 nodes 14756 nps 2951200 pv g1f3 g8f6 b1c3 b8c6
info depth 5 score cp 41 time 32 nodes 150351 nps 4698468 pv b1c3 g8f6 g1f3 b8c6 d2d4
info depth 6 score cp 0 time 510 nodes 2111693 nps 4140574 pv d2d4 d7d5 g1f3 g8f6 b1c3 b8c6
info depth 7 score cp 30 time 4875 nodes 21066927 nps 4321420 pv e2e4 b8c6 g1f3 g8f6 e4e5 f6e4 b1c3
info depth 7 score cp 30 time 44999 nodes 171016216 nps 3800444 pv e2e4 b8c6 g1f3 g8f6 e4e5 f6e4 b1c3
bestmove e2e4

Score of AntaresCpp0.02 vs AntaresCpp0.01: 21 - 20 - 59 [0.505]
...      AntaresCpp0.02 playing White: 16 - 5 - 29  [0.610] 50
...      AntaresCpp0.02 playing Black: 5 - 15 - 30  [0.400] 50
...      White vs Black: 31 - 10 - 59  [0.605] 100
Elo difference: 3.5 +/- 43.8, LOS: 56.2 %, DrawRatio: 59.0 %

Score of AntaresCpp0.02 vs SebLagueEngine0.1: 15 - 103 - 32 [0.207]
...      AntaresCpp0.02 playing White: 7 - 50 - 18  [0.213] 75
...      AntaresCpp0.02 playing Black: 8 - 53 - 14  [0.200] 75
...      White vs Black: 60 - 58 - 32  [0.507] 150
Elo difference: -233.7 +/- 57.4, LOS: 0.0 %, DrawRatio: 21.3 %



Negamax Move Ordering
info depth 1 score cp 58 time 0 nodes 21 nps 210000 pv b1c3
info depth 2 score cp 0 time 1 nodes 157 nps 157000 pv b1c3 b8c6
info depth 3 score cp 58 time 3 nodes 2176 nps 725333 pv b1c3 b8c6 g1f3
info depth 4 score cp 0 time 7 nodes 13851 nps 1978714 pv g1f3 b8c6 b1c3 g8f6
info depth 5 score cp 41 time 24 nodes 91403 nps 3808458 pv g1f3 b8c6 d2d4 g8f6 b1c3
info depth 6 score cp 0 time 267 nodes 1000631 nps 3747681 pv g1f3 g8f6 d2d4 d7d5 b1c3 b8c6
info depth 7 score cp 30 time 2067 nodes 7725204 nps 3737399 pv e2e4 b8c6 g1f3 g8f6 e4e5 f6e4 b1c3
info depth 8 score cp 0 time 17696 nodes 61743103 nps 3489099 pv g1f3 g8f6 e2e3 b8c6 b1c3 d7d6 d2d4 e7e5
info depth 8 score cp 0 time 45000 nodes 156903437 nps 3486743 pv g1f3 g8f6 e2e3 b8c6 b1c3 d7d6 d2d4 e7e5
bestmove g1f3



Score of AntaresCpp0.03 vs AntaresCpp0.02: 80 - 9 - 62 [0.735]
...      AntaresCpp0.03 playing White: 45 - 3 - 28  [0.776] 76
...      AntaresCpp0.03 playing Black: 35 - 6 - 34  [0.693] 75
...      White vs Black: 51 - 38 - 62  [0.543] 151
Elo difference: 177.3 +/- 43.5, LOS: 100.0 %, DrawRatio: 41.1 %

Score of AntaresCpp0.03 vs SebLagueEngine0.1: 34 - 30 - 36 [0.520]
...      AntaresCpp0.03 playing White: 18 - 13 - 19  [0.550] 50
...      AntaresCpp0.03 playing Black: 16 - 17 - 17  [0.490] 50
...      White vs Black: 35 - 29 - 36  [0.530] 100
Elo difference: 13.9 +/- 54.9, LOS: 69.1 %, DrawRatio: 36.0 %



Quiescence Search Move Ordering
info depth 1 score cp 58 time 0 nodes 21 nps 210000 pv b1c3
info depth 2 score cp 0 time 1 nodes 157 nps 157000 pv b1c3 b8c6
info depth 3 score cp 58 time 2 nodes 2176 nps 1088000 pv b1c3 b8c6 g1f3
info depth 4 score cp 0 time 6 nodes 15135 nps 2522500 pv g1f3 g8f6 b1c3 b8c6
info depth 5 score cp 41 time 20 nodes 78230 nps 3911500 pv g1f3 b8c6 d2d4 g8f6 b1c3
info depth 6 score cp 0 time 167 nodes 607033 nps 3634928 pv g1f3 d7d5 b1c3 b8c6 e2e4 g8f6
info depth 7 score cp 30 time 2349 nodes 9543601 nps 4062835 pv e2e4 b8c6 g1f3 g8f6 e4e5 f6e4 b1c3
info depth 8 score cp 0 time 19282 nodes 71098146 nps 3687280 pv d2d4 g8f6 e2e3 d7d5 b1c3 b8c6 g1f3 c8f5
info depth 8 score cp 0 time 44999 nodes 152193051 nps 3382142 pv d2d4 g8f6 e2e3 d7d5 b1c3 b8c6 g1f3 c8f5
bestmove d2d4

Score of AntaresCpp0.04 vs AntaresCpp0.03: 60 - 35 - 105 [0.563]
...      AntaresCpp0.04 playing White: 32 - 16 - 52  [0.580] 100
...      AntaresCpp0.04 playing Black: 28 - 19 - 53  [0.545] 100
...      White vs Black: 51 - 44 - 105  [0.517] 200
Elo difference: 43.7 +/- 33.2, LOS: 99.5 %, DrawRatio: 52.5 %

Score of AntaresCpp0.04 vs SebLagueEngine0.1: 60 - 29 - 61 [0.603]
...      AntaresCpp0.04 playing White: 25 - 16 - 34  [0.560] 75
...      AntaresCpp0.04 playing Black: 35 - 13 - 27  [0.647] 75
...      White vs Black: 38 - 51 - 61  [0.457] 150
Elo difference: 72.9 +/- 43.3, LOS: 99.9 %, DrawRatio: 40.7 %



Killer move ordering
info depth 1 score cp 58 time 0 nodes 21 nps 210000 pv b1c3
info depth 2 score cp 0 time 2 nodes 157 nps 78500 pv b1c3 b8c6
info depth 3 score cp 58 time 4 nodes 975 nps 243750 pv b1c3 b8c6 g1f3
info depth 4 score cp 0 time 6 nodes 3446 nps 574333 pv g1f3 b8c6 b1c3 g8f6
info depth 5 score cp 41 time 12 nodes 23106 nps 1925500 pv g1f3 b8c6 b1c3 g8f6 e2e4
info depth 6 score cp 0 time 52 nodes 155748 nps 2995153 pv e2e4 b8c6 b1c3 g8f6 g1f3 e7e5
info depth 7 score cp 30 time 233 nodes 837200 nps 3593133 pv e2e4 b8c6 g1f3 g8f6 e4e5 f6e4 b1c3
info depth 8 score cp 0 time 2009 nodes 6416736 nps 3193995 pv b1c3 b8c6 g1f3 g8f6 e2e3 d7d6 d2d4 e7e5
info depth 9 score cp 27 time 11604 nodes 38981072 nps 3359278 pv e2e4 e7e5 f1c4 b8c6 g1e2 g8f6 b1c3 f8c5 e1g1
info depth 9 score cp 27 time 44999 nodes 144943108 nps 3221029 pv e2e4 e7e5 f1c4 b8c6 g1e2 g8f6 b1c3 f8c5 e1g1
bestmove e2e4

Score of AntaresCpp0.05 vs AntaresCpp0.04: 41 - 22 - 87 [0.563]
...      AntaresCpp0.05 playing White: 28 - 11 - 36  [0.613] 75
...      AntaresCpp0.05 playing Black: 13 - 11 - 51  [0.513] 75
...      White vs Black: 39 - 24 - 87  [0.550] 150
Elo difference: 44.2 +/- 36.0, LOS: 99.2 %, DrawRatio: 58.0 %
150 of 150 games finished.

Score of AntaresCpp0.05 vs SebLagueEngine0.1: 45 - 6 - 49 [0.695]
...      AntaresCpp0.05 playing White: 22 - 6 - 22  [0.660] 50
...      AntaresCpp0.05 playing Black: 23 - 0 - 27  [0.730] 50
...      White vs Black: 22 - 29 - 49  [0.465] 100
Elo difference: 143.1 +/- 48.4, LOS: 100.0 %, DrawRatio: 49.0 %
100 of 100 games finished.

 Score of AntaresCpp0.05 vs Lynx0.11.0: 65 - 9 - 26 [0.780]
...      AntaresCpp0.05 playing White: 31 - 4 - 15  [0.770] 50
...      AntaresCpp0.05 playing Black: 34 - 5 - 11  [0.790] 50
...      White vs Black: 36 - 38 - 26  [0.490] 100
Elo difference: 219.9 +/- 66.2, LOS: 100.0 %, DrawRatio: 26.0 %
100 of 100 games finished.

Score of AntaresCpp0.05 vs Vice1.0: 11 - 65 - 24 [0.230]
...      AntaresCpp0.05 playing White: 4 - 31 - 15  [0.230] 50
...      AntaresCpp0.05 playing Black: 7 - 34 - 9  [0.230] 50
...      White vs Black: 38 - 38 - 24  [0.500] 100
Elo difference: -209.9 +/- 67.2, LOS: 0.0 %, DrawRatio: 24.0 %
100 of 100 games finished.
*/

