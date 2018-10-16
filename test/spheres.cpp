#include <gtest/gtest.h>

#include "ray.hpp"
#include "sphere.hpp"
#include <cmath>

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

TEST(Spheres, NormalOnSphereX) {
    Sphere s;
    auto n = s.normal(Point(1, 0, 0));
    ASSERT_TRUE(*n == Vector(1, 0, 0));
}

TEST(Spheres, NormalOnSphereY) {
    Sphere s;
    auto n = s.normal(Point(0, 1, 0));
    ASSERT_TRUE(*n == Vector(0, 1, 0));
}

TEST(Spheres, NormalOnSphereZ) {
    Sphere s;
    auto n = s.normal(Point(0, 0, 1));
    ASSERT_TRUE(*n == Vector(0, 0, 1));
}

TEST(Spheres, NormalOnSphereNonAxial) {
    Sphere s;
    double v = std::sqrt(3) / 3;
    auto n = s.normal(Point(v, v, v));
    ASSERT_TRUE(*n == Vector(v, v, v));
}

TEST(Spheres, NormalIsNormalized) {
    Sphere s;
    double v = std::sqrt(3) / 3;
    auto n = s.normal(Point(v, v, v));
    ASSERT_TRUE(n);
    ASSERT_TRUE(*n == n->normalize());
}

TEST(Spheres, NormalOnTranslatedSphere) {
    Sphere s;
    s.setTransform(Matrix<double>::translationMatrix(0, 1, 0));
    auto n = s.normal(Point(0, 1.70711, -0.70711));
    ASSERT_TRUE(*n == Vector(0, 0.70711, -0.70711));
}

TEST(Spheres, NormalOnScaledSphere) {
    Sphere s;
    s.setTransform(Matrix<double>::scalingMatrix(1, 0.5, 1));
    auto n = s.normal(Point(0, std::sqrt(2) / 2, -std::sqrt(2) / 2));
    ASSERT_TRUE(*n == Vector(0, 0.970143, -.24254));
}

TEST(Spheres, SphereHasDefaultMaterial) {
    Sphere s;
    auto m = s.material;
    ASSERT_EQ(m, Material());
}

TEST(Spheres, SphereMayBeAssignedMaterial) {
    Sphere s;
    Material m;
    m.ambient = 1;
    s.material = m;
    ASSERT_EQ(s.material, m);
}
