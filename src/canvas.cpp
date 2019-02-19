#include "canvas.hpp"

#include <iostream>

Canvas::Canvas(int width, int height) : m_width(width), m_height(height) {
    m_canvas.resize(width * height, Color::Blue);
}

void Canvas::setPixel(int x, int y, Color c) {
    m_canvas[x + y * m_width] = c;
}

// FIXME Rounding
void Canvas::write() const {
    std::cout << "P3\n" << m_width << " " << m_height << "\n255\n";
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            const Color &c = m_canvas[x + y * m_width];
            int cx = std::min(std::max(c.r * 255, 0.0), 255.0);
            int cy = std::min(std::max(c.g * 255, 0.0), 255.0);
            int cz = std::min(std::max(c.b * 255, 0.0), 255.0);
            std::cout << cx << " " << cy << " " << cz
                      << (x == m_width - 1 ? "\n" : " ");
        }
    }
    std::cout << "\n";
}

int Canvas::width() const {
    return m_width;
}

int Canvas::height() const {
    return m_height;
}
