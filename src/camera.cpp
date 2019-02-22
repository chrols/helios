#include "camera.hpp"

#include <chrono>
#include <cmath>

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::microseconds;

Camera::Camera(int width, int height)
    : m_width(width), m_height(height), m_fov(PI / 3.0),
      m_transform(Matrix::identity(4)) {
    _calculatePixelSize();
}

Canvas Camera::render(const World &world) const {
    int aaLevel = 1;

    steady_clock::time_point begin = steady_clock::now();

    Canvas image(m_width, m_height);
#pragma omp parallel for schedule(dynamic)
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {

            double step = 1.0 / (1 + aaLevel);
            Color color = Color::Black;

            for (int ay = 1; ay <= aaLevel; ay++) {
                for (int ax = 1; ax <= aaLevel; ax++) {
                    auto ray = rayForPixel(x + step * ax, y + step * ay);
                    color += world.colorAt(ray);
                }
            }

            color = color / (aaLevel * aaLevel);
            image.setPixel(x, y, color);
        }
    }

    steady_clock::time_point end = steady_clock::now();

    std::cerr << "Render took: " << duration_cast<seconds>(end - begin).count()
              << " s" << std::endl;
    std::cerr << "Per pixel: "
              << duration_cast<microseconds>(end - begin).count() /
                     double(m_width * m_height * 1000)
              << " ms" << std::endl;

    return image;
}

Ray Camera::rayForPixel(double x, double y) const {
    auto xoffset = x * m_pixelSize;
    auto yoffset = y * m_pixelSize;

    auto worldX = m_halfWidth - xoffset;
    auto worldY = m_halfWidth - yoffset;

    if (!m_transform.hasInverse())
        return Ray(Point(0, 0, 0), Vector(1, 0, 0));

    auto inverse = m_transform.inverse();
    auto pixel = inverse * Point(worldX, worldY, -1);
    auto origin = inverse * Point(0, 0, 0);
    auto direction = (pixel - origin).normalize();

    return Ray(origin, direction);
}

void Camera::_calculatePixelSize() {
    auto halfView = std::tan(m_fov / 2);
    auto aspect = m_width / m_height;

    if (aspect >= 1.0) {
        m_halfWidth = halfView;
        m_halfHeight = halfView / aspect;
    } else {
        m_halfWidth = halfView * aspect;
        m_halfHeight = halfView;
    }

    m_pixelSize = (m_halfWidth * 2) / m_height;
}

Matrix Camera::transform() const {
    return m_transform;
}

void Camera::setTransform(const Matrix &transform) {
    m_transform = transform;
}
