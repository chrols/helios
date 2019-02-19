#pragma once

#include <cstdint>
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
    enum ColorName {
        Aqua,
        Black,
        Blue,
        Fuchsia,
        Gray,
        Green,
        Lime,
        Maroon,
        Navy,
        Olive,
        Purple,
        Red,
        Silver,
        Teal,
        White,
        Yellow
    };

    Color();
    Color(ColorName name);
    Color(double r, double g, double b);

    Color operator-(const Color &rhs) const;
    Color operator*(double scalar) const;
    Color operator/(double scalar) const;
    Color operator*(const Color &rhs) const;
    Color operator+(const Color &rhs) const;
    Color &operator+=(const Color &rhs);
    bool operator==(const Color &rhs) const;

    uint32_t toRgba() const;

    double r, g, b;
};

std::ostream &operator<<(std::ostream &os, const Tuple &p);
std::ostream &operator<<(std::ostream &os, const Point &p);
std::ostream &operator<<(std::ostream &os, const Color &p);
std::ostream &operator<<(std::ostream &os, const Vector &p);
