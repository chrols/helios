#include "catch.hpp"

#include "pattern.hpp"
#include "sphere.hpp"

TEST_CASE("StripePatternConstantInY", "[Patterns]") {
    StripePattern pattern(Color::White, Color::White);
    REQUIRE(pattern.patternAt(Point(0, 0, 0)) == Color::White);
    REQUIRE(pattern.patternAt(Point(0, 1, 0)) == Color::White);
    REQUIRE(pattern.patternAt(Point(0, 2, 0)) == Color::White);
}

TEST_CASE("StripePatternConstantInZ", "[Patterns]") {
    StripePattern pattern(Color::White, Color::White);
    REQUIRE(pattern.patternAt(Point(0, 0, 0)) == Color::White);
    REQUIRE(pattern.patternAt(Point(0, 0, 1)) == Color::White);
    REQUIRE(pattern.patternAt(Point(0, 0, 2)) == Color::White);
}

TEST_CASE("StripePatternAlternatesInX", "[Patterns]") {
    Color a(1, 1, 1);
    Color b(0, 0, 0);
    StripePattern pattern(a, b);
    REQUIRE(pattern.patternAt(Point(0, 0, 0)) == a);
    REQUIRE(pattern.patternAt(Point(0.9, 0, 0)) == a);
    REQUIRE(pattern.patternAt(Point(1, 0, 0)) == b);
    REQUIRE(pattern.patternAt(Point(-0.1, 0, 0)) == b);
    REQUIRE(pattern.patternAt(Point(-1, 0, 0)) == b);
    REQUIRE(pattern.patternAt(Point(-1.1, 0, 0)) == a);
}

TEST_CASE("DefaultPatternTransformation", "[Patterns]") {
    TestPattern p;
    REQUIRE(p.transform == Matrix::identity(4));
}

TEST_CASE("AssigningTransformation", "[Patterns]") {
    TestPattern pattern;
    pattern.transform = Matrix::translationMatrix(1, 2, 3);
    REQUIRE(pattern.transform == Matrix::translationMatrix(1, 2, 3));
}

TEST_CASE("PatternWithObjectTransformation", "[Patterns]") {
    Sphere s;
    TestPattern pattern;
    s.setTransform(Matrix::scalingMatrix(2, 2, 2));
    auto c = pattern.patternAtObject(Point(2, 3, 4), s);
    REQUIRE(c == Color(1, 1.5, 2));
}

TEST_CASE("PatternWithPatternTransformation", "[Patterns]") {
    Sphere s;
    TestPattern pattern;
    pattern.transform = Matrix::scalingMatrix(2, 2, 2);
    auto c = pattern.patternAtObject(Point(2, 3, 4), s);
    REQUIRE(c == Color(1, 1.5, 2));
}

TEST_CASE("PatternWithBothObjectAndPatternTransformation", "[Patterns]") {
    Sphere s;
    TestPattern pattern;
    s.setTransform(Matrix::scalingMatrix(2, 2, 2));
    pattern.transform = Matrix::translationMatrix(0.5, 1, 1.5);
    auto c = pattern.patternAtObject(Point(2.5, 3, 3.5), s);
    REQUIRE(c == Color(0.75, 0.5, 0.25));
}

TEST_CASE("GradientLinearlyInterpolatesBetweenColors", "[Patterns]") {
    GradientPattern pattern(Color::Black, Color::White);
    REQUIRE(pattern.patternAt(Point(0, 0, 0)) == Color::Black);
    REQUIRE(pattern.patternAt(Point(0.25, 0, 0)) == Color(0.25, 0.25, 0.25));
    REQUIRE(pattern.patternAt(Point(0.5, 0, 0)) == Color(0.5, 0.5, 0.5));
    REQUIRE(pattern.patternAt(Point(0.75, 0, 0)) == Color(0.75, 0.75, 0.75));
}

TEST_CASE("CheckersSholdRepeatInX", "[Pattern]") {
    CheckersPattern pattern(Color::Black, Color::White);
    REQUIRE(pattern.patternAt(Point(0, 0, 0)) == Color::Black);
    REQUIRE(pattern.patternAt(Point(0.99, 0, 0)) == Color::Black);
    REQUIRE(pattern.patternAt(Point(1.01, 0, 0)) == Color::White);
}

TEST_CASE("CheckersSholdRepeatInY", "[Pattern]") {
    CheckersPattern pattern(Color::Black, Color::White);
    REQUIRE(pattern.patternAt(Point(0, 0, 0)) == Color::Black);
    REQUIRE(pattern.patternAt(Point(0, 0.99, 0)) == Color::Black);
    REQUIRE(pattern.patternAt(Point(0, 1.01, 0)) == Color::White);
}

TEST_CASE("CheckersSholdRepeatInZ", "[Pattern]") {
    CheckersPattern pattern(Color::Black, Color::White);
    REQUIRE(pattern.patternAt(Point(0, 0, 0)) == Color::Black);
    REQUIRE(pattern.patternAt(Point(0, 0, 0.99)) == Color::Black);
    REQUIRE(pattern.patternAt(Point(0, 0, 1.01)) == Color::White);
}
