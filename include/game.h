#pragma once

#include "configs/constants.h"
#include "board-matrix.h"
#include "shape.h"

class Game {
public:
    bool                       running = true;                                                          // Flag to control the game loop
    BoardMatrix<unsigned char> grid    = BoardMatrix<unsigned char>(GAME_GRID_WIDTH, GAME_GRID_HEIGHT); // Pointer to the game grid

    void init();
    void loop();
    void terminate();

private:
    std::vector<unsigned int> shapes_pool        = {};      // Pool of next shapes to be played
    Shape                     current_shape      = Shape(); // Current shape being played
    Shape                     held_shape         = Shape(); // Shape to swap with the current shape
    Vec2                      landing_position   = Vec2();  // Position where the current shape will land
    bool                      can_swap           = true;    // Flag to indicate if swapping shapes is allowed
    bool                      held_shape_changed = false;   // Flag to indicate if the held shape has changed
    bool                      force_redraw       = false;   // Flag to force redraw of the game state


    void handle_input();
    void draw();
    void tick();

    bool next_shape();
    bool move_shape(const Vec2 &position);
    bool translate_shape(const Vec2 &position) { return move_shape(current_shape.position + position); }
    void update_landing_position();

    void place_shape();
    void swap_shapes();

    void remove_filled_lines();

    [[nodiscard]] bool is_shape_inbounds(const BoardMatrix<unsigned char> &shape_grid, const Vec2 &pos) const;
    [[nodiscard]] bool is_shape_intersecting(const BoardMatrix<unsigned char> &shape_grid, const Vec2 &pos) const;
};
