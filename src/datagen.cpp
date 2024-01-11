//
// Created by Alexander Tian on 8/16/23.
//

#include <chrono>
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <cmath>
#include "datagen.h"
#include "search.h"
#include "evaluation.h"
#include "useful.h"


void Datagen::integrity_check() {

    std::cout << "-----------------------------" << std::endl;

    for (Datagen_Thread& datagen_thread : datagen_threads) {
        std::string status_color = datagen_thread.paused ? YELLOW : datagen_thread.ping ? GREEN : RED;
        std::string status = datagen_thread.paused ? "paused" : datagen_thread.ping ? "running" : "stalled";

        std::cout << "Thread " << datagen_thread.thread_id << " [" << status_color << status << RESET << "]\n";

        if (!datagen_thread.ping && !datagen_thread.paused) {
            std::cout << "Current Stage: " << datagen_thread.current_stage << "\n";
            std::cout << "node count: " <<  datagen_thread.engine->thread_states[0].node_count << "\n";
            std::cout << "stopped? " << datagen_thread.engine->stopped << "\n";
        }

        datagen_thread.ping = false;
    }

    // uint64_t included_fens = 0;
    uint64_t total_fens = 0;
    uint64_t total_games = 0;
    for (Datagen_Thread& datagen_thread : datagen_threads) {
        total_fens  += datagen_thread.total_fens;
        total_games += datagen_thread.total_games;
        // if (!datagen_thread.paused) included_fens += datagen_thread.total_fens;
    }
    uint64_t elapsed_fens = total_fens - interval_start_fens;

    auto end_time_point = std::chrono::high_resolution_clock::now();
    auto end_time = std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::time_point_cast<std::chrono::milliseconds>(end_time_point).time_since_epoch()).count();
    uint64_t elapsed_time = std::max<uint64_t>(end_time - interval_start_time, 1);

    auto fps  = static_cast<uint64_t>(static_cast<double>(elapsed_fens) / static_cast<double>(elapsed_time) * 1000);
    auto fpst = fps / running_threads;

    std::cout << std::endl;
    std::cout << "Total Games \t [" << CYAN << total_games << RESET << "]\n";
    std::cout << "Total Fens  \t [" << CYAN << total_fens  << RESET << "]\n";
    std::cout << "FPS | FPST  \t [" << CYAN << fps << RESET << " | " << CYAN << fpst << RESET << "]\n";

    std::cout << "-----------------------------" << std::endl;

    interval_start_time = std::chrono::duration_cast<std::chrono::milliseconds>
                          (std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch()).count();
    interval_start_fens = total_fens;
}


void Datagen::integrity_check_process() {
    while (!stopped) {
        std::this_thread::sleep_for(std::chrono::milliseconds(30000));

        integrity_check();
    }
}


void Datagen::start_datagen() {

    running_threads = threads;

    stopped = false;
    std::vector<std::thread> search_threads;
    search_threads.reserve(threads + 1);
    datagen_threads.resize(threads);

    std::cout << "Starting " << threads << " threads" << std::endl;
    start_time = std::chrono::duration_cast<std::chrono::milliseconds>
                 (std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch()).count();
    interval_start_time = start_time;

    for (int thread_id = 0; thread_id < threads; thread_id++) {
        datagen_threads[thread_id] = Datagen_Thread(thread_id, random_seed);
        search_threads.emplace_back([this, thread_id](){
            this->datagen(datagen_threads[thread_id]);
        });
    }

    search_threads.emplace_back([this]() {
        this->integrity_check_process();
    });

    std::string msg;
    std::vector<std::string> tokens{};

    while (getline(std::cin, msg)) {
        tokens.clear();
        tokens = split(msg, ' ');

        if (msg == "stop") {
            stopped = true;
            break;
        }

        if (tokens[0] == "pause" && tokens.size() >= 2) {
            int pause_thread = std::stoi(tokens[1]);
            if (pause_thread < 0 || pause_thread >= threads) continue;

            if (datagen_threads[pause_thread].paused) {
                std::cout << "Thread is already paused" << std::endl;
                continue;
            }

            running_threads--;

            datagen_threads[pause_thread].paused = true;
            std::cout << "Thread " << pause_thread << " paused" << std::endl;
        }

        if (tokens[0] == "resume" && tokens.size() >= 2) {
            int resume_thread = std::stoi(tokens[1]);
            if (resume_thread < 0 || resume_thread >= threads) continue;

            if (!datagen_threads[resume_thread].paused) {
                std::cout << "Thread is already running" << std::endl;
                continue;
            }

            running_threads++;

            datagen_threads[resume_thread].paused = false;
            std::cout << "Thread " << resume_thread << " resumed" << std::endl;
        }
    }

    for (int thread_id = 0; thread_id < threads; thread_id++) {
        search_threads[thread_id].join();
    }

    search_threads.back().join();

    std::cout << "All threads joined" << std::endl;

    // merge();
}

