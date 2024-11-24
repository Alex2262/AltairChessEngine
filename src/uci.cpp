

#include <algorithm>
#include <cmath>
#include "uci.h"
#include "useful.h"
#include "move.h"
#include "search.h"
#include "evaluation.h"
#include "timeman.h"

void UCI::initialize_uci() {
    engine->resize_tt(DEFAULT_TT_SIZE);

    engine->initialize_lmr_reductions();

    Position& position = engine->main_thread.position;
    position.set_fen(START_FEN);

    moves.clear();
}


void UCI::parse_position_moves() {
    Position& position = engine->main_thread.position;
    original_fen_info = position.set_fen(original_fen);

    engine->main_thread.fifty_move = original_fen_info.fifty_move_counter;
    engine->main_thread.base_full_moves = original_fen_info.full_move_counter;

    for (Move move : moves) {
        position.make_move(move, position.state_stack[0], engine->main_thread.fifty_move);

        engine->main_thread.game_ply++;
        engine->main_thread.repetition_table[engine->main_thread.game_ply] = position.hash_key;
    }
}


bool compare_fen(std::string& fen1, std::string& fen2) {
    std::string rf1 = reduce_fen_string(fen1);
    std::string rf2 = reduce_fen_string(fen2);

    std::vector<std::string> ft1 = split(rf1, ' ');
    std::vector<std::string> ft2 = split(rf2, ' ');

    if (ft1[0] != ft2[0]) return false;
    if (ft1[1] != ft2[1]) return false;

    // technically should check index 2 and 3, but some programs don't give those correct.
    // index 0 and 1 should always uniquely determine one position from another from an original position

    return true;
}


void UCI::update_position(std::string& given) {
    Position& position = engine->main_thread.position;

    position.set_state(position.state_stack[0], original_fen_info.fifty_move_counter);
    position.get_pseudo_legal_moves(position.scored_moves[0], Movegen::All, true);

    Move last_move = NO_MOVE;

    for (ScoredMove& scored_move : position.scored_moves[0]) {
        Move move = scored_move.move;
        bool attempt = position.make_move(move, position.state_stack[0], original_fen_info.fifty_move_counter);

        if (!attempt) {
            position.undo_move(move, position.state_stack[0], original_fen_info.fifty_move_counter);
            continue;
        }

        std::string new_fen = position.get_fen(original_fen_info.fifty_move_counter);
        position.undo_move(move, position.state_stack[0], original_fen_info.fifty_move_counter);

        if (compare_fen(given, new_fen)) {
            last_move = move;
            break;
        }
    }

    if (last_move == NO_MOVE) {
        original_fen_info = position.set_fen(given);
        original_fen = given;

        engine->main_thread.fifty_move = original_fen_info.fifty_move_counter;
        engine->main_thread.base_full_moves = original_fen_info.full_move_counter;

        moves.clear();

        return;
    }

    moves.push_back(last_move);
    parse_position_moves();
}


void UCI::parse_position() {
    if (tokens.size() < 2) return;

    Position& position = engine->main_thread.position;

    int next_idx;
    engine->main_thread.game_ply = 0;

    FenInfo fen_info;
    std::string given;

    if (tokens[1] == "startpos") {
        fen_info = position.set_fen(START_FEN);
        next_idx = 2;
    }

    else if (tokens[1] == "fen") {
        std::string fen;
        for (int i = 2; i < 8; i++) {
            fen += tokens[i];
            fen += " ";
        }

        given = fen;
        next_idx = 8;
    }

    else return;

    if (static_cast<int>(tokens.size()) <= next_idx || tokens[next_idx] != "moves") {
        if (!given.empty()) update_position(given);
        return;
    }

    fen_info = position.set_fen(given);
    engine->main_thread.fifty_move = fen_info.fifty_move_counter;
    engine->main_thread.base_full_moves = fen_info.full_move_counter;

    for (int i = next_idx + 1; i < static_cast<int>(tokens.size()); i++) {
        Move move = Move(position, tokens[i]);

        position.make_move(move, position.state_stack[0], engine->main_thread.fifty_move);

        engine->main_thread.game_ply++;
        engine->main_thread.repetition_table[engine->main_thread.game_ply] = position.hash_key;
    }
}


