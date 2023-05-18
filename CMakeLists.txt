cmake_minimum_required(VERSION 3.21)
project(AltairChessEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#set(GCC_COVERAGE_LINK_FLAGS "-static")

#set(CMAKE_EXE_LINKER_FLAGS "${GCC_COVERAGE_LINK_FLAGS}")
include_directories(.)

add_executable(AltairChess
        constants.h
        evaluation.cpp
        evaluation.h
        main.cpp
        move.cpp
        move.h
        perft.cpp
        perft.h
        position.cpp
        position.h
        search.cpp
        search.h
        useful.cpp
        useful.h uci.cpp uci.h zobrist.h bench.cpp bench.h see.cpp see.h evaluation_constants.h)
