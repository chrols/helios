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

TEST(Spheres, SphereDefaultTransformation) {
    Sphere s;
    ASSERT_EQ(s.transform, Matrix<double>::identity(4));
}

TEST(Spheres, ChangeSphereTransformation) {
    Sphere s;
    auto t = Matrix<double>::translationMatrix(2, 3, 4);
    s.setTransform(t);
    s.transform = t;
}

TEST(Spheres, IntersectingScaledSphereWithRay) {
    Ray r(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s;
    s.setTransform(Matrix<double>::scalingMatrix(2, 2, 2));
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0].t, 3);
    ASSERT_EQ(xs[1].t, 7);
}

TEST(Spheres, IntersectingTranslatedSphereWithRay) {
    Ray r(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s;
    s.setTransform(Matrix<double>::scalingMatrix(5, 0, 0));
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 0);
}
