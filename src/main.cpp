#include <iostream>

#include "camera.hpp"
#include "canvas.hpp"
#include "intersection.hpp"
#include "light.hpp"
#include "matrix.hpp"
#include "obj_file.hpp"
#include "plane.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "tuple.hpp"
#include "world.hpp"

#include <gtest/gtest.h>

using namespace std;

int main(int argc, char **argv) {
    const unsigned pixels = 1000;

    ObjFile teapot;
    teapot.readFile("teapot.obj");

    Sphere s;
    s.material.color = Color(1, 0.2, 1);

    auto lightPosition = Point(-3, 3, -3);
    auto lightColor = Color(1, 1, 1);
    auto light = PointLight(lightPosition, lightColor);

    Sphere floor;
    floor.transform = Matrix::scalingMatrix(10, 0.01, 10);
    floor.material.color = Color(1, 0.9, 0.9);
    floor.material.specular = 0;
    floor.material.reflective = 0.2;

    Sphere middle = Sphere::glassSphere();
    middle.transform = Matrix::translationMatrix(-0.5, 1, 0.5);
    // middle.material = Material();
    // middle.material.color = Color(0.1, 1, 0.5);
    // middle.material.diffuse = 0.7;
    // middle.material.specular = 0.3;
    // middle.material.pattern = new StripePattern(Color(1, 0, 0), Color(0, 1,
    // 0));

    Sphere right;
    right.transform = Matrix::translationMatrix(1.5, 0.5, -0.5) *
                      Matrix::scalingMatrix(0.5, 0.5, 0.5);
    right.material.color = Color(0.5, 1, 0.1);
    right.material.diffuse = 0.7;
    right.material.specular = 0.3;

    Sphere left;
    left.transform = Matrix::translationMatrix(-1.5, 0.33, -0.75) *
                     Matrix::scalingMatrix(0.33, 0.33, 0.33);
    left.material = Material();
    left.material.color = Color::White;
    left.material.diffuse = 0.7;
    left.material.specular = 0.3;
    left.material.reflective = 1.0;

    Plane plane;
    plane.material = floor.material;
    plane.material.reflective = 0.2;
    plane.material.pattern =
        new CheckersPattern(Color(0.2, 0.2, 0.2), Color::White);

    const int cubeSize = 10;

    Plane ceiling = plane;
    ceiling.transform = Matrix::translationMatrix(0, cubeSize, 0);

    Plane rightWall = plane;
    rightWall.transform = Matrix::translationMatrix(cubeSize, 0, 0) *
                          Matrix::rotationMatrixZ(PI / 2);

    Plane leftWall = plane;
    leftWall.transform = Matrix::translationMatrix(-cubeSize, 0, 0) *
                         Matrix::rotationMatrixZ(PI / 2);

    Plane frontWall = plane;
    frontWall.transform = Matrix::translationMatrix(0, 0, cubeSize) *
                          Matrix::rotationMatrixX(PI / 2);

    Plane backWall = plane;
    backWall.transform = Matrix::translationMatrix(0, 0, -cubeSize) *
                         Matrix::rotationMatrixX(PI / 2);

    Sphere origin;

    // Triangle tri(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
    Triangle tri(Point(1.36807, 2.43544, -0.227403),
                 Point(1.38197, 2.4, -0.229712), Point(1.4, 2.4, 0));

    World w;
    // w.addObject(left);
    // w.addObject(middle);
    // w.addObject(right);

    std::vector<Triangle> triangles = teapot.triangles();

    for (int i = 0; i < triangles.size(); i++) {
        // Triangle e = triangles[i];
        // std::cout << e.p1 << " " << e.p2 << " " << e.p3 << std::endl;
        w.addObject(triangles[i]);
    }

    // w.addObject(tri);
    w.addObject(plane);
    w.addObject(ceiling);
    w.addObject(leftWall);
    w.addObject(rightWall);
    w.addObject(frontWall);
    w.addObject(backWall);
    w.addLight(light);

    Camera c;
    c.transform =
        Matrix::viewTransform(Point(0, 1, -4), Point(0, 1, 0), Vector(0, 1, 0));

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
