cmake_minimum_required(VERSION 3.21)
project(AltairChessEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -flto")

# Default build type
if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Release)
endif()

find_package(Threads REQUIRED)

#set(GCC_COVERAGE_LINK_FLAGS "-static")

#set(CMAKE_EXE_LINKER_FLAGS "${GCC_COVERAGE_LINK_FLAGS}")
include_directories(.)

add_executable(Altair
        constants.h
        main.cpp
        move.cpp
        move.h
        perft.cpp
        perft.h
        position.cpp
        position.h
        useful.cpp
        useful.h
        uci.cpp
        uci.h
        zobrist.h
        see.cpp
        see.h
        types.h
        bitboard.cpp
        bitboard.h
        tables.h
        fixed_vector.h
        evaluation.cpp
        evaluation.h
        evaluation_constants.h
        move_ordering.cpp
        move_ordering.h mcts.cpp mcts.h search.cpp search.h)

target_link_libraries(Altair Threads::Threads)
