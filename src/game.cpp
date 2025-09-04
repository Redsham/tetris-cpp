#include "game.h"

#include <chrono>
#include <thread>

#include "random.h"
#include "rendering.h"
#include "shape.h"

#include "configs/symbols.h"
#include "configs/input.h"

void Game::init() {
    // Initialize components
    Rendering::init();
    next_shape();
}
void Game::terminate() {
    // Clean up resources
    Rendering::terminate();
}


void Game::loop() {
    using clock     = std::chrono::steady_clock;
    auto last_tick  = clock::now();
    auto last_frame = clock::now();

    tick();
    draw();

    while (running) {
        handle_input();

        auto       now           = clock::now();
        const auto elapsed_frame = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_frame).count();

        if (elapsed_frame >= 1000 / RENDERING_FRAME_RATE || force_redraw) {
            const auto elapsed_tick = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_tick).count();

            if (elapsed_tick >= 1000 / GAME_TICK_RATE) {
                last_tick = now;
                tick();
            }

            last_frame   = now;
            force_redraw = false;

            Rendering::update();
            draw();
            Rendering::refresh();
        }

        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
}

void Game::handle_input() {
    switch (getch()) {
        case ERR:
            return;
        case INPUT_KEY_LEFT: // Move shape left
            translate_shape(Vec2(-1, 0));
            break;
        case INPUT_KEY_RIGHT: // Move shape right
            translate_shape(Vec2(1, 0));
            break;
        case INPUT_KEY_DOWN: // Move shape down
            translate_shape(Vec2(0, 1));
            break;
        case INPUT_KEY_UP: {
            // Rotate shape clockwise
            const auto next_grid = current_shape.blocks.rotate_clockwise();
            if (is_shape_inbounds(next_grid, current_shape.position) && !
                is_shape_intersecting(next_grid, current_shape.position)) {
                current_shape.blocks = next_grid; // Update blocks if valid
                update_landing_position();
            } else {
                const auto compensated_position = current_shape.position + Vec2(0, -1);
                if (is_shape_inbounds(next_grid, compensated_position) && !
                    is_shape_intersecting(next_grid, compensated_position)) {
                    current_shape.blocks = next_grid; // Update blocks if
                    move_shape(compensated_position); // Update position if valid
                }
            }
            break;
        }
        case INPUT_KEY_PLACE:
            move_shape(landing_position);
            place_shape();
            next_shape();
            break;
        case INPUT_KEY_SWAP:
            swap_shapes();
            break;
        default:
            break;
    }
}
void Game::tick() {
    if (!translate_shape(Vec2(0, 1))) {
        place_shape();
        next_shape();
    }
}
void Game::draw() {
    Rendering::set_color(Colors::Default);

    const auto center = Rendering::get_size() / 2;
    const auto origin = Vec2(center.x - GAME_GRID_WIDTH / 2, center.y - GAME_GRID_HEIGHT / 2);

    Rendering::draw_border(Rect(origin + Vec2(-1, -1), Vec2(GAME_GRID_WIDTH * 2, GAME_GRID_HEIGHT) + Vec2(1, 1)));
    Rendering::draw_grid(grid, origin);

    if (Rendering::is_resized() || held_shape_changed) {
        const auto held_window_origin = origin + Vec2(-GAME_HELD_WIDTH * 2 - 2, 0);

        // Clear the held shape area
        Rendering::draw_box(Rect(held_window_origin, Vec2(GAME_HELD_WIDTH * 2, GAME_HELD_HEIGHT)), SYMBOL_EMPTY);

        Rendering::draw_border(Rect(held_window_origin + Vec2(-1, -1), Vec2(GAME_HELD_WIDTH * 2 + 1, GAME_HELD_HEIGHT + 1)));
        Rendering::draw_text(held_window_origin + Vec2(0, -1), L"HELD");

        const auto shape_size       = held_shape.get_size() * Vec2(2, 1);
        const auto held_window_size = Vec2(GAME_HELD_WIDTH * 2, GAME_HELD_HEIGHT);
        Rendering::draw_shape(held_shape, held_window_origin + (held_window_size - shape_size) / 2, false);

        held_shape_changed = false;
    }

    Rendering::draw_shape(current_shape, origin + landing_position * Vec2(2, 1), true);
    Rendering::draw_shape(current_shape, origin + current_shape.position * Vec2(2, 1), false);
}

