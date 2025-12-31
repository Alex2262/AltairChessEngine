

template<Filter filter>
inline ScoredMove Generator::sort_next_move() {
    auto best_score = scored_moves[move_index].score;
    auto best_idx = move_index;
    for (size_t next_count = move_index + 1; next_count < scored_moves.size(); next_count++) {
        ScoredMove& scored_move = scored_moves[next_count];

        if constexpr (filter == Filter::Noisy) {
            if (!scored_move.move.is_capture(*position)) continue;
        }

        else if constexpr (filter == Filter::Good) {
            if (!scored_move.winning_capture) continue;
        }

        else if constexpr (filter == Filter::GoodNoisy) {
            if (!scored_move.move.is_capture(*position)) continue;
            if (!scored_move.winning_capture) continue;
        }

        else if constexpr (filter == Filter::Quiet) {
            if (scored_move.move.is_capture(*position)) continue;
        }

        if (scored_move.move == tt_move) continue;

        if (best_score < scored_move.score) {
            best_score = scored_move.score;
            best_idx = next_count;
        }
    }

    std::swap(scored_moves[move_index], scored_moves[best_idx]);
    return scored_moves[move_index];
}

template<bool qsearch>
inline ScoredMove Generator::next_move() {

    assert(stage != Stage::Terminated);

    ScoredMove picked = {NO_MOVE, 0, false};

    if (stage == Stage::TT_probe) {
        stage = Stage::GenNoisy;
        if (position->is_pseudo_legal(tt_move)) return {tt_move, static_cast<Score>(MO_Margin::TT), true};
    }

    if (stage == Stage::GenNoisy) {
        move_index = 0;
        good_capture_count = 0;
        good_capture_found = 0;

        if constexpr (qsearch) position->get_pseudo_legal_moves<Movegen::Qsearch, true>(scored_moves);
        else position->get_pseudo_legal_moves<Movegen::Noisy, true>(scored_moves);

        get_capture_scores<qsearch>(*thread_state, scored_moves, tt_move, good_capture_count);
        stage = Stage::Noisy;
    }

    if (stage == Stage::Noisy) {
        if (move_index < scored_moves.size() && scored_moves[move_index].move == tt_move) move_index++;

        if (good_capture_found >= good_capture_count) {
            if constexpr (!qsearch) stage = Stage::GenQ_BN;
            else if (move_index >= scored_moves.size()) stage = Stage::Terminated;
        } else {
            if constexpr (qsearch) picked = sort_next_move<Filter::None>();
            else picked = sort_next_move<Filter::Good>();

            good_capture_found++;
            move_index++;
        }
    }

    if (stage == Stage::GenQ_BN) {
        assert(!qsearch);

        position->get_pseudo_legal_moves<Movegen::Quiet, false>(scored_moves);
        get_q_bn_scores(*thread_state, scored_moves, tt_move, last_moves, move_index);

        stage = Stage::Q_BN;
    }

    if (stage == Stage::Q_BN) {
        assert(!qsearch);

        if (move_index < scored_moves.size() && scored_moves[move_index].move == tt_move) move_index++;

        if (move_index >= scored_moves.size()) {
            stage = Stage::Terminated;
        } else {
            picked = sort_next_move<Filter::None>();
            move_index++;
        }
    }

    assert(stage != Stage::Noisy || picked.move.type() != MOVE_TYPE_CASTLE);

    return picked;
}