//
// Created by Alex Tian on 9/12/2022.
//

#ifndef ANTARESCHESSENGINE_MOVE_GENERATOR_H
#define ANTARESCHESSENGINE_MOVE_GENERATOR_H

#include <vector>
#include <string>
#include "constants.h"
#include "position.h"

std::vector<MOVE_TYPE> get_pseudo_legal_moves(const Position& position);

// std::vector<MOVE_TYPE> get_pseudo_legal_captures(Position& position);


#endif //ANTARESCHESSENGINE_MOVE_GENERATOR_H