std::string Datagen::write_fen(Datagen_Thread& datagen_thread, EvalFenStruct eval_fen, double game_result) {
    std::string resulting_fen = eval_fen.fen;
    resulting_fen += " | ";
    resulting_fen += std::to_string(eval_fen.eval);
    resulting_fen += " | ";
    resulting_fen += WDL_scores[static_cast<int>(2.0 * game_result)];

    datagen_thread.total_fens++;

    return resulting_fen;
}

bool Datagen::randomize_opening(Datagen_Thread& datagen_thread, FixedVector<Move, MAX_MOVES>& legal_moves) const {
    datagen_thread.game_length = 0;

    Position& position = datagen_thread.engine->thread_states[0].position;
    int num_random_moves = (position.fischer_random_chess ? initial_random_moves_dfrc : initial_random_moves_standard) +
                           (datagen_thread.total_fens % 2);  // To balance even/odd number of starting moves

    for (int random_move_count = 0; random_move_count < num_random_moves; random_move_count++) {

        position.set_state(position.state_stack[0], datagen_thread.engine->thread_states[0].fifty_move);
        position.get_pseudo_legal_moves<Movegen::All, true>(position.scored_moves[0]);

        legal_moves.clear();

        for (ScoredMove &scored_move: position.scored_moves[0]) {
            Move move = scored_move.move;
            bool attempt = position.make_move<NO_NNUE>(move, position.state_stack[0],
                                                       datagen_thread.engine->thread_states[0].fifty_move);

            position.undo_move<NO_NNUE>(move, position.state_stack[0], datagen_thread.engine->thread_states[0].fifty_move);

            if (attempt) legal_moves.push_back(move);
        }

        if (legal_moves.empty()) return false;

        Move random_move = legal_moves[datagen_thread.prng.rand64() % legal_moves.size()];

        position.make_move<USE_NNUE>(random_move, position.state_stack[0], datagen_thread.engine->thread_states[0].fifty_move);
        position.update_nnue(position.state_stack[0]);
        datagen_thread.game_length++;
    }

    // Verify the position has moves
    position.set_state(position.state_stack[0], datagen_thread.engine->thread_states[0].fifty_move);
    position.get_pseudo_legal_moves<Movegen::All, true>(position.scored_moves[0]);

    bool terminated = true;

    for (ScoredMove& scored_move : position.scored_moves[0]) {
        bool attempt = position.make_move<NO_NNUE>(scored_move.move, position.state_stack[0], datagen_thread.engine->thread_states[0].fifty_move);
        position.undo_move<NO_NNUE>(scored_move.move, position.state_stack[0], datagen_thread.engine->thread_states[0].fifty_move);

        if (attempt) {
            terminated = false;
            break;
        }
    }

    if (terminated) return false;

    // Verification Search
    datagen_thread.engine->soft_time_limit = max_time_per_move;
    datagen_thread.engine->soft_node_limit = 2 * soft_node_limit;

    search(*datagen_thread.engine);

    datagen_thread.engine->soft_node_limit = soft_node_limit;

    if (abs(datagen_thread.engine->search_results.score) >= opening_max_score) return false;

    return true;
}

