#ifndef SHAPE_H
#define SHAPE_H

#include "board-matrix.h"
#include "vec2.h"
#include "vector"

struct Shape {
    // Define the shapes using a 2D vector of unsigned char
    inline static const std::vector<std::vector<std::vector<unsigned char> > > SHAPES = {
        // I shape
        {
            {1, 1, 1, 1}
        },
        // J shape
        {
            {2, 2, 2},
            {0, 0, 2}
        },
        // L shape
        {
            {3, 3, 3},
            {3, 0, 0}
        },
        // O shape
        {
            {4, 4},
            {4, 4}
        },
        // S shape
        {
            {5, 5, 0},
            {0, 5, 5}
        },
        // T shape
        {
            {6, 6, 6},
            {0, 6, 0}
        },
        // Z shape
        {
            {0, 7, 7},
            {7, 7, 0}
        }
    };

    Vec2                       position; // Position of the shape in the game grid
    BoardMatrix<unsigned char> blocks;   // Shape structure;

    explicit Shape(const unsigned int shape_index) {
        if (shape_index >= SHAPES.size()) { throw std::out_of_range("Invalid shape index"); }

        position = Vec2(0, 0);

        const auto &shape = SHAPES[shape_index];
        blocks            = BoardMatrix<unsigned char>(static_cast<int>(shape[0].size()), static_cast<int>(shape.size()));
        for (int y = 0; y < shape.size(); ++y) { for (int x = 0; x < shape[y].size(); ++x) { blocks(x, y) = shape[y][x]; } }
    }
    explicit Shape() : position(Vec2(0, 0)), blocks(BoardMatrix<unsigned char>(0, 0)) {}

    [[nodiscard]] Vec2 get_size() const { return Vec2(blocks.get_width(), blocks.get_height()); }
    [[nodiscard]] bool is_valid() const { return !blocks.is_empty(); }
};

#endif //SHAPE_H
