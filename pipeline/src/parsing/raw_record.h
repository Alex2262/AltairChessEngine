#pragma once

#include "../core/types.h"
#include "../core/canonical_position.h"
#include <string>
#include <optional>

namespace pipeline {

// Raw record from datagen output
// Format: "{FEN} | {EVAL} | {WDL}"
struct RawRecord {
    // Parsed data
    CanonicalPosition position;
    int32_t eval = 0;                // Centipawn evaluation
    WDL wdl = WDL::DRAW;             // Win/Draw/Loss outcome
    int16_t fifty_move = 0;          // Fifty-move clock (from FEN, not part of identity)

    // Cached hash
    Hash hash = 0;                   // Canonical position hash

    // Source tracking (for error reporting)
    size_t line_number = 0;

    // Validation status
    bool is_valid = false;

    // Compute and cache hash
    void compute_hash() {
        hash = position.compute_hash();
    }
};

// Parse result with error handling
struct ParseResult {
    std::optional<RawRecord> record;
    std::string error;
    size_t line_number;

    bool ok() const { return record.has_value(); }

    static ParseResult success(RawRecord&& rec) {
        return {std::move(rec), "", rec.line_number};
    }

    static ParseResult failure(const std::string& err, size_t line) {
        return {std::nullopt, err, line};
    }
};

} // namespace pipeline
