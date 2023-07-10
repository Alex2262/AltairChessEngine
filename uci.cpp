//
// Created by Alex Tian on 9/30/2022.
//

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

void UCI::initialize_uci() const {
    engine->transposition_table.resize(MAX_TT_SIZE);

    engine->initialize_lmr_reductions();

    engine->thread_states.emplace_back();

    Position& position = engine->thread_states[0].position;
    position.set_fen(START_FEN);

    // std::cout << engine->transposition_table.size() << " number of hash entries initialized" << std::endl;
}


void  UCI::time_handler(double self_time, double inc, double movetime, long movestogo) const {
    double rate = 20;
    double time_amt;

    Position& position = engine->thread_states[0].position;

    if (position.is_attacked(position.get_king_pos(position.side), position.side)) rate -= 3;
    if (last_move.is_capture(position)) rate -= 1.5;

    if (movetime > 0) time_amt = movetime * 0.9;
    else if (inc > 0 && movestogo > 0) {
        time_amt = (self_time * 0.8 / static_cast<double>(movestogo)) * (20 / rate) + (inc / 2.0);
        if (time_amt > self_time * 0.8) time_amt = self_time * 0.85 + (inc / 2.0);
    }
    else if (inc > 0) {

        // we always want to have more time than our increment.
        // This ensures we use a lot of our remaining time, but
        // since our increment is larger, it doesn't matter.
        if (self_time < inc) time_amt = self_time / (rate / 10);
        else {
            // If our remaining time is less than the boundary, we should use less time than our increment
            // to get back above the boundary.
            double bound = inc / 2.5 * sqrt(60000.0 / inc);
            if (inc > bound / 2.5) bound = inc * sqrt(90000.0 / inc);
            if (inc > bound / 2.5) bound = 1.5 * inc * sqrt(200000.0 / inc);
            time_amt = std::max(inc * 0.975 + (self_time - bound) / (rate * 1.8), self_time / (rate * 10));
        }
    }
    else if (movestogo > 0) {
        time_amt = (self_time * 0.9 / static_cast<double>(movestogo)) * (20 / rate);
        if (time_amt > self_time * 0.9) time_amt = self_time * 0.95;
    }
    else if (self_time > 0) time_amt = self_time / (rate + 6);
    else time_amt = static_cast<double>(engine->hard_time_limit);

    engine->hard_time_limit = static_cast<uint64_t>(time_amt * 2.22);
    engine->soft_time_limit = static_cast<uint64_t>(time_amt * 0.66);

    if (engine->hard_time_limit > static_cast<uint64_t>(self_time * 0.7)) {
        for (int multiplier = 18; multiplier >= 10; multiplier -= 1) {
            engine->hard_time_limit = static_cast<uint64_t>(time_amt * (multiplier / 10.0));
            if (engine->hard_time_limit <= static_cast<uint64_t>(self_time * 0.7)) break;
        }
    }

    if (engine->hard_time_limit > static_cast<uint64_t>(movetime) && movetime != 0.0) {
        engine->hard_time_limit = static_cast<uint64_t>(time_amt);
    }

    // std::cout << time_amt << " " << engine->hard_time_limit << " " << engine->soft_time_limit << std::endl;
}


