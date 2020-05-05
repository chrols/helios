#pragma once

#include "canvas.hpp"
#include "matrix.hpp"
#include "world.hpp"

class Camera {
public:
    Camera(int width = 200, int height = 100, double fov = PI / 3.0);

    Canvas render(const World &world) const;
    Ray rayForPixel(double x, double y) const;

    Matrix transform() const;
    void setTransform(const Matrix &transform);

private:
    void _calculatePixelSize();

    int m_width;
    int m_height;
    double m_fov;
    Matrix m_transform;

    double m_halfWidth;
    double m_halfHeight;
    double m_pixelSize;
};
