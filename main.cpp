#include <iostream>

#include "canvas.hpp"
#include "intersection.hpp"
#include "matrix.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "tuple.hpp"

#include <gtest/gtest.h>

int main(int argc, char **argv) {
    const unsigned pixels = 1000;

    Sphere s;
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
            auto rayVector = (pos - rayOrigin).normal();
            auto r = Ray(rayOrigin, rayVector);
            auto xs = s.intersect(r);
            if (Intersection::hit(xs)) {
                canvas.setPixel(x, y, red);
            }
        }
    }

    canvas.write();

    //    ::testing::InitGoogleTest(&argc, argv);
    // return RUN_ALL_TESTS();
}
