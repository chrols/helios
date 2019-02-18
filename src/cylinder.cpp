#include "cylinder.hpp"
#include "common.hpp"

#include <limits>

Cylinder::Cylinder()
    : m_minimum(-std::numeric_limits<double>::infinity()),
      m_maximum(std::numeric_limits<double>::infinity()) {}

std::vector<Intersection> Cylinder::localIntersect(const Ray &r) const {
    auto a = r.direction.x * r.direction.x + r.direction.z * r.direction.z;

    if (almostEqual(a, 0.0))
        return {};

    auto b = 2 * r.origin.x * r.direction.x + 2 * r.origin.z * r.direction.z;
    auto c = r.origin.x * r.origin.x + r.origin.z * r.origin.z - 1;
    auto disc = b * b - 4 * a * c;

    if (disc < 0)
        return {};

    auto t0 = (-b - std::sqrt(disc)) / (2 * a);
    auto t1 = (-b + std::sqrt(disc)) / (2 * a);

    if (t0 > t1)
        std::swap(t0, t1);

    auto xs = std::vector<Intersection>();

    auto y0 = r.origin.y + t0 * r.direction.y;

    if (m_minimum < y0 and y0 < m_maximum) {
        xs.emplace_back(Intersection(t0, this));
    }

    auto y1 = r.origin.y + t1 * r.direction.y;

    if (m_minimum < y1 and y1 < m_maximum) {
        xs.emplace_back(Intersection(t1, this));
    }

    return xs;
}

Optional<Vector> Cylinder::localNormal(const Point &p) const {
    return Vector(p.x, 0, p.z);
}

double Cylinder::minimum() const {
    return m_minimum;
}

void Cylinder::setMinimum(double minimum) {
    m_minimum = minimum;
}

double Cylinder::maximum() const {
    return m_maximum;
}

void Cylinder::setMaximum(double maximum) {
    m_maximum = maximum;
}
