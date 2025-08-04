#pragma once

#include <ncursesw/cursesw.h>

#include "shape.h"
#include "vec2.h"

enum class Colors : short {
    Default = 1,
    Black,
    Red,
    Green,
    Blue,
    Yellow,
    Cyan,
    Magenta,
    White
};

class Rendering {
public:
    static void init();      // Initialize the rendering system
    static void terminate(); // Terminate the rendering system

    static void update(); // Update the rendering system

    static void clear() { ::clear(); } // Clear the terminal screen
    static void refresh();             // Refresh the terminal screen

    static int  get_width() { return COLS; }             // Get the width of the terminal screen
    static int  get_height() { return LINES; }           // Get the height of the terminal screen
    static Vec2 get_size() { return Vec2(COLS, LINES); } // Get the size of the terminal screen
    static bool is_resized() { return resized; }         // Check if the terminal has been resized

    static void set_color(Colors color, bool inverted = false); // Set the color for drawing

    static void draw_pixel(int x, int y, wchar_t symbol); // Draw a pixel at the specified coordinates
    static void draw_pixel(const Vec2 &pos, const wchar_t symbol) { draw_pixel(pos.x, pos.y, symbol); }

    static void draw_char(int x, int y, wchar_t symbol); // Draw a character at the specified coordinates
    static void draw_char(const Vec2 &pos, wchar_t symbol) { draw_char(pos.x, pos.y, symbol); }
    // Draw a character at the specified position

    static void draw_pixel_line(const Vec2 &start, const Vec2 &end, wchar_t symbol);
    // Draw a line on the terminal screen
    static void draw_line(const Vec2 &start, const Vec2 &end, wchar_t symbol); // Draw a line between two points

    static void draw_box(const Vec2 &min, const Vec2 &max, wchar_t symbol); // Draw a filled box between two points

    static void draw_border(const Vec2 &min, const Vec2 &max);  // Draw a border around the specified area
    static void draw_text(const Vec2 &pos, const wchar_t *str); // Draw text at the specified position

    static void draw_grid(const BoardMatrix<unsigned char> &grid, Vec2 origin);  // Draw the game grid
    static void draw_shape(const Shape &shape, Vec2 pos, bool is_shadow); // Draw a shape at the specified position

private:
    inline static bool  resized; // Flag to indicate if the terminal has been resized
    inline static Vec2  size;    // Size of the terminal screen
    inline static short color;   // Current color for drawing

    inline static bool overbound;        // Flag to indicate if the drawing is overbound
    inline static bool overbound_redraw; // Flag to redraw the overbound area

    static void init_palette(); // Initialize the color palette
};