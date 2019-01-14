#pragma once

#include "canvas.hpp"
#include "matrix.hpp"
#include "world.hpp"

class Camera {
public:
    Camera();

    Canvas render(const World &world) const;
    Ray rayForPixel(double x, double y) const;

    void calculatePixelSize();

    int width;
    double halfWidth;
    int height;
    double halfHeight;
    double fov;
    double pixelSize;
    Matrix transform;
    mutable Optional<Matrix> cacheInverse;
};