void Datagen::datagen(Datagen_Thread& datagen_thread) {

    datagen_thread.current_stage = "start";

    datagen_thread.engine->transposition_table.resize(DEFAULT_TT_SIZE * 1048576 / 24);
    datagen_thread.engine->initialize_lmr_reductions();
    datagen_thread.engine->thread_states.emplace_back();
    datagen_thread.engine->print_thinking = false;
    // datagen_thread.engine->datagen = true;

    Position& position = datagen_thread.engine->thread_states[0].position;

    const uint64_t thread_fens_max = ceil(max_fens / threads);
    datagen_thread.total_fens = 0;

    if (datagen_thread.thread_id == 0) std::cout << "Max fens per thread: " << thread_fens_max << std::endl;

    position.set_fen(START_FEN);

    std::string file_name = "AltairData/data" + std::to_string(datagen_thread.thread_id) + ".txt";

    std::ofstream datagen_file(file_name);

    FixedVector<Move, MAX_MOVES> legal_moves{};
    FixedVector<EvalFenStruct, MAX_GAME_LENGTH + 64> game_fens{};

    datagen_thread.engine->hard_time_limit = 2 * max_time_per_move;
    datagen_thread.engine->soft_time_limit = max_time_per_move;
    datagen_thread.engine->hard_node_limit = hard_node_limit;
    datagen_thread.engine->soft_node_limit = soft_node_limit;

    while (datagen_thread.total_fens < thread_fens_max) {

        while (datagen_thread.paused && !stopped) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        }

        datagen_thread.current_stage = "loop";

        if (stopped) {
            std::cout << "Thread " << std::to_string(datagen_thread.thread_id) << " games: "
                      << std::to_string(datagen_thread.total_fens) << std::endl;
            break;
        }

        datagen_thread.current_stage = "new game";

        datagen_thread.engine->new_game();
        position.set_fen(START_FEN);

        // DFRC
        if (static_cast<int>(datagen_thread.prng.rand64() % 100) <= dfrc_chance) {
            position.fischer_random_chess = true;
            position.set_dfrc(datagen_thread.prng.rand64() % (960 * 960));
        } else {
            position.fischer_random_chess = false;
        }

        // Randomize Opening
        if (!randomize_opening(datagen_thread, legal_moves)) continue;

        double game_result = -1.0;  // No result
        int win_adjudication_count = 0;
        game_fens.clear();

        // Game loop
        while (true) {

            // Preparation
            datagen_thread.ping = true;
            datagen_thread.engine->soft_time_limit = max_time_per_move;
            datagen_thread.engine->search_results.best_move = NO_MOVE;

            bool in_check = position.is_attacked(position.get_king_pos(position.side), position.side);
            std::string current_fen = position.get_fen(datagen_thread.engine->thread_states[0].fifty_move);

            // Termination Check
            bool terminated = true;
            position.set_state(position.state_stack[0], datagen_thread.engine->thread_states[0].fifty_move);
            position.get_pseudo_legal_moves<Movegen::All, true>(position.scored_moves[0]);
            for (ScoredMove& scored_move : position.scored_moves[0]) {
                bool attempt = position.make_move<NO_NNUE>(scored_move.move, position.state_stack[0], datagen_thread.engine->thread_states[0].fifty_move);
                position.undo_move<NO_NNUE>(scored_move.move, position.state_stack[0], datagen_thread.engine->thread_states[0].fifty_move);
                if (attempt) {
                    terminated = false;
                    break;
                }
            }

            if (terminated) {
                game_result = in_check ? static_cast<double>(~position.side) : 0.5;
                break;
            }

            // Search
            search(*datagen_thread.engine);

            // Get Search info
            Move best_move = datagen_thread.engine->search_results.best_move;
            if (best_move == NO_MOVE) break;

            SCORE_TYPE score = datagen_thread.engine->search_results.score;
            SCORE_TYPE objective_score = position.side == WHITE ? score : -score;
            bool noisy = best_move.is_capture(position) || best_move.type() == MOVE_TYPE_EP ||
                         best_move.type() == MOVE_TYPE_PROMOTION;

            position.make_move<USE_NNUE>(best_move, position.state_stack[0], datagen_thread.engine->thread_states[0].fifty_move);
            position.update_nnue(position.state_stack[0]);

            EvaluationInformation evaluation_information{};
            initialize_evaluation_information(position, evaluation_information);

            // Win adjudication
            if (abs(score) >= 32000 || (
                abs(score) >= win_adjudication_score && ++win_adjudication_count >= win_adjudication_length
                )) game_result = score > 0 ? ~position.side : position.side;
            else if (abs(score) < win_adjudication_score) win_adjudication_count = 0;

            // Draw adjudications
            if (datagen_thread.engine->thread_states[0].fifty_move >= 100
                || datagen_thread.engine->thread_states[0].detect_repetition()
                || datagen_thread.game_length >= MAX_GAME_LENGTH
                || (datagen_thread.engine->thread_states[0].fifty_move >= 20 &&
                    evaluate_drawishness(position, evaluation_information) == 0.0))
                game_result = 0.5;

            if (game_result != -1.0) break;

            // Filter
            if (!noisy && !in_check) {
                game_fens.push_back({current_fen,
                                     objective_score});
            }

            datagen_thread.game_length++;
        }

        if (datagen_thread.game_length < minimum_game_length) continue;
        if (game_result == -1.0) continue;

        datagen_thread.total_games++;

        size_t fens_to_pick = std::min(fens_per_game == 0 ? game_fens.size() : fens_per_game, game_fens.size());
        size_t fens_picked  = 0;

        if (fens_per_game == 0) {
            for (EvalFenStruct& eval_fen : game_fens) {
                auto resulting_fen = write_fen(datagen_thread, eval_fen, game_result);
                datagen_file << resulting_fen << std::endl;
                fens_picked++;
            }
        }

        else {
            while (fens_picked < fens_to_pick) {
                auto next_fen_index = datagen_thread.prng.rand64() % game_fens.size();
                auto next_eval_fen = game_fens[next_fen_index];

                game_fens.pop(next_fen_index);

                auto resulting_fen = write_fen(datagen_thread, next_eval_fen, game_result);

                datagen_file << resulting_fen << std::endl;
                fens_picked++;
            }
        }

    }

    datagen_file.close();
}

