#include "gameManager.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <map_file>\n";
        return 1;
    }

    GameManager game(argv[1]);
    game.run();

    return 0;
}