void UCI::parse_go() {

    Position& position = engine->main_thread.position;

    PLY_TYPE d = 0;
    double wtime = 0, btime = 0, winc = 0, binc = 0, movetime = 0;
    bool infinite = false;

    for (int i = 1; i < static_cast<int>(tokens.size()); i += 2) {
        std::string type = tokens[i];

        uint64_t value = 0;

        if (static_cast<int>(tokens.size()) > i + 1) value = std::stoi(tokens[i + 1]);

        if (type == "depth") d = static_cast<PLY_TYPE>(value);

        else if (type == "nodes") {
            engine->hard_node_limit = value;
            engine->soft_node_limit = value;
        }

        else if (type == "movetime") movetime = static_cast<double>(value);

        else if (type == "wtime") wtime = static_cast<double>(value);
        else if (type == "btime") btime = static_cast<double>(value);

        else if (type == "winc") winc = static_cast<double>(value);
        else if (type == "binc") binc = static_cast<double>(value);

        else if (type == "infinite") infinite = true;

    }

    if (infinite || (d && tokens.size() == 3)) {
        engine->hard_time_limit = TIME_INF;
        engine->soft_time_limit = TIME_INF;
    }
    else {
        double self_time = (position.side == 0) ? wtime : btime;
        double inc = (position.side == 0) ? winc : binc;

        time_handler(*engine, std::max<double>(self_time, 0.0), inc, movetime);
    }

    if (d) engine->max_depth = d;

    engine->stopped = true;
    search(*engine);
}


void UCI::uci_loop() {

    printf(ENGINE_NAME);
    printf(" ");
    printf(ENGINE_VERSION);
    printf(" by ");
    printf(ENGINE_AUTHOR);
    printf("\n");

    char buffer[1024];

    while (std::scanf(" %[^\n]", buffer) != EOF) {
        msg = buffer;
        tokens.clear();

        tokens = split(msg, ' ');

        if (msg == "quit") {
            break;
        }

        if (msg == "stop") {
            engine->stopped = true;
        }

        else if (msg == "uci") {
            printf("id name %s %s\n", ENGINE_NAME, ENGINE_VERSION);
            printf("id author Alexander Tian\n");

            printf("option name Hash type spin default %d min 1 max 24576\n", DEFAULT_TT_SIZE);
            printf("option name Threads type spin default 1 min 1 max 1024\n");

#ifdef DO_SEARCH_TUNING
            for (auto& param : search_params.all_parameters) {
                printf("option name %s type spin default %d min %d max %d\n",
                       param->name.c_str(), param->v, param->min, param->max);
            }
#endif
            printf("uciok\n");
            fflush(stdout);
        }

        else if (tokens[0] == "setoption" && tokens.size() >= 5) {
            if (tokens[2] == "Hash") {
                int mb = std::stoi(tokens[4]);
                mb = std::clamp<int>(mb, 1, 32768);

                engine->resize_tt(mb);
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
            printf("readyok\n");
            fflush(stdout);
        }

        else if (msg == "ucinewgame") {
            Position& position = engine->main_thread.position;
            position.set_fen(START_FEN);
            engine->new_game();
        }

        else if (tokens[0] == "position") {
            parse_position();
        }

        else if (tokens[0] == "go") {
            parse_go();
        }

        else if (tokens[0] == "search_tune_config") {
#ifdef DO_SEARCH_TUNING
            print_search_tuning_config();
#endif
        }

        else if (tokens[0] == "bench") {
            run_bench(*engine);
        }
    }
}