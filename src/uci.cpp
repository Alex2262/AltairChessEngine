

#include <algorithm>
#include <cmath>
#include "uci.h"
#include "useful.h"
#include "move.h"
#include "search.h"
#include "evaluation.h"
#include "timeman.h"

void UCI::initialize_uci() const {
    engine->resize_tt(DEFAULT_TT_SIZE);

    engine->initialize_lmr_reductions();

    Position& position = engine->main_thread.position;
    position.set_fen(START_FEN);
}


void UCI::parse_position() {
    if (tokens.size() < 2) return;

    Position& position = engine->main_thread.position;

    int next_idx;
    engine->main_thread.game_ply = 0;

    FenInfo fen_info;

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

        fen_info = position.set_fen(fen);
        next_idx = 8;
    }

    else return;

    engine->main_thread.fifty_move = fen_info.fifty_move_counter;
    engine->main_thread.base_full_moves = fen_info.full_move_counter;

    if (static_cast<int>(tokens.size()) <= next_idx || tokens[next_idx] != "moves") return;

    for (int i = next_idx + 1; i < static_cast<int>(tokens.size()); i++) {
        Move move = Move(position, tokens[i]);
        last_move = move;

        position.make_move(move, position.state_stack[0], engine->main_thread.fifty_move);

        engine->main_thread.game_ply++;
        engine->main_thread.repetition_table[engine->main_thread.game_ply] = position.hash_key;
    }
}


void UCI::parse_go() {

    Position& position = engine->main_thread.position;

    PLY_TYPE d = 0, perft_depth = 0;
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
    }
}