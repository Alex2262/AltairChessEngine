

#include <iostream>
#include <random>
#include "position.h"
#include "perft.h"
#include "uci.h"
#include "bench.h"
#include "datagen.h"

int main(int argc, char* argv[]) {

    UCI main_uci;
    main_uci.initialize_uci();

    // BENCH arg-parsing
    bool bench_flag = false;
    bool datagen_flag = false;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "bench") == 0) bench_flag = true;
        if (strcmp(argv[i], "datagen") == 0) datagen_flag = true;
    }

    if (bench_flag) {
        run_bench(*main_uci.engine, BENCH_DEPTH);
        return 0;
    }

    if (datagen_flag) {
        Datagen datagen{};

        if (argc < 3) {
            std::cout << "Thread number expected" << std::endl;
            return 0;
        }

        std::string thread_count = argv[2];
        std::random_device random_device;
        std::mt19937 gen(random_device());
        std::uniform_int_distribution<> distribution(1, 1048576);

        int thread_num = std::stoi(thread_count);

        datagen.threads = thread_num;
        datagen.random_seed = distribution(gen);

        datagen.start_datagen();

        return 0;
    }

    // Begin the UCI input loop
    main_uci.uci_loop();


    return 0;
}
