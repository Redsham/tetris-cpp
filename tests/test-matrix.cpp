#include <gtest/gtest.h>

#include "board-matrix.h"

// --- Main Tests ---

TEST(matrix, Initialization) {
    constexpr int WIDTH  = 5;
    constexpr int HEIGHT = 5;

    const BoardMatrix<unsigned char> matrix(WIDTH, HEIGHT);

    EXPECT_EQ(matrix.get_width(), WIDTH);
    EXPECT_EQ(matrix.get_height(), HEIGHT);
    EXPECT_EQ(matrix.get_size(), WIDTH * HEIGHT);
    EXPECT_FALSE(matrix.is_empty());
}

TEST(matrix, Fill) {
    constexpr int           WIDTH  = 3;
    constexpr int           HEIGHT = 3;
    constexpr unsigned char VALUE  = 42;

    BoardMatrix<unsigned char> matrix(WIDTH, HEIGHT);
    matrix.fill(VALUE);

    for (int y = 0; y < HEIGHT; ++y) { for (int x = 0; x < WIDTH; ++x) { EXPECT_EQ(matrix(x, y), VALUE); } }
}

TEST(matrix, Index) {
    constexpr int              WIDTH  = 4;
    constexpr int              HEIGHT = 4;
    BoardMatrix<unsigned char> matrix(WIDTH, HEIGHT);

    for (int y = 0; y < HEIGHT; ++y) { for (int x = 0; x < WIDTH; ++x) { matrix(x, y) = static_cast<unsigned char>(x + y); } }

    for (int y = 0; y < HEIGHT; ++y) { for (int x = 0; x < WIDTH; ++x) { EXPECT_EQ(matrix.get_index(x, y), y * WIDTH + x); } }
}

TEST(matrix, Access) {
    constexpr int              WIDTH  = 4;
    constexpr int              HEIGHT = 4;
    BoardMatrix<unsigned char> matrix(WIDTH, HEIGHT);

    for (int y = 0; y < HEIGHT; ++y) { for (int x = 0; x < WIDTH; ++x) { matrix(x, y) = static_cast<unsigned char>(x + y); } }

    for (int y = 0; y < HEIGHT; ++y) { for (int x = 0; x < WIDTH; ++x) { EXPECT_EQ(matrix(x, y), static_cast<unsigned char>(x + y)); } }
}

// --- Copy and Move Tests ---

TEST(matrix, CopyConstructor) {
    BoardMatrix<unsigned char> original(2, 2);
    original(0, 0) = 1;
    original(1, 0) = 2;
    original(0, 1) = 3;
    original(1, 1) = 4;

    BoardMatrix copy(original);

    EXPECT_EQ(copy.get_width(), original.get_width());
    EXPECT_EQ(copy.get_height(), original.get_height());
    EXPECT_EQ(copy(0, 0), original(0, 0));
    EXPECT_EQ(copy(1, 0), original(1, 0));
    EXPECT_EQ(copy(0, 1), original(0, 1));
    EXPECT_EQ(copy(1, 1), original(1, 1));
}

TEST(matrix, CopyAssignment) {
    BoardMatrix<unsigned char> original(2, 2);
    original(0, 0) = 1;
    original(1, 0) = 2;
    original(0, 1) = 3;
    original(1, 1) = 4;

    BoardMatrix<unsigned char> copy = original;

    EXPECT_EQ(copy.get_width(), original.get_width());
    EXPECT_EQ(copy.get_height(), original.get_height());
    EXPECT_EQ(copy(0, 0), original(0, 0));
    EXPECT_EQ(copy(1, 0), original(1, 0));
    EXPECT_EQ(copy(0, 1), original(0, 1));
    EXPECT_EQ(copy(1, 1), original(1, 1));
}

TEST(matrix, MoveConstructor) {
    BoardMatrix<unsigned char> original(2, 2);
    original(0, 0) = 1;
    original(1, 0) = 2;
    original(0, 1) = 3;
    original(1, 1) = 4;

    BoardMatrix moved(std::move(original));

    EXPECT_EQ(moved.get_width(), 2);
    EXPECT_EQ(moved.get_height(), 2);
    EXPECT_EQ(moved(0, 0), 1);
    EXPECT_EQ(moved(1, 0), 2);
    EXPECT_EQ(moved(0, 1), 3);
    EXPECT_EQ(moved(1, 1), 4);
}

TEST(matrix, MoveAssignment) {
    BoardMatrix<unsigned char> original(2, 2);
    original(0, 0) = 1;
    original(1, 0) = 2;
    original(0, 1) = 3;
    original(1, 1) = 4;

    BoardMatrix<unsigned char> moved = std::move(original);

    EXPECT_EQ(moved.get_width(), 2);
    EXPECT_EQ(moved.get_height(), 2);
    EXPECT_EQ(moved(0, 0), 1);
    EXPECT_EQ(moved(1, 0), 2);
    EXPECT_EQ(moved(0, 1), 3);
    EXPECT_EQ(moved(1, 1), 4);
}

// --- Rotation Tests ---

TEST(matrix, ClockwiseRotation) {
    BoardMatrix<unsigned char> matrix(2, 2);
    matrix(0, 0) = 1;
    matrix(1, 0) = 2;
    matrix(0, 1) = 3;
    matrix(1, 1) = 4;

    auto rotated = matrix.rotate_clockwise();

    EXPECT_EQ(rotated(0, 0), 3);
    EXPECT_EQ(rotated(1, 0), 1);
    EXPECT_EQ(rotated(0, 1), 4);
    EXPECT_EQ(rotated(1, 1), 2);
}

TEST(matrix, CounterClockwiseRotation) {
    BoardMatrix<unsigned char> matrix(2, 2);
    matrix(0, 0) = 1;
    matrix(1, 0) = 2;
    matrix(0, 1) = 3;
    matrix(1, 1) = 4;

    auto rotated = matrix.rotate_counter_clockwise();

    EXPECT_EQ(rotated(0, 0), 2);
    EXPECT_EQ(rotated(1, 0), 4);
    EXPECT_EQ(rotated(0, 1), 1);
    EXPECT_EQ(rotated(1, 1), 3);
}
