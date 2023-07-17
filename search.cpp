
//
// Created by Alex Tian on 9/22/2022.
//

#include <thread>
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
#include "move_ordering.h"


// Initialize a table for Late Move Reductions, and the base reductions to be applied
void Engine::initialize_lmr_reductions() {
    for (PLY_TYPE depth = 0; depth < MAX_AB_DEPTH; depth++) {
        for (int moves = 0; moves < 64; moves++) {
            LMR_REDUCTIONS_QUIET[depth][moves] =
                    std::max(0.0,
                             std::log(depth) * std::log(moves) / double(tuning_parameters.LMR_divisor_quiet / 100.0)
                             + double(tuning_parameters.LMR_base_quiet / 100.0));
            LMR_REDUCTIONS_NOISY[depth][moves] =
                    std::max(0.0,
                             std::log(depth) * std::log(moves) / double(tuning_parameters.LMR_divisor_noisy / 100.0)
                             + double(tuning_parameters.LMR_base_noisy / 100.0));
        }
    }
}


// Clear the transposition table
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


// Resets the Engine object for a new search
void Engine::reset() {
    node_count = 0;
    primary_thread_node_count = 0;
    std::memset(node_table, 0, sizeof(node_table));

    for (Thread_State& thread_state : thread_states) {
        thread_state.current_search_depth = 1;
        thread_state.search_ply = 0;

        std::memset(thread_state.killer_moves, 0, sizeof(thread_state.killer_moves));
    }

    selective_depth = 0;

    std::memset(pv_length, 0, sizeof(pv_length));
    std::memset(pv_table, 0, sizeof(pv_table));

    if (show_stats) {
        search_results.alpha_raised_count = 0;
        std::memset(search_results.qsearch_fail_highs, 0, sizeof(search_results.qsearch_fail_highs));
        std::memset(search_results.search_fail_highs, 0, sizeof(search_results.search_fail_highs));
        std::memset(search_results.search_fail_high_types, 0, sizeof(search_results.search_fail_high_types));
    }
}


// Resets the Engine object for a new game
void Engine::new_game() {
    reset();

    for (Thread_State& thread_state : thread_states) {
        std::memset(thread_state.repetition_table, 0, sizeof(thread_state.repetition_table));
        std::memset(thread_state.killer_moves, 0, sizeof(thread_state.killer_moves));
        std::memset(thread_state.history_moves, 0, sizeof(thread_state.history_moves));
        std::memset(thread_state.capture_history, 0, sizeof(thread_state.capture_history));
        std::memset(thread_state.continuation_history, 0, sizeof(thread_state.continuation_history));

        thread_state.game_ply = 0;
        thread_state.fifty_move = 0;

    }

    stopped = true;

    std::memset(pv_length, 0, sizeof(pv_length));
    std::memset(pv_table, 0, sizeof(pv_table));
    clear_tt();
}


// Detects a repetition (Checks for only 2 repetitions)
bool Thread_State::detect_repetition() {

    for (PLY_TYPE i = game_ply - 2; i >= std::max<PLY_TYPE>(game_ply - fifty_move, 0); i--) {
        if (repetition_table[i] == repetition_table[game_ply]) {
            return true;
        }
    }

    return false;
}


// Probes the transposition table for a matching entry based on the position's hash key and other factors.
short Engine::probe_tt_entry(int thread_id, HASH_TYPE hash_key, SCORE_TYPE alpha, SCORE_TYPE beta, PLY_TYPE depth,
                             TT_Entry& return_entry) {
    TT_Entry& tt_entry = transposition_table[hash_key % transposition_table.size()];

    if (tt_entry.key == hash_key) {
        return_entry.move = tt_entry.move;
        return_entry.depth = tt_entry.depth;
        return_entry.flag = tt_entry.flag;

        return_entry.score = tt_entry.score;

        // Adjust mate scores based on ply
        if (return_entry.score < -MATE_BOUND) return_entry.score += thread_states[thread_id].search_ply;
        else if (return_entry.score > MATE_BOUND) return_entry.score -= thread_states[thread_id].search_ply;

        if (tt_entry.depth >= depth) {

            if (tt_entry.flag == HASH_FLAG_EXACT) return RETURN_HASH_SCORE;
            if (tt_entry.flag == HASH_FLAG_ALPHA && return_entry.score <= alpha) return RETURN_HASH_SCORE;
            if (tt_entry.flag == HASH_FLAG_BETA && return_entry.score >= beta) return RETURN_HASH_SCORE;
        }

        return USE_HASH_MOVE;
    }

    return NO_HASH_ENTRY;
}


// Records an entry to the transposition table
void Engine::record_tt_entry(int thread_id, HASH_TYPE hash_key, SCORE_TYPE score, short tt_flag, Move move, PLY_TYPE depth,
                             SCORE_TYPE static_eval, bool pv_node) {

    TT_Entry& tt_entry = transposition_table[hash_key % transposition_table.size()];

    if (score < -MATE_BOUND) score -= thread_states[thread_id].search_ply;
    else if (score > MATE_BOUND) score += thread_states[thread_id].search_ply;

    PLY_TYPE artificial_depth = depth + 3 + 2 * pv_node;

    if (tt_entry.key != hash_key || artificial_depth >= tt_entry.depth || tt_flag == HASH_FLAG_EXACT) {
        tt_entry.key = hash_key;
        tt_entry.depth = depth;
        tt_entry.flag = tt_flag;
        tt_entry.score = score;
        tt_entry.evaluation = static_eval;
        tt_entry.move = move;
    }
}


