
//
// Created by Alex Tian on 9/22/2022.
//

#include <chrono>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cassert>
#include "search.h"
#include "evaluation.h"
#include "evaluation_constants.h"
#include "move.h"
#include "useful.h"
#include "see.h"


void Engine::clear_tt() {
    for (TT_Entry& tt_entry : transposition_table) {
        tt_entry.key = 0;
        tt_entry.score = 0;
        tt_entry.evaluation = NO_EVALUATION;
        tt_entry.move = NO_MOVE;
        tt_entry.depth = 0;
        tt_entry.flag = 0;
    }
}


void Engine::reset() {
    node_count = 0;
    selective_depth = 0;
    current_search_depth = 0;
    search_ply = 0;

    std::memset(pv_length, 0, sizeof(pv_length));
    std::memset(pv_table, 0, sizeof(pv_table));

    std::memset(killer_moves, 0, sizeof(killer_moves));
    //std::memset(history_moves, 0, sizeof(history_moves));
    //std::memset(capture_history, 0, sizeof(capture_history));
    std::memset(continuation_history, 0, sizeof(continuation_history));

    if (show_stats) {
        search_results.alpha_raised_count = 0;
        std::memset(search_results.qsearch_fail_highs, 0, sizeof(search_results.qsearch_fail_highs));
        std::memset(search_results.search_fail_highs, 0, sizeof(search_results.search_fail_highs));
        std::memset(search_results.search_fail_high_types, 0, sizeof(search_results.search_fail_high_types));
    }
}


void Engine::new_game() {
    reset();

    std::memset(repetition_table, 0, sizeof(repetition_table));
    std::memset(pv_length, 0, sizeof(pv_length));
    std::memset(pv_table, 0, sizeof(pv_table));

    std::memset(killer_moves, 0, sizeof(killer_moves));
    std::memset(history_moves, 0, sizeof(history_moves));
    std::memset(capture_history, 0, sizeof(capture_history));
    std::memset(continuation_history, 0, sizeof(continuation_history));
    clear_tt();

    game_ply = 0;
    fifty_move = 0;

    stopped = true;
}


bool Engine::detect_repetition() {

    for (int i = game_ply - 2; i >= game_ply - fifty_move; i--) {
        if (repetition_table[i] == repetition_table[game_ply]) {
            return true;
        }
    }

    return false;
}


short Engine::probe_tt_entry(HASH_TYPE hash_key, SCORE_TYPE alpha, SCORE_TYPE beta, PLY_TYPE depth,
                             TT_Entry& return_entry) {
    TT_Entry& tt_entry = transposition_table[hash_key % transposition_table.size()];

    if (tt_entry.key == hash_key) {
        return_entry.move = tt_entry.move;
        return_entry.depth = tt_entry.depth;
        return_entry.flag = tt_entry.flag;

        return_entry.score = tt_entry.score;
        if (return_entry.score < -MATE_BOUND) return_entry.score += search_ply;
        else if (return_entry.score > MATE_BOUND) return_entry.score -= search_ply;

        if (tt_entry.depth >= depth) {

            if (tt_entry.flag == HASH_FLAG_EXACT) return RETURN_HASH_SCORE;
            if (tt_entry.flag == HASH_FLAG_ALPHA && return_entry.score <= alpha) return RETURN_HASH_SCORE;
            if (tt_entry.flag == HASH_FLAG_BETA && return_entry.score >= beta) return RETURN_HASH_SCORE;
        }

        return USE_HASH_MOVE;
    }

    return NO_HASH_ENTRY;
}

void Engine::record_tt_entry(HASH_TYPE hash_key, SCORE_TYPE score, short tt_flag, MOVE_TYPE move, PLY_TYPE depth,
                             SCORE_TYPE static_eval) {

    TT_Entry& tt_entry = transposition_table[hash_key % transposition_table.size()];

    if (score < -MATE_BOUND) score -= search_ply;
    else if (score > MATE_BOUND) score += search_ply;

    if (tt_entry.key != hash_key || depth + 2 > tt_entry.depth || tt_flag == HASH_FLAG_EXACT) {
        tt_entry.key = hash_key;
        tt_entry.depth = depth;
        tt_entry.flag = tt_flag;
        tt_entry.score = score;
        tt_entry.evaluation = static_eval;
        tt_entry.move = move;
    }
}


