#pragma once

#include <algorithm>

#include "vec2.h"

struct Rect {
    Vec2 position; // Position of the rectangle (top-left corner)
    Vec2 size;     // Size of the rectangle

    Rect() : position(0, 0), size(0, 0) {} // Default constructor initializes to (0, 0) for both position and size
    Rect(const Vec2 &position, const Vec2 &size) : position(position), size(size) {}
    Rect(const int x, const int y, const int width, const int height) : position(x, y), size(width, height) {}

    static Rect from_points(const Vec2 &p1, const Vec2 &p2) {
        // Create a rectangle from two points
        return Rect(
                    Vec2(std::min(p1.x, p2.x), std::min(p1.y, p2.y)),
                    Vec2(std::abs(p1.x - p2.x), std::abs(p1.y - p2.y))
                   );
    }

    [[nodiscard]] Vec2 get_left_top() const {
        // Get the top-left corner of the rectangle
        return position;
    }
    [[nodiscard]] Vec2 get_right_top() const {
        // Get the top-right corner of the rectangle
        return Vec2(position.x + size.x, position.y);
    }
    [[nodiscard]] Vec2 get_left_bottom() const {
        // Get the bottom-left corner of the rectangle
        return Vec2(position.x, position.y + size.y);
    }
    [[nodiscard]] Vec2 get_right_bottom() const {
        // Get the bottom-right corner of the rectangle
        return position + size;
    }

    [[nodiscard]] Vec2 get_center() const {
        // Get the center point of the rectangle
        return position + size / 2;
    }

    [[nodiscard]] bool contains(const Vec2 &point) const {
        // Check if a point is inside the rectangle
        return point.x >= position.x && point.x < position.x + size.x &&
               point.y >= position.y && point.y < position.y + size.y;
    }
    [[nodiscard]] bool contains(const Rect &other) const {
        // Check if this rectangle contains another rectangle
        return contains(other.position) &&
               contains(other.get_right_top()) &&
               contains(other.get_left_bottom()) &&
               contains(other.get_right_bottom());
    }
    [[nodiscard]] bool intersects(const Rect &other) const {
        return !(position.x + size.x <= other.position.x ||
                 other.position.x + other.size.x <= position.x ||
                 position.y + size.y <= other.position.y ||
                 other.position.y + other.size.y <= position.y);
    }
};
