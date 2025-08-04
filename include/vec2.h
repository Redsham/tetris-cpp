#pragma once

struct Vec2 {
    int x, y; // Components

    explicit Vec2(const int x = 0, const int y = 0) : x(x), y(y) {
    } // Constructor with default values

    Vec2 operator+(const Vec2 &other) const { return Vec2(x + other.x, y + other.y); } // Addition operator
    Vec2 operator-(const Vec2 &other) const { return Vec2(x - other.x, y - other.y); } // Subtraction operator
    Vec2 operator*(const Vec2 &other) const { return Vec2(x * other.x, y * other.y); } // Component-wise multiplication
    Vec2 operator/(const Vec2 &other) const { return Vec2(x / other.x, y / other.y); } // Component-wise division

    Vec2 operator*(const int scalar) const { return Vec2(x * scalar, y * scalar); }    // Scalar multiplication
    Vec2 operator/(const int scalar) const { return Vec2(x / scalar, y / scalar); }    // Scalar division

    bool operator==(const Vec2 &other) const { return x == other.x && y == other.y; }  // Equality operator
    bool operator!=(const Vec2 &other) const { return x != other.x || y != other.y; }  // Inequality operator

    Vec2 &operator+=(const Vec2 &other) {
        x += other.x;
        y += other.y;
        return *this;
    } // Addition assignment operator
    Vec2 &operator-=(const Vec2 &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    } // Subtraction assignment operator
    Vec2 &operator*=(const Vec2 &other) {
        x *= other.x;
        y *= other.y;
        return *this;
    } // Component-wise multiplication assignment operator
    Vec2 &operator/=(const Vec2 &other) {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    Vec2 &operator*=(const int scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    } // Scalar multiplication assignment operator
    Vec2 &operator/=(const int scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    } // Scalar division assignment operator
};