short Engine::probe_tt_entry_q(HASH_TYPE hash_key, SCORE_TYPE alpha, SCORE_TYPE beta,
                               SCORE_TYPE& return_score, MOVE_TYPE& tt_move) {
    TT_Entry& tt_entry = transposition_table[hash_key % transposition_table.size()];

    if (tt_entry.key == hash_key) {
        tt_move = tt_entry.move;

        return_score = tt_entry.score;
        if (return_score < -MATE_BOUND) return_score += search_ply;
        else if (return_score > MATE_BOUND) return_score -= search_ply;

        if (tt_entry.flag == HASH_FLAG_EXACT) return RETURN_HASH_SCORE;
        if (tt_entry.flag == HASH_FLAG_ALPHA && return_score <= alpha) return RETURN_HASH_SCORE;
        if (tt_entry.flag == HASH_FLAG_BETA && return_score >= beta) return RETURN_HASH_SCORE;


        return USE_HASH_MOVE;
    }

    return NO_HASH_ENTRY;
}


void Engine::record_tt_entry_q(HASH_TYPE hash_key, SCORE_TYPE score, short tt_flag, MOVE_TYPE move,
                               SCORE_TYPE static_eval) {
    TT_Entry& tt_entry = transposition_table[hash_key % transposition_table.size()];

    if (score < -MATE_BOUND) score -= search_ply;
    else if (score > MATE_BOUND) score += search_ply;

    if (tt_entry.key != hash_key || tt_flag == HASH_FLAG_EXACT) { // TODO: try doing || depth == -1 for always replace in qs.
        tt_entry.key = hash_key;
        tt_entry.depth = -1;
        tt_entry.flag = tt_flag;
        tt_entry.score = score;
        tt_entry.evaluation = static_eval;
        tt_entry.move = move;
    }
}


SCORE_TYPE Engine::probe_tt_evaluation(HASH_TYPE hash_key) {
    TT_Entry& tt_entry = transposition_table[hash_key % transposition_table.size()];

    if (tt_entry.key == hash_key && tt_entry.evaluation != NO_EVALUATION) return tt_entry.evaluation;
    return NO_EVALUATION;
}

void Engine::tt_prefetch_read(HASH_TYPE hash_key) {
    __builtin_prefetch(&transposition_table[hash_key % transposition_table.size()]);
}

void Engine::tt_prefetch_write(HASH_TYPE hash_key) {
    __builtin_prefetch(&transposition_table[hash_key % transposition_table.size()], 1);
}


