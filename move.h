
#ifndef ANTARESCHESSENGINE_MOVE_H
#define ANTARESCHESSENGINE_MOVE_H

// Major contributions by Archishmaan Peyyety as a pull request to Alex2262/BitboardEngine

#include <cstdint>
#include "types.h"
#include "string"

enum MoveType : uint8_t {
    MOVE_TYPE_NORMAL	= 0b0000,
    MOVE_TYPE_EP		= 0b0001,
    MOVE_TYPE_CASTLE	= 0b0010,
    MOVE_TYPE_PROMOTION	= 0b0011,
};

enum PromotionType : uint8_t {
    PROMOTION_KNIGHT	= 0b0000,
    PROMOTION_BISHOP	= 0b0001,
    PROMOTION_ROOK		= 0b0010,
    PROMOTION_QUEEN		= 0b0011,
};

class Position;

// The normal Move class that is used for the most part as it only requires an uint16_t
class Move {
private:
    // Bits are arranged as follows
    // | 2 bits for promotion piece | 2 bits for type | 6 bits for from | 6 bits for to
    uint16_t move;
public:
    inline Move() : move(0) {}

    inline explicit Move(uint16_t m) { move = m; }

    inline Move(Square origin_square, Square target_square) : move(0) {
        move = (origin_square << 6) | target_square;
    }

    inline Move(Square origin_square, Square target_square, MoveType type) : move(0) {
        move = (type << 12) | (origin_square << 6) | target_square;
    }

    inline Move(Square origin_square, Square target_square, MoveType type, PromotionType promotion_type) : move(0) {
        move = (promotion_type << 14) | (type << 12) | (origin_square << 6) | target_square;
    }

    [[nodiscard]] bool is_capture(const Position& position) const;

    Move(const Position& position, std::string uci);
    [[nodiscard]] std::string get_uci(const Position& position) const;

    [[nodiscard]] inline Square target() const { return Square(move & 0x3f); }
    [[nodiscard]] inline Square origin() const { return Square((move >> 6) & 0x3f); }
    [[nodiscard]] inline MoveType type() const { return MoveType((move >> 12) & 0x3); }
    [[nodiscard]] inline PromotionType promotion_type() const { return PromotionType((move >> 14) & 0x3); }
    [[nodiscard]] inline uint16_t internal_move() const { return move; };

    bool operator==(Move a) const { return move == a.move; }
    bool operator!=(Move a) const { return move != a.move; }
};


// The InformativeMove class stores selected and occupied pieces as extra information for usage in tables such as
// continuation histories that require this information to be preserved in the move class
class InformativeMove {
private:
    // Bits are arranged as follows
    // | 4 bits for selected | 4 bits for occupied | 2 bits for promotion piece -->
    // | 2 bits for type | 6 bits for from | 6 bits for to
    uint32_t move;
public:
    inline InformativeMove() : move(0) {}

    inline explicit InformativeMove(uint32_t m) { move = m; }

    inline InformativeMove(Square origin, Square target, Piece selected, Piece occupied,
                           MoveType type, PromotionType promotion_type) : move(0) {
        move = (selected << 20) | (occupied << 16) | (promotion_type << 14) | (type << 12) | (origin << 6) | target;
    }

    inline InformativeMove(Move normal_move, Piece selected, Piece occupied) : move(0) {
        move = (selected << 20) | (occupied << 16) | normal_move.internal_move();
    }

    [[nodiscard]] inline Square target() const { return Square(move & 0x3f); }
    [[nodiscard]] inline Square origin() const { return Square((move >> 6) & 0x3f); }
    [[nodiscard]] inline MoveType type() const { return MoveType((move >> 12) & 0x3); }
    [[nodiscard]] inline PromotionType promotion_type() const { return PromotionType((move >> 14) & 0x3); }
    [[nodiscard]] inline Piece occupied() const { return Piece((move >> 16) & 0xf); }
    [[nodiscard]] inline Piece selected() const { return Piece((move >> 20) & 0xf); }
    [[nodiscard]] inline Move normal_move() const { return Move(move & 0xffff); }

    bool operator==(InformativeMove a) const { return move == a.move; }
    bool operator!=(InformativeMove a) const { return move != a.move; }
};

const Move NO_MOVE = Move();
const InformativeMove NO_INFORMATIVE_MOVE = InformativeMove();


#endif //ANTARESCHESSENGINE_MOVE_H