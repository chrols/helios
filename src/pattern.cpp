#include "pattern.hpp"

#include "object.hpp"

Pattern::Pattern() : transform(Matrix<double>::identity(4)) {}

Color Pattern::patternAtObject(const Point &point, const Object &object) const {
    auto objectPoint = object.transform.inverse() * point;
    auto patternPoint = transform.inverse() * objectPoint;
    return patternAt(patternPoint);
}

Color TestPattern::patternAt(const Point &point) const {
    return Color(point.x, point.y, point.z);
}

StripePattern::StripePattern(Color a, Color b) : m_a(a), m_b(b) {}

Color StripePattern::patternAt(const Point &point) const {
    Color a = m_a;
    Color b = m_b;

    if (int(std::floor(point.x)) % 2 == 0) {
        return a;
    } else {
        return b;
    }
}
