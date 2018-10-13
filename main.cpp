#include <iostream>

#include "canvas.hpp"
#include "intersection.hpp"
#include "light.hpp"
#include "matrix.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "tuple.hpp"

#include <gtest/gtest.h>

int main(int argc, char **argv) {
    if (argc >= 2 && strcmp(argv[1], "-test") == 0) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }

    const unsigned pixels = 1000;

    Sphere s;
    s.material.color = Color(1, 0.2, 1);
    auto lightPosition = Point(-10, 10, -10);
    auto lightColor = Color(1, 1, 1);
    auto light = PointLight(lightPosition, lightColor);
    Point rayOrigin(0, 0, -5);
    Canvas canvas(pixels, pixels);
    Color red(1.0, 0, 0);
    double wallZ = 10;
    double wallSize = 7.0;
    double half = wallSize / 2.0;
    auto pixelSize = wallSize / pixels;

#pragma omp parallel for schedule(dynamic)
    for (int y = 0; y < pixels; y++) {
        auto worldY = half - pixelSize * y;
        for (int x = 0; x < pixels; x++) {
            auto worldX = -half + pixelSize * x;
            auto pos = Point(worldX, worldY, wallZ);
            auto rayVector = (pos - rayOrigin).normalize();
            auto r = Ray(rayOrigin, rayVector);
            auto xs = s.intersect(r);
            auto hit = Intersection::hit(xs);
            if (hit) {
                auto point = r.position(hit->t);
                auto normal = hit->object->normal(point);
                auto eye = -r.direction;
                auto color =
                    lighting(hit->object->material, light, point, eye, *normal);
                canvas.setPixel(x, y, color);
            }
        }
    }

    canvas.write();
}
