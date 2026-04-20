#include "analytics/streaming_stats.h"
#include "compilation/shard_format.h"
#include "core/canonical_position.h"
#include "parsing/fen_parser.h"
#include "parsing/record_parser.h"

#include <cmath>
#include <exception>
#include <iostream>
#include <string>

using namespace pipeline;

namespace {

void expect(const bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

RawRecord parse_record(const std::string& line) {
    auto result = RecordParser::parse_line(line, 1);
    expect(result.ok(), "Failed to parse record: " + result.error);
    return std::move(*result.record);
}

void test_core_position_validation() {
    CanonicalPosition valid;
    valid.board[e1] = WHITE_KING;
    valid.board[e8] = BLACK_KING;
    valid.board[a2] = WHITE_PAWN;
    valid.board[h7] = BLACK_PAWN;

    expect(valid.is_valid(), "Simple legal canonical position should validate");

    CanonicalPosition invalid = valid;
    invalid.board[a1] = WHITE_PAWN;
    invalid.board[a2] = EMPTY;
    expect(!invalid.is_valid(), "Pawn on rank 1 should be rejected");

    const auto signature = MaterialSignature::from_position(valid);
    expect(signature.counts[0] == 1, "White pawn count should be tracked in material signature");
    expect(signature.counts[5] == 1, "Black pawn count should be tracked in material signature");
    expect(valid.total_material() == 2, "Total material should ignore kings");
}

void test_fen_and_record_parsing() {
    const auto standard = FenParser::parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    expect(standard.success, "Standard FEN should parse");
    expect(standard.position.side == WHITE, "Side to move should parse");
    expect(standard.position.castling == (WHITE_OO | WHITE_OOO | BLACK_OO | BLACK_OOO), "Standard castling bits should parse");
    expect(standard.position.ep_square == NO_SQUARE, "Dash en passant should map to NO_SQUARE");

    const auto frc = FenParser::parse("r1k2r2/8/8/8/8/8/8/R1K2R2 w FAfa - 7 1");
    expect(frc.success, "FRC castling FEN should parse");
    expect(frc.position.castling == (WHITE_OO | WHITE_OOO | BLACK_OO | BLACK_OOO), "FRC castling letters should map to the same four castling bits");
    expect(frc.fifty_move == 7, "Halfmove clock should parse");

    const auto legacy = FenParser::parse("rnbqk2r/ppp1ppbp/3p1np1/8/2P5/2NP2PN/PP2PPBP/R1BQ1RK b kq - 4 1");
    expect(legacy.success, "Pipeline parser should accept the historical one-square trailing-empty omission");

    const auto legacy_multi = FenParser::parse("1r3k2/1pr1ppb1/p1np2p1/7p/2PPBP1P/1P4P1/P2RN1K1/3R b - - 1 1");
    expect(legacy_multi.success, "Pipeline parser should accept historical FENs with multiple omitted trailing empties");

    const auto legacy_empty_rank = FenParser::parse("2rn1k2/2r5/pp1ppbp1/5p1p/P1PP1P1P/1PR2BP1/2R1N1K1/ b - - 4 1");
    expect(legacy_empty_rank.success, "Pipeline parser should accept historical FENs that omit an entirely empty final rank");

    const auto invalid = FenParser::parse("rnbqk2r/ppp1ppbp/3p1np1/8/2P5/2NP2PN/PP2PPBP/R1BQ11 b kq - 4 1");
    expect(!invalid.success, "Pipeline parser should still reject malformed final ranks that do not match the legacy bug");

    auto record = RecordParser::parse_line(
        "r1k2r2/8/8/8/8/8/8/R1K2R2 w FAfa - 7 1 | 34 | 0.5", 12);
    expect(record.ok(), "Well-formed datagen line should parse");
    expect(record.record->line_number == 12, "Record parser should preserve line numbers");
    expect(record.record->eval == 34, "Eval should parse from datagen record");
    expect(record.record->wdl == WDL::DRAW, "WDL should parse from datagen record");
    expect(record.record->position.castling == (WHITE_OO | WHITE_OOO | BLACK_OO | BLACK_OOO), "Record parser should preserve FRC castling semantics");
}

void test_streaming_analytics() {
    StreamingStats stats;

    RawRecord valid_a = parse_record("4k3/8/8/8/8/8/P7/4K3 w - - 0 1 | 25 | 1.0");
    RawRecord valid_b = parse_record("4k3/7p/8/8/8/8/8/4K3 b - - 3 1 | -80 | 0.0");
    RawRecord invalid;

    stats.add(valid_a);
    stats.add(valid_b);
    stats.add(invalid);

    expect(stats.total_records == 3, "Streaming stats should count every record");
    expect(stats.valid_records == 2, "Streaming stats should count only valid records as valid");
    expect(stats.invalid_records() == 1, "Streaming stats should derive invalid record count");

    expect(stats.wdl.win == 1, "Win count should aggregate");
    expect(stats.wdl.loss == 1, "Loss count should aggregate");
    expect(stats.wdl.draw == 0, "Draw count should aggregate");

    expect(stats.side_to_move.white == 1, "White-to-move count should aggregate");
    expect(stats.side_to_move.black == 1, "Black-to-move count should aggregate");

    expect(stats.material.total == 2, "Material counter should count valid positions");
    expect(stats.material.unique_signatures() == 2, "Distinct material signatures should be tracked");
    expect(stats.material_phase.total == 2, "Material phase stats should count valid positions");
    expect(stats.material_phase.total_material[1] == 2, "Total material histogram should bucket simple king-and-pawn positions");
    expect(stats.material_phase.non_pawn_material[0] == 2, "Non-pawn material histogram should recognize pawn-only material");
    expect(stats.material_phase.material_imbalance[MaterialPhaseStats::max_imbalance] == 0, "Imbalance zero bucket should stay empty for asymmetric samples");
    expect(stats.material_phase.material_imbalance[MaterialPhaseStats::max_imbalance + 1] == 1, "White-up-one material imbalance should be tracked");
    expect(stats.material_phase.material_imbalance[MaterialPhaseStats::max_imbalance - 1] == 1, "Black-up-one material imbalance should be tracked");
    expect(stats.material_phase.halfmove_clock[0] == 1 && stats.material_phase.halfmove_clock[3] == 1,
           "Halfmove clock histogram should aggregate parsed fifty-move values");

    expect(stats.eval_hist.total() == 2, "Eval histogram should include valid records");
    expect(stats.eval_hist.counts[EvalHistogram::bucket_for(25)] == 1, "Positive eval should land in the expected bucket");
    expect(stats.eval_hist.counts[EvalHistogram::bucket_for(-80)] == 1, "Negative eval should land in the expected bucket");

    expect(stats.en_passant.none == 2, "En passant none-count should aggregate");
    expect(stats.king_positions.total == 2, "King position stats should count valid positions");
    expect(stats.uniqueness.estimate() > 0.0, "Uniqueness estimator should see inserted hashes");
}

void test_packed_board_roundtrip() {
    CanonicalPosition position;
    position.board[e1] = WHITE_KING;
    position.board[e8] = BLACK_KING;
    position.board[a2] = WHITE_PAWN;
    position.board[h7] = BLACK_QUEEN;
    position.side = BLACK;

    const auto packed = pack_record(position, encode_stm(position.side), encode_wdl(WDL::DRAW), -42);
    expect(packed.stm == 1, "Packed record should encode side to move");
    expect(packed.wdl == 1, "Packed record should encode WDL");
    expect(packed.eval == -42, "Packed record should preserve eval");

    const auto unpacked = unpack_record_board(packed);
    expect(unpacked.side == BLACK, "Unpacked record should restore side to move");
    expect(unpacked.board[e1] == WHITE_KING, "Packed board should preserve white king");
    expect(unpacked.board[e8] == BLACK_KING, "Packed board should preserve black king");
    expect(unpacked.board[a2] == WHITE_PAWN, "Packed board should preserve white pawn");
    expect(unpacked.board[h7] == BLACK_QUEEN, "Packed board should preserve black queen");
    expect(unpacked.board[d4] == EMPTY, "Packed board should preserve empty squares");
}

}  // namespace

int main() {
    try {
        test_core_position_validation();
        test_fen_and_record_parsing();
        test_streaming_analytics();
        test_packed_board_roundtrip();
        std::cout << "pipeline_tests: ok\n";
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "pipeline_tests: failed: " << ex.what() << "\n";
        return 1;
    }
}
