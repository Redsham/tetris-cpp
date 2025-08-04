#include "game.h"

int main() {
    Game game{};

    game.init();      // Initialize the game
    game.loop();      // Start the game loop
    game.terminate(); // Clean up and exit the game
}
