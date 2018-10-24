#include <iostream>

#include "camera.hpp"
#include "canvas.hpp"
#include "intersection.hpp"
#include "light.hpp"
#include "matrix.hpp"
#include "plane.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "tuple.hpp"
#include "world.hpp"

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

    Sphere floor;
    floor.transform = Matrix<double>::scalingMatrix(10, 0.01, 10);
    floor.material.color = Color(1, 0.9, 0.9);
    floor.material.specular = 0;

    Sphere leftWall;
    leftWall.transform = Matrix<double>::translationMatrix(0, 0, 5) *
                         Matrix<double>::rotationMatrixY(-PI / 4) *
                         Matrix<double>::rotationMatrixX(PI / 2) *
                         Matrix<double>::scalingMatrix(10, 0.01, 10);
    leftWall.material = floor.material;

    Sphere rightWall;
    rightWall.transform = Matrix<double>::translationMatrix(0, 0, 5) *
                          Matrix<double>::rotationMatrixY(PI / 4) *
                          Matrix<double>::rotationMatrixX(PI / 2) *
                          Matrix<double>::scalingMatrix(10, 0.01, 10);
    rightWall.material = floor.material;

    Sphere middle;
    middle.transform = Matrix<double>::translationMatrix(-0.5, 1, 0.5);
    middle.material = Material();
    middle.material.color = Color(0.1, 1, 0.5);
    middle.material.diffuse = 0.7;
    middle.material.specular = 0.3;

    Sphere right;
    right.transform = Matrix<double>::translationMatrix(1.5, 0.5, -0.5) *
                      Matrix<double>::scalingMatrix(0.5, 0.5, 0.5);
    right.material = Material();
    right.material.color = Color(0.5, 1, 0.1);
    right.material.diffuse = 0.7;
    right.material.specular = 0.3;

    Sphere left;
    left.transform = Matrix<double>::translationMatrix(-1.5, 0.33, -0.75) *
                     Matrix<double>::scalingMatrix(0.33, 0.33, 0.33);
    left.material = Material();
    left.material.color = Color(1, 0.8, 0.1);
    left.material.diffuse = 0.7;
    left.material.specular = 0.3;

    Plane plane;
    plane.material = floor.material;

    World w;
    w.addObject(left);
    w.addObject(middle);
    w.addObject(right);
    w.addObject(plane);
    // w.addObject(floor);
    // w.addObject(leftWall);
    // w.addObject(rightWall);
    w.addLight(light);

    Camera c;
    c.transform = Matrix<double>::viewTransform(Point(0, 1, -5), Point(0, 1, 0),
                                                Vector(0, 1, 0));

    c.render(w).write();
}

// Point rayOrigin(0, 0, -5);
//     Canvas canvas(pixels, pixels);
//     Color red(1.0, 0, 0);
//     double wallZ = 10;
//     double wallSize = 7.0;
//     double half = wallSize / 2.0;
//     auto pixelSize = wallSize / pixels;

// #pragma omp parallel for schedule(dynamic)
//     for (int y = 0; y < pixels; y++) {
//         auto worldY = half - pixelSize * y;
//         for (int x = 0; x < pixels; x++) {
//             auto worldX = -half + pixelSize * x;
//             auto pos = Point(worldX, worldY, wallZ);
//             auto rayVector = (pos - rayOrigin).normalize();
//             auto r = Ray(rayOrigin, rayVector);
//             auto xs = s.intersect(r);
//             auto hit = Intersection::hit(xs);
//             if (hit) {
//                 auto point = r.position(hit->t);
//                 auto normal = hit->object->normal(point);
//                 auto eye = -r.direction;
//                 auto color =
//                     lighting(hit->object->material, light, point, eye,
//                     *normal);
//                 canvas.setPixel(x, y, color);
//             }
//         }
//     }
