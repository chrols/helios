#pragma once

#include <iostream>

// FIXME: add w
// w = 1 (point)
// w = 0 (vector)

class Tuple {
public:
    Tuple(double x, double y, double z, double w);

    bool operator==(const Tuple &rhs) const;

    double x, y, z, w;
};

class Vector : public Tuple {
public:
    Vector();
    Vector(double x, double y, double z);

    Vector operator-() const;
    Vector operator+(const Vector &rhs) const;
    Vector operator-(const Vector &rhs) const;
    Vector operator*(double scalar) const;
    Vector operator/(double scalar) const;

    double magnitude() const;
    Vector normal() const;
    double dot(const Vector &rhs) const;
    Vector cross(const Vector &rhs) const;
};

class Point : public Tuple {
public:
    Point();
    Point(double x, double y, double z);

    Point operator+(const Vector &rhs) const;
    Point operator-(const Vector &rhs) const;
    Vector operator-(const Point &rhs) const;
};

using Color = Point;

std::ostream &operator<<(std::ostream &os, const Tuple &p);
