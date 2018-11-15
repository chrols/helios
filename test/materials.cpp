#include "catch.hpp"

#include "light.hpp"
#include "material.hpp"
#include <cmath>

TEST_CASE("DefaultMaterial", "[Materials]") {
    auto m = Material();
    REQUIRE(m.color == Color(1, 1, 1));
    REQUIRE(m.ambient == 0.1);
    REQUIRE(m.diffuse == 0.9);
    REQUIRE(m.specular == 0.9);
    REQUIRE(m.shininess == 200.0);
}

TEST_CASE("LightingWithEyeBetweenLightAndSurface", "[Materials]") {
    Material m;
    Point position;

    auto eyev = Vector(0, 0, -1);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight(Point(0, 0, -10), Color(1, 1, 1));
    auto result = Phong::lighting(m, light, position, eyev, normalv);
    REQUIRE(result == Color(1.9, 1.9, 1.9));
}

TEST_CASE("LightingWithEyeBetweenLightAndSurfaceEyeOffset45Deg",
          "[Materials]") {
    Material m;
    Point position;
    double v = std::sqrt(2) / 2;
    auto eyev = Vector(0, v, v);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight(Point(0, 0, -10), Color(1, 1, 1));
    auto result = Phong::lighting(m, light, position, eyev, normalv);
    REQUIRE(result == Color(1.0, 1.0, 1.0));
}

TEST_CASE("LightingWithEyeOppositeSurfaceLightOffset45Deg", "[Materials]") {
    Material m;
    Point position;
    auto eyev = Vector(0, 0, -1);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight(Point(0, 10, -10), Color(1, 1, 1));
    auto result = Phong::lighting(m, light, position, eyev, normalv);
    REQUIRE(result == Color(0.7364, 0.7364, 0.7634));
}

TEST_CASE("LightingWithEyeInPathOfReflectionVector", "[Materials]") {
    Material m;
    Point position;
    auto eyev = Vector(0, -std::sqrt(2) / 2, -std::sqrt(2) / 2);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight(Point(0, 10, -10), Color(1, 1, 1));
    auto result = Phong::lighting(m, light, position, eyev, normalv);
    REQUIRE(result == Color(1.6364, 1.6364, 1.6364));
}

TEST_CASE("LightingWithLightBehindSurface", "[Materials]") {
    Material m;
    Point position;
    auto eyev = Vector(0, 0, -1);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight(Point(0, 0, 10), Color(1, 1, 1));
    auto result = Phong::lighting(m, light, position, eyev, normalv);
    REQUIRE(result == Color(0.1, 0.1, 0.1));
}

TEST_CASE("LightingWithSurfaceInShadow", "[Materials]") {
    Material material;
    Point position;
    auto eyeVector = Vector(0, 0, -1);
    auto normal = Vector(0, 0, -1);
    auto light = PointLight(Point(0, 0, -10), Color(1, 1, 1));
    auto inShadow = true;
    auto result =
        Phong::lighting(material, light, position, eyeVector, normal, inShadow);
    REQUIRE(result == Color(0.1, 0.1, 0.1));
}

TEST_CASE("LightingWithPatternApplied", "[Materials]") {
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
    REQUIRE(c1 == Color(1, 1, 1));
    REQUIRE(c2 == Color(0, 0, 0));
}

TEST_CASE("TrasparencyAndRefractionForDefaultMaterial", "[Materials]") {
    Material m;
    REQUIRE(m.transparency == 0.0);
    REQUIRE(m.refraction == 1.0);
}
