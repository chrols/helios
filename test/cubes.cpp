#include "catch.hpp"

#include "cube.hpp"

TEST_CASE("A ray intesects a cube", "[Cubes]") {
    Cube c;
    std::vector<Intersection> xs;

    // +x
    xs = c.localIntersect(Ray(Point(5, 0.5, 0), Vector(-1, 0, 0)));
    REQUIRE(xs[0].t == 4);
    REQUIRE(xs[1].t == 6);

    // -x
    xs = c.localIntersect(Ray(Point(-5, 0.5, 0), Vector(1, 0, 0)));
    REQUIRE(xs[0].t == 4);
    REQUIRE(xs[1].t == 6);

    // +y
    xs = c.localIntersect(Ray(Point(0.5, 5, 0), Vector(0, -1, 0)));
    REQUIRE(xs[0].t == 4);
    REQUIRE(xs[1].t == 6);

    // -y
    xs = c.localIntersect(Ray(Point(0.5, -5, 0), Vector(0, 1, 0)));
    REQUIRE(xs[0].t == 4);
    REQUIRE(xs[1].t == 6);

    // +z
    xs = c.localIntersect(Ray(Point(0.5, 0, 5), Vector(0, 0, -1)));
    REQUIRE(xs[0].t == 4);
    REQUIRE(xs[1].t == 6);

    // -z
    xs = c.localIntersect(Ray(Point(0.5, 0, -5), Vector(0, 0, 1)));
    REQUIRE(xs[0].t == 4);
    REQUIRE(xs[1].t == 6);

    // Inside
    xs = c.localIntersect(Ray(Point(0, 0.5, 0), Vector(0, 0, 1)));
    REQUIRE(xs[0].t == -1);
    REQUIRE(xs[1].t == 1);
}

TEST_CASE("A ray misses a cube", "[Cubes]") {
    Cube c;
    std::vector<Intersection> xs;

    xs = c.localIntersect(Ray(Point(-2, 0, 0), Vector(0.2673, 0.5345, 0.8018)));
    REQUIRE(xs.size() == 0);

    xs = c.localIntersect(Ray(Point(0, -2, 0), Vector(0.8018, 0.2673, 0.5345)));
    REQUIRE(xs.size() == 0);

    xs = c.localIntersect(Ray(Point(0, 0, -2), Vector(0.5345, 0.8018, 0.2673)));
    REQUIRE(xs.size() == 0);

    xs = c.localIntersect(Ray(Point(2, 0, 2), Vector(0, 0, -1)));
    REQUIRE(xs.size() == 0);

    xs = c.localIntersect(Ray(Point(0, 2, 2), Vector(0, -1, 0)));
    REQUIRE(xs.size() == 0);

    xs = c.localIntersect(Ray(Point(2, 2, 0), Vector(-1, 0, 0)));
    REQUIRE(xs.size() == 0);
}

TEST_CASE("The normal on the surface of a cube", "[Cubes]") {
    Cube c;
    REQUIRE(c.localNormal(Point(1, 0.5, -0.8)) == Vector(1, 0, 0));
    REQUIRE(c.localNormal(Point(-1, -0.2, 0.9)) == Vector(-1, 0, 0));
    REQUIRE(c.localNormal(Point(-0.4, 1, -0.1)) == Vector(0, 1, 0));
    REQUIRE(c.localNormal(Point(0.3, -1, -0.7)) == Vector(0, -1, 0));
    REQUIRE(c.localNormal(Point(-0.6, 0.3, 1)) == Vector(0, 0, 1));
    REQUIRE(c.localNormal(Point(0.4, 0.4, -1)) == Vector(0, 0, -1));
    REQUIRE(c.localNormal(Point(1, 1, 1)) == Vector(1, 0, 0));
    REQUIRE(c.localNormal(Point(-1, -1, -1)) == Vector(-1, 0, 0));
}
