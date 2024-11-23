
#include <string>
#include <vector>
#include <algorithm>
#include "constants.h"
#include "types.h"

template <typename Out>
void split(const std::string &s, char delim, Out result) {
    size_t start = 0;
    size_t end = s.find(delim);

    while (end != std::string::npos) {
        *result++ = s.substr(start, end - start); // Extract substring between start and delimiter
        start = end + 1;                         // Move past the delimiter
        end = s.find(delim, start);              // Find the next delimiter
    }

    *result++ = s.substr(start); // Add the last substring
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