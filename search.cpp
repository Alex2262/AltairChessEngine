
//
// Created by Alex Tian on 9/22/2022.
//

#include <chrono>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <unordered_set>
#include "search.h"
#include "evaluation.h"
#include "move.h"
#include "useful.h"

static double LMR_REDUCTIONS[TOTAL_MAX_DEPTH][64];

void initialize_lmr_reductions() {
    for (PLY_TYPE depth = 0; depth < TOTAL_MAX_DEPTH; depth++) {
        for (int moves = 0; moves < 64; moves++) {
            LMR_REDUCTIONS[depth][moves] = std::max(0.0, std::log(depth) * std::log(moves) / 1.8 + 1.4);
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
    selective_depth = 0;
    current_search_depth = 0;
    search_ply = 0;

    std::memset(pv_length, 0, sizeof(pv_length));
    std::memset(pv_table, 0, sizeof(pv_table));

    std::memset(killer_moves, 0, sizeof(killer_moves));
    //std::memset(history_moves, 0, sizeof(history_moves));
    //std::memset(capture_history, 0, sizeof(capture_history));
    std::memset(counter_moves, 0, sizeof(counter_moves));
}


void Engine::new_game() {
    reset();

    std::memset(repetition_table, 0, sizeof(repetition_table));
    std::memset(pv_length, 0, sizeof(pv_length));
    std::memset(pv_table, 0, sizeof(pv_table));

    std::memset(killer_moves, 0, sizeof(killer_moves));
    std::memset(history_moves, 0, sizeof(history_moves));
    std::memset(capture_history, 0, sizeof(capture_history));
    std::memset(counter_moves, 0, sizeof(counter_moves));
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
                                  SCORE_TYPE& return_score, MOVE_TYPE& tt_move) {
    TT_Entry& tt_entry = transposition_table[hash_key % transposition_table.size()];

    if (tt_entry.key == hash_key) {
        tt_move = tt_entry.move;

        if (tt_entry.depth >= depth) {

            return_score = tt_entry.score;
            if (return_score < -MATE_BOUND) return_score += search_ply;
            else if (return_score > MATE_BOUND) return_score -= search_ply;

            if (tt_entry.flag == HASH_FLAG_EXACT) return RETURN_HASH_SCORE;
            if (tt_entry.flag == HASH_FLAG_ALPHA && return_score <= alpha) return RETURN_HASH_SCORE;
            if (tt_entry.flag == HASH_FLAG_BETA && return_score >= beta) return RETURN_HASH_SCORE;
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


void update_history_entry(SCORE_TYPE& score, SCORE_TYPE bonus) {
    score -= (score * abs(bonus)) / 324;
    score += bonus * 32;
}


SCORE_TYPE qsearch(Engine& engine, Position& position, SCORE_TYPE alpha, SCORE_TYPE beta, PLY_TYPE depth) {

    // position.print_board();
    engine.node_count++;
    // engine.selective_depth = std::max(engine.search_ply, engine.selective_depth);

    // Check time and max nodes
    if (engine.current_search_depth >= engine.min_depth && (engine.node_count & 2047) == 0 ) {
        auto time = std::chrono::high_resolution_clock::now();
        long current_time = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::time_point_cast<std::chrono::milliseconds>(time).time_since_epoch()).count();

        if (current_time - engine.start_time >= engine.hard_time_limit ||
            (engine.max_nodes && engine.node_count >= engine.max_nodes))
            engine.stopped = true;
    }

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
    position.set_state(engine.search_ply, engine.fifty_move, static_eval);

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
    engine.selective_depth = std::max(engine.search_ply, engine.selective_depth);

    bool root = !engine.search_ply;

    // Early search exits
    if (!root) {

        if (engine.search_ply >= MAX_AB_DEPTH - 1) return evaluate(position);

        // Detect repetitions and fifty move rule
        if (engine.fifty_move >= 100 || engine.detect_repetition()) return 0;

        // Mate Distance Pruning from CPW
        SCORE_TYPE mating_value = MATE_SCORE - engine.search_ply;
        if (mating_value < beta) {
            beta = mating_value;
            if (alpha >= mating_value) return mating_value;
        }
        mating_value = -MATE_SCORE + engine.search_ply;
        if (mating_value > alpha) {
            alpha = mating_value;
            if (beta <= mating_value) return mating_value;
        }

    }

    bool in_check = position.is_attacked(position.king_positions[position.side]);
    if (in_check) depth++;  // Check extension

    // Start quiescence search at the start of regular negamax search to counter the horizon effect.
    if (depth <= 0) {
        return qsearch(engine, position, alpha, beta, engine.max_q_depth);
    }

    // Increase node count
    engine.node_count++;

    // Get evaluation
    SCORE_TYPE static_eval = engine.probe_tt_evaluation(position.hash_key);
    if (static_eval == NO_EVALUATION) static_eval = evaluate(position);

    // Set values for State
    position.set_state(engine.search_ply, engine.fifty_move, static_eval);

    // TT probing
    SCORE_TYPE tt_value = 0;
    MOVE_TYPE tt_move = NO_MOVE;
    short tt_return_type = engine.probe_tt_entry(position.hash_key, alpha, beta, depth, tt_value, tt_move);

    // We are allowed to return the hash score
    if (tt_return_type == RETURN_HASH_SCORE) {
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
            if (!engine.search_ply) {
                engine.pv_table[0][0] = tt_move;
                engine.pv_length[0] = 1;
            }

            return tt_value;
        }
    }

    // Variable to record the hash flag
    short tt_hash_flag = HASH_FLAG_ALPHA;

    // Hack to determine pv_node, because when it is not a pv node we are being searched by
    // a zero window with alpha == beta - 1
    bool pv_node = alpha != beta - 1;
    bool null_search = !do_null && !root;

    // if (!pv_node) std::cout << alpha << " " << beta << std::endl;

    // The "improving" heuristic is when the current position has a better static evaluation than the evaluation
    // from a full-move or two plies ago. When this is true, we can be more aggressive with
    // beta-reductions (eval is too high) as we will have more certainty that the position is better;
    // however, we should be less aggressive with alpha-reductions (eval is too low) as we have less certainty
    // that the position is awful.
    bool improving = false;

    if (!in_check && engine.search_ply >= 2) {
        SCORE_TYPE past_eval = position.state_stack[engine.search_ply - 2].evaluation;
        if (past_eval != NO_EVALUATION && static_eval > past_eval) improving = true;
    }

    // Internal Iterative Reduction. Rebel's idea
    if (tt_move == NO_MOVE) {
        if (depth >= 4) depth--;
        if (depth >= 8) depth--;
    }

    // Reverse Futility Pruning
    // If the last move was very bad, such that the static evaluation - a margin is still greater
    // than the opponent's best score, then return the static evaluation.
    if (!pv_node && depth <= 7 && !in_check && static_eval - ((206 - improving * 58) * depth) >= beta) {
        return static_eval;
    }

    // Razoring
    // Ideas from Stockfish
    // If the evaluation is really low, and we cannot improve alpha even with qsearch, then return.
    // If the evaluation is improving then increase the margin because we are less certain that the
    // position is terrible.
    int razoring_margins[3] = {0, 320, 800};
    if (!in_check && !pv_node && depth <= 2 && static_eval + razoring_margins[depth] + improving * 120 < alpha) {
        SCORE_TYPE return_eval = qsearch(engine, position, alpha, beta, engine.max_q_depth);
        if (return_eval < alpha) return return_eval;
    }

    // Null move pruning
    // We give the opponent an extra move and if they are not able to make their position
    // any better, then our position is too good, and we don't need to search any deeper.
    if (depth >= 2 && do_null && !in_check && !pv_node && static_eval >= beta) {

        // Adaptive NMP
        int reduction = 3 + depth / 3 + std::min(3, (static_eval - beta) / 256);

        position.make_null_move(engine.search_ply, engine.fifty_move);

        engine.search_ply++;
        engine.game_ply++;

        // zero window search with reduced depth
        SCORE_TYPE return_eval = -negamax(engine, position, -beta, -beta + 1, depth - reduction, false);

        engine.game_ply--;
        engine.search_ply--;
        position.undo_null_move(engine.search_ply, engine.fifty_move);

        if (return_eval >= beta) return beta;

    }

    int legal_moves = 0;
    MOVE_TYPE last_move = engine.search_ply ? position.state_stack[engine.search_ply - 1].move : NO_MOVE;

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

        SCORE_TYPE move_history_score = engine.history_moves
                [get_selected(move)][MAILBOX_TO_STANDARD[get_target_square(move)]];

        bool quiet = !get_is_capture(move) && get_move_type(move) != MOVE_TYPE_EP;

        // Pruning
        if (!pv_node && get_move_type(move) != MOVE_TYPE_PROMOTION && legal_moves > 0) {
            // Late Move Pruning
            if (depth <= 3 && legal_moves > depth * 8) break;

            // Quiet Late Move Pruning
            if (quiet && legal_moves > static_cast<int>((4 + 1.4 * depth * depth) * (1 - 0.25 * !improving))) break;

            // History Pruning
            if (depth <= 8 && move_history_score < (depth + improving) * -12000) continue;
        }


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
        double reduction;

        bool is_killer_move = move == engine.killer_moves[0][engine.search_ply - 1] ||
                              move == engine.killer_moves[1][engine.search_ply - 1];
        bool is_counter_move = last_move != NO_MOVE &&
                               engine.counter_moves[position.side][MAILBOX_TO_STANDARD[get_origin_square(last_move)]]
                               [MAILBOX_TO_STANDARD[get_target_square(last_move)]] == move;

        bool full_depth_zero_window;

        // Late Move Reductions
        // The idea that if moves are ordered well, then moves that are searched
        // later shouldn't be as good, and therefore we don't need to search them to a very high depth
        if (legal_moves >= 2
                && ((engine.search_ply && !pv_node) || legal_moves >= 4)
                && depth >= 3
                && quiet
                && !in_check
                ){

            reduction = LMR_REDUCTIONS[depth][legal_moves];

            reduction -= pv_node;

            reduction -= improving * 0.9;

            reduction -= is_killer_move * 0.75;

            reduction -= is_counter_move * 0.25;

            reduction -= move_history_score / 8000.0;

            // My idea that in a null move search you can be more aggressive with LMR
            reduction += null_search;

            // Idea from Weiss, where you reduce more if the move is quiet and TT move is a capture
            reduction += get_is_capture(tt_move) * 0.5;

            PLY_TYPE new_depth = static_cast<PLY_TYPE>(depth -
                    std::min(depth - 1, std::max(0, static_cast<int>(reduction))) - 1);

            return_eval = -negamax(engine, position, -alpha - 1, -alpha, new_depth, true);

            full_depth_zero_window = return_eval > alpha && new_depth != depth - 1;
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

                // History Heuristic for move ordering
                SCORE_TYPE bonus = depth * (depth + 1 + null_search) - 1;
                if (quiet) {
                    update_history_entry(engine.history_moves
                        [get_selected(move)][MAILBOX_TO_STANDARD[get_target_square(move)]],
                        bonus);
                } else {
                    update_history_entry(engine.capture_history[get_selected(move)]
                        [get_occupied(move)][MAILBOX_TO_STANDARD[get_target_square(move)]],
                        bonus);
                }

                // Deduct bonus for moves that don't raise alpha
                for (int failed_move_index = 0; failed_move_index < move_index; failed_move_index++) {
                    MOVE_TYPE temp_move = position.moves[engine.search_ply][failed_move_index];
                    if (!get_is_capture(temp_move)) {
                        update_history_entry(engine.history_moves
                                             [get_selected(temp_move)]
                                             [MAILBOX_TO_STANDARD[get_target_square(temp_move)]],
                                             -bonus);
                    } else {
                        update_history_entry(engine.capture_history[get_selected(temp_move)]
                                             [get_occupied(temp_move)]
                                             [MAILBOX_TO_STANDARD[get_target_square(temp_move)]],
                                             -bonus);
                    }
                }

                // Alpha - Beta cutoff. This is a 'cut node' and we have failed high
                if (return_eval >= beta) {
                    // Killer Heuristic for move ordering
                    if (quiet) {
                        engine.killer_moves[1][engine.search_ply] = engine.killer_moves[0][engine.search_ply];
                        engine.killer_moves[0][engine.search_ply] = move;

                        if (last_move != NO_MOVE)
                            engine.counter_moves[position.side][MAILBOX_TO_STANDARD[get_origin_square(last_move)]]
                                                [MAILBOX_TO_STANDARD[get_target_square(last_move)]] = move;
                    }

                    tt_hash_flag = HASH_FLAG_BETA;
                    break;
                }
            }
        }
    }

    if (legal_moves == 0 && !in_check) return 0;
    else if (legal_moves == 0) return -MATE_SCORE + engine.search_ply;


    engine.record_tt_entry(position.hash_key, best_score, tt_hash_flag, best_move, depth, static_eval);

    return best_score;
}


void iterative_search(Engine& engine, Position& position) {

    engine.stopped = false;
    engine.terminated = false;

    position.clear_movelist();
    engine.reset();

    auto start_time = std::chrono::high_resolution_clock::now();
    engine.start_time = std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::time_point_cast<std::chrono::milliseconds>(start_time).time_since_epoch()).count();

    SQUARE_TYPE original_side = position.side;

    SCORE_TYPE alpha = -SCORE_INF;
    SCORE_TYPE beta = SCORE_INF;
    SCORE_TYPE aspiration_window = STARTING_WINDOW;

    PLY_TYPE running_depth = 1;

    std::string best_pv;
    SCORE_TYPE best_score = 0;

    while (running_depth <= engine.max_depth) {
        engine.current_search_depth = running_depth;
        SCORE_TYPE return_eval = negamax(engine, position, alpha, beta, running_depth, false);

        // Reset the window
        if (return_eval <= alpha || return_eval >= beta) {
            alpha = -SCORE_INF;
            beta = SCORE_INF;
            aspiration_window = STARTING_WINDOW;
            continue;
        }

        // Adjust the window
        alpha = return_eval - aspiration_window;
        beta = return_eval + aspiration_window;
        aspiration_window -= 20 / static_cast<int>(running_depth + 3);

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
        long elapsed_time = ms_int.count();
        elapsed_time = std::max(elapsed_time, 1L);

        if (running_depth >= engine.min_depth) {
            if (elapsed_time >= engine.soft_time_limit) engine.stopped = true;
        }

        if (abs(best_score) >= MATE_BOUND) {
            SCORE_TYPE score = best_score >= MATE_BOUND ?
                    (MATE_SCORE - best_score) / 2 + 1: (-MATE_SCORE - best_score) / 2;

            std::cout << "info multipv 1 depth " << running_depth << " seldepth " << engine.selective_depth
                      << " score mate " << score << " time " << elapsed_time
                      << " nodes " << engine.node_count << " nps " << int(engine.node_count / (elapsed_time / 1000.0))
                      << " pv " << best_pv << std::endl;
        }
        else {
            std::cout << "info multipv 1 depth " << running_depth << " seldepth " << engine.selective_depth
                      << " score cp " << best_score << " time " << elapsed_time
                      << " nodes " << engine.node_count << " nps " << int(engine.node_count / (elapsed_time / 1000.0))
                      << " pv " << best_pv << std::endl;
        }

        if (engine.stopped || running_depth == engine.max_depth) {
            break;
        }

        running_depth++;
    }

    std::cout << "bestmove " << split(best_pv, ' ')[0] << std::endl;

    engine.terminated = true;
}