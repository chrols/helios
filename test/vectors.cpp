#include <gtest/gtest.h>

#include "../tuple.hpp"
#include <cmath>

TEST(Vectors, ReflectingVectorApproachingAt45Deg) {
    auto v = Vector(1, -1, 0);
    auto n = Vector(0, 1, 0);
    auto r = v.reflect(n);
    ASSERT_TRUE(r == Vector(1, 1, 0));
}

TEST(Vectors, ReflectingVectorOffSlantedSurface) {
    double d = std::sqrt(2) / 2;
    auto v = Vector(0, -1, 0);
    auto n = Vector(d, d, 0);
    auto r = v.reflect(n);
    ASSERT_TRUE(r == Vector(1, 0, 0));
}
