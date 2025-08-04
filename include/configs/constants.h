#pragma once

constexpr int          GAME_GRID_WIDTH  = 10;                                 // Width of the terminal screen (in cells)
constexpr int          GAME_GRID_HEIGHT = 20;                                 // Height of the terminal screen (in cells)
constexpr int          GAME_GRID_SIZE   = GAME_GRID_WIDTH * GAME_GRID_HEIGHT; // Total number of cells in the game grid (in cells)
constexpr unsigned int GAME_TICK_RATE   = 1;                                  // Number of ticks per second
constexpr int          GAME_HELD_WIDTH  = 4;                                  // Width of the held shape display (in cells)
constexpr int          GAME_HELD_HEIGHT = 4;                                  // Height of the held shape display (in cells)

constexpr unsigned int RENDERING_FRAME_RATE = 24; // Target frame rate for the game loop
