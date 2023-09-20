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


void Datagen::start_datagen() {
    stopped = false;
    std::vector<std::thread> search_threads;
    search_threads.reserve(threads);

    if (opening_chance > 0) {
        // opening_fens = get_file_fens("/Users/alexandertian/Documents/UHO_XXL_+0.90_+1.19.epd");
        opening_fens = get_file_fens("/Users/alexandertian/Documents/noob_4moves.epd");
    }

    std::cout << "Starting " << threads << " threads" << std::endl;

    for (int thread_id = 0; thread_id < threads; thread_id++) {
        search_threads.emplace_back([this, thread_id]() {
            this->datagen(Datagen_Thread(thread_id));
        });
    }

    std::string msg;
    while (getline(std::cin, msg)) {
        if (msg == "stop") {
            stopped = true;
            break;
        }
    }

    for (int thread_id = 0; thread_id < threads; thread_id++) {
        search_threads[thread_id].join();
    }

    std::cout << "All threads joined" << std::endl;

    merge();
}

std::string Datagen::write_fen(Datagen_Thread& datagen_thread, std::string& fen, double game_result) {
    std::string resulting_fen = fen;
    resulting_fen += " [";
    resulting_fen += WDL_scores[static_cast<int>(2.0 * game_result)];
    resulting_fen += "]";

    datagen_thread.total_fens++;

    if (datagen_thread.total_fens % 1000 == 0) {
        auto end_time_point = std::chrono::high_resolution_clock::now();
        auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_point
                                                                            - datagen_thread.start_time_point);

        uint64_t elapsed_time = ms_int.count();
        elapsed_time = std::max<uint64_t>(elapsed_time, 1);
        auto fps = static_cast<uint64_t>(static_cast<double>(datagen_thread.total_fens) / static_cast<double>(elapsed_time) * 1000);

        std::cout << "Thread "  << datagen_thread.thread_id
                  << " games: " << datagen_thread.total_games
                  << " fens: "  << datagen_thread.total_fens
                  << " fps: "   << fps
                  << std::endl;
    }

    return resulting_fen;
}

bool Datagen::randomize_opening(Datagen_Thread& datagen_thread, FixedVector<Move, MAX_MOVES>& legal_moves) const {
    Position& position = datagen_thread.engine->thread_states[0].position;
    for (int random_move_count = 0; random_move_count < initial_random_moves + (datagen_thread.total_fens % 2); random_move_count++) {
        position.set_state(position.state_stack[0], datagen_thread.engine->thread_states[0].fifty_move);
        position.get_pseudo_legal_moves(position.scored_moves[0]);

        legal_moves.clear();

        for (ScoredMove &scored_move: position.scored_moves[0]) {
            Move move = scored_move.move;
            bool attempt = position.make_move(move, position.state_stack[0],
                                              datagen_thread.engine->thread_states[0].fifty_move);

            if (attempt) legal_moves.push_back(move);

            position.undo_move(move, position.state_stack[0], datagen_thread.engine->thread_states[0].fifty_move);
        }

        if (legal_moves.empty()) {
            return false;
        }

        Move random_move = legal_moves[datagen_thread.prng.rand64() % legal_moves.size()];

        position.make_move(random_move, position.state_stack[0], datagen_thread.engine->thread_states[0].fifty_move);
        datagen_thread.game_length++;
    }

    // Verification Search
    datagen_thread.engine->hard_time_limit = max_time_per_move;
    datagen_thread.engine->soft_time_limit = TIME_INF;
    datagen_thread.engine->soft_node_limit = 3 * nodes_per_move;

    lazy_smp_search(*datagen_thread.engine);

    if (abs(datagen_thread.engine->search_results.score) >= opening_max_score) return false;

    return true;
}

