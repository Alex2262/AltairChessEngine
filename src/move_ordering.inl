

inline ScoredMove Generator::sort_next_move() {
    auto best_score = scored_moves[move_index].score;
    auto best_idx = move_index;
    const size_t size = scored_moves.size();

    for (size_t next_count = move_index + 1; next_count < size; next_count++) {
        const Score score = scored_moves[next_count].score;
        if (score > best_score) {
            best_score = score;
            best_idx = next_count;
        }
    }

    std::swap(scored_moves[move_index], scored_moves[best_idx]);
    return scored_moves[move_index];
}

template<bool qsearch>
inline ScoredMove Generator::next_move() {

    assert(stage != Stage::Terminated);

    if (stage == Stage::TT_probe) {
        if (gen_all) stage = Stage::GenAll;
        else stage = Stage::GenNoisy;
        if (position->is_pseudo_legal(tt_move)) return {tt_move, static_cast<Score>(MO_Margin::TT), true};
    }

    if (stage == Stage::GenAll) {
        assert(!qsearch);
        move_index = 0;
        position->get_pseudo_legal_moves<Movegen::All, true>(scored_moves);
        get_all_scores(*thread_state, scored_moves, tt_move, last_moves);

        max_heap.heapify(scored_moves);
        stage = Stage::All;
    }

    if (stage == Stage::All) {
        assert(!qsearch);
        if (move_index >= scored_moves.size()) stage = Stage::Terminated;
        else {
            ScoredMove picked = max_heap.extract(scored_moves);
            move_index++;

            if (picked.move == tt_move) return next_move<qsearch>();
            return picked;
        }

        return {NO_MOVE, 0, false};
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
        if (good_capture_found >= good_capture_count) {
            if constexpr (qsearch) stage = Stage::Terminated;
            else stage = Stage::GenQ_BN;
        } else {
            ScoredMove picked = sort_next_move();
            move_index++;

            if (picked.move == tt_move) return next_move<qsearch>();

            good_capture_found++;
            return picked;
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

        if (move_index >= scored_moves.size()) {
            stage = Stage::Terminated;
        } else {
            ScoredMove picked;
            picked = sort_next_move();
            move_index++;

            if (picked.move == tt_move) return next_move<qsearch>();
            else return picked;
        }
    }

    return {NO_MOVE, 0, false};
}
