#include <gtest/gtest.h>

#include "pattern.hpp"
#include "sphere.hpp"

TEST(Patterns, StripePatternConstantInY) {
    StripePattern pattern(Color(1, 1, 1), Color(0, 0, 0));
    ASSERT_TRUE(pattern.patternAt(Point(0, 0, 0)) == Color(1, 1, 1));
    ASSERT_TRUE(pattern.patternAt(Point(0, 1, 0)) == Color(1, 1, 1));
    ASSERT_TRUE(pattern.patternAt(Point(0, 2, 0)) == Color(1, 1, 1));
}

TEST(Patterns, StripePatternConstantInZ) {
    StripePattern pattern(Color(1, 1, 1), Color(0, 0, 0));
    ASSERT_TRUE(pattern.patternAt(Point(0, 0, 0)) == Color(1, 1, 1));
    ASSERT_TRUE(pattern.patternAt(Point(0, 0, 1)) == Color(1, 1, 1));
    ASSERT_TRUE(pattern.patternAt(Point(0, 0, 2)) == Color(1, 1, 1));
}

TEST(Patterns, StripePatternAlternatesInX) {
    Color a(1, 1, 1);
    Color b(0, 0, 0);
    StripePattern pattern(a, b);
    ASSERT_TRUE(pattern.patternAt(Point(0, 0, 0)) == a);
    ASSERT_TRUE(pattern.patternAt(Point(0.9, 0, 0)) == a);
    ASSERT_TRUE(pattern.patternAt(Point(1, 0, 0)) == b);
    ASSERT_TRUE(pattern.patternAt(Point(-0.1, 0, 0)) == b);
    ASSERT_TRUE(pattern.patternAt(Point(-1, 0, 0)) == b);
    ASSERT_TRUE(pattern.patternAt(Point(-1.1, 0, 0)) == a);
}

TEST(Patterns, DefaultPatternTransformation) {
    TestPattern p;
    ASSERT_TRUE(p.transform == Matrix<double>::identity(4));
}

TEST(Patterns, AssigningTransformation) {
    TestPattern pattern;
    pattern.transform = Matrix<double>::translationMatrix(1, 2, 3);
    ASSERT_EQ(pattern.transform, Matrix<double>::translationMatrix(1, 2, 3));
}

TEST(Patterns, PatternWithObjectTransformation) {
    Sphere s;
    TestPattern pattern;
    s.transform = Matrix<double>::scalingMatrix(2, 2, 2);
    auto c = pattern.patternAtObject(Point(2, 3, 4), s);
    ASSERT_EQ(c, Color(1, 1.5, 2));
}

TEST(Patterns, PatternWithPatternTransformation) {
    Sphere s;
    TestPattern pattern;
    pattern.transform = Matrix<double>::scalingMatrix(2, 2, 2);
    auto c = pattern.patternAtObject(Point(2, 3, 4), s);
    ASSERT_EQ(c, Color(1, 1.5, 2));
}

TEST(Patterns, PatternWithBothObjectAndPatternTransformation) {
    Sphere s;
    TestPattern pattern;
    s.transform = Matrix<double>::scalingMatrix(2, 2, 2);
    pattern.transform = Matrix<double>::translationMatrix(0.5, 1, 1.5);
    auto c = pattern.patternAtObject(Point(2.5, 3, 3.5), s);
    ASSERT_EQ(c, Color(0.75, 0.5, 0.25));
}
