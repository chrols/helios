#include "catch.hpp"

#include "tuple.hpp"
#include <cmath>

TEST_CASE("ReflectingVectorApproachingAt45Deg", "[Vectors]") {
    auto v = Vector(1, -1, 0);
    auto n = Vector(0, 1, 0);
    auto r = v.reflect(n);
    REQUIRE(r == Vector(1, 1, 0));
}

TEST_CASE("ReflectingVectorOffSlantedSurface", "[Vectors]") {
    double d = std::sqrt(2) / 2;
    auto v = Vector(0, -1, 0);
    auto n = Vector(d, d, 0);
    auto r = v.reflect(n);
    REQUIRE(r == Vector(1, 0, 0));
}
