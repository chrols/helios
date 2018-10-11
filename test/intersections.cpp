#include <gtest/gtest.h>

#include "intersection.hpp"
#include "sphere.hpp"

TEST(Intersections, HitWhenAllIntersectionHavePositiveT) {
    Sphere s;
    Intersection i1(1, &s);
    Intersection i2(1, &s);
    Intersections xs = {i1, i2};
    auto h = Intersection::hit(xs);
    ASSERT_EQ(h, i1);
}
