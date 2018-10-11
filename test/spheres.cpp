#include <gtest/gtest.h>

#include "../ray.hpp"
#include "../sphere.hpp"

TEST(Spheres, RayIntersectsSphereAtTwoPoints) {
    Ray r(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s;
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0].t, 4);
    ASSERT_EQ(xs[1].t, 6);
    ASSERT_EQ(xs[0].object, &s);
    ASSERT_EQ(xs[1].object, &s);
}