// Probes the transposition table for a matching entry (only for quiescence search)
short Engine::probe_tt_entry_q(int thread_id, HASH_TYPE hash_key, SCORE_TYPE alpha, SCORE_TYPE beta,
                               SCORE_TYPE& return_score, Move& tt_move) {
    TT_Entry& tt_entry = transposition_table[hash_key % transposition_table.size()];

    if (tt_entry.key == hash_key) {
        tt_move = tt_entry.move;

        return_score = tt_entry.score;
        if (return_score < -MATE_BOUND) return_score += thread_states[thread_id].search_ply;
        else if (return_score > MATE_BOUND) return_score -= thread_states[thread_id].search_ply;

        if (tt_entry.flag == HASH_FLAG_EXACT) return RETURN_HASH_SCORE;
        if (tt_entry.flag == HASH_FLAG_ALPHA && return_score <= alpha) return RETURN_HASH_SCORE;
        if (tt_entry.flag == HASH_FLAG_BETA && return_score >= beta) return RETURN_HASH_SCORE;


        return USE_HASH_MOVE;
    }

    return NO_HASH_ENTRY;
}


// Records an entry to the transposition table (only for quiescence search)
void Engine::record_tt_entry_q(int thread_id, HASH_TYPE hash_key, SCORE_TYPE score, short tt_flag, Move move,
                               SCORE_TYPE static_eval) {
    TT_Entry& tt_entry = transposition_table[hash_key % transposition_table.size()];

    if (score < -MATE_BOUND) score -= thread_states[thread_id].search_ply;
    else if (score > MATE_BOUND) score += thread_states[thread_id].search_ply;

    if (tt_entry.key != hash_key || tt_flag == HASH_FLAG_EXACT) { // TODO: try doing || depth == -1 for always replace in qs.
        tt_entry.key = hash_key;
        tt_entry.depth = -1;
        tt_entry.flag = tt_flag;
        tt_entry.score = score;
        tt_entry.evaluation = static_eval;
        tt_entry.move = move;
    }
}


// Probes the transposition table for an evaluation
SCORE_TYPE Engine::probe_tt_evaluation(HASH_TYPE hash_key) {
    TT_Entry& tt_entry = transposition_table[hash_key % transposition_table.size()];

    if (tt_entry.key == hash_key && tt_entry.evaluation != NO_EVALUATION) return tt_entry.evaluation;
    return NO_EVALUATION;
}

// Prefetching for cache
void Engine::tt_prefetch_read(HASH_TYPE hash_key) {
    __builtin_prefetch(&transposition_table[hash_key % transposition_table.size()]);
}

void Engine::tt_prefetch_write(HASH_TYPE hash_key) {
    __builtin_prefetch(&transposition_table[hash_key % transposition_table.size()], 1);
}


bool Engine::check_time() {
    auto time = std::chrono::high_resolution_clock::now();
    uint64_t current_time = std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::time_point_cast<std::chrono::milliseconds>(time).time_since_epoch()).count();

    if (current_time - start_time >= hard_time_limit) {
        stopped = true;
        return true;
    }

    return false;
}


// History entry updates with scaling
void update_history_entry(SCORE_TYPE& score, SCORE_TYPE bonus) {
    score -= (score * abs(bonus)) / 324;
    score += bonus * 32;
}


// The Quiescence Search function
// This is used to counter the horizon effect in which negamax is unable to resolve
// noisy moves after a certain depth has been reached. The qsearch function will look at remaining captures
// until it reaches a quiet position.
SCORE_TYPE qsearch(Engine& engine, SCORE_TYPE alpha, SCORE_TYPE beta, PLY_TYPE depth, int thread_id) {

    // Initialize Variables
    Thread_State& thread_state = engine.thread_states[thread_id];
    Position& position = thread_state.position;

    engine.tt_prefetch_read(position.hash_key);  // Prefetch the TT for cache

    // Check the remaining time
    if (engine.stopped || (thread_id == 0 && thread_state.current_search_depth >= engine.min_depth &&
        (engine.node_count & 2047) == 0 && engine.check_time())) {
        return 0;
    }

    // Check remaining nodes to be searched
    if (engine.max_nodes && engine.node_count >= engine.max_nodes) engine.stopped = true;

    // Probe the transposition table
    SCORE_TYPE tt_value = 0;
    Move tt_move = NO_MOVE;
    short tt_return_type = engine.probe_tt_entry_q(thread_id, position.hash_key, alpha, beta, tt_value, tt_move);

    if (tt_return_type == RETURN_HASH_SCORE) {
        return tt_value;
    }

    // Get the static evaluation of the position
    SCORE_TYPE static_eval = engine.probe_tt_evaluation(position.hash_key);
    if (static_eval == NO_EVALUATION) static_eval = evaluate(position);

    // Return the evaluation if we have reached a stand-pat, or we have reached the maximum depth
    if (depth == 0 || static_eval >= beta) return static_eval;

    // Set alpha to the greatest of either alpha or the evaluation
    alpha = (static_eval > alpha) ? static_eval : alpha;

    // Variable to record the hash flag
    short tt_hash_flag = HASH_FLAG_ALPHA;

    // Set values for State
    position.set_state(position.state_stack[thread_state.search_ply], thread_state.fifty_move);
    position.state_stack[thread_state.search_ply].evaluation = static_eval;

    // Get the moves and score them
    position.get_pseudo_legal_captures(position.scored_moves[thread_state.search_ply]);
    get_capture_scores(thread_state, position.scored_moves[thread_state.search_ply], tt_move);

    // Variables for getting information about the best score / best move
    SCORE_TYPE best_score = static_eval;
    Move best_move = NO_MOVE;

    // Search loop
    int legal_moves = 0;
    for (int move_index = 0; move_index < static_cast<int>(position.scored_moves[thread_state.search_ply].size()); move_index++) {

        // Sort and choose the next move to be searched
        Move move = sort_next_move(position.scored_moves[thread_state.search_ply], move_index);

        // Delta / Futility pruning
        // If the piece we capture plus a margin cannot even improve our score then
        // there is no point in searching it
        if (static_eval + MVV_LVA_VALUES[position.board[move.target()] % BLACK_PAWN] +
            engine.tuning_parameters.delta_margin < alpha) {
            continue;
        }

        // SEE pruning
        if (static_eval + 60 <= alpha && !get_static_exchange_evaluation(position, move, 1)) {
            best_score = std::max(best_score, static_eval + 60);
            continue;
        }

        // Attempt the current pseudo-legal move
        bool attempt = position.make_move(move, position.state_stack[thread_state.search_ply], thread_state.fifty_move);

        if (!attempt) {
            position.undo_move(move, position.state_stack[thread_state.search_ply], thread_state.fifty_move);
            continue;
        }

        engine.node_count++;
        if (thread_id == 0) engine.primary_thread_node_count++;

        // Recursively search
        thread_state.search_ply++;

        SCORE_TYPE return_eval = -qsearch(engine, -beta, -alpha, depth - 1, thread_id);

        thread_state.search_ply--;

        // Undo the move
        position.undo_move(move, position.state_stack[thread_state.search_ply], thread_state.fifty_move);

        if (engine.stopped) return 0;

        legal_moves++;

        // Update information
        if (return_eval > best_score) {
            best_score = return_eval;
            best_move = move;

            if (return_eval > alpha) {
                alpha = return_eval;
                tt_hash_flag = HASH_FLAG_EXACT;

                // Captures History Heuristic for move ordering
                SCORE_TYPE bonus = 2;
                update_history_entry(thread_state.capture_history[position.board[move.origin()]]
                                     [position.board[move.target()]][move.target()],
                                     bonus);

                if (return_eval >= beta) {
                    if (engine.show_stats) {
                        if (legal_moves <= FAIL_HIGH_STATS_COUNT) {
                            engine.search_results.qsearch_fail_highs[legal_moves - 1]++;
                        }
                    }

                    engine.record_tt_entry_q(thread_id, position.hash_key, best_score, HASH_FLAG_BETA, best_move, static_eval);
                    return best_score;
                }
            }
        }

    }

    // Save to the transposition table
    engine.tt_prefetch_write(position.hash_key);
    engine.record_tt_entry_q(thread_id, position.hash_key, best_score, tt_hash_flag, best_move, static_eval);

    return best_score;
}


