#include <gtest/gtest.h>
#include "vec2.h"

// --- Basic Vector Operations ---

TEST(vector, Addition) {
    const Vec2 a{2, 3};
    const Vec2 b{4, 1};
    const Vec2 result = a + b;

    EXPECT_EQ(result.x, 6);
    EXPECT_EQ(result.y, 4);
}

TEST(vector, Subtraction) {
    const Vec2 a{5, 7};
    const Vec2 b{3, 2};
    const Vec2 result = a - b;

    EXPECT_EQ(result.x, 2);
    EXPECT_EQ(result.y, 5);
}

TEST(vector, Multiplication) {
    const Vec2 a{3, 4};
    const Vec2 b{2, 5};
    const Vec2 result = a * b;

    EXPECT_EQ(result.x, 6);
    EXPECT_EQ(result.y, 20);
}

TEST(vector, Division) {
    const Vec2 a{8, 12};
    const Vec2 b{2, 3};
    const Vec2 result = a / b;

    EXPECT_EQ(result.x, 4);
    EXPECT_EQ(result.y, 4);
}

// --- Scalar Operations ---

TEST(vector, ScalarMultiplication) {
    const Vec2    a{3, 4};
    constexpr int SCALAR = 2;
    const Vec2    result = a * SCALAR;

    EXPECT_EQ(result.x, 6);
    EXPECT_EQ(result.y, 8);
}

TEST(vector, ScalarDivision) {
    const Vec2    a{10, 20};
    constexpr int SCALAR = 2;
    const Vec2    result = a / SCALAR;

    EXPECT_EQ(result.x, 5);
    EXPECT_EQ(result.y, 10);
}

// --- Equality and Inequality ---

TEST(vector, Equality) {
    const Vec2 a{3, 4};
    const Vec2 b{3, 4};
    const Vec2 c{5, 6};

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST(vector, Inequality) {
    const Vec2 a{3, 4};
    const Vec2 b{3, 4};
    const Vec2 c{5, 6};

    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
}

// --- Assignment Operators ---

TEST(vector, AdditionAssignment) {
    Vec2       a{1, 2};
    const Vec2 b{3, 4};
    a += b;

    EXPECT_EQ(a.x, 4);
    EXPECT_EQ(a.y, 6);
}

TEST(vector, SubtractionAssignment) {
    Vec2       a{5, 7};
    const Vec2 b{2, 3};
    a -= b;

    EXPECT_EQ(a.x, 3);
    EXPECT_EQ(a.y, 4);
}

TEST(vector, MultiplicationAssignment) {
    Vec2       a{2, 3};
    const Vec2 b{4, 5};
    a *= b;

    EXPECT_EQ(a.x, 8);
    EXPECT_EQ(a.y, 15);
}

TEST(vector, DivisionAssignment) {
    Vec2       a{10, 15};
    const Vec2 b{2, 3};
    a /= b;

    EXPECT_EQ(a.x, 5);
    EXPECT_EQ(a.y, 5);
}

TEST(vector, ScalarMultiplicationAssignment) {
    Vec2          a{2, 3};
    constexpr int SCALAR = 4;
    a *= SCALAR;

    EXPECT_EQ(a.x, 8);
    EXPECT_EQ(a.y, 12);
}

TEST(vector, ScalarDivisionAssignment) {
    Vec2          a{8, 12};
    constexpr int SCALAR = 4;
    a /= SCALAR;

    EXPECT_EQ(a.x, 2);
    EXPECT_EQ(a.y, 3);
}
