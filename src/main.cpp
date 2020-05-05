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
#include "scene_file.hpp"

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


    const char *inputFilename = nullptr;
    const char *outputFilename = nullptr;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            if (argc > i+1) {
                outputFilename = argv[i+1];
            }
        } else if (strcmp(argv[i], "-i") == 0) {
            if (argc > i+1) {
                inputFilename = argv[i+1];
            }
        }
    }

    if (!outputFilename) {
        std::cerr << "No output file specified" << std::endl;
        return -1;
    }

    if (!inputFilename) {
        std::cerr << "No input file specified" << std::endl;
        return -1;
    }


    SceneFile f(inputFilename);
    writeBmpFile(outputFilename, f.render());
    return 0;
}
