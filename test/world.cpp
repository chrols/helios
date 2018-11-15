#include "catch.hpp"

#include "pattern.hpp"
#include "plane.hpp"
#include "world.hpp"

TEST_CASE("IntersectWorldWithRay", "[World]", ) {
    World world = World::testWorld();
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto xs = world.intersect(ray);
    REQUIRE(xs.size() == 4);
    REQUIRE(xs[0].t == 4);
    REQUIRE(xs[1].t == 4.5);
    REQUIRE(xs[2].t == 5.5);
    REQUIRE(xs[3].t == 6);
}

TEST_CASE("ReflectedColorForNonReflectiveMaterial", "[World]") {
    World world;
    Ray ray(Point(0, 0, 0), Vector(0, 0, 1));
    Sphere sphere;
    sphere.material.ambient = 1;
    Intersection hit(1, &sphere);
    hit.precompute(ray);
    auto color = world.reflectedColor(hit);
    REQUIRE(color == Color::Black);
}

TEST_CASE("RefractedColorWithOpaqueSurface", "[World]") {
    World world = World::testWorld();
    const Object *object = world.firstObject();
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    std::vector<Intersection> xs;
    xs.emplace_back(Intersection(4, object));
    xs.emplace_back(Intersection(6, object));
    REQUIRE(!xs.empty());
    xs[0].precompute(ray, xs);
    Color c = world.refractedColor(xs[0], 5);
    REQUIRE(c == Color::Black);
}

TEST_CASE("RefractedColorAtMaximumRecursiveDepth", "[World]") {
    World world;
    Sphere sphere;
    sphere.material.transparency = 1.0;
    sphere.material.refraction = 1.5;
    world.addObject(sphere);

    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    std::vector<Intersection> xs;
    xs.emplace_back(Intersection(4, &sphere));
    xs.emplace_back(Intersection(6, &sphere));
    xs[0].precompute(ray, xs);
    auto c = world.refractedColor(xs[0], 0);
    REQUIRE(c == Color::Black);
}

TEST_CASE("RefractedColorUnderTotalInternalReflection", "[World]") {
    World world;
    Sphere sphere;
    sphere.material.transparency = 1.0;
    sphere.material.refraction = 1.5;
    world.addObject(sphere);

    Ray ray(Point(0, 0, std::sqrt(2.0) / 2.0), Vector(0, 1, 0));
    std::vector<Intersection> xs;
    xs.emplace_back(Intersection(-std::sqrt(2.0) / 2.0, &sphere));
    xs.emplace_back(Intersection(std::sqrt(2.0) / 2.0, &sphere));
    xs[1].precompute(ray, xs);
    auto c = world.refractedColor(xs[1], 5);
    REQUIRE(c == Color::Black);
}

TEST_CASE("RefractedColorWithRefractedRay", "[World]") {
    World world = World::testWorld();
    world.clearObjects();

    Sphere a;
    a.material.ambient = 1.0;
    a.material.pattern = new TestPattern();
    world.addObject(a);

    Sphere b;
    b.material.transparency = 1.0;
    b.material.refraction = 1.5;
    world.addObject(b);

    Ray ray(Point(0, 0, 0.1), Vector(0, 1, 0));
    std::vector<Intersection> xs;
    xs.emplace_back(Intersection(-0.9899, &a));
    xs.emplace_back(Intersection(-0.4899, &b));
    xs.emplace_back(Intersection(0.4899, &b));
    xs.emplace_back(Intersection(0.9899, &a));

    xs[2].precompute(ray, xs);
    auto c = world.refractedColor(xs[2], 5);
    REQUIRE(c == Color(0, 0.99878, 0.04724));
}

TEST_CASE("ShadeHitWithTransparentMaterial", "[World]") {
    World world = World::testWorld();

    Plane floor;
    floor.transform = Matrix::translationMatrix(0, -1, 0);
    floor.material.transparency = 0.5;
    floor.material.refraction = 1.5;
    world.addObject(floor);

    Sphere ball;
    ball.material.color = Color::Red;
    ball.material.ambient = 0.5;
    ball.transform = Matrix::translationMatrix(0, -3.5, -0.5);
    world.addObject(ball);

    Ray ray(Point(0, 0, -3),
            Vector(0, -std::sqrt(2.0) / 2.0, std::sqrt(2.0) / 2.0));

    std::vector<Intersection> xs;
    xs.emplace_back(Intersection(std::sqrt(2.0), &floor));
    xs[0].precompute(ray, xs);
    Color color = world._shadeHit(xs[0]);
    REQUIRE(color == Color(0.93642, 0.68642, 0.68642));
}

TEST_CASE("ShadeHitReflectiveTransparentMaterial", "[World]") {
    World world = World::testWorld();
    Ray ray(Point(0, 0, -3), Vector(0, -std::sqrt(2) / 2, std::sqrt(2) / 2));

    Plane floor;
    floor.transform = Matrix::translationMatrix(0, -1, 0);
    floor.material.reflective = 0.5;
    floor.material.transparency = 0.5;
    floor.material.refraction = 1.5;
    world.addObject(floor);

    Sphere ball;
    ball.material.color = Color(1, 0, 0);
    ball.material.ambient = 0.5;
    ball.transform = Matrix::translationMatrix(0, -3.5, -0.5);
    world.addObject(ball);

    std::vector<Intersection> xs = {Intersection(std::sqrt(2), &floor)};
    xs[0].precompute(ray, xs);

    auto color = world._shadeHit(xs[0]);

    REQUIRE(color == Color(0.93391, 0.69643, 0.69243));
}
