#include <gtest/gtest.h>

#include "matrix.hpp"
#include "ray.hpp"

TEST(Rays, ComputingPointFromDistance) {
    Ray ray(Point(2, 3, 4), Vector(1, 0, 0));
    ASSERT_TRUE(Point(2, 3, 4) == ray.position(0));
    ASSERT_TRUE(Point(4.5, 3, 4) == ray.position(2.5));
}

TEST(Rays, TranslatingRay) {
    Ray r(Point(1, 2, 3), Vector(0, 1, 0));
    auto m = Matrix<double>::translationMatrix(3, 4, 5);
    auto r2 = r.transform(m);
    ASSERT_TRUE(r2.origin == Point(4, 6, 8));
    ASSERT_TRUE(r2.direction == Vector(0, 1, 0));
}

TEST(Rays, ScalingRay) {
    Ray r(Point(1, 2, 3), Vector(0, 1, 0));
    auto m = Matrix<double>::scalingMatrix(2, 3, 4);
    auto r2 = r.transform(m);
    ASSERT_TRUE(r2.origin == Point(2, 6, 12));
    ASSERT_TRUE(r2.direction == Vector(0, 3, 0));
}
