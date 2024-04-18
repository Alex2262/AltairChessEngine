

#include <iostream>
#include <algorithm>
#include <cmath>
#include "uci.h"
#include "useful.h"
#include "move.h"
#include "search.h"
#include "evaluation.h"
#include "perft.h"
#include "bench.h"
#include "see.h"
#include "timeman.h"

void UCI::initialize_uci() const {
    engine->resize_tt(DEFAULT_TT_SIZE);

    engine->initialize_lmr_reductions();

    engine->thread_states.emplace_back();

    Position& position = engine->thread_states[0].position;
    position.set_fen(START_FEN);
}


void UCI::parse_position() {
    if (tokens.size() < 2) return;

    Position& position = engine->thread_states[0].position;

    int next_idx;
    engine->thread_states[0].game_ply = 0;

    FenInfo fen_info;

    if (tokens[1] == "startpos") {
        fen_info = position.set_fen(START_FEN);
        next_idx = 2;
    }

    else if (tokens[1] == "dfrc") {
        if (!position.fischer_random_chess) {
            std::cout << "Fischer Random Chess not enabled" << std::endl;
            return;
        }

        fen_info = position.set_fen(START_FEN);

        int dfrc_index = std::stoi(tokens[2]);
        position.set_dfrc(dfrc_index);
        next_idx = 3;

        std::cout << position << std::endl;
    }

    else if (tokens[1] == "fen") {
        std::string fen;
        for (int i = 2; i < 8; i++) {
            fen += tokens[i];
            fen += " ";
        }

        fen_info = position.set_fen(fen);
        next_idx = 8;
    }

    else return;

    engine->thread_states[0].fifty_move = fen_info.fifty_move_counter;
    engine->thread_states[0].base_full_moves = fen_info.full_move_counter;

    if (static_cast<int>(tokens.size()) <= next_idx || tokens[next_idx] != "moves") return;

    for (int i = next_idx + 1; i < static_cast<int>(tokens.size()); i++) {
        Move move = Move(position, tokens[i]);
        last_move = move;

        position.make_move<USE_NNUE>(move, position.state_stack[0], engine->thread_states[0].fifty_move);
        position.update_nnue(position.state_stack[0]);

        engine->thread_states[0].game_ply++;
        engine->thread_states[0].repetition_table[engine->thread_states[0].game_ply] = position.hash_key;
    }
}


void UCI::parse_go() {

    Position& position = engine->thread_states[0].position;

    PLY_TYPE d = 0, perft_depth = 0;
    double wtime = 0, btime = 0, winc = 0, binc = 0, movetime = 0;
    long movestogo = 0;
    bool infinite = false;

    for (int i = 1; i < static_cast<int>(tokens.size()); i += 2) {
        std::string type = tokens[i];

        uint64_t value = 0;

        if (static_cast<int>(tokens.size()) > i + 1) value = std::stoi(tokens[i + 1]);

        if (type == "depth") d = static_cast<PLY_TYPE>(value);

        else if (type == "perft") perft_depth = static_cast<PLY_TYPE>(value);

        else if (type == "nodes") {
            engine->hard_node_limit = value;
            engine->soft_node_limit = value;
        }

        else if (type == "movetime") movetime = static_cast<double>(value);

        else if (type == "wtime") wtime = static_cast<double>(value);
        else if (type == "btime") btime = static_cast<double>(value);

        else if (type == "winc") winc = static_cast<double>(value);
        else if (type == "binc") binc = static_cast<double>(value);

        else if (type == "movestogo") movestogo = static_cast<long>(value);
        else if (type == "infinite") infinite = true;

    }

    if (perft_depth > 0) {
        uci_perft(position, perft_depth, 0);
        return;
    }
    if (infinite || (d && tokens.size() == 3)) {
        engine->hard_time_limit = TIME_INF;
        engine->soft_time_limit = TIME_INF;
    }
    else {
        double self_time = (position.side == 0) ? wtime : btime;
        double inc = (position.side == 0) ? winc : binc;

        time_handler(*engine, std::max<double>(self_time, 0.0), inc, movetime, movestogo);
    }

    if (d) engine->max_depth = d;

    engine->stopped = true;
    if (!search_threads.empty()) {
        search_threads[0].join();

        while (!engine->thread_states[0].terminated);  // to prevent some stupid exceptions
        if (engine->thread_states[0].terminated) search_threads.erase(search_threads.end() - 1);
    }

    search_threads.emplace_back(search, std::ref(*engine));

    //iterative_search(engine, position);
}