SCORE_TYPE qsearch(Engine& engine, Position& position, SCORE_TYPE alpha, SCORE_TYPE beta, PLY_TYPE depth) {

    engine.tt_prefetch_read(position.hash_key);

    // position.print_board();
    engine.node_count++;
    // engine.selective_depth = std::max(engine.search_ply, engine.selective_depth);

    // Check time and max nodes
    if (engine.current_search_depth >= engine.min_depth && (engine.node_count & 2047) == 0 ) {
        auto time = std::chrono::high_resolution_clock::now();
        uint64_t current_time = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::time_point_cast<std::chrono::milliseconds>(time).time_since_epoch()).count();

        if (current_time - engine.start_time >= engine.hard_time_limit) {
            engine.stopped = true;
        }
    }

    if (engine.max_nodes && engine.node_count >= engine.max_nodes) engine.stopped = true;

    SCORE_TYPE tt_value = 0;
    MOVE_TYPE tt_move = NO_MOVE;
    short tt_return_type = engine.probe_tt_entry_q(position.hash_key, alpha, beta, tt_value, tt_move);

    if (tt_return_type == RETURN_HASH_SCORE) {
        return tt_value;
    }

    // When the tt_value is above a bound (USE_HASH_MOVE), the function tells us to use the
    // tt_entry move for move ordering
    else if (tt_value > USE_HASH_MOVE) tt_move = tt_value - USE_HASH_MOVE;

    SCORE_TYPE static_eval = engine.probe_tt_evaluation(position.hash_key);
    if (static_eval == NO_EVALUATION) static_eval = evaluate(position);
    // SCORE_TYPE static_eval = evaluate(position);

    if (depth == 0 || static_eval >= beta) return static_eval;

    // Variable to record the hash flag
    short tt_hash_flag = HASH_FLAG_ALPHA;

    alpha = (static_eval > alpha) ? static_eval : alpha;

    // Set values for State
    position.set_state(engine.search_ply, engine.fifty_move);
    position.state_stack[engine.search_ply].evaluation = static_eval;

    position.get_pseudo_legal_captures(engine.search_ply);

    SCORE_TYPE best_score = static_eval;
    MOVE_TYPE best_move = NO_MOVE;

    int legal_moves = 0;
    for (int move_index = 0; move_index < static_cast<int>(position.moves[engine.search_ply].size()); move_index++) {

        MOVE_TYPE move = position.moves[engine.search_ply][move_index];

        bool attempt = position.make_move(move, engine.search_ply, engine.fifty_move);

        if (!attempt) {
            position.undo_move(move, engine.search_ply, engine.fifty_move);
            continue;
        }

        engine.search_ply++;
        position.side ^= 1;

        SCORE_TYPE return_eval = -qsearch(engine, position, -beta, -alpha, depth - 1);

        position.side ^= 1;
        engine.search_ply--;

        position.undo_move(move, engine.search_ply, engine.fifty_move);

        if (engine.stopped) return 0;

        legal_moves++;

        if (return_eval > best_score) {
            best_score = return_eval;
            best_move = move;

            if (return_eval > alpha) {
                alpha = return_eval;
                tt_hash_flag = HASH_FLAG_EXACT;

                if (return_eval >= beta) {
                    engine.record_tt_entry_q(position.hash_key, best_score, HASH_FLAG_BETA, best_move, static_eval  );
                    return best_score;
                }
            }
        }

    }

    engine.tt_prefetch_write(position.hash_key);
    engine.record_tt_entry_q(position.hash_key, best_score, tt_hash_flag, best_move, static_eval);

    return best_score;
}


