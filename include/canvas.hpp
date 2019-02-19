#pragma once

#include <vector>

#include "tuple.hpp"

class Canvas {
public:
    Canvas(int width, int height);
    void setPixel(int x, int y, Color c);
    void write() const;
    int width() const;
    int height() const;
    std::vector<Color> m_canvas;

private:
    int m_width, m_height;
};
