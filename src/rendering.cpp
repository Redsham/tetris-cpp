#include "rendering.h"

#include <algorithm>
#include <clocale>
#include <sstream>

#include "../include/configs/symbols.h"

constexpr short INVERTED_OFFSET = static_cast<short>(Colors::White);

void Rendering::init() {
    setlocale(LC_ALL, ""); // Set locale to the user's environment
    initscr();             // Initialize ncurses mode
    cbreak();              // Disable line buffering, allowing input to be processed immediately
    noecho();              // Disable echoing of typed characters
    keypad(stdscr, TRUE);  // Enable special keys (like arrow keys)
    nodelay(stdscr, TRUE); // Make getch() non-blocking
    curs_set(0);           // Hide the cursor
    start_color();         // Initialize color functionality
    init_palette();        // Initialize the color palette
}
void Rendering::terminate() {
    endwin(); // End ncurses mode
}

void Rendering::update() {
    overbound = false; // Reset the overbound flag
    resized   = false; // Reset the resized flag

    if (size != get_size()) {
        resized = true;
        size    = get_size();
        clear(); // Clear the screen if the size has changed
    }
}

void Rendering::refresh() {
    if (overbound) {
        clear();

        set_color(Colors::Red, true);

        const auto center = get_size() / 2;
        draw_text(Vec2(center.x - 7, center.y), L"Out of bounds!");

        set_color(Colors::Default);
    }

    ::refresh();
}

void Rendering::set_color(Colors color, const bool inverted) {
    short new_color;
    if (inverted) {
        new_color = INVERTED_OFFSET + static_cast<short>(color);
    } else {
        new_color = static_cast<short>(color);
    }
    if (new_color != Rendering::color) {
        attroff(COLOR_PAIR(Rendering::color)); // Turn off the previous color
        attron(COLOR_PAIR(new_color));         // Turn on the new color
        Rendering::color = new_color;
    }
}

void Rendering::draw_pixel(const int x, const int y, const wchar_t symbol) {
    if (x < 0 || y < 0 || x * 2 >= get_width() || y >= get_height()) {
        overbound = true; // Set the overbound flag if the coordinates are out of bounds
        return;
    }

    move(y, x * 2);                   // Move to the position, multiplying x by 2 for pixel width
    printw("%lc%lc", symbol, symbol); // Print the pixel character
}

void Rendering::draw_char(const int x, const int y, const wchar_t symbol) {
    if (x < 0 || y < 0 || x >= get_width() || y >= get_height()) {
        overbound = true; // Set the overbound flag if the coordinates are out of bounds
        return;
    }

    move(y, x);            // Move to the position, multiplying x by 2 for pixel width
    printw("%lc", symbol); // Print the character
}

void Rendering::draw_grid(const BoardMatrix<unsigned char> &grid, const Vec2 origin) {
    for (int y = 0; y < grid.get_height(); ++y) {
        for (int x = 0; x < grid.get_width(); ++x) {
            if (const auto value = grid(x, y); value != 0) {
                set_color(static_cast<Colors>(value + 2), true);
                draw_pixel(origin.x + x, origin.y + y, SYMBOL_EMPTY);
            } else {
                set_color(Colors::Black, false);
                draw_pixel(origin.x + x, origin.y + y, SYMBOL_EMPTY);
            }
        }
    }

    set_color(Colors::Default, false);
}

void Rendering::draw_shape(const Shape &shape, const Vec2 pos, const bool is_shadow) {
    // Draw the shape on the grid
    for (int y = 0; y < shape.blocks.get_height(); ++y) {
        for (int x = 0; x < shape.blocks.get_width(); ++x) {
            if (const auto block = shape.blocks(x, y); block != 0) {
                set_color(static_cast<Colors>(block + 2), !is_shadow);
                draw_pixel(pos.x + x, pos.y + y, is_shadow ? SYMBOL_SHADOW : SYMBOL_EMPTY);
            }
        }
    }

    set_color(Colors::Default, false);
}

void Rendering::draw_pixel_line(const Vec2 &start, const Vec2 &end, const wchar_t symbol) {
    const int dx    = end.x - start.x;
    const int dy    = end.y - start.y;
    const int steps = std::max(abs(dx), abs(dy));

    const auto x_inc = static_cast<float>(dx) / static_cast<float>(steps);
    const auto y_inc = static_cast<float>(dy) / static_cast<float>(steps);

    auto x = static_cast<float>(start.x);
    auto y = static_cast<float>(start.y);

    for (int i = 0; i <= steps; ++i) {
        draw_pixel(static_cast<int>(x), static_cast<int>(y), symbol);
        x += x_inc;
        y += y_inc;
    }
}

