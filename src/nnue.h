//
// Created by Alexander Tian on 6/16/23.
//

#ifndef ALTAIR_NNUE_H
#define ALTAIR_NNUE_H

#include <iostream>
#include <cstring>
#include <array>
#include <span>
#include <vector>
#include <algorithm>
#include "constants.h"
#include "simd.h"

class Position;

constexpr size_t INPUT_SIZE = 768;
constexpr size_t LAYER1_SIZE = 1024;

constexpr size_t KING_INPUT_BUCKETS = 5;
constexpr size_t MATERIAL_OUTPUT_BUCKETS = 8;
constexpr int    MATERIAL_OUTPUT_BUCKET_DIVISOR = 32 / MATERIAL_OUTPUT_BUCKETS;

constexpr int16_t CRELU_MIN = 0;

constexpr SCORE_TYPE SCALE = 400;

constexpr int16_t QA = 255;
constexpr int16_t QB = 64;

constexpr int16_t QAB = QA * QB;

const auto CRELU_MIN_VEC = SIMD::get_int16_vec(CRELU_MIN);
const auto QA_VEC        = SIMD::get_int16_vec(QA);

const int KING_BUCKET_MAP[64] = {
        0, 0, 0, 1, 1, 2, 2, 2,
        0, 0, 1, 1, 1, 1, 2, 2,
        0, 3, 3, 3, 4, 4, 4, 2,
        3, 3, 3, 3, 4, 4, 4, 4,
        3, 3, 3, 3, 4, 4, 4, 4,
        3, 3, 3, 3, 4, 4, 4, 4,
        3, 3, 3, 3, 4, 4, 4, 4,
        3, 3, 3, 3, 4, 4, 4, 4,
};

struct alignas(64) NNUE_Params {
    std::array<int16_t, KING_INPUT_BUCKETS * INPUT_SIZE * LAYER1_SIZE> feature_weights;
    std::array<int16_t, LAYER1_SIZE> feature_bias;
    std::array<int16_t, LAYER1_SIZE * 2 * MATERIAL_OUTPUT_BUCKETS> output_weights;
    std::array<int16_t, MATERIAL_OUTPUT_BUCKETS> output_bias;
};

extern const NNUE_Params& original_nnue_parameters;

inline const NNUE_Params get_nnue_parameters() {
    NNUE_Params parameters;
    parameters.feature_bias = original_nnue_parameters.feature_bias;
    parameters.feature_weights = original_nnue_parameters.feature_weights;
    parameters.output_bias = original_nnue_parameters.output_bias;
    parameters.output_weights = {};

    // Transpose Output Weights
    const int original_rows = 2 * LAYER1_SIZE;
    const int original_cols = MATERIAL_OUTPUT_BUCKETS;

    for (int i = 0; i < original_rows; i++) {
        for (int j = 0; j < original_cols; j++) {
            parameters.output_weights[j * original_rows + i] =
                    original_nnue_parameters.output_weights[i * original_cols + j];
        }
    }

    return parameters;
}

extern const NNUE_Params nnue_parameters;

template <size_t hidden_size>
struct alignas(64) Accumulator {

    int king_buckets[2] = {0, 0};

    std::array<int16_t, hidden_size> white;
    std::array<int16_t, hidden_size> black;

    inline void init(std::span<const int16_t, hidden_size> bias) {
        std::memcpy(white.data(), bias.data(), bias.size_bytes());
        std::memcpy(black.data(), bias.data(), bias.size_bytes());
    }

    inline void init_side(std::span<const int16_t, hidden_size> bias, Color color) {
        std::memcpy(color == WHITE ? white.data() : black.data(),
                    bias.data(),
                    bias.size_bytes());
    }
};

constexpr int32_t screlu(int16_t x) {
    const auto clipped = std::clamp<int16_t>(static_cast<int16_t>(x), CRELU_MIN, QA);
    return clipped * clipped;
}

class NNUE_State {
public:
    explicit NNUE_State() {
        accumulator_stack.reserve(TOTAL_MAX_DEPTH);
    }

    ~NNUE_State() = default;

    std::vector<Accumulator<LAYER1_SIZE>> accumulator_stack{};
    Accumulator<LAYER1_SIZE> *current_accumulator{};

    void push();
    void pop();

    void reset_side(Position& position, Color color);

    SCORE_TYPE evaluate(Position& position, Color color);

    std::pair<size_t, size_t> get_feature_indices(Piece piece, Square sq);

    static int32_t screlu_flatten(const std::array<int16_t, LAYER1_SIZE> &our,
                                  const std::array<int16_t, LAYER1_SIZE> &opp,
                                  const std::array<int16_t, LAYER1_SIZE * 2 * MATERIAL_OUTPUT_BUCKETS> &weights,
                                  int output_bucket);

    static int32_t screlu_flatten_simd(const std::array<int16_t, LAYER1_SIZE> &our,
                                       const std::array<int16_t, LAYER1_SIZE> &opp,
                                       const std::array<int16_t, LAYER1_SIZE * 2 * MATERIAL_OUTPUT_BUCKETS> &weights,
                                       int output_bucket);

    void reset_nnue(Position& position);

    template <bool Activate>
    inline void update_feature(Piece piece, Square square) {
        const auto [white_idx, black_idx] = get_feature_indices(piece, square);

        if constexpr (Activate) {
            activate_all(current_accumulator->white, white_idx * LAYER1_SIZE);
            activate_all(current_accumulator->black, black_idx * LAYER1_SIZE);
        }

        else {
            deactivate_all(current_accumulator->white, white_idx * LAYER1_SIZE);
            deactivate_all(current_accumulator->black, black_idx * LAYER1_SIZE);
        }
    }

    template <bool Activate>
    inline void update_feature_side(Piece piece, Square square, Color color) {
        const auto [white_idx, black_idx] = get_feature_indices(piece, square);

        auto& accumulator = color == WHITE ? current_accumulator->white : current_accumulator->black;
        auto index = color == WHITE ? white_idx : black_idx;

        if constexpr (Activate) {
            activate_all(accumulator, index * LAYER1_SIZE);
        }

        else {
            deactivate_all(accumulator, index * LAYER1_SIZE);
        }
    }

    static inline void activate_all(std::array<int16_t, LAYER1_SIZE>& input, size_t offset) {
        for (size_t i = 0; i < LAYER1_SIZE; ++i) input[i] +=
                nnue_parameters.feature_weights[offset + i];
    }

    static inline void deactivate_all(std::array<int16_t, LAYER1_SIZE>& input, size_t offset) {
        for (size_t i = 0; i < LAYER1_SIZE; ++i) input[i] -=
                nnue_parameters.feature_weights[offset + i];
    }
};


#endif //ALTAIR_NNUE_H