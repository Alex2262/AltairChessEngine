//
// Created by Alexander Tian on 6/16/23.
//

#include "nnue.h"
#include "position.h"

#ifdef _MSC_VER
#undef _MSC_VER
#endif

#include "incbin.h"

INCBIN(nnue, "src/taffreta-net.bin");
// INCBIN(nnue, "/Users/alexandertian/CLionProjects/Altair/src/taffreta-net.bin");

const NNUE_Params &nnue_parameters = *reinterpret_cast<const NNUE_Params *>(gnnueData);

void NNUE_State::push() {
    accumulator_stack.push_back(*current_accumulator);
    current_accumulator = &accumulator_stack.back();
}

void NNUE_State::pop() {
    accumulator_stack.pop_back();
    current_accumulator = &accumulator_stack.back();
}


SCORE_TYPE NNUE_State::evaluate(Position& position, Color color) const {

    const int output_bucket = (popcount(position.all_pieces) - 2) / MATERIAL_OUTPUT_BUCKET_DIVSIOR;
    const auto output = color == WHITE
                        ? screlu_flatten(current_accumulator->white, current_accumulator->black, nnue_parameters.output_weights, output_bucket)
                        : screlu_flatten(current_accumulator->black, current_accumulator->white, nnue_parameters.output_weights, output_bucket);
    return (output + nnue_parameters.output_bias[output_bucket]) * SCALE / QAB;
}

std::pair<size_t, size_t> NNUE_State::get_feature_indices(Piece piece, Square sq) {
    constexpr size_t color_offset = 64 * 6;
    constexpr size_t piece_offset = 64;

    const Color color = get_color(piece);
    const auto piece_type = get_piece_type(piece, color);

    const auto white_idx =  color * color_offset + piece_type * piece_offset + static_cast<size_t>(sq);
    const auto black_idx = ~color * color_offset + piece_type * piece_offset + static_cast<size_t>(sq ^ 56);

    return {white_idx, black_idx};
}

int32_t NNUE_State::screlu_flatten(const std::array<int16_t, LAYER1_SIZE> &our,
                                   const std::array<int16_t, LAYER1_SIZE> &opp,
                                   const std::array<int16_t, LAYER1_SIZE * 2 * MATERIAL_OUTPUT_BUCKETS> &weights,
                                   int output_bucket) {
    int32_t sum = 0;
    int output_bucket_offset = output_bucket * 2 * LAYER1_SIZE;

    for (size_t i = 0; i < LAYER1_SIZE; i++) {
        sum += screlu(our[i]) * weights[output_bucket_offset +               i];
        sum += screlu(opp[i]) * weights[output_bucket_offset + LAYER1_SIZE + i];
    }

    return sum / QA;
}

void NNUE_State::reset_nnue(Position& position) {
    accumulator_stack.clear();
    current_accumulator = &accumulator_stack.emplace_back();

    current_accumulator->init(nnue_parameters.feature_bias);

    for (int square = 0; square < 64; square++) {
        if (position.board[square] < EMPTY) {
            update_feature<true>(position.board[square], static_cast<Square>(square));
        }
    }
}