// The core of the engine, negamax.
// This is a recursive search function based on the minimax algorithm that uses alpha-beta pruning
// among other heuristics.
SCORE_TYPE negamax(Engine& engine, SCORE_TYPE alpha, SCORE_TYPE beta, PLY_TYPE depth, bool do_null, int thread_id) {

    // Initialize Variables
    Thread_State& thread_state = engine.thread_states[thread_id];
    Position& position = thread_state.position;

    engine.tt_prefetch_read(position.hash_key);  // Prefetch

    // Initialize PV length
    if (thread_id == 0 && thread_state.search_ply <= MAX_AB_DEPTH) {
        engine.pv_length[thread_state.search_ply] = thread_state.search_ply;
    }

    // Check the remaining time
    if (engine.stopped || (thread_id == 0 && thread_state.current_search_depth >= engine.min_depth &&
        (engine.node_count & 2047) == 0 && engine.check_time())) {
        return 0;
    }

    bool root = !thread_state.search_ply;

    // Early search exits
    if (!root) {

        // Depth guard
        if (thread_state.search_ply >= MAX_AB_DEPTH - 2) return evaluate(position);

        // Detect repetitions and fifty move rule
        if (thread_state.fifty_move >= 100 || thread_state.detect_repetition()) return 3 - static_cast<int>(engine.node_count & 8);

        // Mate Distance Pruning from CPW
        SCORE_TYPE mating_value = MATE_SCORE - thread_state.search_ply;
        if (mating_value < beta) {
            beta = mating_value;
            if (alpha >= mating_value) return mating_value;
        }
        mating_value = -MATE_SCORE + thread_state.search_ply;
        if (mating_value > alpha) {
            alpha = mating_value;
            if (beta <= mating_value) return mating_value;
        }

    }

    engine.selective_depth = std::max(thread_state.search_ply, engine.selective_depth);

    // Start quiescence search at the start of regular negamax search to counter the horizon effect.
    if (depth <= 0) {
        return qsearch(engine, alpha, beta, engine.max_q_depth, thread_id);
    }

    // Information about the current node
    // Hack to determine pv_node, because when it is not a pv node we are being searched by
    // a zero window with alpha == beta - 1
    bool pv_node = alpha != beta - 1;
    bool singular_search = position.state_stack[thread_state.search_ply].excluded_move != NO_MOVE;
    bool null_search = !do_null && !root;

    // Set values for State
    position.set_state(position.state_stack[thread_state.search_ply], thread_state.fifty_move);

    // TT probing
    TT_Entry tt_entry{};
    short tt_return_type = engine.probe_tt_entry(thread_id, position.hash_key, alpha, beta, depth, tt_entry);

    if (singular_search) tt_return_type = USE_HASH_MOVE;

    SCORE_TYPE tt_value = tt_entry.score;
    Move tt_move = tt_entry.move;

    // We are allowed to return the hash score
    if (tt_return_type == RETURN_HASH_SCORE && !pv_node) {
        return tt_value;
    }

    // Variable to record the hash flag
    short tt_hash_flag = HASH_FLAG_ALPHA;

    // Get evaluation
    SCORE_TYPE static_eval = NO_EVALUATION;

    // Check if we are currently in check.
    bool in_check;

    if (position.state_stack[thread_state.search_ply].in_check != -1) {
        in_check = static_cast<bool>(position.state_stack[thread_state.search_ply].in_check);
    } else {
        in_check = position.is_attacked(position.get_king_pos(position.side), position.side);
    }

    // The "improving" heuristic is when the current position has a better static evaluation than the evaluation
    // from a full-move or two plies ago. When this is true, we can be more aggressive with
    // beta-reductions (eval is too high) as we will have more certainty that the position is better;
    // however, we should be less aggressive with alpha-reductions (eval is too low) as we have less certainty
    // that the position is awful.

    // The failing heuristic is the opposite. We are failing when the current evaluation is worse than the
    // previous evaluation by a certain margin.
    bool improving = false;
    bool failing = false;

    // Save the current evaluation
    if (!in_check) {
        static_eval = engine.probe_tt_evaluation(position.hash_key);
        if (static_eval == NO_EVALUATION) static_eval = evaluate(position);
        position.state_stack[thread_state.search_ply].evaluation = static_eval;
    }

    // Calculate if we are "improving", or "failing"
    if (!in_check && static_eval != NO_EVALUATION && thread_state.search_ply >= 2) {
        SCORE_TYPE past_eval = position.state_stack[thread_state.search_ply - 2].evaluation;
        if (past_eval != NO_EVALUATION) {
            if (static_eval > past_eval) improving = true;
            if (!pv_node && static_eval < past_eval - (60 + 40 * depth)) failing = true;
        }
    }

    // Internal Iterative Reduction. Based on Rebel's idea
    if (tt_move == NO_MOVE && !singular_search) {
        if (depth >= 4) depth--;
        if (depth >= 8) depth--;
    }

    // Forward Pruning Methods
    if (!pv_node && !in_check && !singular_search && abs(beta) < MATE_BOUND) {

        // Reverse Futility Pruning
        // If the last move was very bad, such that the static evaluation - a margin is still greater
        // than the opponent's best score, then return the static evaluation.
        if (depth <= engine.tuning_parameters.RFP_depth && static_eval -
            engine.tuning_parameters.RFP_margin * (depth - improving) >= beta) {
            return static_eval;
        }

        // Null move pruning
        // We give the opponent an extra move and if they are not able to make their position
        // any better, then our position is too good, and we don't need to search any deeper.
        if (depth >= engine.tuning_parameters.NMP_depth && do_null && static_eval >= beta &&
            position.get_non_pawn_material_count() >= 1 + (depth >= 10)) {

            // Adaptive NMP
            int reduction = engine.tuning_parameters.NMP_base +
                            depth / engine.tuning_parameters.NMP_depth_divisor +
                            std::min(3, (static_eval - beta) / engine.tuning_parameters.NMP_eval_divisor);

            position.make_null_move(position.state_stack[thread_state.search_ply], thread_state.fifty_move);

            thread_state.search_ply++;
            thread_state.game_ply++;

            // zero window search with reduced depth
            SCORE_TYPE return_eval = -negamax(engine, -beta, -beta + 1, depth - reduction, false, thread_id);

            thread_state.game_ply--;
            thread_state.search_ply--;
            position.undo_null_move(position.state_stack[thread_state.search_ply], thread_state.fifty_move);

            if (return_eval >= beta) {
                return beta;
            }
        }
    }

    // Internal Iterative Deepening
    if (pv_node && depth >= 4 && tt_move == NO_MOVE && !singular_search) {
        negamax(engine, alpha, beta, static_cast<PLY_TYPE>(depth - 3), true, thread_id);  // TODO: test no null moves here
        tt_move = engine.transposition_table[position.hash_key % engine.transposition_table.size()].move;
    }

    // Used for the continuation history heuristic
    InformativeMove last_move_one = thread_state.search_ply >= 1 ? position.state_stack[thread_state.search_ply - 1].move : NO_INFORMATIVE_MOVE;
    InformativeMove last_move_two = thread_state.search_ply >= 2 ? position.state_stack[thread_state.search_ply - 2].move : NO_INFORMATIVE_MOVE;

    // Retrieving the pseudo legal moves in the current position as a list of integers
    // Score the moves
    position.get_pseudo_legal_moves(position.scored_moves[thread_state.search_ply]);
    get_move_scores(thread_state, position.scored_moves[thread_state.search_ply],
                    tt_move, last_move_one, last_move_two);

    // Best score for fail soft, and best move for tt
    SCORE_TYPE best_score = -SCORE_INF;
    Move best_move = NO_MOVE;

    // Other information for pruning / reductions
    int alpha_raised_count = 0;
    int legal_moves = 0;
    bool recapture_found = false;

    // Iterate through moves and recursively search with Negamax
    for (int move_index = 0; move_index < static_cast<int>(position.scored_moves[thread_state.search_ply].size()); move_index++) {

        // Sort the next move. If an early move causes a cutoff then we have saved time
        // by only sorting one or a few moves rather than the whole list.
        sort_next_move(position.scored_moves[thread_state.search_ply], move_index);
        Move move = position.scored_moves[thread_state.search_ply][move_index].move;
        InformativeMove informative_move = InformativeMove(move, position.board[move.origin()], position.board[move.target()]);
        SCORE_TYPE move_score = position.scored_moves[thread_state.search_ply][move_index].score;

        // Skip the excluded move since we are in a singular search
        if (move == position.state_stack[thread_state.search_ply].excluded_move) continue;

        SCORE_TYPE move_history_score = thread_state.history_moves
            [position.board[move.origin()]][move.target()];

        bool quiet = !move.is_capture(position) && move.type() != MOVE_TYPE_EP;

        // Pruning
        if (!root && legal_moves >= 1 && abs(best_score) < MATE_BOUND) {
            // Late Move Pruning
            if (!pv_node && depth <= engine.tuning_parameters.LMP_depth &&
                legal_moves >= depth * engine.tuning_parameters.LMP_margin) break;

            // Quiet Late Move Pruning
            if (!pv_node && quiet && legal_moves >= 2 + depth * depth / (1 + !improving + failing)) break;

            // Futility Pruning
            if (!pv_node && quiet && depth <= 5 && static_eval + (depth - !improving) * 140 + 70 <= alpha) break;

            // History Pruning
            if (!pv_node && depth <= engine.tuning_parameters.history_pruning_depth &&
                move_history_score <= (depth + improving) * -engine.tuning_parameters.history_pruning_divisor) continue;

            // SEE Pruning
            if (depth <= (3 + 3 * !quiet + 5 * pv_node) && legal_moves >= 3 &&
                 -MATE_BOUND < alpha && alpha < MATE_BOUND &&
                 move_history_score <= 5000 &&
                 !get_static_exchange_evaluation(position, move, (quiet ? -50 : -90) * depth))
                continue;

        }

        // Make the move
        bool attempt = position.make_move(move, position.state_stack[thread_state.search_ply], thread_state.fifty_move);

        // The move put us in check, therefore it was not legal, and we must disregard it
        if (!attempt) {
            position.undo_move(move, position.state_stack[thread_state.search_ply], thread_state.fifty_move);
            continue;
        }

        // Increase node count
        engine.node_count++;
        if (thread_id == 0) engine.primary_thread_node_count++;

        // Calculate if the current move is a recapture
        bool recapture = false;
        if (last_move_one != NO_INFORMATIVE_MOVE && last_move_one.target() == move.target()) {
            recapture_found = true;
            recapture = true;
        }

        // Extensions
        PLY_TYPE extension = in_check;

        // Pawn going to 7th rank must be passed
        bool passed_pawn = get_piece_type(informative_move.selected(), ~position.side) == PAWN &&
                           static_cast<int>(rank_of(move.target())) == 6 - 5 * (~position.side);  // side has already been flipped
        bool queen_promotion = move.type() == MOVE_TYPE_PROMOTION &&
                               static_cast<PieceType>(move.promotion_type() + 1) == QUEEN;

        if (move_score >= 0 && (passed_pawn || queen_promotion)) extension++;

        // Checking for singularity
        if (!root &&
            depth >= 8 &&
            move == tt_move &&
            tt_entry.depth >= depth - 3 &&
            tt_entry.flag != HASH_FLAG_ALPHA &&
            position.state_stack[thread_state.search_ply].excluded_move == NO_MOVE &&
            abs(tt_entry.score) < MATE_BOUND) {

            position.undo_move(move, position.state_stack[thread_state.search_ply], thread_state.fifty_move);

            int singular_beta = tt_entry.score - depth * 2;

            position.state_stack[thread_state.search_ply].excluded_move = move;
            SCORE_TYPE return_eval = negamax(engine, singular_beta - 1, singular_beta, (depth - 1) / 2,
                                             false, thread_id);
            position.state_stack[thread_state.search_ply].excluded_move = NO_MOVE;

            // Singular Extensions
            if (return_eval < singular_beta) {
                extension++;
                if (!pv_node && return_eval < singular_beta - 24) extension++;
            }

            // Multi-cut Pruning
            else if (singular_beta >= beta) {
                return singular_beta;
            }

            else if (tt_entry.score >= beta) {
                extension--;
            }

            position.make_move(move, position.state_stack[thread_state.search_ply], thread_state.fifty_move);
        }

        extension = std::min<PLY_TYPE>(extension, std::min<PLY_TYPE>(2, MAX_AB_DEPTH - 1 - depth));

        int double_extensions = root ? 0 : position.state_stack[thread_state.search_ply].double_extensions;

        if (double_extensions >= 7) {
            extension = std::min<PLY_TYPE>(extension, 1);
        }

        position.state_stack[thread_state.search_ply].double_extensions = root ? 0 :
                position.state_stack[thread_state.search_ply - 1].double_extensions + (extension == 2);

        PLY_TYPE new_depth = depth + extension - 1;

        // Prepare for recursive searching
        thread_state.search_ply++;
        thread_state.game_ply++;
        thread_state.repetition_table[thread_state.game_ply] = position.hash_key;

        bool move_gives_check = position.is_attacked(position.get_king_pos(position.side), position.side);
        position.state_stack[thread_state.search_ply].in_check = static_cast<int>(move_gives_check);


        bool is_killer_move = informative_move == thread_state.killer_moves[0][thread_state.search_ply - 1] ||
                              informative_move == thread_state.killer_moves[1][thread_state.search_ply - 1];

        bool interesting = passed_pawn || queen_promotion || move_gives_check || is_killer_move;

        SCORE_TYPE return_eval = -SCORE_INF;

        uint64_t current_nodes = engine.primary_thread_node_count;

        double reduction;
        bool full_depth_zero_window;
        bool bad_capture = move_score < 10000;

        // Late Move Reductions (LMR)
        // The idea that if moves are ordered well, then moves that are searched
        // later shouldn't be as good, and therefore we don't need to search them to a very high depth
        if (legal_moves >= 2 + 2 * root + pv_node
            && depth >= 3
            && (quiet || bad_capture)
            ){

            // Get the base reduction based on depth and moves searched
            reduction = quiet ?
                    engine.LMR_REDUCTIONS_QUIET[depth][std::min(legal_moves, 63)] :
                    engine.LMR_REDUCTIONS_NOISY[depth][std::min(legal_moves, 63)];

            // Fewer reductions if we are in a pv node, since moves are likely to be better and more important
            reduction -= pv_node;

            // Fewer reductions when improving, since the current node and moves searched in it are more important
            reduction -= improving * 0.9;
            reduction += failing;

            // Fewer reductions for interesting moves which we define above
            reduction -= interesting;

            // Do not reduce moves as much if we are in check, because the position is possibly volatile
            reduction -= in_check;

            // Scale the reduction based on the move's history score
            reduction -= move_history_score > 0 ? move_history_score / 7200.0 : move_history_score / 16000.0;

            // Scale reductions if the move is a recapture, or if we have already found a recapture
            reduction -= recapture * 0.5;
            reduction += !recapture && recapture_found && quiet && !move_gives_check && move_history_score <= 0;

            // Scale reductions based on how many moves have already raised alpha
            reduction += static_cast<double>(alpha_raised_count) * (0.3 + 0.5 * tt_move.is_capture(position));

            // My idea that in a null move search you can be more aggressive with LMR
            reduction += null_search;

            // Idea from Weiss, where you reduce more if the TT move is a capture
            reduction += tt_move.is_capture(position) * 0.3;

            // Clamp the LMR depth
            auto lmr_depth = std::clamp<PLY_TYPE>(new_depth - static_cast<PLY_TYPE>(reduction), 1, new_depth);

            // Recursively search
            return_eval = -negamax(engine, -alpha - 1, -alpha, lmr_depth, true, thread_id);

            // Check if we need to search at full depth with a zero window
            full_depth_zero_window = return_eval > alpha && lmr_depth != new_depth;
        }

        else {
            // Check if we need to search at full depth with a zero window
            full_depth_zero_window = !pv_node || legal_moves >= 1;
        }

        // Search at a full depth with a zero window
        // The zero window is a type of assumption that the current move being searched will not raise alpha,
        // which is why the bounds are [-alpha - 1, -alpha] instead of [-beta, -alpha]
        if (full_depth_zero_window)
            return_eval = -negamax(engine, -alpha - 1, -alpha, new_depth, true, thread_id);

        // Search to a full depth at normal bounds if necessary
        if (return_eval == -SCORE_INF || (pv_node && ((return_eval > alpha && return_eval < beta) || legal_moves == 0)))
            return_eval = -negamax(engine, -beta, -alpha, new_depth, true, thread_id);

        // Undo the move and other changes
        thread_state.game_ply--;
        position.state_stack[thread_state.search_ply].in_check = -1;
        thread_state.search_ply--;

        position.undo_move(move, position.state_stack[thread_state.search_ply], thread_state.fifty_move);

        // Return early if the engine is stopped in order to prevent changes
        if (engine.stopped) return 0;

        // Update legal move count
        legal_moves++;

        // This move is better than other moves searched
        if (return_eval > best_score) {
            best_score = return_eval;
            best_move = move;

            // Calculate nodes for each move for time management scaling
            if (root && thread_id == 0) {
                engine.node_table[position.board[best_move.origin()]]
                    [best_move.target()] += engine.primary_thread_node_count - current_nodes;
            }

            // Write moves into the PV table
            if (thread_id == 0) {
                engine.pv_table[thread_state.search_ply][thread_state.search_ply] = move;

                for (int next_ply = thread_state.search_ply + 1; next_ply < engine.pv_length[thread_state.search_ply + 1]; next_ply++) {
                    engine.pv_table[thread_state.search_ply][next_ply] = engine.pv_table[thread_state.search_ply + 1][next_ply];
                }

                engine.pv_length[thread_state.search_ply] = engine.pv_length[thread_state.search_ply + 1];
            }

            // The move has raised alpha
            if (return_eval > alpha) {
                alpha_raised_count++;
                alpha = return_eval;

                // We have found a better move that increased achieved us an exact score
                tt_hash_flag = HASH_FLAG_EXACT;

                // History Heuristic for move ordering
                SCORE_TYPE bonus = depth * (depth + 1 + null_search + pv_node + improving) - 1;

                if (quiet) {
                    update_history_entry(thread_state.history_moves
                                         [position.board[move.origin()]][move.target()],
                                         bonus);

                    if (last_move_one != NO_INFORMATIVE_MOVE) {
                        update_history_entry(thread_state.continuation_history
                                             [last_move_one.selected()]
                                             [last_move_one.target()]
                                             [informative_move.selected()]
                                             [informative_move.target()],
                                             bonus);
                    }

                    if (last_move_two != NO_INFORMATIVE_MOVE) {
                        update_history_entry(thread_state.continuation_history
                                             [last_move_two.selected()]
                                             [last_move_two.target()]
                                             [informative_move.selected()]
                                             [informative_move.target()],
                                             bonus);
                    }

                } else {
                    update_history_entry(thread_state.capture_history[position.board[move.origin()]]
                                         [position.board[move.target()]][move.target()],
                                         bonus);
                }

                // Deduct bonus for moves that don't raise alpha
                for (int failed_move_index = 0; failed_move_index < move_index; failed_move_index++) {
                    Move temp_move = position.scored_moves[thread_state.search_ply][failed_move_index].move;
                    if (!temp_move.is_capture(position) && move.type() != MOVE_TYPE_EP) {
                        update_history_entry(thread_state.history_moves
                                             [position.board[temp_move.origin()]]
                                             [temp_move.target()],
                                             -bonus);

                        if (last_move_one != NO_INFORMATIVE_MOVE) {
                            update_history_entry(thread_state.continuation_history
                                                 [last_move_one.selected()]
                                                 [last_move_one.target()]
                                                 [position.board[temp_move.origin()]]
                                                 [temp_move.target()],
                                                 -bonus);
                        }

                        if (last_move_two != NO_INFORMATIVE_MOVE) {
                            update_history_entry(thread_state.continuation_history
                                                 [last_move_two.selected()]
                                                 [last_move_two.target()]
                                                 [position.board[temp_move.origin()]]
                                                 [temp_move.target()],
                                                 -bonus);
                        }

                    } else {
                        update_history_entry(thread_state.capture_history[position.board[temp_move.origin()]]
                                             [position.board[temp_move.target()]]
                                             [temp_move.target()],
                                             -bonus);
                    }
                }

                if (engine.show_stats) {
                    engine.search_results.alpha_raised_count++;
                    if (legal_moves <= ALPHA_RAISE_STATS_COUNT) {
                        engine.search_results.search_alpha_raises[legal_moves-1]++;
                    }
                }

                // Alpha - Beta cutoff. We have failed high here.
                if (return_eval >= beta) {
                    if (engine.show_stats) {
                        if (legal_moves <= FAIL_HIGH_STATS_COUNT) engine.search_results.search_fail_highs[legal_moves-1]++;
                        if (move == tt_move) engine.search_results.search_fail_high_types[0]++;
                        else if (informative_move == thread_state.killer_moves[0][thread_state.search_ply]) engine.search_results.search_fail_high_types[1]++;
                        else if (informative_move == thread_state.killer_moves[1][thread_state.search_ply]) engine.search_results.search_fail_high_types[2]++;
                        else if (quiet) engine.search_results.search_fail_high_types[3]++;
                        else if (bad_capture) engine.search_results.search_fail_high_types[4]++;
                        else engine.search_results.search_fail_high_types[5]++;
                    }

                    // Killer Heuristic for move ordering
                    if (quiet) {
                        if (!null_search || thread_state.killer_moves[0][thread_state.search_ply] == NO_INFORMATIVE_MOVE) {
                            thread_state.killer_moves[1][thread_state.search_ply] = thread_state.killer_moves[0][thread_state.search_ply];
                            thread_state.killer_moves[0][thread_state.search_ply] = informative_move;
                        } else {
                            thread_state.killer_moves[1][thread_state.search_ply] = informative_move;
                        }
                    }

                    tt_hash_flag = HASH_FLAG_BETA;
                    break;
                }
            }
        }
    }

    engine.tt_prefetch_write(position.hash_key);

    if (legal_moves == 0) {
        if (singular_search) return alpha;
        if (!in_check) return 0;
        else return -MATE_SCORE + thread_state.search_ply;
    }

    engine.record_tt_entry(thread_id, position.hash_key, best_score, tt_hash_flag, best_move, depth, static_eval, pv_node);

    return best_score;
}


