
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cassert>
#include "constants.h"
#include "types.h"

template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}


Piece piece_to_num(char piece) {

    auto it = std::find(std::begin(PIECE_MATCHER), std::end(PIECE_MATCHER), piece);
    return static_cast<Piece>(it - std::begin(PIECE_MATCHER));
}