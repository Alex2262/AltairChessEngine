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
#include "move.h"
#include "useful.h"

static double LMR_REDUCTIONS[2][TOTAL_MAX_DEPTH][64];

void initialize_lmr_reductions() {
    for (PLY_TYPE depth = 0; depth < TOTAL_MAX_DEPTH; depth++) {
        for (int moves = 0; moves < 64; moves++) {
            LMR_REDUCTIONS[1][depth][moves] = std::max(0.0, std::log(depth) * std::log(moves) / 3.00 + 0.5);
            LMR_REDUCTIONS[1][depth][moves] = std::max(0.0, std::log(depth) * std::log(moves) / 1.75 + 1.5);
        }
    }
}



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

    current_search_depth = 0;
    search_ply = 0;

    std::memset(pv_length, 0, sizeof(pv_length));
    std::memset(pv_table, 0, sizeof(pv_table));

    std::memset(killer_moves, 0, sizeof(killer_moves));
    std::memset(history_moves, 0, sizeof(history_moves));
    std::memset(counter_moves, 0, sizeof(counter_moves));
}


void Engine::new_game() {
    reset();

    std::memset(repetition_table, 0, sizeof(repetition_table));
    clear_tt();

    game_ply = 0;
    fifty_move = 0;
}


bool Engine::detect_repetition() {

    for (int i = game_ply - 2; i >= game_ply - fifty_move; i--) {
        if (repetition_table[i] == repetition_table[game_ply]) {
            return true;
        }
    }

    return false;
}


SCORE_TYPE Engine::probe_tt_entry(HASH_TYPE hash_key, SCORE_TYPE alpha, SCORE_TYPE beta, PLY_TYPE depth) {
    TT_Entry& tt_entry = transposition_table[hash_key % MAX_TT_SIZE];

    if (tt_entry.key == hash_key) {
        if (tt_entry.depth >= depth) {
            if (tt_entry.flag == HASH_FLAG_EXACT) return tt_entry.score;
            if (tt_entry.flag == HASH_FLAG_ALPHA && tt_entry.score <= alpha) return tt_entry.score;
            if (tt_entry.flag == HASH_FLAG_BETA && tt_entry.score >= beta) return tt_entry.score;
        }

        return USE_HASH_MOVE + tt_entry.move;
    }

    return NO_HASH_ENTRY;
}

void Engine::record_tt_entry(HASH_TYPE hash_key, SCORE_TYPE score, short tt_flag, MOVE_TYPE move, PLY_TYPE depth,
                             SCORE_TYPE static_eval) {

    TT_Entry& tt_entry = transposition_table[hash_key % MAX_TT_SIZE];

    if (tt_entry.key != hash_key || depth > tt_entry.depth || tt_flag == HASH_FLAG_EXACT) {
        tt_entry.key = hash_key;
        tt_entry.depth = depth;
        tt_entry.flag = tt_flag;
        tt_entry.score = score;
        tt_entry.evaluation = static_eval;
        tt_entry.move = move;
    }
}


SCORE_TYPE Engine::probe_tt_entry_q(HASH_TYPE hash_key, SCORE_TYPE alpha, SCORE_TYPE beta) {
    TT_Entry& tt_entry = transposition_table[hash_key % MAX_TT_SIZE];

    if (tt_entry.key == hash_key) {

        if (tt_entry.flag == HASH_FLAG_EXACT) return tt_entry.score;
        if (tt_entry.flag == HASH_FLAG_ALPHA && tt_entry.score <= alpha) return tt_entry.score;
        if (tt_entry.flag == HASH_FLAG_BETA && tt_entry.score >= beta) return tt_entry.score;


        return USE_HASH_MOVE + tt_entry.move;
    }

    return NO_HASH_ENTRY;
}


void Engine::record_tt_entry_q(HASH_TYPE hash_key, SCORE_TYPE score, short tt_flag, MOVE_TYPE move,
                               SCORE_TYPE static_eval) {
    TT_Entry& tt_entry = transposition_table[hash_key % MAX_TT_SIZE];

    if (tt_entry.key != hash_key || tt_flag == HASH_FLAG_EXACT) {
        tt_entry.key = hash_key;
        tt_entry.depth = -1;
        tt_entry.flag = tt_flag;
        tt_entry.score = score;
        tt_entry.evaluation = static_eval;
        tt_entry.move = move;
    }
}


