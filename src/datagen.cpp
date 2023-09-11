
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
    search_threads.resize(threads);

    if (opening_chance > 0) {
        opening_fens = get_file_fens("/Users/alexandertian/Documents/UHO_XXL_+0.90_+1.19.epd");
    }

    std::cout << "Starting " << threads << " threads" << std::endl;

    for (int thread_id = 0; thread_id < threads; thread_id++) {
        search_threads.emplace_back([this, thread_id]() {
            this->datagen(thread_id);
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

void Datagen::datagen(int thread_id) {
    std::unique_ptr<Engine> engine = std::make_unique<Engine>();

    engine->transposition_table.resize(MAX_TT_SIZE);
    engine->initialize_lmr_reductions();
    engine->thread_states.emplace_back();
    engine->soft_node_limit = nodes_per_move;
    engine->print_thinking = false;

    Position& position = engine->thread_states[0].position;

    const int thread_fens_max = ceil(max_fens / threads);
    int total_fens = 0;

    if (thread_id == 0) std::cout << "Max fens per thread: " << thread_fens_max << std::endl;

    position.set_fen(START_FEN);

    std::string file_name = "AltairData/data" + std::to_string(thread_id) + ".txt";

    std::ofstream datagen_file(file_name);

    FixedVector<Move, MAX_MOVES> legal_moves{};
    FixedVector<std::string, MAX_GAME_LENGTH + 1> game_fens{};

    auto start_time_point = std::chrono::high_resolution_clock::now();

    while (total_fens < thread_fens_max) {
        if (stopped) {
            std::cout << "Thread " << std::to_string(thread_id) << " games: " << std::to_string(total_fens) << std::endl;
            break;
        }

        engine->new_game();
        position.set_fen(START_FEN);

        bool opening_success = true;
        int game_length = 0;

        if (rand() % 100 < opening_chance) {
            std::string opening_fen = opening_fens[rand() % opening_fens.size()];
            engine->thread_states[0].fifty_move = position.set_fen(opening_fen);
            game_length = 9;
        }

        else {
            for (int random_move_count = 0;
                 random_move_count < initial_random_moves + (total_fens % 2); random_move_count++) {
                position.set_state(position.state_stack[0], engine->thread_states[0].fifty_move);
                position.get_pseudo_legal_moves(position.scored_moves[0]);

                legal_moves.clear();

                for (ScoredMove &scored_move: position.scored_moves[0]) {
                    Move move = scored_move.move;
                    bool attempt = position.make_move(move, position.state_stack[0],
                                                      engine->thread_states[0].fifty_move);

                    if (attempt) legal_moves.push_back(move);

                    position.undo_move(move, position.state_stack[0], engine->thread_states[0].fifty_move);
                }

                if (legal_moves.empty()) {
                    opening_success = false;
                    break;
                }

                Move random_move = legal_moves[rand() % legal_moves.size()];

                position.make_move(random_move, position.state_stack[0], engine->thread_states[0].fifty_move);
                game_length++;
            }
        }

        if (!opening_success) continue;

        // Verification Search
        engine->hard_time_limit = max_time_per_move;
        engine->soft_time_limit = TIME_INF;
        engine->soft_node_limit = 0;
        engine->max_depth = 12;

        lazy_smp_search(*engine);

        if (abs(engine->search_results.score) >= opening_max_score) continue;

        engine->soft_node_limit = nodes_per_move;
        engine->max_depth = MAX_AB_DEPTH - 1;

        double game_result = -1.0;  // No result
        int adjudication_count = 0;
        game_fens.clear();

        while (true) {

            engine->hard_time_limit = max_time_per_move;
            engine->soft_time_limit = TIME_INF;
            engine->search_results.best_move = NO_MOVE;

            lazy_smp_search(*engine);

            Move best_move = engine->search_results.best_move;
            SCORE_TYPE score = engine->search_results.score;

            // Depth was not finished
            if (best_move == NO_MOVE) break;

            bool noisy = best_move.is_capture(position) || best_move.type() == MOVE_TYPE_EP;

            position.make_move(best_move, position.state_stack[0], engine->thread_states[0].fifty_move);

            bool in_check = position.is_attacked(position.get_king_pos(position.side), position.side);

            // Score adjudication
            if (abs(score) >= adjudication_score) {
                adjudication_count++;
                if (adjudication_count >= adjudication_length) {
                    game_result = score > 0 ? ~position.side : position.side;
                    break;
                }
            } else {
                adjudication_count = 0;
            }

            if (engine->thread_states[0].fifty_move >= 100 || engine->thread_states[0].detect_repetition()) {
                game_result = 0.5;
                break;
            }

            // Check for drawn positions after 100 plies (50 full moves)
            if (game_length >= 100) {
                EvaluationInformation evaluation_information{};
                initialize_evaluation_information(position, evaluation_information);

                double drawishness = evaluate_drawishness(position, evaluation_information);

                if (drawishness == 0.0) {
                    game_result = 0.5;
                    break;
                }
            }

            if (game_length >= MAX_GAME_LENGTH) {
                game_result = 0.5;
                break;
            }

            position.set_state(position.state_stack[0], engine->thread_states[0].fifty_move);
            position.get_pseudo_legal_moves(position.scored_moves[0]);

            int legal_move_count = 0;

            for (ScoredMove& scored_move : position.scored_moves[0]) {
                Move move = scored_move.move;
                bool attempt = position.make_move(move, position.state_stack[0], engine->thread_states[0].fifty_move);
                position.undo_move(move, position.state_stack[0], engine->thread_states[0].fifty_move);

                if (attempt) {
                    legal_move_count++;
                    break;
                }
            }

            if (legal_move_count == 0) {
                game_result = in_check ?
                              static_cast<double>(~position.side) : 0.5;
                break;
            }

            if (!noisy && !in_check) {
                game_fens.push_back(position.get_fen(engine->thread_states[0].fifty_move));
            }

            game_length++;

        }

        if (game_length < minimum_game_length) continue;

        if (game_result == -1.0) continue;

        for (const auto &fen : game_fens) {
            std::string result = fen;
            result += "; [";
            result += WDL_scores[static_cast<int>(2.0 * game_result)];
            result += "]";

            datagen_file << result << std::endl;
            total_fens++;

            if (total_fens % 1000 == 0) {
                auto end_time_point = std::chrono::high_resolution_clock::now();
                auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_point
                                                                                    - start_time_point);

                uint64_t elapsed_time = ms_int.count();
                elapsed_time = std::max<uint64_t>(elapsed_time, 1);
                auto fps = static_cast<uint64_t>(static_cast<double>(total_fens) / static_cast<double>(elapsed_time) * 1000);

                std::cout << "Thread " << thread_id
                          << " fens: " << total_fens
                          << " fps: " << fps
                          << std::endl;
            }
        }

    }

    datagen_file.close();
}

std::vector<std::string> Datagen::get_file_fens(const std::string &file_name) {
    std::ifstream infile(file_name);
    std::string basic_fen, side, castling, ep, fifty, result;
    std::vector<std::string> fens;
    while (infile >> basic_fen >> side >> castling >> ep >> fifty >> result) {
        std::string fen = basic_fen;
        fen += " ";
        fen += side;
        fen += " ";
        fen += castling;
        fen += " ";
        fen += ep;
        fen += " ";
        fen += fifty;
        fen += " ";
        fen += result;
        fen += "\n";

        fens.push_back(fen);
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
            datagen_file << fens[fen_i];
            total_fens++;
        }
    }

    std::cout << "All " << total_fens << " fens merged" << std::endl;

    datagen_file.close();
}