void UCI::uci_loop() {

    std::cout << std::string(ENGINE_NAME) + " " + std::string(ENGINE_VERSION) + " by " + std::string(ENGINE_AUTHOR) << std::endl;
    while (getline(std::cin, msg)) {
        tokens.clear();

        tokens = split(msg, ' ');

        if (msg == "quit") {
            break;
        }

        if (msg == "stop") {
            engine->stopped = true;
            if (!search_threads.empty()) {
                search_threads[0].join();

                while (!engine->thread_states[0].terminated);  // to prevent some stupid exceptions
                if (engine->thread_states[0].terminated) search_threads.erase(search_threads.end() - 1);
            }
        }

        else if (msg == "uci") {
            std::cout << "id name " + std::string(ENGINE_NAME) + " " + std::string(ENGINE_VERSION) << std::endl;
            std::cout << "id author Alexander Tian" << std::endl;

            std::cout << "option name Hash type spin default " << DEFAULT_TT_SIZE << " min " << 1 << " max " << 24576
                      << std::endl;

            std::cout << "option name Threads type spin default " << 1 << " min " << 1 << " max " << 1024
                      << std::endl;

            std::cout << "option name UCI_Chess960 type check default false"
                      << std::endl;

            std::cout << "option name UCI_ShowWDL type check default false"
                      << std::endl;

            std::cout << "option name UseNNUE type check default true"
                      << std::endl;

            std::cout << "option name MultiPV type spin default " << 1 << " min " << 1 << " max " << 256
                      << std::endl;

            std::cout << "option name Move Overhead type spin default " << 50 << " min " << 0 << " max " << 1000
                      << std::endl;

#ifdef DO_SEARCH_TUNING
            for (auto& param : search_params.all_parameters) {
                std::cout << "option name " << param->name
                          << " type spin default " << param->v
                          << " min " << param->min
                          << " max " << param->max
                          << std::endl;

            }
#endif
            std::cout << "uciok" << std::endl;
        }

        else if (tokens[0] == "setoption" && tokens.size() >= 5) {
            if (tokens[2] == "Hash") {
                int mb = std::stoi(tokens[4]);
                mb = std::clamp<int>(mb, 1, 32768);

                engine->resize_tt(mb);
                std::cout << engine->transposition_table.size() << " number of hash entries initialized" << std::endl;
            }

            else if (tokens[2] == "Threads") {
                engine->num_threads = std::clamp(std::stoi(tokens[4]), 1, 1024);
                engine->thread_states.resize(engine->num_threads);
            }

            else if (tokens[2] == "UCI_Chess960") {
                engine->thread_states[0].position.fischer_random_chess = tokens[4] == "true";
            }

            else if (tokens[2] == "UCI_ShowWDL") {
                engine->show_wdl = tokens[4] == "true";
            }

            else if (tokens[2] == "UseNNUE") {
                engine->use_nnue = tokens[4] == "true";
            }

            else if (tokens[2] == "MultiPV") {
                engine->multi_pv = std::clamp(std::stoi(tokens[4]), 1, 256);
            }

            else if (tokens[2] == "Move" && tokens[3] == "Overhead") {
                engine->move_overhead = std::stoi(tokens[5]);
            }

            else {
#ifdef DO_SEARCH_TUNING
                bool param_changed = false;
                for (auto& param : search_params.all_parameters) {
                    if (tokens[2] == param->name) {
                        param->v = std::stoi(tokens[4]);
                        param_changed = true;
                    }
                }

                if (param_changed) {
                    engine->initialize_lmr_reductions();
                }
#endif
            }
        }

        else if (msg == "isready") {
            std::cout << "readyok" << std::endl;
        }

        else if (msg == "ucinewgame") {
            Position& position = engine->thread_states[0].position;
            position.set_fen(START_FEN);
            engine->new_game();
        }

        else if (tokens[0] == "position") {
            parse_position();
        }

        else if (tokens[0] == "go") {
            parse_go();
        }

        else if (tokens[0] == "bench") {
            run_bench(*engine, BENCH_DEPTH);
        }

        else if (tokens[0] == "stats") {

#ifdef SHOW_STATISTICS
            print_statistics(engine->search_results);
#endif
        }

        else if (tokens[0] == "search_tune_config") {
#ifdef DO_SEARCH_TUNING
            print_search_tuning_config();
#endif
        }

        else if (tokens[0] == "evaluate") {
            SCORE_TYPE evaluation = engine->use_nnue ? engine->evaluate<USE_NNUE>(0) :
                                                       engine->evaluate<NO_NNUE >(0);
            std::cout << evaluation << std::endl;
        }

        else if (tokens[0] == "see") {
            Position& position = engine->thread_states[0].position;
            std::cout << get_static_exchange_evaluation(position, Move(position, tokens[1]), 1) << std::endl;
        }

        else if (tokens[0] == "fen") {
            Position& position = engine->thread_states[0].position;
            std::cout << position.get_fen(engine->thread_states[0].fifty_move) << std::endl;
        }
    }
}