SCORE_TYPE Engine::probe_tt_evaluation(HASH_TYPE hash_key) {
    TT_Entry& tt_entry = transposition_table[hash_key % MAX_TT_SIZE];

    if (tt_entry.key == hash_key && tt_entry.evaluation != NO_EVALUATION) return tt_entry.evaluation;
    return NO_EVALUATION;
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

    SCORE_TYPE tt_value = engine.probe_tt_entry_q(position.hash_key, alpha, beta);
    MOVE_TYPE tt_move = NO_MOVE;

    // When the tt_value is below NO_HASH_ENTRY, there is a score to return that we can use
    if (tt_value < NO_HASH_ENTRY) {
        if (!engine.search_ply) {
            MOVE_TYPE move = engine.transposition_table[position.hash_key % MAX_TT_SIZE].move;
            engine.pv_table[0][0] = move;
            engine.pv_length[0] = 1;
        }

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

    position.get_pseudo_legal_captures(engine.search_ply);
    get_capture_scores(position.moves[engine.search_ply], position.move_scores[engine.search_ply], tt_move);

    SCORE_TYPE best_score = static_eval;
    MOVE_TYPE best_move = NO_MOVE;

    for (int move_index = 0; move_index < position.moves[engine.search_ply].size(); move_index++) {

        sort_next_move(position.moves[engine.search_ply], position.move_scores[engine.search_ply], move_index);
        MOVE_TYPE move = position.moves[engine.search_ply][move_index];

        // Delta / Futility pruning
        // If the piece we capture plus a margin cannot even improve our score then
        // there is no point in searching it
        if (static_eval + PIECE_VALUES_MID[get_occupied(move) % BLACK_PAWN] + 220 < alpha) continue;

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

    engine.record_tt_entry_q(position.hash_key, best_score, tt_hash_flag, best_move, static_eval);

    return best_score;
}


SCORE_TYPE negamax(Engine& engine, Position& position, SCORE_TYPE alpha, SCORE_TYPE beta, PLY_TYPE depth, bool do_null) {

    // Initialize PV length
    engine.pv_length[engine.search_ply] = engine.search_ply;

    // Detect repetitions and fifty move rule
    if (engine.search_ply && (engine.fifty_move >= 100 || engine.detect_repetition())) return 0;

    // Start quiescence search at the end of regular negamax search to counter the horizon effect.
    if (depth == 0) {
        return qsearch(engine, position, alpha, beta, engine.max_q_depth);
    }

    engine.node_count++;

    bool in_check = position.is_attacked(position.king_positions[position.side]);
    if (in_check) depth++;  // Check extension

    // Get a value from probe_tt_entry that will correspond to either returning a score immediately
    // or returning no hash entry, or returning move int to sort
    SCORE_TYPE tt_value = engine.probe_tt_entry(position.hash_key, alpha, beta, depth);
    MOVE_TYPE tt_move = NO_MOVE;

    // When the tt_value is below NO_HASH_ENTRY, there is a score to return that we can use
    if (tt_value < NO_HASH_ENTRY) {
        if (!engine.search_ply) {
            MOVE_TYPE move = engine.transposition_table[position.hash_key % MAX_TT_SIZE].move;
            engine.pv_table[0][0] = move;
            engine.pv_length[0] = 1;
        }

        return tt_value;
    }

    // When the tt_value is above a bound (USE_HASH_MOVE), the function tells us to use the
    // tt_entry move for move ordering
    else if (tt_value > USE_HASH_MOVE) tt_move = tt_value - USE_HASH_MOVE;

    // Variable to record the hash flag
    short tt_hash_flag = HASH_FLAG_ALPHA;

    // Hack to determine pv_node, because when it is not a pv node we are being searched by
    // a zero window with alpha == beta - 1
    bool pv_node = alpha != beta - 1;

    SCORE_TYPE static_eval = engine.probe_tt_evaluation(position.hash_key);

    // Reverse Futility Pruning
    if (depth <= 2 && !in_check && !pv_node) {
        if (static_eval == NO_EVALUATION) static_eval = evaluate(position);
        if (static_eval - 160 * depth >= beta) return static_eval;
    }

    // Null move pruning
    // We give the opponent an extra move and if they are not able to make their position
    // any better, then our position is too good, and we don't need to search any deeper.
    if (depth >= 3 && do_null && !in_check && !pv_node) {
        // Adaptive NMP
        // depth 3 == 2
        // depth 8 == 3
        // depth 13 == 4
        // depth 18 == 5

        int reduction = (depth + 2)/5 + 1;

        position.make_null_move(engine.search_ply, engine.fifty_move);

        engine.search_ply++;
        engine.game_ply++;

        // zero window search with reduced depth
        SCORE_TYPE return_eval = -negamax(engine, position, -beta, -beta + 1, depth - 1 - reduction, false);

        engine.game_ply--;
        engine.search_ply--;
        position.undo_null_move(engine.search_ply, engine.fifty_move);

        if (return_eval >= beta) return beta;

    }

    int legal_moves = 0;
    MOVE_TYPE last_move = engine.search_ply ? position.undo_move_stack[engine.search_ply - 1].move : NO_MOVE;

    // Retrieving the pseudo legal moves in the current position as a list of integers
    // Score the moves
    position.get_pseudo_legal_moves(engine.search_ply);
    get_move_scores(engine, position.moves[engine.search_ply], position.move_scores[engine.search_ply],
                    tt_move, last_move);

    // Best score for fail soft, and best move for tt
    SCORE_TYPE best_score = -SCORE_INF;
    MOVE_TYPE best_move = NO_MOVE;

    // Iterate through moves and recursively search with Negamax
    for (int move_index = 0; move_index < position.moves[engine.search_ply].size(); move_index++) {

        // Sort the next move. If an early move causes a cutoff then we have saved time
        // by only sorting one or a few moves rather than the whole list.
        sort_next_move(position.moves[engine.search_ply], position.move_scores[engine.search_ply], move_index);
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

        SCORE_TYPE return_eval;
        double reduction = 0;

        bool quiet = !get_is_capture(move);
        bool is_killer_move = move == engine.killer_moves[0][engine.search_ply - 1] ||
                              move == engine.killer_moves[1][engine.search_ply - 1];

        bool full_depth_zero_window;

        // Late Move Reductions
        // The idea that if moves are ordered well, then moves that are searched
        // later shouldn't be as good, and therefore we don't need to search them to a very high depth
        if (legal_moves >= 2
                && ((engine.search_ply && !pv_node) || legal_moves >= 4)
                && depth >= 3
                && !in_check
                && get_move_type(move) == 0
                ){

            reduction = LMR_REDUCTIONS[quiet][depth][legal_moves];

            reduction -= pv_node;

            reduction -= is_killer_move;

            reduction -= engine.history_moves[get_selected(move)][MAILBOX_TO_STANDARD[get_target_square(move)]]
                    / 20000.0;

            reduction += quiet && get_is_capture(tt_move);

            reduction = static_cast<PLY_TYPE>(std::min(depth - 2, std::max(0, static_cast<int>(reduction))));

            return_eval = -negamax(engine, position, -alpha - 1, -alpha, depth - reduction - 1, true);

            full_depth_zero_window = return_eval > alpha && reduction;
        }

        else {
            full_depth_zero_window = !pv_node || legal_moves >= 1;
        }

        // Principle Variation Search
        // We assume that the first move should be the principle variation / best move, so the rest of the moves
        // should be searched with a zero window

        if (full_depth_zero_window)
            return_eval = -negamax(engine, position, -alpha - 1, -alpha, depth - 1, true);

        if (pv_node && ((return_eval > alpha && return_eval < beta) || legal_moves == 0))
            return_eval = -negamax(engine, position, -beta, -alpha, depth - 1, true);

        position.side ^= 1;
        engine.game_ply--;
        engine.search_ply--;

        position.undo_move(move, engine.search_ply, engine.fifty_move);

        if (engine.stopped) return 0;

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

                // History Heuristic for move ordering
                if (!get_is_capture(move)) {
                    engine.history_moves[get_selected(move)][MAILBOX_TO_STANDARD[get_target_square(move)]]
                                         += depth * depth;
                }

                // Alpha - Beta cutoff. This is a 'cut node' and we have failed high
                if (return_eval >= beta) {
                    // Killer Heuristic for move ordering
                    if (!get_is_capture(move)) {
                        engine.killer_moves[1][engine.search_ply] = engine.killer_moves[0][engine.search_ply];
                        engine.killer_moves[0][engine.search_ply] = move;

                        if (last_move != NO_MOVE)
                            engine.counter_moves[get_selected(last_move)]
                                                [MAILBOX_TO_STANDARD[get_target_square(last_move)]] = move;
                    }
                    // Do not save mate scores into TT because of bugs
                    if (-MATE_SCORE < best_score && best_score < MATE_SCORE) {
                        engine.record_tt_entry(position.hash_key, best_score, HASH_FLAG_BETA, best_move, depth,
                                               static_eval);
                    }
                    return best_score;
                }
            }
        }

        legal_moves++;
    }

    if (legal_moves == 0 && !in_check) return 0;
    else if (legal_moves == 0) return -MATE_SCORE - depth;

    if (-MATE_SCORE < best_score && best_score < MATE_SCORE) {
        engine.record_tt_entry(position.hash_key, best_score, tt_hash_flag, best_move, depth, static_eval);
    }

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
        SCORE_TYPE return_eval = negamax(engine, position, alpha, beta, running_depth, false);

        std::string pv_line;
        for (int c = 0; c < engine.pv_length[0]; c++) {
            pv_line += get_uci_from_move(engine.pv_table[0][c]);
            pv_line += " ";
            position.side ^= 1;
        }

        position.side = original_side;

        if (!engine.stopped) {
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

        if (engine.stopped || running_depth == engine.max_depth - 1) {
            std::cout << "bestmove " << split(best_pv, ' ')[0] << std::endl;
            break;
        }

        running_depth++;
    }
}


