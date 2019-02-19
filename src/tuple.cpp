#include "tuple.hpp"

#include "common.hpp"
#include <cmath>
#include <limits>

Tuple::Tuple(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}

bool Tuple::operator==(const Tuple &rhs) const {
    return (almostEqual(x, rhs.x) && almostEqual(y, rhs.y) &&
            almostEqual(z, rhs.z) && almostEqual(w, rhs.w));
}

Vector::Vector() : Tuple(0.0, 0.0, 0.0, 0.0) {}

Vector::Vector(double x, double y, double z) : Tuple(x, y, z, 0.0) {}

Vector Vector::operator-() const {
    Vector p(-x, -y, -z);
    return p;
}

Vector Vector::operator+(const Vector &rhs) const {
    Vector p;
    p.x = x + rhs.x;
    p.y = y + rhs.y;
    p.z = z + rhs.z;
    return p;
}

Vector Vector::operator-(const Vector &rhs) const {
    Vector p;
    p.x = x - rhs.x;
    p.y = y - rhs.y;
    p.z = z - rhs.z;
    return p;
}

Vector Vector::operator*(double scalar) const {
    Vector p(x * scalar, y * scalar, z * scalar);
    return p;
}

Vector Vector::operator/(double scalar) const {
    Vector p(x / scalar, y / scalar, z / scalar);
    return p;
}

double Vector::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

Vector Vector::normalize() const {
    return (*this / magnitude());
}

Vector Vector::reflect(const Vector &n) const {
    return ((*this) - n * 2 * dot(n));
}

double Vector::dot(const Vector &rhs) const {
    return (x * rhs.x + y * rhs.y + z * rhs.z);
}

Vector Vector::cross(const Vector &rhs) const {
    return Vector(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z,
                  x * rhs.y - y * rhs.x);
}

Point::Point() : Tuple(0.0, 0.0, 0.0, 1.0) {}

Point::Point(double x, double y, double z) : Tuple(x, y, z, 1.0f) {}

Point Point::operator+(const Vector &rhs) const {
    return Point(x + rhs.x, y + rhs.y, z + rhs.z);
}

Point Point::operator-(const Vector &rhs) const {
    return Point(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector Point::operator-(const Point &rhs) const {
    return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
}

Color::Color() : r(0), g(0), b(0) {}

Color::Color(ColorName name) {
    switch (name) {
    case Aqua:
        r = 0;
        g = 1;
        b = 1;
        break;
    case Black:
        r = 0;
        g = 0;
        b = 0;
        break;
    case Blue:
        r = 0;
        g = 0;
        b = 1;
        break;
    case Fuchsia:
        r = 1;
        g = 0;
        b = 1;
        break;
    case Gray:
        r = 0.5;
        g = 0.5;
        b = 0.5;
        break;
    case Green:
        r = 0;
        g = 0.5;
        b = 0;
        break;
    case Lime:
        r = 0;
        g = 1;
        b = 0;
        break;
    case Maroon:
        r = 0.5;
        g = 0;
        b = 0;
        break;
    case Navy:
        r = 0;
        g = 0;
        b = 0.5;
        break;
    case Olive:
        r = 0.5;
        g = 0.5;
        b = 0;
        break;
    case Purple:
        r = 0.5;
        g = 0;
        b = 0.5;
        break;
    case Red:
        r = 1;
        g = 0;
        b = 0;
        break;
    case Silver:
        r = 0;
        g = 0.75;
        b = 0.75;
        break;
    case Teal:
        r = 0;
        g = 0.5;
        b = 0.5;
        break;
    case White:
        r = 1;
        g = 1;
        b = 1;
        break;
    case Yellow:
        r = 1;
        g = 1;
        b = 0;
        break;
    }
}

Color::Color(double r, double g, double b) : r(r), g(g), b(b) {}

Color Color::operator-(const Color &rhs) const {
    return Color(r - rhs.r, g - rhs.g, b - rhs.b);
}

Color Color::operator*(double scalar) const {
    return Color(r * scalar, g * scalar, b * scalar);
}

Color Color::operator/(double scalar) const {
    return Color(r / scalar, g / scalar, b / scalar);
}

Color Color::operator*(const Color &rhs) const {
    return Color(r * rhs.r, g * rhs.g, b * rhs.b);
}

Color Color::operator+(const Color &rhs) const {
    return Color(r + rhs.r, g + rhs.g, b + rhs.b);
}

Color &Color::operator+=(const Color &rhs) {
    r += rhs.r;
    g += rhs.g;
    b += rhs.b;
    return *this;
}

bool Color::operator==(const Color &rhs) const {
    return (almostEqual(r, rhs.r) && almostEqual(g, rhs.g) &&
            almostEqual(b, rhs.b));
}

uint32_t Color::toRgba() const {
    uint8_t rc = std::min(std::max(r * 255, 0.0), 255.0);
    uint8_t gc = std::min(std::max(g * 255, 0.0), 255.0);
    uint8_t bc = std::min(std::max(b * 255, 0.0), 255.0);

    return (rc << 16 | gc << 8 | bc);
}

std::ostream &operator<<(std::ostream &os, const Tuple &p) {
    os << "(" << p.x << ", " << p.y << ", " << p.z << ", " << p.w << ")";
    return os;
}

std::ostream &operator<<(std::ostream &os, const Point &p) {
    os << "Point(" << p.x << ", " << p.y << ", " << p.z << ")";
    return os;
}

std::ostream &operator<<(std::ostream &os, const Color &p) {
    os << "Color(" << p.r << ", " << p.g << ", " << p.b << ")";
    return os;
}

std::ostream &operator<<(std::ostream &os, const Vector &p) {
    os << "Vector(" << p.x << ", " << p.y << ", " << p.z << ")";
    return os;
}
