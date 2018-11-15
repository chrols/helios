#include "catch.hpp"

#include "ray.hpp"
#include "sphere.hpp"
#include <cmath>

TEST_CASE("RayIntersectsSphereAtTwoPoints", "[Spheres]") {
    Ray r(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s;
    auto xs = s.intersect(r);
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].t == 4);
    REQUIRE(xs[1].t == 6);
    REQUIRE(xs[0].object == &s);
    REQUIRE(xs[1].object == &s);
}

TEST_CASE("SphereDefaultTransformation", "[Spheres]") {
    Sphere s;
    REQUIRE(s.transform == Matrix::identity(4));
}

TEST_CASE("ChangeSphereTransformation", "[Spheres]") {
    Sphere s;
}

TEST_CASE("IntersectingScaledSphereWithRay", "[Spheres]") {
    Ray r(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s;
    s.scale(2, 2, 2);
    auto xs = s.intersect(r);
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].t == 3);
    REQUIRE(xs[1].t == 7);
}

TEST_CASE("IntersectingTranslatedSphereWithRay", "[Spheres]") {
    Ray r(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s;
    s.scale(5, 0, 0);
    auto xs = s.intersect(r);
    REQUIRE(xs.size() == 0);
}

TEST_CASE("NormalOnSphereX", "[Spheres]") {
    Sphere s;
    auto n = s.normal(Point(1, 0, 0));
    REQUIRE(*n == Vector(1, 0, 0));
}

TEST_CASE("NormalOnSphereY", "[Spheres]") {
    Sphere s;
    auto n = s.normal(Point(0, 1, 0));
    REQUIRE(*n == Vector(0, 1, 0));
}

TEST_CASE("NormalOnSphereZ", "[Spheres]") {
    Sphere s;
    auto n = s.normal(Point(0, 0, 1));
    REQUIRE(*n == Vector(0, 0, 1));
}

TEST_CASE("NormalOnSphereNonAxial", "[Spheres]") {
    Sphere s;
    double v = std::sqrt(3) / 3;
    auto n = s.normal(Point(v, v, v));
    REQUIRE(*n == Vector(v, v, v));
}

TEST_CASE("NormalIsNormalized", "[Spheres]") {
    Sphere s;
    double v = std::sqrt(3) / 3;
    auto n = s.normal(Point(v, v, v));
    REQUIRE(n);
    REQUIRE(*n == n->normalize());
}

TEST_CASE("NormalOnTranslatedSphere", "[Spheres]") {
    Sphere s;
    s.move(0, 1, 0);
    auto n = s.normal(Point(0, 1.70711, -0.70711));
    REQUIRE(*n == Vector(0, 0.70711, -0.70711));
}

TEST_CASE("NormalOnScaledSphere", "[Spheres]") {
    Sphere s;
    s.scale(1, 0.5, 1);
    auto n = s.normal(Point(0, std::sqrt(2) / 2, -std::sqrt(2) / 2));
    REQUIRE(*n == Vector(0, 0.970143, -.24254));
}

TEST_CASE("SphereHasDefaultMaterial", "[Spheres]") {
    Sphere s;
    auto m = s.material;
    REQUIRE(m == Material());
}

TEST_CASE("SphereMayBeAssignedMaterial", "[Spheres]") {
    Sphere s;
    Material m;
    m.ambient = 1;
    s.material = m;
    REQUIRE(s.material == m);
}
