
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


std::string reduce_fen_string(const std::string &fen_string) {
    std::string result = fen_string;

    result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));

    result.erase(std::find_if(result.rbegin(), result.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), result.end());

    auto new_end = std::unique(result.begin(), result.end(), [](char left, char right) {
        return std::isspace(left) && std::isspace(right);
    });
    result.erase(new_end, result.end());

    return result;
}

Piece piece_to_num(char piece) {

    auto it = std::find(std::begin(PIECE_MATCHER), std::end(PIECE_MATCHER), piece);
    return static_cast<Piece>(it - std::begin(PIECE_MATCHER));
}