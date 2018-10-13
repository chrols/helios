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
    return Vector(y * rhs.z + z * rhs.y, z * rhs.x + x * rhs.z,
                  x * rhs.y + y * rhs.x);
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

Color::Color(double r, double g, double b) : r(r), g(g), b(b) {}

Color Color::operator*(double scalar) const {
    return Color(r * scalar, g * scalar, b * scalar);
}

Color Color::operator*(const Color &rhs) const {
    return Color(r * rhs.r, g * rhs.g, b * rhs.b);
}

Color Color::operator+(const Color &rhs) const {
    return Color(r + rhs.r, g + rhs.g, b + rhs.b);
}
bool Color::operator==(const Color &rhs) const {
    return (almostEqual(r, rhs.r) && almostEqual(g, rhs.g) &&
            almostEqual(b, rhs.b));
}

std::ostream &operator<<(std::ostream &os, const Tuple &p) {
    os << "(" << p.x << ", " << p.y << ", " << p.z << ", " << p.w << ")";
}

std::ostream &operator<<(std::ostream &os, const Color &p) {
    os << "(" << p.r << ", " << p.g << ", " << p.b << ")";
}
