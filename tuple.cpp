#include "tuple.hpp"

#include <cmath>
#include <limits>

Point::Point(float x, float y, float z) : x(x), y(y), z(z) {}

Point::Point() : Point(0, 0, 0) {}

Point Point::operator-() const {
    Point p(-x, -y, -z);
    return p;
}

Point Point::operator+(const Point &rhs) const {
    Point p;
    p.x = x + rhs.x;
    p.y = y + rhs.y;
    p.z = z + rhs.z;
    return p;
}

Point Point::operator-(const Point &rhs) const {
    Point p;
    p.x = x - rhs.x;
    p.y = y - rhs.y;
    p.z = z - rhs.z;
    return p;
}

Point Point::operator*(double scalar) const {
    Point p(x * scalar, y * scalar, z * scalar);
    return p;
}

Point Point::operator/(double scalar) const {
    Point p(x / scalar, y / scalar, z / scalar);
    return p;
}

bool Point::operator==(const Point &rhs) const {
    if (std::abs(x - rhs.x) > std::numeric_limits<float>::epsilon())
        return false;
    if (std::abs(y - rhs.y) > std::numeric_limits<float>::epsilon())
        return false;
    if (std::abs(z - rhs.z) > std::numeric_limits<float>::epsilon())
        return false;
    return true;
}

double Point::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

Point Point::normal() const {
    return (*this / magnitude());
}

double Point::dot(const Point &rhs) const {
    return (x * rhs.x + y * rhs.y + z * rhs.z);
}

Point Point::cross(const Point &rhs) const {
    return Point(y * rhs.z + z * rhs.y, z * rhs.x + x * rhs.z,
                 x * rhs.y + y * rhs.x);
}

std::ostream &operator<<(std::ostream &os, const Point &p) {
    os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
}