void Datagen::datagen(Datagen_Thread datagen_thread) {

    datagen_thread.engine->transposition_table.resize(MAX_TT_SIZE);
    datagen_thread.engine->initialize_lmr_reductions();
    datagen_thread.engine->thread_states.emplace_back();
    datagen_thread.engine->print_thinking = false;

    Position& position = datagen_thread.engine->thread_states[0].position;

    const int thread_fens_max = ceil(max_fens / threads);
    datagen_thread.total_fens = 0;

    if (datagen_thread.thread_id == 0) std::cout << "Max fens per thread: " << thread_fens_max << std::endl;

    position.set_fen(START_FEN);

    std::string file_name = "AltairData/data" + std::to_string(datagen_thread.thread_id) + ".txt";

    std::ofstream datagen_file(file_name);

    FixedVector<Move, MAX_MOVES> legal_moves{};
    FixedVector<std::string, MAX_GAME_LENGTH + 1> game_fens{};

    datagen_thread.start_time_point = std::chrono::high_resolution_clock::now();

    while (datagen_thread.total_fens < thread_fens_max) {
        if (stopped) {
            std::cout << "Thread " << std::to_string(datagen_thread.thread_id) << " games: "
                      << std::to_string(datagen_thread.total_fens) << std::endl;
            break;
        }

        datagen_thread.engine->new_game();
        position.set_fen(START_FEN);

        if (datagen_thread.prng.rand64() % 100 < opening_chance) {
            std::string opening_fen = opening_fens[datagen_thread.prng.rand64() % opening_fens.size()];
            datagen_thread.engine->thread_states[0].fifty_move = position.set_fen(opening_fen);
            datagen_thread.game_length = 8;
        }

        else if (!randomize_opening(datagen_thread, legal_moves)) continue;

        double game_result = -1.0;  // No result
        int win_adjudication_count  = 0;
        int draw_adjudication_count = 0;

        game_fens.clear();

        while (true) {

            datagen_thread.engine->hard_time_limit = max_time_per_move;
            datagen_thread.engine->soft_time_limit = TIME_INF;
            datagen_thread.engine->search_results.best_move = NO_MOVE;

            datagen_thread.engine->soft_node_limit = nodes_per_move;

            lazy_smp_search(*datagen_thread.engine);

            Move best_move = datagen_thread.engine->search_results.best_move;
            SCORE_TYPE score = datagen_thread.engine->search_results.score;

            // Depth was not finished
            if (best_move == NO_MOVE) break;

            bool noisy = best_move.is_capture(position) || best_move.type() == MOVE_TYPE_EP ||
                         best_move.type() == MOVE_TYPE_PROMOTION;

            position.make_move(best_move, position.state_stack[0], datagen_thread.engine->thread_states[0].fifty_move);

            bool in_check = position.is_attacked(position.get_king_pos(position.side), position.side);

            EvaluationInformation evaluation_information{};
            initialize_evaluation_information(position, evaluation_information);

            position.set_state(position.state_stack[0], datagen_thread.engine->thread_states[0].fifty_move);
            position.get_pseudo_legal_moves(position.scored_moves[0]);

            bool terminated = true;

            for (ScoredMove& scored_move : position.scored_moves[0]) {
                bool attempt = position.make_move(scored_move.move, position.state_stack[0], datagen_thread.engine->thread_states[0].fifty_move);
                position.undo_move(scored_move.move, position.state_stack[0], datagen_thread.engine->thread_states[0].fifty_move);

                if (attempt) {
                    terminated = false;
                    break;
                }
            }

            if (terminated) {
                game_result = in_check ?
                              static_cast<double>(~position.side) : 0.5;
                break;
            }

            if (datagen_thread.engine->thread_states[0].fifty_move >= 100 || datagen_thread.engine->thread_states[0].detect_repetition())
                game_result = 0.5;

            if (datagen_thread.game_length >= MAX_GAME_LENGTH)
                game_result = 0.5;

            double drawishness = evaluate_drawishness(position, evaluation_information);

            // Win adjudication
            if ((abs(score) >= win_adjudication_score) &&
                ++win_adjudication_count >= win_adjudication_length) game_result = score > 0 ? ~position.side : position.side;
            else win_adjudication_count = 0;

            // Draw adjudication
            if (datagen_thread.game_length >= draw_adjudication_plies &&
                (abs(score) <= draw_adjudication_score || drawishness == 0.0) &&
                ++draw_adjudication_count >= draw_adjudication_length) game_result = 0.5;
            else draw_adjudication_count = 0;

            if (game_result != -1.0) break;

            // Filter
            if (!noisy && !in_check && drawishness >= 0.9)
                game_fens.push_back(position.get_fen(datagen_thread.engine->thread_states[0].fifty_move));

            datagen_thread.game_length++;

        }

        if (datagen_thread.game_length < minimum_game_length) continue;

        if (game_result == -1.0) continue;

        datagen_thread.total_games++;

        size_t fens_to_pick = std::min(fens_per_game == 0 ? game_fens.size() : fens_per_game, game_fens.size());
        size_t fens_picked  = 0;

        while (fens_picked < fens_to_pick) {
            auto next_fen_index = datagen_thread.prng.rand64() % game_fens.size();
            auto next_fen = game_fens[next_fen_index];

            game_fens.pop(next_fen_index);

            auto resulting_fen = write_fen(datagen_thread, next_fen, game_result);

            datagen_file << resulting_fen << std::endl;
            fens_picked++;
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