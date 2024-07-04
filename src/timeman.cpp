//
// Created by Alexander Tian on 4/16/24.
//

#include <cmath>
#include "timeman.h"

double position_time_scale(Position& position) {

    /*
     * We want to scale time based on the position and phase of the game.
     * We should aim to use the most time out of the opening in the complex middle-game.
     *
     * A simple way to calculate the phase of the game is to give a score for each piece and sum up the total score
     * that is calculated for each piece.
     *
     * We also consider the number of pawns on the lower ranks of the board.
     */

    int phase_scores[6] = {1, 3, 3, 7, 15, 0};

    int max_score = 2 * (8 * phase_scores[0] + 2 * phase_scores[1] + 2 * phase_scores[2] + 2 * phase_scores[3] + phase_scores[4]);
    int current_score = 0;

    for (int piece = 0; piece < 12; piece++) {
        current_score += popcount(position.pieces[piece]) * phase_scores[piece % 6];
    }

    int low_rank_pawns = 0;

    BITBOARD white_pawns = position.pieces[WHITE_PAWN];
    while (white_pawns) {
        Square square = poplsb(white_pawns);
        Rank rank = rank_of(square);

        if (rank <= 2) low_rank_pawns++;
    }

    BITBOARD black_pawns = position.pieces[BLACK_PAWN];
    while (black_pawns) {
        Square square = poplsb(black_pawns);
        Rank rank = rank_of(square);

        if (rank >= 5) low_rank_pawns++;
    }

    double phase_ratio = static_cast<double>(current_score) / max_score;

    // std::cout << current_score << " " << max_score << " " << phase_ratio << " " << low_rank_pawns << std::endl;

    // Little material on the board
    if (phase_ratio <= 0.1) return 0.2;

    if (low_rank_pawns <= 4) return 0.1 + 0.6 * phase_ratio;

    if (low_rank_pawns <= 8) return 0.3 + 0.7 * phase_ratio;

    // Only two pawns are on "higher ranks", likely to be in the early opening.
    if (low_rank_pawns >= 14) return 0.3 + 0.3 * phase_ratio;

    if (low_rank_pawns >= 10) return 0.4 + 0.5 * phase_ratio;

    return 0.6 + 0.6 * phase_ratio;
}


void time_handler(Engine& engine, double self_time, double inc, double movetime, long movestogo) {
    double time_amt;

    double movestogo_ratio = movestogo == 0 ? 0 : std::clamp(std::atan((movestogo + 20) / 24.0), 0.84, 1.1);

    Position& position = engine.thread_states[0].position;

    double pts = position_time_scale(position);

    // std::cout << movetime << std::endl;

    if (movetime > 0) {
        time_amt = movetime * 0.9;
        goto update;
    }

    if (self_time == 0) {
        time_amt = 10000;
        goto update;
    }

    if (movestogo == 0 && inc == 0) {
        time_amt = self_time / 24;
        time_amt *= (0.8 + 0.2 * pts);
        goto update;
    }

    if (movestogo > 0 && inc == 0) {
        time_amt = self_time * movestogo_ratio / static_cast<double>(movestogo);
        if (time_amt > self_time * 0.9) time_amt = self_time * 0.9;

        if (movestogo == 1) time_amt = self_time * 0.9;
        else time_amt *= (0.7 + 0.3 * pts);

        goto update;
    }

    if (inc > 0 && movestogo == 0) {
        time_amt = self_time / 20 + inc * 0.75;
        time_amt *= (0.7 + 0.3 * pts);
        goto update;
    }

    if (movestogo > 0 && inc > 0) {
        time_amt = self_time * movestogo_ratio / static_cast<double>(movestogo) + inc * 0.75;
        if (time_amt > self_time * 0.9) time_amt = std::min(self_time * 0.85 + inc * 0.75, self_time * 0.9);

        if (movestogo == 1) time_amt = self_time * 0.9;
        else time_amt *= (0.7 + 0.3 * pts);

        goto update;
    }

    time_amt = 10000;

update:

    if (self_time) time_amt = std::min(time_amt, self_time * 0.95);

    engine.hard_time_limit = std::max(static_cast<uint64_t>(time_amt),
                                      static_cast<uint64_t>(time_amt * (search_params.TM_hard_scalar.v / 100.0))
                                      - engine.move_overhead);

    engine.soft_time_limit = static_cast<uint64_t>(time_amt * (search_params.TM_soft_scalar.v / 100.0));

    if (self_time) {
        engine.soft_time_limit = std::min(engine.soft_time_limit, static_cast<uint64_t>(self_time * 0.8));
    }

    if (engine.hard_time_limit > static_cast<uint64_t>(self_time * 0.8) && self_time > 0) {
        engine.hard_time_limit = static_cast<uint64_t>(self_time * 0.8);
    }

    if (engine.hard_time_limit > static_cast<uint64_t>(movetime) && movetime != 0.0) {
        engine.hard_time_limit = static_cast<uint64_t>(time_amt);
    }

    // std::cout << time_amt << " " << engine.soft_time_limit << " " << engine.hard_time_limit << std::endl;
}