void print_thinking(Engine& engine, NodeType node, SCORE_TYPE best_score, int thread_id) {

    Thread_State& thread_state = engine.thread_states[thread_id];
    Position& position = thread_state.position;

    PLY_TYPE depth = thread_state.current_search_depth;

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
    Color original_side = position.side;
    for (int c = 0; c < max_pv_length; c++) {
        pv_line += engine.pv_table[0][c].get_uci(position);
        pv_line += " ";
        position.side = ~position.side;
    }
    position.side = original_side;

    // Print the UCI search information
    std::cout << "info multipv 1 depth " << depth << " seldepth " << engine.selective_depth
              << " score " << result_type << " time " << elapsed_time
              << " nodes " << engine.node_count << " nps " << nps
              << " pv " << pv_line << std::endl;

}


SCORE_TYPE aspiration_window(Engine& engine, SCORE_TYPE previous_score, PLY_TYPE& asp_depth, Move& best_move, int thread_id) {

    Thread_State& thread_state = engine.thread_states[thread_id];

    SCORE_TYPE alpha = -SCORE_INF;
    SCORE_TYPE beta = SCORE_INF;
    SCORE_TYPE delta = std::max(6 + static_cast<int>(85 / (asp_depth - 2)), 10);

    PLY_TYPE depth = thread_state.current_search_depth;

    if (depth >= MINIMUM_ASP_DEPTH) {
        alpha = std::max(previous_score - delta, -SCORE_INF);
        beta  = std::min(previous_score + delta,  SCORE_INF);
    }

    SCORE_TYPE return_eval = 0;
    while (true) {

        // Completely expand the bounds once they have exceeded a certain score
        if (alpha <= -1000) alpha = -SCORE_INF;
        if (beta  >=  1000) beta  =  SCORE_INF;

        return_eval = negamax(engine, alpha, beta, depth, false, thread_id);

        if (engine.stopped) break;

        // The aspiration window search has failed low.
        // The position is probably worse than we expect, so both alpha and beta should be relaxed.
        // Alpha will be relaxed with delta while beta will be skewed towards alpha.
        if (return_eval <= alpha) {
            alpha = std::max(alpha - delta, -SCORE_INF);
            beta  = (alpha + 3 * beta) / 4;
            depth = thread_state.current_search_depth;

            asp_depth--;
            asp_depth = std::max<PLY_TYPE>(6, asp_depth);

            if (depth >= 18 && thread_id == 0) print_thinking(engine, Lower_Node, return_eval, thread_id);
        }

        // The aspiration window search has failed high.
        // The position is probably better than we expect, so we can be more aggressive with aspiration windows
        // and only relax the beta bound while also reducing depth.
        else if (return_eval >= beta) {
            beta  = std::min(beta + delta, SCORE_INF);
            depth = std::max(engine.min_depth,
                             static_cast<PLY_TYPE>(static_cast<int>(depth) - (return_eval < MATE_BOUND)));

            asp_depth--;
            asp_depth = std::max<PLY_TYPE>(6, asp_depth);

            if (thread_id == 0) best_move = engine.pv_table[0][0];  // Safe to update the best move on fail highs.

            if (depth >= 18 && thread_id == 0) print_thinking(engine, Upper_Node, return_eval, thread_id);
        }

        // We have achieved an exact node where the score was between alpha and beta.
        // We are certain of our score and can now safely return.
        else {

            if (thread_id == 0) print_thinking(engine, Exact_Node, return_eval, thread_id);
            break;
        }

        // Increase delta in the case that we must re-search the aspiration windows multiple times.
        delta += delta * 2 / 3;
    }

    return return_eval;
}


