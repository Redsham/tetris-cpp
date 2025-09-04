#pragma once

struct Vec2 {
    // --- Variables ---

    int x, y; // Components

    // --- Constructors ---

    constexpr          Vec2() : x(0), y(0) {}                                 // Default constructor initializes to (0, 0)
    explicit constexpr Vec2(const int x, const int y) : x(x), y(y) {} // Constructor with default values

    // --- Static constant vectors ---

    static const Vec2 zero;  // Static constant for zero vector
    static const Vec2 one;   // Static constant for one vector
    static const Vec2 up;    // Static constant for up vector
    static const Vec2 down;  // Static constant for down vector
    static const Vec2 left;  // Static constant for left vector
    static const Vec2 right; // Static constant for right vector

    // --- Operator overloads ---

    Vec2 operator+(const Vec2 &other) const { return Vec2(x + other.x, y + other.y); } // Addition operator
    Vec2 operator-(const Vec2 &other) const { return Vec2(x - other.x, y - other.y); } // Subtraction operator
    Vec2 operator*(const Vec2 &other) const { return Vec2(x * other.x, y * other.y); } // Component-wise multiplication
    Vec2 operator/(const Vec2 &other) const { return Vec2(x / other.x, y / other.y); } // Component-wise division

    Vec2 operator*(const int scalar) const { return Vec2(x * scalar, y * scalar); } // Scalar multiplication
    Vec2 operator/(const int scalar) const { return Vec2(x / scalar, y / scalar); } // Scalar division

    bool operator==(const Vec2 &other) const { return x == other.x && y == other.y; } // Equality operator
    bool operator!=(const Vec2 &other) const { return x != other.x || y != other.y; } // Inequality operator

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

// --- Static constant definitions ---
inline const Vec2 Vec2::zero  = Vec2(0, 0);
inline const Vec2 Vec2::one   = Vec2(1, 1);
inline const Vec2 Vec2::up    = Vec2(0, -1);
inline const Vec2 Vec2::down  = Vec2(0, 1);
inline const Vec2 Vec2::left  = Vec2(-1, 0);
inline const Vec2 Vec2::right = Vec2(1, 0);