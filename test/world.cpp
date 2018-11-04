#include <gtest/gtest.h>

#include "world.hpp"

TEST(DISABLED_World, IntersectWorldWithRay) {
    World world = World::testWorld();
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto xs = world.intersect(ray);
    ASSERT_EQ(xs.size(), 4);
    ASSERT_EQ(xs[0].t, 4);
    ASSERT_EQ(xs[1].t, 4.5);
    ASSERT_EQ(xs[2].t, 5.5);
    ASSERT_EQ(xs[3].t, 6);
}

TEST(World, ReflectedColorForNonReflectiveMaterial) {
    World world;
    Ray ray(Point(0, 0, 0), Vector(0, 0, 1));
    Sphere sphere;
    sphere.material.ambient = 1;
    Intersection hit(1, &sphere);
    hit.precompute(ray);
    auto color = world.reflectedColor(hit);
    ASSERT_EQ(color, Color::Black);
}