void iterative_search(Engine& engine, int thread_id) {

    Thread_State& thread_state = engine.thread_states[thread_id];
    Position& position = thread_state.position;

    // Reset certain information
    engine.stopped = false;
    thread_state.terminated = false;

    // Initialize the start time
    auto start_time = std::chrono::high_resolution_clock::now();
    engine.start_time = std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::time_point_cast<std::chrono::milliseconds>(start_time).time_since_epoch()).count();

    // Initialize variables
    SCORE_TYPE previous_score = 0;
    PLY_TYPE running_depth = 1;
    PLY_TYPE asp_depth = 6;

    uint64_t original_soft_time_limit = engine.soft_time_limit;
    Move best_move = NO_MOVE;

    SCORE_TYPE low_depth_score = 0;

    while (running_depth <= engine.max_depth) {
        thread_state.current_search_depth = running_depth;
        position.clear_state_stack();

        // Run a search with aspiration window bounds
        previous_score = aspiration_window(engine, previous_score, asp_depth, best_move, thread_id);

        // Store the best move when the engine has finished a search (it hasn't stopped in the middle of a search)
        if (thread_id == 0 && !engine.stopped) best_move = engine.pv_table[0][0];

        if (thread_id == 0) {
            if (running_depth <= 4) low_depth_score = previous_score;

            if (running_depth >= 8) {
                auto best_node_percentage =
                        static_cast<double>(engine.node_table[position.board[best_move.origin()]] [best_move.target()]) /
                        static_cast<double>(engine.primary_thread_node_count);

                double node_scaling_factor = (1.5 - best_node_percentage) * 1.35;

                SCORE_TYPE score_difference = previous_score - low_depth_score;
                score_difference = std::clamp(score_difference, -120, 120);

                double score_scaling_factor = 1.05 - (score_difference / 270.0);
                //std::cout << previous_score - low_depth_score << " " << score_difference << std::endl;
                //std::cout << score_scaling_factor << std::endl;

                engine.soft_time_limit = static_cast<uint64_t>(static_cast<double>(original_soft_time_limit)
                        * node_scaling_factor
                        * score_scaling_factor);

                // std::cout << "Soft Time Limit changed to: " << engine.soft_time_limit << std::endl;
            }


            // Calculate the elapsed time
            auto end_time = std::chrono::high_resolution_clock::now();
            auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(end_time
                                                                                - start_time);
            uint64_t elapsed_time = ms_int.count();
            elapsed_time = std::max<uint64_t>(elapsed_time, 1);

            // Stop the engine when we have exceeded the soft time limit
            if (running_depth >= engine.min_depth && thread_id == 0) {
                if (elapsed_time >= engine.soft_time_limit) engine.stopped = true;
            }
        }

        // End the search when the engine has stopped running
        if (engine.stopped || running_depth == engine.max_depth) {
            break;
        }

        // Increase the aspiration depth for aspiration bounds scaling
        if (running_depth >= 6) {
            asp_depth++;
        }

        // Increase search depth
        running_depth++;
    }

    engine.search_results.depth_reached = running_depth;
    engine.search_results.node_count = engine.node_count;

    if (thread_id == 0) {
        std::string best_move_str = best_move.get_uci(position);
        std::cout << "bestmove " << best_move_str << std::endl;
    }

    thread_state.terminated = true;
}