SCORE_TYPE negamax(Engine& engine, Position& position, SCORE_TYPE alpha, SCORE_TYPE beta, PLY_TYPE depth) {

    engine.tt_prefetch_read(position.hash_key);

    // Initialize PV length
    engine.pv_length[engine.search_ply] = engine.search_ply;
    engine.selective_depth = std::max(engine.search_ply, engine.selective_depth);

    bool root = !engine.search_ply;

    // Early search exits
    if (!root) {

        if (engine.search_ply >= MAX_AB_DEPTH - 1) return evaluate(position);

        // Detect repetitions and fifty move rule
        if (engine.fifty_move >= 100 || engine.detect_repetition()) return 3 - static_cast<int>(engine.node_count & 8);
    }

    // Start quiescence search at the start of regular negamax search to counter the horizon effect.
    if (depth <= 0) {
        return qsearch(engine, position, alpha, beta, engine.max_q_depth);
    }

    // Increase node count
    engine.node_count++;

    // Set values for State
    position.set_state(engine.search_ply, engine.fifty_move);

    // TT probing
    TT_Entry tt_entry{};
    short tt_return_type = engine.probe_tt_entry(position.hash_key, alpha, beta, depth, tt_entry);

    SCORE_TYPE tt_value = tt_entry.score;
    MOVE_TYPE tt_move = tt_entry.move;

    // We are allowed to return the hash score
    if (tt_return_type == RETURN_HASH_SCORE && !root) {
        bool return_tt_value = true;

        // We have to check if there's a repetition before returning a score
        if (tt_move) {
            position.make_move(tt_move, engine.search_ply, engine.fifty_move);

            engine.search_ply++;
            engine.fifty_move++;
            engine.game_ply++;
            engine.repetition_table[engine.game_ply] = position.hash_key;
            position.side ^= 1;

            if (engine.fifty_move >= 100 || engine.detect_repetition()) return_tt_value = false;

            position.side ^= 1;
            engine.game_ply--;
            engine.search_ply--;

            position.undo_move(tt_move, engine.search_ply, engine.fifty_move);
        }
        else return_tt_value = false;

        if (return_tt_value) {
            return tt_value;
        }
    }

    // Variable to record the hash flag
    short tt_hash_flag = HASH_FLAG_ALPHA;

    int legal_moves = 0;

    // Retrieving the pseudo legal moves in the current position as a list of integers
    // Score the moves
    position.get_pseudo_legal_moves(engine.search_ply);

    // Best score for fail soft, and best move for tt
    SCORE_TYPE best_score = -SCORE_INF;
    MOVE_TYPE best_move = NO_MOVE;

    // Iterate through moves and recursively search with Negamax
    for (int move_index = 0; move_index < static_cast<int>(position.moves[engine.search_ply].size()); move_index++) {

        MOVE_TYPE move = position.moves[engine.search_ply][move_index];

        // Make the move
        bool attempt = position.make_move(move, engine.search_ply, engine.fifty_move);

        // The move put us in check, therefore it was not legal, and we must disregard it
        if (!attempt) {
            position.undo_move(move, engine.search_ply, engine.fifty_move);
            continue;
        }

        engine.search_ply++;
        engine.fifty_move++;
        engine.game_ply++;
        engine.repetition_table[engine.game_ply] = position.hash_key;
        position.side ^= 1;

        SCORE_TYPE return_eval = -negamax(engine, position, -beta, -alpha, depth - 1);

        position.side ^= 1;
        engine.game_ply--;
        engine.search_ply--;

        position.undo_move(move, engine.search_ply, engine.fifty_move);

        if (engine.stopped) return 0;

        // Update legal move count
        legal_moves++;

        // This move is better than other moves searched
        if (return_eval > best_score) {
            best_score = return_eval;
            best_move = move;

            // Write moves into PV table
            engine.pv_table[engine.search_ply][engine.search_ply] = move;
            for (int next_ply = engine.search_ply+1; next_ply < engine.pv_length[engine.search_ply+1]; next_ply++) {
                engine.pv_table[engine.search_ply][next_ply] = engine.pv_table[engine.search_ply + 1][next_ply];
            }

            engine.pv_length[engine.search_ply] = engine.pv_length[engine.search_ply + 1];

            if (return_eval > alpha) {
                alpha = return_eval;

                // We have found a better move that increased achieved us an exact score
                tt_hash_flag = HASH_FLAG_EXACT;

                // Alpha - Beta cutoff. We have failed high here.
                if (return_eval >= beta) {
                    tt_hash_flag = HASH_FLAG_BETA;
                    break;
                }
            }
        }
    }

    engine.tt_prefetch_write(position.hash_key);

    bool in_check;
    if (position.state_stack[engine.search_ply].in_check != -1) {
        in_check = static_cast<bool>(position.state_stack[engine.search_ply].in_check);
    } else {
        in_check = position.is_attacked(position.king_positions[position.side]);
    }

    if (legal_moves == 0 && !in_check) return 0;
    else if (legal_moves == 0) return -MATE_SCORE + engine.search_ply;


    engine.record_tt_entry(position.hash_key, best_score, tt_hash_flag, best_move, depth, NO_EVALUATION);

    return best_score;
}


