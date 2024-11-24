
#ifndef ALTAIR_USEFUL_H
#define ALTAIR_USEFUL_H

#include <vector>
#include <string>

template <typename Out>
void split(const std::string &s, char delim, Out result);

std::vector<std::string> split(const std::string &s, char delim);

std::string reduce_fen_string(const std::string &fen_string);

Piece piece_to_num(char piece);

#endif //ALTAIR_USEFUL_H