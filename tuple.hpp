#pragma once

#include <iostream>

// FIXME: add w
// w = 1 (point)
// w = 0 (vector)

class Point {
public:
    Point();
    Point(float x, float y, float z);

    Point operator-() const;
    Point operator+(const Point &rhs) const;
    Point operator-(const Point &rhs) const;
    Point operator*(double scalar) const;
    Point operator/(double scalar) const;
    bool operator==(const Point &rhs) const;

    double magnitude() const;
    Point normal() const;
    double dot(const Point &rhs) const;
    Point cross(const Point &rhs) const;

    float x, y, z;
};

using Vector = Point;
using Tuple = Point;
using Color = Point;

std::ostream &operator<<(std::ostream &os, const Point &p);
