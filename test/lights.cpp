#include <gtest/gtest.h>

#include "light.hpp"
#include "tuple.hpp"

TEST(Lights, PointLightHasPositionAndIntensity) {
    auto intensity = Color(1, 1, 1);
    auto position = Point(0, 0, 0);
    auto light = PointLight(position, intensity);
    ASSERT_TRUE(light.position == position);
    ASSERT_TRUE(light.intensity == intensity);
}
