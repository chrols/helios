#include <iostream>
#include <cstring>

#include "bmp_file.hpp"
#include "camera.hpp"
#include "canvas.hpp"
#include "cylinder.hpp"
#include "group.hpp"
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

using namespace std;

std::shared_ptr<Sphere> hexagonCorner() {
    auto corner = std::make_shared<Sphere>();
    corner->setTransform(Matrix::translationMatrix(0, 0, -1) *
                         Matrix::scalingMatrix(0.25, 0.25, 0.25));
    return corner;
}

std::shared_ptr<Cylinder> hexagonEdge() {
    auto edge = std::make_shared<Cylinder>();
    edge->setMinimum(0);
    edge->setMaximum(1);
    edge->setTransform(Matrix::translationMatrix(0, 0, -1) *
                       Matrix::rotationMatrixY(-PI / 6) *
                       Matrix::rotationMatrixZ(-PI / 2) *
                       Matrix::scalingMatrix(0.25, 1, 0.25));

    return edge;
}

std::shared_ptr<Group> hexagonSide() {
    auto side = std::make_shared<Group>();
    side->addChild(hexagonCorner());
    side->addChild(hexagonEdge());
    return side;
}

std::shared_ptr<Group> hexagon() {
    auto hex = std::make_shared<Group>();

    for (int n = 0; n < 6; n++) {
        auto side = hexagonSide();
        side->setTransform(Matrix::rotationMatrixY(n * PI / 3));
        hex->addChild(side);
    }

    return hex;
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cerr << "No output file specified" << std::endl;
        return -1;
    }

    const char *outputFilename = nullptr;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            if (argc > i+1) {
                outputFilename = argv[i+1];
                std::cerr << std::string(outputFilename) << std::endl;
            }
        } else if (strcmp(argv[i], "") == 0) {
        }
    }

    if (!outputFilename) {
        std::cerr << "No output file specified" << std::endl;
        return -1;
    }

    ObjFile teapot;
    teapot.readFile("cube.obj");

    auto s = std::make_shared<Sphere>();
    s->material.color = Color(1, 0.2, 1);

    auto lightPosition = Point(-3, 3, -3);
    auto lightColor = Color(1, 1, 1);
    auto light = PointLight(lightPosition, lightColor);

    auto floor = std::make_shared<Sphere>();
    floor->setTransform(Matrix::scalingMatrix(10, 0.01, 10));
    floor->material.color = Color(1, 0.9, 0.9);
    floor->material.specular = 0;
    floor->material.reflective = 0.2;

    auto middle = Sphere::glassSphere();
    middle->setTransform(Matrix::translationMatrix(-0.5, 1, 0.5));

    auto right = std::make_shared<Sphere>();
    right->setTransform(Matrix::translationMatrix(1.5, 0.5, -0.5) *
                        Matrix::scalingMatrix(0.5, 0.5, 0.5));
    right->material.color = Color(0.5, 1, 0.1);
    right->material.diffuse = 0.7;
    right->material.specular = 0.3;

    auto left = std::make_shared<Sphere>();
    left->setTransform(Matrix::translationMatrix(-1.5, 0.33, -0.75) *
                       Matrix::scalingMatrix(0.33, 0.33, 0.33));
    left->material = Material();
    left->material.color = Color::White;
    left->material.diffuse = 0.7;
    left->material.specular = 0.3;
    left->material.reflective = 1.0;

    auto plane = std::make_shared<Plane>();
    plane->material = floor->material;
    plane->material.reflective = 0.2;
    plane->material.pattern =
        new CheckersPattern(Color(0.2, 0.2, 0.2), Color::White);

    const int cubeSize = 10;

    auto ceiling = std::make_shared<Plane>(*plane);
    ceiling->setTransform(Matrix::translationMatrix(0, cubeSize, 0));

    auto rightWall = std::make_shared<Plane>(*plane);
    rightWall->setTransform(Matrix::translationMatrix(cubeSize, 0, 0) *
                            Matrix::rotationMatrixZ(PI / 2));

    auto leftWall = std::make_shared<Plane>(*plane);
    leftWall->setTransform(Matrix::translationMatrix(-cubeSize, 0, 0) *
                           Matrix::rotationMatrixZ(PI / 2));

    auto frontWall = std::make_shared<Plane>(*plane);
    frontWall->setTransform(Matrix::translationMatrix(0, 0, cubeSize) *
                            Matrix::rotationMatrixX(PI / 2));

    auto backWall = std::make_shared<Plane>(*plane);
    backWall->setTransform(Matrix::translationMatrix(0, 0, -cubeSize) *
                           Matrix::rotationMatrixX(PI / 2));

    World w;
    w.addObject(left);
    w.addObject(middle);
    w.addObject(right);
    w.addObject(plane);
    w.addObject(ceiling);
    w.addObject(leftWall);
    w.addObject(rightWall);
    w.addObject(frontWall);
    w.addObject(backWall);

    auto hexy = hexagon();
    hexy->setTransform(Matrix::rotationMatrixX(PI / 2));
    w.addObject(hexy);

    w.addLight(light);

    Camera c;
    c.setTransform(Matrix::viewTransform(Point(0, 1, -4), Point(0, 1, 0),
                                         Vector(0, 1, 0)));

    writeBmpFile(outputFilename, c.render(w));
}