void print_thinking(Engine& engine, Position& position, NodeType node, SCORE_TYPE best_score) {

    PLY_TYPE depth = engine.current_search_depth;

    // Calculate the elapsed time and NPS
    auto end_time = std::chrono::high_resolution_clock::now();
    auto end_int = std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::time_point_cast<std::chrono::milliseconds>(end_time).time_since_epoch()).count();

    uint64_t elapsed_time = end_int - engine.start_time;
    elapsed_time = std::max<uint64_t>(elapsed_time, 1);

    auto nps = static_cast<uint64_t>(static_cast<double>(engine.node_count) /
                                     (static_cast<double>(elapsed_time) / 1000.0));

    // Format the scores for printing to UCI
    SCORE_TYPE format_score = best_score;
    std::string result_type = "cp ";
    if (abs(best_score) >= MATE_BOUND) {
        result_type = "mate ";
        format_score = best_score >= MATE_BOUND ?
                       (MATE_SCORE - best_score) / 2 + 1: (-MATE_SCORE - best_score) / 2;
    }

    result_type += std::to_string(format_score);

    // Identify the type of node / bound if necessary
    if (node == Lower_Node) result_type += " lowerbound";
    else if (node == Upper_Node) result_type += " upperbound";

    // PV information
    std::string pv_line;

    // If the depth is low, or we are printing a PV line from a failed aspiration search,
    // then only store a limited number of moves in the PV line
    int max_pv_length = engine.pv_length[0];
    if (depth <= 12 || node == Lower_Node || node == Upper_Node)
        max_pv_length = std::min(max_pv_length, 1 + max_pv_length / 3);

    // Get the PV line
    SQUARE_TYPE original_side = position.side;
    for (int c = 0; c < max_pv_length; c++) {
        pv_line += get_uci_from_move(engine.pv_table[0][c]);
        pv_line += " ";
        position.side ^= 1;
    }
    position.side = original_side;

    // Print the UCI search information
    std::cout << "info multipv 1 depth " << depth << " seldepth " << engine.selective_depth
              << " score " << result_type << " time " << elapsed_time
              << " nodes " << engine.node_count << " nps " << nps
              << " pv " << pv_line << std::endl;

}


void iterative_search(Engine& engine, Position& position) {

    // Reset certain information
    engine.stopped = false;
    engine.terminated = false;

    position.clear_movelist();
    engine.reset();

    // Initialize the start time
    auto start_time = std::chrono::high_resolution_clock::now();
    engine.start_time = std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::time_point_cast<std::chrono::milliseconds>(start_time).time_since_epoch()).count();

    // Initialize variables
    PLY_TYPE running_depth = 1;

    MOVE_TYPE best_move = NO_MOVE;

    while (running_depth <= engine.max_depth) {
        engine.current_search_depth = running_depth;

        // Run a search with aspiration window bounds
        SCORE_TYPE score = negamax(engine, position, -SCORE_INF, SCORE_INF, running_depth);

        // Store the best move when the engine has finished a search (it hasn't stopped in the middle of a search)
        if (!engine.stopped) {
            best_move = engine.pv_table[0][0];
            print_thinking(engine, position, Exact_Node, score);
        }

        // Calculate the elapsed time
        auto end_time = std::chrono::high_resolution_clock::now();
        auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(end_time
                                                                            - start_time);
        uint64_t elapsed_time = ms_int.count();
        elapsed_time = std::max<uint64_t>(elapsed_time, 1);

        // Stop the engine when we have exceeded the soft time limit
        if (running_depth >= engine.min_depth) {
            if (elapsed_time >= engine.soft_time_limit) engine.stopped = true;
        }

        // End the search when the engine has stopped running
        if (engine.stopped || running_depth == engine.max_depth) {
            break;
        }

        // Increase search depth
        running_depth++;
    }

    engine.search_results.depth_reached = running_depth;
    engine.search_results.node_count = engine.node_count;

    std::string best_move_str = get_uci_from_move(best_move);
    std::cout << "bestmove " << best_move_str << std::endl;

    engine.terminated = true;
}