std::vector<std::string> Datagen::get_file_fens(const std::string &file_name) {
    std::ifstream infile(file_name);
    std::string basic_fen, side, castling, ep, fifty, result;
    std::vector<std::string> fens;

    std::string line;
    while (std::getline(infile, line)) {
        fens.push_back(line);
    }

    infile.close();

    std::cout << file_name << " processed" << std::endl;

    return fens;
}

void Datagen::merge() {

    std::cout << "Merging Fens" << std::endl;

    std::string datagen_file_name = "AltairData/Altair";
    datagen_file_name += ENGINE_VERSION;
    datagen_file_name += "_data.txt";

    uint64_t total_fens = 0;
    std::vector<std::vector<std::string>> all_fens;

    // std::string old_file_name = "AltairData/Altair4.0.0_data_old.txt";

    all_fens.push_back(get_file_fens(datagen_file_name));
    // all_fens.push_back(get_file_fens(old_file_name));

    std::ofstream datagen_file(datagen_file_name);

    for (int i = 0; i < threads; i++) {
        std::string thread_file_name = "AltairData/data";
        thread_file_name += std::to_string(i);
        thread_file_name += ".txt";

        all_fens.push_back(get_file_fens(thread_file_name));
    }

    for (auto fens : all_fens) {
        for (int fen_i = 0; fen_i < static_cast<int>(fens.size()) - 1; fen_i++) {
            datagen_file << fens[fen_i] << std::endl;
            total_fens++;
        }
    }

    std::cout << "All " << total_fens << " fens merged" << std::endl;

    datagen_file.close();
}