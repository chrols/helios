#include "catch.hpp"

#include "cylinder.hpp"

TEST_CASE("A ray misses a cylinder", "[Cylinders]") {
    Cylinder c;

    auto xs = c.localIntersect(Ray(Point(1, 0, 0), Vector(0, 1, 0)));
    REQUIRE(xs.size() == 0);

    xs = c.localIntersect(Ray(Point(0, 0, 0), Vector(0, 1, 0)));
    REQUIRE(xs.size() == 0);

    xs = c.localIntersect(Ray(Point(0, 0, -5), Vector(1, 1, 1)));
    REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray strikes a cylinder", "[Cylinders]") {
    Cylinder c;

    auto xs = c.localIntersect(Ray(Point(1, 0, -5), Vector(0, 0, 1)));
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].t == 5);
    REQUIRE(xs[1].t == 5);

    xs = c.localIntersect(Ray(Point(0, 0, -5), Vector(0, 0, 1)));
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].t == 4);
    REQUIRE(xs[1].t == 6);

    xs =
        c.localIntersect(Ray(Point(0.5, 0, -5), Vector(0.1, 1, 1).normalize()));
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].t == Approx(6.80798));
    REQUIRE(xs[1].t == Approx(7.08872));
}
