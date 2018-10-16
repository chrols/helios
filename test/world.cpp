#include <gtest/gtest.h>

#include "world.hpp"

TEST(World, IntersectWorldWithRay) {
    auto world = World::testWorld();
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto xs = world.intersect(ray);
    ASSERT_EQ(xs.size(), 4);
    ASSERT_EQ(xs[0].t, 4);
    ASSERT_EQ(xs[1].t, 4.5);
    ASSERT_EQ(xs[2].t, 5.5);
    ASSERT_EQ(xs[3].t, 6);
}
