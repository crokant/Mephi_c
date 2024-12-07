#include "Game.h"

int main() {
    int size;
    std::cout << "Enter board size: ";
    std::cin >> size;

    Game game(size);
    game.start();

    return 0;
}
