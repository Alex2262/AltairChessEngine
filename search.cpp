//
// Created by Alex Tian on 9/22/2022.
//

#include "search.h"
#include "move_generator.h"
#include "evaluation.h"
#include "move.h"
#include <chrono>
#include <iostream>


SCORE_TYPE negamax(Engine& engine, Position& position, SCORE_TYPE alpha, SCORE_TYPE beta, PLY_TYPE depth) {

    engine.pv_length[engine.search_ply] = engine.search_ply;
    engine.node_count += 1;

    if (depth == 0) {
        return evaluate(position);
    }

    if (engine.node_count % 1000 == 0) {
        auto time = std::chrono::high_resolution_clock::now();
        long current_time = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::time_point_cast<std::chrono::milliseconds>(time).time_since_epoch()).count();

        if (current_time - engine.start_time >= engine.max_time) engine.stopped = true;
    }

    if (engine.stopped) return 0;

    bool in_check = position.is_attacked(position.king_positions[position.side]);

    std::vector<MOVE_TYPE> moves = get_pseudo_legal_moves(position);

    SQUARE_TYPE current_ep_square = position.ep_square;
    uint16_t current_castle_ability_bits = position.castle_ability_bits;
    uint64_t current_hash_key = position.hash_key;

    int legal_moves = 0;

    SCORE_TYPE best_score = -SCORE_INF;
    // MOVE_TYPE best_move = NO_MOVE;

    for (MOVE_TYPE move : moves) {

        bool attempt = position.make_move(move);

        if (!attempt) {
            position.undo_move(move, current_ep_square, current_castle_ability_bits, current_hash_key);
            continue;
        }

        engine.search_ply += 1;
        position.side ^= 1;

        SCORE_TYPE return_eval = -negamax(engine, position, -beta, -alpha, depth - 1);

        position.side ^= 1;
        engine.search_ply -= 1;
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

        auto end_time = std::chrono::high_resolution_clock::now();

        auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(end_time
                                                                                                        - start_time);
        double elapsed_time = ms_int.count();
        if (elapsed_time == 0) elapsed_time = 0.1;

        std::cout << "info depth " << running_depth << " score cp " << best_score << " time " << int(elapsed_time)
                  << " nodes " << engine.node_count << " nps " << int(engine.node_count / (elapsed_time / 1000))
                  << " pv " << best_pv << std::endl;

        if (engine.stopped) break;

        running_depth++;
    }
}