bool Game::next_shape() {
    if (shapes_pool.empty()) {
        shapes_pool = {0, 1, 2, 3, 4, 5, 6};                     // All shape indices
        Random::shuffle(shapes_pool.begin(), shapes_pool.end()); // Shuffle the shape indices
    }

    // Generate a new random shape
    const auto shape_index = shapes_pool.back();
    shapes_pool.pop_back();

    current_shape = Shape(shape_index);
    move_shape(Vec2(grid.get_width() / 2 - current_shape.get_size().x / 2, 0));

    return is_shape_inbounds(current_shape.blocks, current_shape.position) && !
           is_shape_intersecting(current_shape.blocks, current_shape.position);
}
bool Game::move_shape(const Vec2 &position) {
    // Check if the new position is within bounds
    if (!is_shape_inbounds(current_shape.blocks, position)) { return false; }

    // Check if the new position intersects with existing blocks
    if (is_shape_intersecting(current_shape.blocks, position)) { return false; }

    // Update the current shape's position
    current_shape.position = position;
    update_landing_position();

    return true;
}
void Game::update_landing_position() {
    landing_position           = current_shape.position;
    Vec2 next_landing_position = current_shape.position + Vec2(0, 1);

    while (is_shape_inbounds(current_shape.blocks, next_landing_position) &&
           !is_shape_intersecting(current_shape.blocks, next_landing_position)) {
        landing_position = next_landing_position;
        next_landing_position += Vec2(0, 1);
    }
}

void Game::place_shape() {
    can_swap = true; // Allow swapping shapes again after placing the current shape

    // Place the shape on the grid at its current position
    for (int y = 0; y < current_shape.blocks.get_height(); ++y) {
        for (int x = 0; x < current_shape.blocks.get_width(); ++x) {
            if (current_shape.blocks(x, y) != 0) {
                const auto grid_x     = current_shape.position.x + x;
                const auto grid_y     = current_shape.position.y + y;
                const auto grid_value = current_shape.blocks(x, y);

                if (grid_value != 0) { grid(grid_x, grid_y) = grid_value; }
            }
        }
    }

    remove_filled_lines();
}
void Game::swap_shapes() {
    if (!can_swap) { return; }

    if (held_shape.is_valid()) {
        std::swap(current_shape, held_shape);
        move_shape(Vec2(grid.get_width() / 2 - current_shape.get_size().x / 2, 0));
    } else {
        held_shape = current_shape;
        next_shape();
    }

    held_shape_changed = true;  // Indicate that the held shape has changed
    can_swap           = false; // Prevent swapping again until the next shape is placed
}

void Game::remove_filled_lines() {
    for (int y = 0; y < grid.get_height(); ++y) {
        bool filled = true;

        for (int x = 0; x < grid.get_width(); ++x) {
            if (grid(x, y) == 0) {
                filled = false;
                break;
            }
        }

        if (filled) {
            // Remove the filled line by shifting all lines above it down
            for (int shift_y = y; shift_y > 0; --shift_y) { for (int x = 0; x < grid.get_width(); ++x) { grid(x, shift_y) = grid(x, shift_y - 1); } }

            // Clear the top line
            for (int x = 0; x < grid.get_width(); ++x) { grid(x, 0) = 0; }
        }
    }
}

bool Game::is_shape_inbounds(const BoardMatrix<unsigned char> &shape_grid, const Vec2 &pos) const {
    // Check if the shape is within the grid bounds
    return pos.x >= 0 && pos.x + shape_grid.get_width() <= grid.get_width() &&
           pos.y >= 0 && pos.y + shape_grid.get_height() <= grid.get_height();
}
bool Game::is_shape_intersecting(const BoardMatrix<unsigned char> &shape_grid, const Vec2 &pos) const {
    for (int y = 0; y < shape_grid.get_height(); ++y) {
        for (int x = 0; x < shape_grid.get_width(); ++x) {
            if (shape_grid(x, y) != 0) {
                const auto grid_x = pos.x + x;
                const auto grid_y = pos.y + y;

                if (grid(grid_x, grid_y) != 0) {
                    return true; // Collision detected
                }
            }
        }
    }

    return false; // No collision
}
