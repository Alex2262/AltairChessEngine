#include "fen_parser.h"

#include <cctype>
#include <limits>
#include <vector>

namespace pipeline {

namespace {

std::string_view trim(std::string_view value) {
    while (!value.empty() && std::isspace(static_cast<unsigned char>(value.front()))) value.remove_prefix(1);
    while (!value.empty() && std::isspace(static_cast<unsigned char>(value.back()))) value.remove_suffix(1);
    return value;
}

std::vector<std::string_view> split_fields(std::string_view text) {
    std::vector<std::string_view> fields;
    text = trim(text);

    while (!text.empty()) {
        size_t token_end = 0;
        while (token_end < text.size() && !std::isspace(static_cast<unsigned char>(text[token_end]))) {
            ++token_end;
        }

        fields.push_back(text.substr(0, token_end));
        text.remove_prefix(token_end);
        text = trim(text);
    }

    return fields;
}

bool parse_non_negative_int(std::string_view text, int16_t& value) {
    if (text.empty()) {
        value = 0;
        return true;
    }

    int parsed = 0;
    for (const char c : text) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;

        parsed = parsed * 10 + (c - '0');
        if (parsed > std::numeric_limits<int16_t>::max()) return false;
    }

    value = static_cast<int16_t>(parsed);
    return true;
}

}  // namespace

FenParseResult FenParser::parse(std::string_view fen) {
    const std::vector<std::string_view> fen_tokens = split_fields(fen);

    if (fen_tokens.size() < 4) {
        return FenParseResult::fail("FEN has fewer than 4 fields");
    }

    const std::string_view position = fen_tokens[0];
    const std::string_view player = fen_tokens[1];
    const std::string_view castling = fen_tokens[2];
    const std::string_view en_passant = fen_tokens[3];

    const std::string_view half_move_clock = fen_tokens.size() >= 5 ? fen_tokens[4] : std::string_view("0");
    const std::string_view full_move_counter = fen_tokens.size() >= 6 ? fen_tokens[5] : std::string_view("1");
    (void)full_move_counter;

    CanonicalPosition pos;
    int16_t fifty_move = 0;

    pos.side = (player == "w") ? WHITE : BLACK;
    if (player != "w" && player != "b") {
        return FenParseResult::fail("Invalid side to move in FEN");
    }

    auto square = 56;
    int current_rank_width = 0;
    int rank_count = 1;

    for (const char c : position) {
        if (c == '/') {
            if (current_rank_width != 8 || rank_count >= 8) {
                return FenParseResult::fail("Invalid board in FEN");
            }

            square -= 16;
            current_rank_width = 0;
            ++rank_count;
        } else if (std::isdigit(static_cast<unsigned char>(c))) {
            for (int empty_amt = 0; empty_amt < c - '0'; ++empty_amt) {
                if (current_rank_width >= 8 || square < 0 || square >= 64) {
                    return FenParseResult::fail("Invalid board in FEN");
                }

                pos.board[square++] = EMPTY;
                ++current_rank_width;
            }
        } else if (std::isalpha(static_cast<unsigned char>(c))) {
            const Piece piece = piece_from_char(c);
            if (piece == EMPTY || current_rank_width >= 8 || square < 0 || square >= 64) {
                return FenParseResult::fail("Invalid board in FEN");
            }

            pos.board[square++] = piece;
            ++current_rank_width;
        } else {
            return FenParseResult::fail("Invalid board in FEN");
        }
    }

    // Accept the historical engine/datagen bug where the final rank omitted the trailing empty count.
    // That means the final rank is short, but only because it ended with one or more empty squares.
    if (rank_count == 8 &&
        current_rank_width < 8 &&
        !position.empty() &&
        (position.back() == '/' || std::isalpha(static_cast<unsigned char>(position.back())))) {
        while (current_rank_width < 8) {
            if (square < 0 || square >= 64) {
                return FenParseResult::fail("Invalid board in FEN");
            }

            pos.board[square++] = EMPTY;
            ++current_rank_width;
        }
    }

    if (square != 8 || current_rank_width != 8 || rank_count != 8) {
        return FenParseResult::fail("Invalid board in FEN");
    }

    pos.castling = 0;

    if (castling != "-") {
        const Square white_king = pos.king_square(WHITE);
        const Square black_king = pos.king_square(BLACK);

        if (white_king == NO_SQUARE || black_king == NO_SQUARE) {
            return FenParseResult::fail("Invalid castling rights in FEN");
        }

        for (const char c : castling) {
            if (c == 'K') pos.castling |= WHITE_OO;
            else if (c == 'Q') pos.castling |= WHITE_OOO;
            else if (c == 'k') pos.castling |= BLACK_OO;
            else if (c == 'q') pos.castling |= BLACK_OOO;
            else if (c >= 'A' && c <= 'H') {
                const int rook_file = c - 'A';
                const int king_file = square_file(white_king);
                pos.castling |= rook_file > king_file ? WHITE_OO : WHITE_OOO;
            } else if (c >= 'a' && c <= 'h') {
                const int rook_file = c - 'a';
                const int king_file = square_file(black_king);
                pos.castling |= rook_file > king_file ? BLACK_OO : BLACK_OOO;
            } else {
                return FenParseResult::fail("Invalid castling rights in FEN");
            }
        }
    }

    if (en_passant.size() > 1) {
        if (en_passant.size() != 2 ||
            en_passant[0] < 'a' || en_passant[0] > 'h' ||
            (en_passant[1] != '3' && en_passant[1] != '6')) {
            return FenParseResult::fail("Invalid en passant square in FEN");
        }

        pos.ep_square = make_square(en_passant[0] - 'a', en_passant[1] - '1');
    } else if (en_passant == "-") {
        pos.ep_square = NO_SQUARE;
    } else {
        return FenParseResult::fail("Invalid en passant square in FEN");
    }

    if (!parse_non_negative_int(half_move_clock, fifty_move)) {
        return FenParseResult::fail("Invalid halfmove clock in FEN");
    }

    if (!pos.is_valid()) {
        return FenParseResult::fail("Position validation failed");
    }

    return FenParseResult::ok(std::move(pos), fifty_move);
}

}  // namespace pipeline
