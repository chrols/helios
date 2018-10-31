#include <gtest/gtest.h>

#include "pattern.hpp"

TEST(Patterns, StripePatternConstantInY) {
    StripePattern pattern(Color(1, 1, 1), Color(0, 0, 0));
    ASSERT_TRUE(pattern.stripeAt(Point(0, 0, 0)) == Color(1, 1, 1));
    ASSERT_TRUE(pattern.stripeAt(Point(0, 1, 0)) == Color(1, 1, 1));
    ASSERT_TRUE(pattern.stripeAt(Point(0, 2, 0)) == Color(1, 1, 1));
}

TEST(Patterns, StripePatternConstantInZ) {
    StripePattern pattern(Color(1, 1, 1), Color(0, 0, 0));
    ASSERT_TRUE(pattern.stripeAt(Point(0, 0, 0)) == Color(1, 1, 1));
    ASSERT_TRUE(pattern.stripeAt(Point(0, 0, 1)) == Color(1, 1, 1));
    ASSERT_TRUE(pattern.stripeAt(Point(0, 0, 2)) == Color(1, 1, 1));
}

TEST(Patterns, StripePatternAlternatesInX) {
    Color a(1, 1, 1);
    Color b(0, 0, 0);
    StripePattern pattern(a, b);
    ASSERT_TRUE(pattern.stripeAt(Point(0, 0, 0)) == a);
    ASSERT_TRUE(pattern.stripeAt(Point(0.9, 0, 0)) == a);
    ASSERT_TRUE(pattern.stripeAt(Point(1, 0, 0)) == b);
    ASSERT_TRUE(pattern.stripeAt(Point(-0.1, 0, 0)) == b);
    ASSERT_TRUE(pattern.stripeAt(Point(-1, 0, 0)) == b);
    ASSERT_TRUE(pattern.stripeAt(Point(-1.1, 0, 0)) == a);
}
