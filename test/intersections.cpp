#include "catch.hpp"

#include <utility>

#include "intersection.hpp"
#include "plane.hpp"
#include "sphere.hpp"

TEST_CASE("HitWhenAllIntersectionHavePositiveT", "[Intersections]") {
    auto s = std::make_shared<Sphere>();
    Intersection i1(1, s);
    Intersection i2(1, s);
    std::vector<Intersection> xs = {i1, i2};
    auto h = Intersection::hit(xs);
    REQUIRE(h);
    REQUIRE(*h == i1);
}

TEST_CASE("HitWhenSomeIntersectionHaveNegativeT", "[Intersections]") {
    auto s = std::make_shared<Sphere>();
    Intersection i1(-1, s);
    Intersection i2(1, s);
    std::vector<Intersection> xs = {i1, i2};
    auto h = Intersection::hit(xs);
    REQUIRE(h);
    REQUIRE(*h == i2);
}

TEST_CASE("HitWhenAllIntersectionHaveNegativeT", "[Intersections]") {
    auto s = std::make_shared<Sphere>();
    Intersection i1(-1, s);
    Intersection i2(-2, s);
    std::vector<Intersection> xs = {i1, i2};
    auto h = Intersection::hit(xs);
    REQUIRE(!h);
}

TEST_CASE("TheHitIsAlwaysTheLowestNonNegativeIntersection", "[Intersections]") {
    auto s = std::make_shared<Sphere>();
    Intersection i1(5, s);
    Intersection i2(7, s);
    Intersection i3(-3, s);
    Intersection i4(2, s);

    std::vector<Intersection> xs = {i1, i2, i3, i4};
    auto h = Intersection::hit(xs);
    REQUIRE(*h == i4);
}

TEST_CASE("PrecomputingStateOfIntersection", "[Intersections]") {
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto sphere = std::make_shared<Sphere>();
    auto hit = Intersection(4.0, sphere);
    hit.precompute(ray);
    REQUIRE(hit.point == Point(0, 0, -1));
    REQUIRE(hit.eyeVector == Vector(0, 0, -1));
    REQUIRE(hit.normalVector == Vector(0, 0, -1));
}

// Intersection occurs on the outside
// Intersection occurs on the inside

TEST_CASE("PrecomputingReflectionVector", "[Intersections]") {
    auto shape = std::make_shared<Plane>();
    Ray ray(Point(0, 1, -1),
            Vector(0, -std::sqrt(2) / 2.0, std::sqrt(2) / 2.0));
    Intersection hit(std::sqrt(2), shape);
    hit.precompute(ray);
    REQUIRE(hit.reflectVector ==
            Vector(0, std::sqrt(2) / 2.0, std::sqrt(2) / 2.0));
}

TEST_CASE("NsAtVariousIntersections", "[Intersections]") {
    auto a = Sphere::glassSphere();
    a->setTransform(Matrix::scalingMatrix(2, 2, 2));
    a->material.refraction = 1.5;

    auto b = Sphere::glassSphere();
    b->setTransform(Matrix::translationMatrix(0, 0, -0.25));
    b->material.refraction = 2.0;

    auto c = Sphere::glassSphere();
    c->setTransform(Matrix::translationMatrix(0, 0, 0.25));
    c->material.refraction = 2.5;

    Ray ray(Point(0, 0, -4), Vector(0, 0, 1));

    std::vector<Intersection> xs;
    xs.emplace_back(Intersection(2, a));
    xs.emplace_back(Intersection(2.75, b));
    xs.emplace_back(Intersection(3.25, c));
    xs.emplace_back(Intersection(4.75, b));
    xs.emplace_back(Intersection(5.25, c));
    xs.emplace_back(Intersection(6, a));

    std::vector<double> expectedN1 = {1.0, 1.5, 2.0, 2.5, 2.5, 1.5};
    std::vector<double> expectedN2 = {1.5, 2.0, 2.5, 2.5, 1.5, 1.0};

    for (int i = 0; i < 5; i++) {
        xs[i].precompute(ray, xs);
        REQUIRE(xs[i].n1 == expectedN1[i]);
        REQUIRE(xs[i].n2 == expectedN2[i]);
    }
}

TEST_CASE("TheUnderPointIsOffsetBelowSurface", "[Intersections]") {
    auto sphere = Sphere::glassSphere();
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    Intersection hit(4, sphere);
    std::vector<Intersection> xs = {hit};
    hit.precompute(ray, xs);
    REQUIRE(hit.underPoint.z > -1);
    REQUIRE(hit.underPoint.z < -0.9);
}

TEST_CASE("SchlickApproximationUnderTotalInternalReflection",
          "[Intersections]") {
    auto sphere = Sphere::glassSphere();
    Ray ray(Point(0, 0, std::sqrt(2) / 2), Vector(0, 1, 0));
    std::vector<Intersection> xs = {Intersection(-std::sqrt(2) / 2, sphere),
                                    Intersection(std::sqrt(2) / 2, sphere)};
    xs[1].precompute(ray, xs);
    auto reflectance = xs[1].reflectance();
    REQUIRE(reflectance == 1);
}

TEST_CASE("SchlickApproximationWithPerpendicularViewingAngle",
          "[Intersections]") {
    auto sphere = Sphere::glassSphere();
    Ray ray(Point(0, 0, 0), Vector(0, 1, 0));
    std::vector<Intersection> xs = {Intersection(-1, sphere),
                                    Intersection(1, sphere)};
    xs[1].precompute(ray, xs);
    auto reflectance = xs[1].reflectance();
    REQUIRE(almostEqual(reflectance, 0.04));
}

TEST_CASE("SchlickApproximationWithSmallAngleAndN2GtN1", "[Intersections]") {
    auto sphere = Sphere::glassSphere();
    Ray ray(Point(0, 0.99, -2), Vector(0, 0, 1));
    std::vector<Intersection> xs = {Intersection(1.8589, sphere)};
    xs[0].precompute(ray, xs);
    auto reflectance = xs[0].reflectance();
    REQUIRE(almostEqual(reflectance, 0.48873));
}