void lazy_smp_search(Engine& engine) {

    engine.reset();

    std::vector<std::thread> search_threads;
    //std::vector<Position> new_positions;

    for (int thread_id = 1; thread_id < engine.num_threads; thread_id++) {
        // std::cout << "Creating Helper Thread #" << thread_id << std::endl;
        engine.thread_states[thread_id] = engine.thread_states[0];
        search_threads.emplace_back(iterative_search, std::ref(engine), thread_id);
    }

    //engine.thread_states[0].position.print_board();
    iterative_search(engine, 0);
    // std::cout << "Search ended" << std::endl;

    for (int thread_id = engine.num_threads - 1; thread_id >= 1; thread_id--) {
        search_threads[thread_id - 1].join();
        // std::cout << "Helper Thread #" << thread_id << " closed." << std::endl;
    }

    if (engine.show_stats) print_statistics(engine.search_results);

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
    std::cout << "Quiet move fail highs: " << res.search_fail_high_types[3] << " percentage: " <<
              double(res.search_fail_high_types[3]) / double(total_fail_highs) * 100 << "%\n";
    std::cout << "Bad Noisy move fail highs: " << res.search_fail_high_types[4] << " percentage: " <<
              double(res.search_fail_high_types[4]) / double(total_fail_highs) * 100 << "%\n";
    std::cout << "Good Noisy move fail highs: " << res.search_fail_high_types[5] << " percentage: " <<
              double(res.search_fail_high_types[5]) / double(total_fail_highs) * 100 << "%\n";

    std::cout << "\n\n---------------------------------------------------------" << std::endl;
}


void print_search_tuning_config(Tuning_Parameters& tuning_parameters) {
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


void print_move_ordering_tuning_config(Move_Ordering_Parameters& tuning_parameters) {
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
