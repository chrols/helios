#include "catch.hpp"

#include "light.hpp"
#include "tuple.hpp"

TEST_CASE("PointLightHasPositionAndIntensity", "[Lights]") {
    auto intensity = Color(1, 1, 1);
    auto position = Point(0, 0, 0);
    auto light = PointLight(position, intensity);
    REQUIRE(light.position == position);
    REQUIRE(light.intensity == intensity);
}
