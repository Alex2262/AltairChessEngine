//
// Created by Alexander Tian on 6/16/23.
//

#include <iostream>
#include "nnue.h"
#include "position.h"

#ifdef _MSC_VER
#undef _MSC_VER
#endif

#include "incbin.h"

INCBIN(nnue, "src/ceres-net.bin");
// INCBIN(nnue, "/Users/alexandertian/CLionProjects/Altair/src/ceres-net.bin");

const NNUE_Params &original_nnue_parameters = *reinterpret_cast<const NNUE_Params *>(gnnueData);
const NNUE_Params nnue_parameters = get_nnue_parameters();

void NNUE_State::push() {
    accumulator_stack.push_back(*current_accumulator);
    current_accumulator = &accumulator_stack.back();
}

void NNUE_State::pop() {
    accumulator_stack.pop_back();
    current_accumulator = &accumulator_stack.back();
}


void NNUE_State::reset_side(Position& position, Color color) {
    current_accumulator->init_side(nnue_parameters.feature_bias, color);

    for (int piece = WHITE_PAWN; piece < static_cast<int>(EMPTY); piece++) {
        BITBOARD piece_bb = position.pieces[piece];
        while (piece_bb) {
            Square square = poplsb(piece_bb);
            update_feature_side<true>(static_cast<Piece>(piece), square, color);
        }
    }
}


SCORE_TYPE NNUE_State::evaluate(Position& position, Color color) {

    const int output_bucket = (popcount(position.all_pieces) - 2) / MATERIAL_OUTPUT_BUCKET_DIVISOR;

    const auto flatten = []() {
        if constexpr (SIMD::ARCH == SIMD::Arch::AUTO) return screlu_flatten;
        return screlu_flatten_simd;
    }();

    const auto output = color == WHITE
                        ? flatten(current_accumulator->white, current_accumulator->black, nnue_parameters.output_weights, output_bucket)
                        : flatten(current_accumulator->black, current_accumulator->white, nnue_parameters.output_weights, output_bucket);

    return (output + nnue_parameters.output_bias[output_bucket]) * SCALE / QAB;
}

std::pair<size_t, size_t> NNUE_State::get_feature_indices(Piece piece, Square sq) {
    constexpr size_t color_offset = 384;
    constexpr size_t piece_offset = 64;

    const Color color = get_color(piece);
    const auto piece_type = get_piece_type(piece, color);

    const auto white_idx = INPUT_SIZE * (current_accumulator->king_buckets[WHITE])
            +  color * color_offset + piece_type * piece_offset + static_cast<size_t>(sq);
    const auto black_idx = INPUT_SIZE * (current_accumulator->king_buckets[BLACK])
            + ~color * color_offset + piece_type * piece_offset + static_cast<size_t>(sq ^ 56);

    return {white_idx, black_idx};
}

int32_t NNUE_State::screlu_flatten(const std::array<int16_t, LAYER1_SIZE> &our,
                                   const std::array<int16_t, LAYER1_SIZE> &opp,
                                   const std::array<int16_t, LAYER1_SIZE * 2 * MATERIAL_OUTPUT_BUCKETS> &weights,
                                   int output_bucket) {
    int32_t sum = 0;

    const int offset_1 = output_bucket * 2 * LAYER1_SIZE;
    const int offset_2 = offset_1 + LAYER1_SIZE;

    for (size_t i = 0; i < LAYER1_SIZE; i++) {
        sum += screlu(our[i]) * weights[offset_1 + i];
        sum += screlu(opp[i]) * weights[offset_2 + i];
    }

    return sum / QA;
}

int32_t NNUE_State::screlu_flatten_simd(const std::array<int16_t, LAYER1_SIZE> &our,
                                        const std::array<int16_t, LAYER1_SIZE> &opp,
                                        const std::array<int16_t, LAYER1_SIZE * 2 * MATERIAL_OUTPUT_BUCKETS> &weights,
                                        int output_bucket) {
    auto sum = SIMD::vec_int32_zero();
    const int offset_1 = output_bucket * 2 * LAYER1_SIZE;
    const int offset_2 = offset_1 + LAYER1_SIZE;

    for (size_t i = 0; i < LAYER1_SIZE; i += SIMD::REGISTER_SIZE) {

        // OUR perspective
        auto our_weight = SIMD::int16_load(&our[i]);
        our_weight      = SIMD::vec_int16_clamp(our_weight, CRELU_MIN_VEC, QA_VEC);

        auto out_weight_1 = SIMD::int16_load(&weights[offset_1 + i]);
        auto our_product  = SIMD::vec_int16_madd_int32(our_weight, SIMD::vec_int16_multiply(our_weight, out_weight_1));

        sum = SIMD::vec_int32_add(sum, our_product);

        // OPP perspective
        auto opp_weight = SIMD::int16_load(&opp[i]);
        opp_weight      = SIMD::vec_int16_clamp(opp_weight, CRELU_MIN_VEC, QA_VEC);

        auto out_weight_2 = SIMD::int16_load(&weights[offset_2 + i]);
        auto opp_product  = SIMD::vec_int16_madd_int32(opp_weight, SIMD::vec_int16_multiply(opp_weight, out_weight_2));

        sum = SIMD::vec_int32_add(sum, opp_product);

    }

    return SIMD::vec_int32_hadd(sum) / QA;
}

void NNUE_State::reset_nnue(Position& position) {
    accumulator_stack.clear();
    current_accumulator = &accumulator_stack.emplace_back();

    current_accumulator->init(nnue_parameters.feature_bias);

    current_accumulator->king_buckets[WHITE] = KING_BUCKET_MAP[position.get_king_pos(WHITE)];
    current_accumulator->king_buckets[BLACK] = KING_BUCKET_MAP[position.get_king_pos(BLACK) ^ 56];

    // std::cout << current_accumulator->king_buckets[WHITE] << std::endl;
    // std::cout << current_accumulator->king_buckets[BLACK] << std::endl;

    for (int square = 0; square < 64; square++) {
        if (position.board[square] < EMPTY) {
            update_feature<true>(position.board[square], static_cast<Square>(square));
        }
    }
}
