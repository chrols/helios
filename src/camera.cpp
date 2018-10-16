#include "camera.hpp"

#include <cmath>

Camera::Camera()
    : width(256), height(144), fov(PI / 3.0),
      transform(Matrix<double>::identity(4)) {
    calculatePixelSize();
}

Canvas Camera::render(const World &world) const {
    Canvas image(width, height);
#pragma omp parallel for schedule(dynamic)
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            auto ray = rayForPixel(x, y);
            auto color = world.colorAt(ray);
            image.setPixel(x, y, color);
        }
    }

    return image;
}

Ray Camera::rayForPixel(unsigned x, unsigned y) const {
    auto xoffset = (x + 0.5) * pixelSize;
    auto yoffset = (y + 0.5) * pixelSize;

    auto worldX = halfWidth - xoffset;
    auto worldY = halfWidth - yoffset;

    if (!transform.hasInverse())
        return Ray(Point(0, 0, 0), Vector(1, 0, 0));

    auto inverse = transform.inverse();
    auto pixel = inverse * Point(worldX, worldY, -1);
    auto origin = inverse * Point(0, 0, 0);
    auto direction = (pixel - origin).normalize();

    return Ray(origin, direction);
}

void Camera::calculatePixelSize() {
    auto halfView = std::tan(fov / 2);
    auto aspect = width / height;

    if (aspect >= 1.0) {
        halfWidth = halfView;
        halfHeight = halfView / aspect;
    } else {
        halfWidth = halfView * aspect;
        halfHeight = halfView;
    }

    pixelSize = (halfWidth * 2) / height;
}
