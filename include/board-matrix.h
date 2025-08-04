#pragma once

#include "vec2.h"
#include <vector>
#include <algorithm>

template<std::default_initializable T>
struct BoardMatrix {
    BoardMatrix() : data(0), width(0), height(0) {}
    BoardMatrix(const int w, const int h, const T default_value = T{}) : data(w * h), width(w), height(h) { fill(default_value); }

    BoardMatrix(const BoardMatrix &other);
    BoardMatrix &operator=(const BoardMatrix &other);

    BoardMatrix(BoardMatrix &&other) noexcept;
    BoardMatrix &operator=(BoardMatrix &&other) noexcept;

    [[nodiscard]] int  get_width() const { return width; }                                           // Get dimensions of the grid
    [[nodiscard]] int  get_height() const { return height; }                                         // Get dimensions of the grid
    [[nodiscard]] int  get_size() const { return width * height; }                                   // Get total size of the grid (width * height)
    [[nodiscard]] int  get_index(const int x, const int y) const { return y * width + x; }           // Get index from coordinates
    [[nodiscard]] int  get_index(const Vec2 &coords) const { return get_index(coords.x, coords.y); } // Get index from position
    [[nodiscard]] bool is_empty() const { return width == 0 || height == 0; }                        // Check if the grid is empty
    [[nodiscard]] T *  get_raw() const { return data; }                                              // Get raw pointer to the data

    void fill(const T &value) noexcept; // Fill the grid with a specific value

    BoardMatrix rotate_clockwise() const;         // Return a new grid rotated 90 degrees clockwise
    BoardMatrix rotate_counter_clockwise() const; // Return a new grid rotated 90 degrees counter-clockwise

    T &      operator()(const int x, const int y) { return data[y * width + x]; }
    T &      operator()(const Vec2 &pos) { return (*this)(pos.x, pos.y); }
    const T &operator()(const int x, const int y) const { return data[y * width + x]; }
    const T &operator()(const Vec2 &pos) const { return (*this)(pos.x, pos.y); }

private:
    std::vector<T, std::allocator<T> > data;   // Data storage for the grid
    int                                width;  // Width of the grid
    int                                height; // Height of the grid
};

// --- Implementation ---

template<std::default_initializable T>
BoardMatrix<T>::BoardMatrix(const BoardMatrix &other) : data(other.width * other.height), width(other.width), height(other.height) { std::copy(other.data.begin(), other.data.end(), data.begin()); }
template<std::default_initializable T>
BoardMatrix<T> &BoardMatrix<T>::operator=(const BoardMatrix &other) {
    if (this == &other) { return *this; }

    width  = other.width;
    height = other.height;
    data.resize(width * height);
    std::copy(other.data.begin(), other.data.end(), data.begin());

    return *this;
}

template<std::default_initializable T>
BoardMatrix<T>::BoardMatrix(BoardMatrix &&other) noexcept : data(other.data), width(other.width), height(other.height) {
    other.data.clear();
    other.width  = 0;
    other.height = 0;
}
template<std::default_initializable T>
BoardMatrix<T> &BoardMatrix<T>::operator=(BoardMatrix &&other) noexcept {
    if (this == &other) { return *this; }

    data   = std::move(other.data);
    width  = other.width;
    height = other.height;

    other.data.clear();
    other.width  = 0;
    other.height = 0;

    return *this;
}

template<std::default_initializable T>
void BoardMatrix<T>::fill(const T &value) noexcept { std::fill(data.begin(), data.end(), value); }

template<std::default_initializable T>
BoardMatrix<T> BoardMatrix<T>::rotate_clockwise() const {
    BoardMatrix rotated(height, width);
    for (int y = 0; y < height; ++y) { for (int x = 0; x < width; ++x) { rotated.data[x * height + (height - 1 - y)] = data[y * width + x]; } }
    return rotated;
}
template<std::default_initializable T>
BoardMatrix<T> BoardMatrix<T>::rotate_counter_clockwise() const {
    BoardMatrix rotated(height, width);
    for (int y = 0; y < height; ++y) { for (int x = 0; x < width; ++x) { rotated.data[(width - 1 - x) * height + y] = data[y * width + x]; } }
    return rotated;
}
