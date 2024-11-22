

#include "uci.h"

int main(int argc, char* argv[]) {

    UCI main_uci;
    main_uci.initialize_uci();

    // Begin the UCI input loop
    main_uci.uci_loop();


    return 0;
}
