#include <gtest/gtest.h>

#include "../ray.hpp"

TEST(Rays, ComputingPointFromDistance) {
    Ray ray(Point(2, 3, 4), Vector(1, 0, 0));
    ASSERT_TRUE(Point(2, 3, 4) == ray.position(0));
    ASSERT_TRUE(Point(4.5, 3, 4) == ray.position(2.5));
}
