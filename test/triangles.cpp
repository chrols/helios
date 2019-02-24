#include "catch.hpp"

#include "triangle.hpp"

TEST_CASE("Constructing a triangle", "[Triangles]") {
    Point p1(0, 1, 0);
    Point p2(-1, 0, 0);
    Point p3(1, 0, 0);
    Triangle t(p1, p2, p3);

    // REQUIRE(t.p1 == p1);
    // REQUIRE(t.p2 == p2);
    // REQUIRE(t.p3 == p3);
    // REQUIRE(t.e1 == Vector(-1, -1, 0));
    // REQUIRE(t.e2 == Vector(1, -1, 0));
    REQUIRE(t.normal(Point(0, 0, 0)) == Vector(0, 0, -1));
}

TEST_CASE("Intersecting a ray parallel to the triangle", "[Triangles]") {
    Triangle t(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
    Ray r(Point(0, -1, -2), Vector(0, 1, 0));

    auto xs = t.localIntersect(r);
    REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray misses the p1-p3 edge", "[Triangles]") {
    Triangle t(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
    Ray r(Point(1, 1, -2), Vector(0, 0, 1.));

    auto xs = t.localIntersect(r);
    REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray misses the p1-p2 edge", "[Triangles]") {
    Triangle t(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
    Ray r(Point(-1, 1, -2), Vector(0, 0, 1));

    auto xs = t.localIntersect(r);
    REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray misses the p2-p3 edge", "[Triangles]") {
    Triangle t(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
    Ray r(Point(0, -1, -2), Vector(0, 0, 1));

    auto xs = t.localIntersect(r);
    REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray strikes a triangle", "[Triangles]") {
    auto t = std::make_shared<Triangle>(Point(0, 1, 0), Point(-1, 0, 0),
                                        Point(1, 0, 0));
    Ray r(Point(0, 0.5, -2), Vector(0, 0, 1));

    auto xs = t->localIntersect(r);
    REQUIRE(xs[0].t == 2);
}
