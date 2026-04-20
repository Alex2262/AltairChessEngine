cmake_minimum_required(VERSION 3.21)
project(AltairPipeline)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -flto")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)
enable_testing()

# Core pipeline library
add_library(altair_pipeline STATIC
    src/core/canonical_zobrist.cpp
    src/core/canonical_position.cpp
    src/parsing/fen_parser.cpp
    src/parsing/record_parser.cpp
    src/analytics/csv_writer.cpp
    src/analytics/metrics.cpp
    src/analytics/streaming_stats.cpp
    src/compilation/shard_writer.cpp
    src/compilation/shard_compiler.cpp
)

target_include_directories(altair_pipeline PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(altair_pipeline ZLIB::ZLIB Threads::Threads)

# CLI: analyze_raw
add_executable(analyze_raw cli/analyze_raw.cpp)
target_link_libraries(analyze_raw altair_pipeline)

# CLI: compile_shards
add_executable(compile_shards cli/compile_shards.cpp)
target_link_libraries(compile_shards altair_pipeline)

# CLI: analyze_shards (to be added later)
# add_executable(analyze_shards cli/analyze_shards.cpp)
# target_link_libraries(analyze_shards altair_pipeline)

add_executable(pipeline_tests tests/pipeline_tests.cpp)
target_link_libraries(pipeline_tests altair_pipeline)

add_test(NAME pipeline_tests COMMAND pipeline_tests)
