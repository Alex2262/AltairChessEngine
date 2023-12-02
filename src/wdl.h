
#ifndef ALTAIR_WDL_H
#define ALTAIR_WDL_H

#include "constants.h"
#include "types.h"

// Based on https://github.com/official-stockfish/WDL_model

constexpr int normalized_move_count = 32;
constexpr SCORE_TYPE normalization_score = 231;  // Normalization Score based on move 32 calculations

// Polynomial Coefficients
constexpr double WDL_AS[] = {  -2.33314248,   24.12932524,    1.45406761,  208.36909917};
constexpr double WDL_BS[] = {  -2.51362618,   25.89441004,  -75.42634185,  125.03185242};

inline std::pair<double, double> get_wdl_parameters(PLY_TYPE ply) {
    // Game Move Counter
    double gmc = std::min(static_cast<double>(ply) / 2.0 / static_cast<double>(normalized_move_count),
                          240.0);

    double a = ((WDL_AS[0] * gmc + WDL_AS[1]) * gmc + WDL_AS[2]) * gmc + WDL_AS[3];
    double b = ((WDL_BS[0] * gmc + WDL_BS[1]) * gmc + WDL_BS[2]) * gmc + WDL_BS[3];

    return std::pair{a, b};
}

inline std::tuple<SCORE_TYPE, SCORE_TYPE, SCORE_TYPE> get_wdl(SCORE_TYPE score, PLY_TYPE ply) {
    auto [a, b] = get_wdl_parameters(ply);
    auto pov_score = std::clamp<double>(score, -4000.0, 4000.0);

    auto win_probability  = static_cast<SCORE_TYPE>(1000.0 / (1.0 + std::exp((a - pov_score) / b)));
    auto loss_probability = static_cast<SCORE_TYPE>(1000.0 / (1.0 + std::exp((a + pov_score) / b)));
    auto draw_probability = 1000 - win_probability - loss_probability;

    return std::tuple{win_probability, draw_probability, loss_probability};
}

inline SCORE_TYPE normalize_score(SCORE_TYPE score, PLY_TYPE ply) {
    if (score == 0 || std::abs(score) > MATE_BOUND) return score;
    double a = get_wdl_parameters(ply).first;

    return static_cast<SCORE_TYPE>(static_cast<double>(score) * 100.0 / a);
}

inline SCORE_TYPE normalize_score_basic(SCORE_TYPE score) {
    if (score == 0 || std::abs(score) > MATE_BOUND) return score;
    return static_cast<SCORE_TYPE>(static_cast<double>(score) * 100.0 / normalization_score);
}

#endif //ALTAIR_WDL_H
