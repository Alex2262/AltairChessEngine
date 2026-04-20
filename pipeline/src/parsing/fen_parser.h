#pragma once

#include "../core/canonical_position.h"
#include <string>
#include <string_view>

namespace pipeline {

// Result of FEN parsing
struct FenParseResult {
    CanonicalPosition position;
    int16_t fifty_move = 0;          // Fifty-move clock from FEN
    bool success = false;
    std::string error;

    static FenParseResult ok(CanonicalPosition&& pos, int16_t fifty) {
        FenParseResult r;
        r.position = std::move(pos);
        r.fifty_move = fifty;
        r.success = true;
        return r;
    }

    static FenParseResult fail(const std::string& err) {
        FenParseResult r;
        r.error = err;
        r.success = false;
        return r;
    }
};

// FEN parser - extracts position from FEN string
// FEN format: "board side castling ep halfmove [fullmove]"
class FenParser {
public:
    // Parse a FEN string into a canonical position
    static FenParseResult parse(std::string_view fen);
};

} // namespace pipeline
