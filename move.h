
#ifndef ANTARESCHESSENGINE_MOVE_H
#define ANTARESCHESSENGINE_MOVE_H

#include <string>
#include "constants.h"
#include "position.h"

std::string get_uci_from_move(MOVE_TYPE move);

MOVE_TYPE get_move_from_uci(const Position& position, std::string uci);



inline MOVE_TYPE encode_move(SQUARE_TYPE origin_square, SQUARE_TYPE target_square,
                             PIECE_TYPE selected, PIECE_TYPE occupied,
                             uint16_t move_type, PIECE_TYPE promotion_piece, bool is_capture) {
    return origin_square | target_square << 7 | selected << 14 | occupied << 18 | move_type << 22 | \
        promotion_piece << 25 | is_capture << 29;
}

inline SQUARE_TYPE get_origin_square(MOVE_TYPE move) {
    return move & 0x7f;
}

inline SQUARE_TYPE get_target_square(MOVE_TYPE move) {
    return (move & 0x3f80) >> 7;
}

inline PIECE_TYPE get_selected(MOVE_TYPE move) {
    return (move & 0x3c000) >> 14;
}

inline PIECE_TYPE get_occupied(MOVE_TYPE move) {
    return (move & 0x3c0000) >> 18;
}

inline uint16_t get_move_type(MOVE_TYPE move) {
    return (move & 0x1c00000) >> 22;
}

inline PIECE_TYPE get_promotion_piece(MOVE_TYPE move) {
    return (move & 0x1e000000) >> 25;
}

inline bool get_is_capture(MOVE_TYPE move) {
    return (move & 0x20000000) >> 29;
}



#endif //ANTARESCHESSENGINE_MOVE_H