//
// Created by Alexander Tian on 6/16/23.
//

#include "nnue.h"
#include "position.h"

#ifdef _MSC_VER
#undef _MSC_VER
#endif

#include "incbin.h"

INCBIN(nnue, "src/nnue.bin");
// INCBIN(nnue, "/Users/alexandertian/CLionProjects/Altair/src/net-2.bin");

const NNUE_Params &nnue_parameters = *reinterpret_cast<const NNUE_Params *>(gnnueData);

void NNUE_State::push() {
    accumulator_stack.push_back(*current_accumulator);
    current_accumulator = &accumulator_stack.back();
}

void NNUE_State::pop() {
    accumulator_stack.pop_back();
    current_accumulator = &accumulator_stack.back();
}


SCORE_TYPE NNUE_State::evaluate(Color color) const {
    const auto output = color == WHITE
                        ? crelu_flatten(current_accumulator->white, current_accumulator->black, nnue_parameters.output_weights)
                        : crelu_flatten(current_accumulator->black, current_accumulator->white, nnue_parameters.output_weights);
    return (output + nnue_parameters.output_bias) * SCALE / Q;
}

std::pair<size_t , size_t> NNUE_State::get_feature_indices(Piece piece, Square sq) {
    constexpr size_t color_offset = 64 * 6;
    constexpr size_t piece_offset = 64;

    const Color color = get_color(piece);
    const auto piece_type = get_piece_type(piece, color);

    const auto whiteIdx =  color * color_offset + piece_type * piece_offset + static_cast<size_t>(sq);
    const auto blackIdx = ~color * color_offset + piece_type * piece_offset + static_cast<size_t>(sq ^ 56);

    return {whiteIdx, blackIdx};
}

int32_t NNUE_State::crelu_flatten(const std::array<int16_t, LAYER1_SIZE> &us,
                                   const std::array<int16_t, LAYER1_SIZE> &them, const std::array<int16_t, LAYER1_SIZE * 2> &weights) {
    int32_t sum = 0;

    for (size_t i = 0; i < LAYER1_SIZE; ++i) {
        sum += crelu(  us[i]) * weights[              i];
        sum += crelu(them[i]) * weights[LAYER1_SIZE + i];
    }

    return sum;
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