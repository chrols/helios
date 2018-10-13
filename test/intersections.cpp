#include <gtest/gtest.h>

#include "../intersection.hpp"
#include "../sphere.hpp"

TEST(Intersections, HitWhenAllIntersectionHavePositiveT) {
    Sphere s;
    Intersection i1(1, &s);
    Intersection i2(1, &s);
    std::vector<Intersection> xs = {i1, i2};
    auto h = Intersection::hit(xs);
    ASSERT_TRUE(h);
    ASSERT_TRUE(*h == i1);
}

TEST(Intersections, HitWhenSomeIntersectionHaveNegativeT) {
    Sphere s;
    Intersection i1(-1, &s);
    Intersection i2(1, &s);
    std::vector<Intersection> xs = {i1, i2};
    auto h = Intersection::hit(xs);
    ASSERT_TRUE(h);
    ASSERT_TRUE(*h == i2);
}

TEST(Intersections, HitWhenAllIntersectionHaveNegativeT) {
    Sphere s;
    Intersection i1(-1, &s);
    Intersection i2(-2, &s);
    std::vector<Intersection> xs = {i1, i2};
    auto h = Intersection::hit(xs);
    ASSERT_FALSE(h);
}

TEST(Intersections, TheHitIsAlwaysTheLowestNonNegativeIntersection) {
    Sphere s;
    Intersection i1(5, &s);
    Intersection i2(7, &s);
    Intersection i3(-3, &s);
    Intersection i4(2, &s);

    std::vector<Intersection> xs = {i1, i2, i3, i4};
    auto h = Intersection::hit(xs);
    ASSERT_TRUE(*h == i4);
}