void Rendering::draw_line(const Vec2 &start, const Vec2 &end, wchar_t symbol) {
    const int dx    = end.x - start.x;
    const int dy    = end.y - start.y;
    const int steps = std::max(abs(dx), abs(dy));

    const auto x_inc = static_cast<float>(dx) / static_cast<float>(steps);
    const auto y_inc = static_cast<float>(dy) / static_cast<float>(steps);

    auto x = static_cast<float>(start.x);
    auto y = static_cast<float>(start.y);

    for (int i = 0; i <= steps; ++i) {
        draw_char(static_cast<int>(x), static_cast<int>(y), symbol);
        x += x_inc;
        y += y_inc;
    }
}
void Rendering::draw_box(const Vec2 &min, const Vec2 &max, const wchar_t symbol) {
    for (int y = min.y; y <= max.y; ++y) {
        for (int x = min.x; x <= max.x; ++x) {
            draw_char(x, y, symbol);
        }
    }
}

void Rendering::draw_border(const Vec2 &min, const Vec2 &max) {
    // Draw the top border
    draw_line(Vec2(min.x * 2, min.y), Vec2(max.x * 2, min.y), SYMBOL_BORDER_HORIZONTAL);
    // Draw the bottom border
    draw_line(Vec2(min.x * 2, max.y), Vec2(max.x * 2 + 1, max.y), SYMBOL_BORDER_HORIZONTAL);
    // Draw the left border
    draw_line(Vec2(min.x * 2, min.y), Vec2(min.x * 2, max.y), SYMBOL_BORDER_VERTICAL);
    draw_line(Vec2(max.x * 2, min.y + 1), Vec2(max.x * 2, max.y - 1), SYMBOL_EMPTY);
    // Draw the right border
    draw_line(Vec2(max.x * 2 + 1, min.y), Vec2(max.x * 2 + 1, max.y), SYMBOL_BORDER_VERTICAL);
    draw_line(Vec2(min.x * 2 + 1, min.y + 1), Vec2(min.x * 2 + 1, max.y - 1), SYMBOL_EMPTY);

    // Draw corners
    draw_char(min.x * 2, min.y, SYMBOL_BORDER_TOP_LEFT);
    draw_char(max.x * 2 + 1, min.y, SYMBOL_BORDER_TOP_RIGHT);
    draw_char(min.x * 2, max.y, SYMBOL_BORDER_BOTTOM_LEFT);
    draw_char(max.x * 2 + 1, max.y, SYMBOL_BORDER_BOTTOM_RIGHT);
}

void Rendering::draw_text(const Vec2 &pos, const wchar_t *str) {
    move(pos.y, pos.x); // Move to the specified position
    printw("%ls", str); // Print the wide string
}

void Rendering::init_palette() {
    init_pair(static_cast<short>(Colors::Default), COLOR_WHITE, COLOR_BLACK);
    init_pair(static_cast<short>(Colors::Black), COLOR_BLACK, COLOR_BLACK);
    init_pair(static_cast<short>(Colors::Red), COLOR_RED, COLOR_BLACK);
    init_pair(static_cast<short>(Colors::Green), COLOR_GREEN, COLOR_BLACK);
    init_pair(static_cast<short>(Colors::Blue), COLOR_BLUE, COLOR_BLACK);
    init_pair(static_cast<short>(Colors::Yellow), COLOR_YELLOW, COLOR_BLACK);
    init_pair(static_cast<short>(Colors::Cyan), COLOR_CYAN, COLOR_BLACK);
    init_pair(static_cast<short>(Colors::Magenta), COLOR_MAGENTA, COLOR_BLACK);
    init_pair(static_cast<short>(Colors::White), COLOR_WHITE, COLOR_BLACK);

    // Используем INVERTED_OFFSET для инвертированных цветов
    init_pair(INVERTED_OFFSET + static_cast<short>(Colors::Default), COLOR_BLACK, COLOR_WHITE);
    init_pair(INVERTED_OFFSET + static_cast<short>(Colors::Black), COLOR_WHITE, COLOR_WHITE);
    init_pair(INVERTED_OFFSET + static_cast<short>(Colors::Red), COLOR_BLACK, COLOR_RED);
    init_pair(INVERTED_OFFSET + static_cast<short>(Colors::Green), COLOR_BLACK, COLOR_GREEN);
    init_pair(INVERTED_OFFSET + static_cast<short>(Colors::Blue), COLOR_BLACK, COLOR_BLUE);
    init_pair(INVERTED_OFFSET + static_cast<short>(Colors::Yellow), COLOR_BLACK, COLOR_YELLOW);
    init_pair(INVERTED_OFFSET + static_cast<short>(Colors::Cyan), COLOR_BLACK, COLOR_CYAN);
    init_pair(INVERTED_OFFSET + static_cast<short>(Colors::Magenta), COLOR_BLACK, COLOR_MAGENTA);
    init_pair(INVERTED_OFFSET + static_cast<short>(Colors::White), COLOR_BLACK, COLOR_WHITE);

    color = static_cast<short>(Colors::Default);
    attron(COLOR_PAIR(static_cast<short>(Colors::Default)));
}