void print_statistics(Search_Results& res) {


    std::cout << "------------------- SEARCH STATISTICS -------------------\n\n\n";

    std::cout << "Total Nodes Searched: " << res.node_count << "\n";
    std::cout << "Average Nodes Searched: " << res.node_count / res.num_searches << "\n\n";

    std::cout << "Average Branching Factor: " <<
              pow(res.node_count / res.num_searches, 1.0/res.depth_reached) << "\n\n";

    std::cout << "Average # of times alpha is raised per node: " <<
              static_cast<double>(res.alpha_raised_count) / static_cast<double>(res.node_count)
              << "\n\n";

    uint64_t search_total = 0;
    for (unsigned long long e : res.search_alpha_raises) {
        search_total += e;
    }

    for (int i = 0; i < ALPHA_RAISE_STATS_COUNT; i++) {
        uint64_t e = res.search_alpha_raises[i];
        std::cout << "search alpha raises at index " << i << ": " << double(e) / double(search_total) * 100 << "%" << std::endl;
    }

    std::cout << "\n";

    uint64_t qsearch_total = 0;
    search_total = 0;
    for (int i = 0; i < FAIL_HIGH_STATS_COUNT; i++) {
        uint64_t qe = res.qsearch_fail_highs[i];
        uint64_t e = res.search_fail_highs[i];
        qsearch_total += qe;
        search_total += e;
    }
    for (int i = 0; i < FAIL_HIGH_STATS_COUNT; i++) {
        uint64_t e = res.qsearch_fail_highs[i];
        std::cout << "q-search fail high at index " << i << ": " << double(e) / double(qsearch_total) * 100 << "%" << std::endl;
    }

    std::cout << "\n";

    for (int i = 0; i < FAIL_HIGH_STATS_COUNT; i++) {
        uint64_t e = res.search_fail_highs[i];
        std::cout << "search fail high at index " << i << ": " << double(e) / double(search_total) * 100 << "%" << std::endl;
    }

    std::cout << "\n";

    uint64_t total_fail_highs = 0;
    for (uint64_t e : res.search_fail_high_types) total_fail_highs += e;

    std::cout << "TT move fail highs: " << res.search_fail_high_types[0] << " percentage: " <<
              double(res.search_fail_high_types[0]) / double(total_fail_highs) * 100 << "%\n";
    std::cout << "Killer move 1 fail highs: " << res.search_fail_high_types[1] << " percentage: " <<
              double(res.search_fail_high_types[1]) / double(total_fail_highs) * 100 << "%\n";
    std::cout << "Killer move 2 fail highs: " << res.search_fail_high_types[2] << " percentage: " <<
              double(res.search_fail_high_types[2]) / double(total_fail_highs) * 100 << "%\n";
    std::cout << "Counter move fail highs: " << res.search_fail_high_types[3] << " percentage: " <<
              double(res.search_fail_high_types[3]) / double(total_fail_highs) * 100 << "%\n";
    std::cout << "Quiet move fail highs: " << res.search_fail_high_types[4] << " percentage: " <<
              double(res.search_fail_high_types[4]) / double(total_fail_highs) * 100 << "%\n";
    std::cout << "Noisy move fail highs: " << res.search_fail_high_types[5] << " percentage: " <<
              double(res.search_fail_high_types[5]) / double(total_fail_highs) * 100 << "%\n";

    std::cout << "\n\n---------------------------------------------------------" << std::endl;
}


void print_tuning_config(Tuning_Parameters& tuning_parameters) {
    std::cout << "{";
    for (auto & i : tuning_parameters.tuning_parameter_array) {
        std::cout << "\n\t\"" << i.name << "\": {"
                  << "\n\t\t\"value\": " << i.value
                  << ",\n\t\t\"min_value\": " << i.min
                  << ",\n\t\t\"max_value\": " << i.max
                  << ",\n\t\t\"step\": " << i.step
                  << "\n\t},"
                  << std::endl;
    }
    std::cout << "}" << std::endl;
}
