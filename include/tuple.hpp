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
    Vector normalize() const;
    Vector reflect(const Vector &n) const;
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

class Color {
public:
    Color();
    Color(double r, double g, double b);

    Color operator*(double scalar) const;
    Color operator*(const Color &rhs) const;
    Color operator+(const Color &rhs) const;
    bool operator==(const Color &rhs) const;
    double r, g, b;
};

std::ostream &operator<<(std::ostream &os, const Tuple &p);
std::ostream &operator<<(std::ostream &os, const Color &p);
