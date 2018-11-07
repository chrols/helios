#include <gtest/gtest.h>

#include "light.hpp"
#include "material.hpp"
#include <cmath>

TEST(Materials, DefaultMaterial) {
    auto m = Material();
    ASSERT_EQ(m.color, Color(1, 1, 1));
    ASSERT_EQ(m.ambient, 0.1);
    ASSERT_EQ(m.diffuse, 0.9);
    ASSERT_EQ(m.specular, 0.9);
    ASSERT_EQ(m.shininess, 200.0);
}

TEST(Materials, LightingWithEyeBetweenLightAndSurface) {
    Material m;
    Point position;

    auto eyev = Vector(0, 0, -1);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight(Point(0, 0, -10), Color(1, 1, 1));
    auto result = Phong::lighting(m, light, position, eyev, normalv);
    ASSERT_TRUE(result == Color(1.9, 1.9, 1.9));
}

TEST(Materials, LightingWithEyeBetweenLightAndSurfaceEyeOffset45Deg) {
    Material m;
    Point position;
    double v = std::sqrt(2) / 2;
    auto eyev = Vector(0, v, v);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight(Point(0, 0, -10), Color(1, 1, 1));
    auto result = Phong::lighting(m, light, position, eyev, normalv);
    ASSERT_TRUE(result == Color(1.0, 1.0, 1.0));
}

TEST(Materials, LightingWithEyeOppositeSurfaceLightOffset45Deg) {
    Material m;
    Point position;
    auto eyev = Vector(0, 0, -1);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight(Point(0, 10, -10), Color(1, 1, 1));
    auto result = Phong::lighting(m, light, position, eyev, normalv);
    ASSERT_TRUE(result == Color(0.7364, 0.7364, 0.7634));
}

TEST(Materials, LightingWithEyeInPathOfReflectionVector) {
    Material m;
    Point position;
    auto eyev = Vector(0, -std::sqrt(2) / 2, -std::sqrt(2) / 2);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight(Point(0, 10, -10), Color(1, 1, 1));
    auto result = Phong::lighting(m, light, position, eyev, normalv);
    ASSERT_TRUE(result == Color(1.6364, 1.6364, 1.6364));
}

TEST(Materials, LightingWithLightBehindSurface) {
    Material m;
    Point position;
    auto eyev = Vector(0, 0, -1);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight(Point(0, 0, 10), Color(1, 1, 1));
    auto result = Phong::lighting(m, light, position, eyev, normalv);
    ASSERT_TRUE(result == Color(0.1, 0.1, 0.1));
}

TEST(Materials, LightingWithSurfaceInShadow) {
    Material material;
    Point position;
    auto eyeVector = Vector(0, 0, -1);
    auto normal = Vector(0, 0, -1);
    auto light = PointLight(Point(0, 0, -10), Color(1, 1, 1));
    auto inShadow = true;
    auto result =
        Phong::lighting(material, light, position, eyeVector, normal, inShadow);
    ASSERT_TRUE(result == Color(0.1, 0.1, 0.1));
}

TEST(Materials, LightingWithPatternApplied) {
    Material m;
    m.pattern = new StripePattern(Color(1, 1, 1), Color(0, 0, 0));
    m.ambient = 1;
    m.diffuse = 0;
    m.specular = 0;
    Vector eye(0, 0, -1);
    Vector normal(0, 0, -1);
    auto light = PointLight(Point(0, 0, -10), Color(1, 1, 1));
    auto c1 = Phong::lighting(m, light, Point(0.9, 0, 0), eye, normal);
    auto c2 = Phong::lighting(m, light, Point(1.1, 0, 0), eye, normal);
    ASSERT_TRUE(c1 == Color(1, 1, 1));
    ASSERT_TRUE(c2 == Color(0, 0, 0));
}

TEST(Materials, TrasparencyAndRefractionForDefaultMaterial) {
    Material m;
    ASSERT_EQ(m.transparency, 0.0);
    ASSERT_EQ(m.refraction, 1.0);
}
