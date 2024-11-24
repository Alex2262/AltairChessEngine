cmake_minimum_required(VERSION 3.16)
project(AltairChessEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Os -std=c++20 -DNDEBUG -flto -ffunction-sections -fdata-sections -fvisibility=hidden -fno-rtti -fno-exceptions -g0 -fmerge-all-constants -fshort-enums -fomit-frame-pointer -fno-asynchronous-unwind-tables -falign-functions=1 -fno-ident")

# Default build type
if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Release)
endif()

#set(GCC_COVERAGE_LINK_FLAGS "-static")

#set(CMAKE_EXE_LINKER_FLAGS "${GCC_COVERAGE_LINK_FLAGS}")
include_directories(.)

add_executable(Altair
        src/constants.h
        src/main.cpp
        src/move.cpp
        src/move.h
        src/position.cpp
        src/position.h
        src/search.cpp
        src/search.h
        src/useful.cpp
        src/useful.h
        src/uci.cpp
        src/uci.h
        src/zobrist.h
        src/see.cpp
        src/see.h
        src/types.h
        src/bitboard.cpp
        src/bitboard.h
        src/attacks.h
        src/fixed_vector.h
        src/evaluation.cpp
        src/evaluation.h
        src/evaluation_constants.h
        src/move_ordering.cpp
        src/move_ordering.h
        src/timeman.cpp src/timeman.h)

