#include <gtest/gtest.h>
#include "rect.h"

// --- Initialization Tests ---

TEST(rect, DefaultConstructor) {
    const Rect rect;
    EXPECT_EQ(rect.position.x, 0);
    EXPECT_EQ(rect.position.y, 0);
    EXPECT_EQ(rect.size.x, 0);
    EXPECT_EQ(rect.size.y, 0);
}

TEST(rect, ParameterizedConstructor) {
    const Rect rect(Vec2(1, 2), Vec2(3, 4));
    EXPECT_EQ(rect.position.x, 1);
    EXPECT_EQ(rect.position.y, 2);
    EXPECT_EQ(rect.size.x, 3);
    EXPECT_EQ(rect.size.y, 4);
}

TEST(rect, ConstructorWithIntegers) {
    const Rect rect(1, 2, 3, 4);
    EXPECT_EQ(rect.position.x, 1);
    EXPECT_EQ(rect.position.y, 2);
    EXPECT_EQ(rect.size.x, 3);
    EXPECT_EQ(rect.size.y, 4);
}

TEST(rect, ConstructorFromPoints) {
    const Rect rect = Rect::from_points(Vec2(1, 2), Vec2(4, 5));
    EXPECT_EQ(rect.position.x, 1);
    EXPECT_EQ(rect.position.y, 2);
    EXPECT_EQ(rect.size.x, 3);
    EXPECT_EQ(rect.size.y, 3);
}

// --- Getters Tests ---

TEST(rect, GetLeftTop) {
    const Rect rect(Vec2(1, 2), Vec2(3, 4));
    const Vec2 left_top = rect.get_left_top();
    EXPECT_EQ(left_top.x, 1);
    EXPECT_EQ(left_top.y, 2);
}

TEST(rect, GetRightTop) {
    const Rect rect(Vec2(1, 2), Vec2(3, 4));
    const Vec2 right_top = rect.get_right_top();
    EXPECT_EQ(right_top.x, 4);
    EXPECT_EQ(right_top.y, 2);
}

TEST(rect, GetLeftBottom) {
    const Rect rect(Vec2(1, 2), Vec2(3, 4));
    const Vec2 left_bottom = rect.get_left_bottom();
    EXPECT_EQ(left_bottom.x, 1);
    EXPECT_EQ(left_bottom.y, 6);
}

TEST(rect, GetRightBottom) {
    const Rect rect(Vec2(1, 2), Vec2(3, 4));
    const Vec2 right_bottom = rect.get_right_bottom();
    EXPECT_EQ(right_bottom.x, 4);
    EXPECT_EQ(right_bottom.y, 6);
}

TEST(rect, GetCenter) {
    const Rect rect(Vec2(1, 2), Vec2(3, 4));
    const Vec2 center = rect.get_center();
    EXPECT_EQ(center.x, 2);
    EXPECT_EQ(center.y, 4);
}

// --- Contains Tests ---

TEST(rect, ContainsPointInside) {
    const Rect rect(Vec2(1, 2), Vec2(3, 4));
    EXPECT_TRUE(rect.contains(Vec2(2, 3)));
}

TEST(rect, ContainsPointOnEdge) {
    const Rect rect(Vec2(1, 2), Vec2(3, 4));
    EXPECT_TRUE(rect.contains(Vec2(1, 2))); // Top-left corner
    EXPECT_TRUE(rect.contains(Vec2(3, 2))); // Top-right corner
    EXPECT_TRUE(rect.contains(Vec2(1, 5))); // Bottom-left corner
    EXPECT_TRUE(rect.contains(Vec2(3, 5))); // Bottom-right corner
}

TEST(rect, DoesNotContainPointOutside) {
    const Rect rect(Vec2(1, 2), Vec2(3, 4));
    EXPECT_FALSE(rect.contains(Vec2(0, 0))); // Outside
    EXPECT_FALSE(rect.contains(Vec2(5, 5))); // Outside
}

TEST(rect, DoesNotContainPointOnEdgeOutside) {
    const Rect rect(Vec2(1, 2), Vec2(3, 4));
    EXPECT_FALSE(rect.contains(Vec2(0, 2))); // Left edge outside
    EXPECT_FALSE(rect.contains(Vec2(5, 2))); // Right edge outside
    EXPECT_FALSE(rect.contains(Vec2(1, 1))); // Top edge outside
    EXPECT_FALSE(rect.contains(Vec2(1, 7))); // Bottom edge outside
}

// --- Intersects Tests ---

TEST(rect, IntersectsWithAnotherRect) {
    const Rect rect1(Vec2(1, 2), Vec2(3, 4));
    const Rect rect2(Vec2(2, 3), Vec2(3, 4));
    EXPECT_TRUE(rect1.intersects(rect2));
}

TEST(rect, DoesNotIntersectWithAnotherRect) {
    const Rect rect1(Vec2(1, 2), Vec2(3, 4));
    const Rect rect2(Vec2(5, 6), Vec2(3, 4));
    EXPECT_FALSE(rect1.intersects(rect2));
}

TEST(rect, IntersectsWithEdgeTouching) {
    const Rect rect1(Vec2(1, 2), Vec2(3, 4));
    const Rect rect2(Vec2(3, 2), Vec2(3, 4)); // Touching at the right edge
    EXPECT_TRUE(rect1.intersects(rect2));
}

TEST(rect, IntersectsWithCornerTouching) {
    const Rect rect1(Vec2(1, 2), Vec2(3, 4));
    const Rect rect2(Vec2(3, 4), Vec2(3, 4)); // Touching at the bottom-right corner
    EXPECT_TRUE(rect1.intersects(rect2));
}

TEST(rect, DoesNotIntersectWithEdgeOutside) {
    const Rect rect1(Vec2(1, 2), Vec2(3, 4));
    const Rect rect2(Vec2(0, 2), Vec2(1, 3)); // Left edge outside
    EXPECT_FALSE(rect1.intersects(rect2));
}

TEST(rect, DoesNotIntersectWithCornerOutside) {
    const Rect rect1(Vec2(1, 2), Vec2(3, 4));
    const Rect rect2(Vec2(0, 0), Vec2(1, 1)); // Top-left corner outside
    EXPECT_FALSE(rect1.intersects(rect2));
}