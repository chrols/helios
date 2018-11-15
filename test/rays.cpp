#include "catch.hpp"

#include "matrix.hpp"
#include "ray.hpp"

TEST_CASE("ComputingPointFromDistance", "[Rays]") {
    Ray ray(Point(2, 3, 4), Vector(1, 0, 0));
    REQUIRE(Point(2, 3, 4) == ray.position(0));
    REQUIRE(Point(4.5, 3, 4) == ray.position(2.5));
}

TEST_CASE("TranslatingRay", "[Rays]") {
    Ray r(Point(1, 2, 3), Vector(0, 1, 0));
    auto m = Matrix::translationMatrix(3, 4, 5);
    auto r2 = r.transform(m);
    REQUIRE(r2.origin == Point(4, 6, 8));
    REQUIRE(r2.direction == Vector(0, 1, 0));
}

TEST_CASE("ScalingRay", "[Rays]") {
    Ray r(Point(1, 2, 3), Vector(0, 1, 0));
    auto m = Matrix::scalingMatrix(2, 3, 4);
    auto r2 = r.transform(m);
    REQUIRE(r2.origin == Point(2, 6, 12));
    REQUIRE(r2.direction == Vector(0, 3, 0));
}