void UCI::parse_position() {
    if (tokens.size() < 2) return;

    Position& position = engine->thread_states[0].position;

    int next_idx;
    engine->thread_states[0].game_ply = 0;

    if (tokens[1] == "startpos") {
        engine->thread_states[0].fifty_move = position.set_fen(START_FEN);
        next_idx = 2;
    }

    else if (tokens[1] == "fen") {
        std::string fen;
        for (int i = 2; i < 8; i++) {
            fen += tokens[i];
            fen += " ";
        }

        engine->thread_states[0].fifty_move = position.set_fen(fen);
        next_idx = 8;
    }

    else return;

    if (static_cast<int>(tokens.size()) <= next_idx || tokens[next_idx] != "moves") return;

    for (int i = next_idx + 1; i < static_cast<int>(tokens.size()); i++) {
        // std::cout << tokens[i] << std::endl;
        Move move = Move(position, tokens[i]);
        last_move = move;
        // std::cout << move << " " << get_uci_from_move(move) << std::endl;
        position.make_move(move, position.state_stack[0], engine->thread_states[0].fifty_move);

        engine->thread_states[0].game_ply++;
        engine->thread_states[0].repetition_table[engine->thread_states[0].game_ply] = position.hash_key;
    }

    // std::cout << engine.detect_repetition() << std::endl;

    // position.print_board();
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

        else if (type == "nodes") engine->max_nodes = value;

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

        time_handler(std::max<double>(self_time - engine->move_overhead, 0.0), inc, movetime, movestogo);
    }

    if (d) engine->max_depth = d;

    engine->stopped = true;
    if (!search_threads.empty()) {
        search_threads[0].join();

        while (!engine->thread_states[0].terminated);  // to prevent some stupid exceptions
        if (engine->thread_states[0].terminated) search_threads.erase(search_threads.end() - 1);
    }

    search_threads.emplace_back(lazy_smp_search, std::ref(*engine));

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

            std::cout << "option name Hash type spin default " << 64 << " min " << 1 << " max " << 1024
                      << std::endl;

            std::cout << "option name nodes type spin default " << 0 << " min " << 0 << " max " << 2147483647
                      << std::endl;

            std::cout << "option name Threads type spin default " << 1 << " min " << 1 << " max " << 1024
                      << std::endl;

            std::cout << "option name UCI_Chess960 type check default " << false
                      << std::endl;

            std::cout << "option name Statistics type check default " << false
                      << std::endl;

            std::cout << "option name Move Overhead type spin default " << 10 << " min " << 0 << " max " << 1000
                      << std::endl;

            if (engine->do_tuning) {
                for (auto & i : engine->tuning_parameters.tuning_parameter_array) {
                    std::cout << "option name " << i.name
                              << " type spin default " << i.value
                              << " min " << i.min
                              << " max " << i.max
                              << std::endl;

                }
            }

            if (engine->thread_states[0].do_move_ordering_tuning) {
                for (auto & i : engine->thread_states[0].move_ordering_parameters.tuning_parameter_array) {
                    std::cout << "option name " << i.name
                              << " type spin default " << i.value
                              << " min " << i.min
                              << " max " << i.max
                              << std::endl;

                }
            }

            std::cout << "uciok" << std::endl;
        }

        else if (tokens[0] == "setoption" && tokens.size() >= 5) {
            if (tokens[2] == "Hash") {
                int mb = std::stoi(tokens[4]);
                mb = std::min(1024, std::max(1, mb));
                engine->transposition_table.resize(mb * (1000000 / 24));
                std::cout << engine->transposition_table.size() << " number of hash entries initialized" << std::endl;
            }

            else if (tokens[2] == "Threads") {
                engine->num_threads = std::clamp(std::stoi(tokens[4]), 1, 1024);
                engine->thread_states.resize(engine->num_threads);
            }

            else if (tokens[2] == "nodes") {
                uint64_t max_nodes = std::stoi(tokens[4]);
                engine->max_nodes = max_nodes;
                std::cout << "max nodes set to " << engine->max_nodes << std::endl;
            }

            else if (tokens[2] == "UCI_Chess960") {
                engine->thread_states[0].position.fischer_random_chess = tokens[4] == "true";
            }

            else if (tokens[2] == "Statistics") {
                engine->show_stats = tokens[4] == "true";
            }

            else if (tokens[2] == "Move" && tokens[3] == "Overhead") {
                engine->move_overhead = std::stoi(tokens[5]);
            }

            else {
                if (engine->do_tuning) {
                    for (auto & i : engine->tuning_parameters.tuning_parameter_array) {
                        if (tokens[2] == i.name) {
                            i.value = std::stoi(tokens[4]);
                        }
                    }
                }

                if (engine->thread_states[0].do_move_ordering_tuning) {
                    for (auto & i : engine->thread_states[0].move_ordering_parameters.tuning_parameter_array) {
                        if (tokens[2] == i.name) {
                            i.value = std::stoi(tokens[4]);
                        }
                    }
                }
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
            if (!engine->show_stats) {
                std::cout << "Statistics UCI option has not been enabled" << std::endl;
                continue;
            }

            print_statistics(engine->search_results);
        }

        else if (tokens[0] == "search_tune_wf" && engine->do_tuning) {
            print_search_tuning_config(engine->tuning_parameters);
        }

        else if (tokens[0] == "move_ordering_tune_wf" && engine->thread_states[0].do_move_ordering_tuning) {
            print_move_ordering_tuning_config(engine->thread_states[0].move_ordering_parameters);
        }

        else if (tokens[0] == "evaluate") {
            Position& position = engine->thread_states[0].position;
            std::cout << evaluate(position) << std::endl;
        }

        else if (tokens[0] == "see") {
            Position& position = engine->thread_states[0].position;
            std::cout << get_static_exchange_evaluation(position, Move(position, tokens[1]), 1);
        }
    }
}