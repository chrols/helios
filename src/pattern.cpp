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

GradientPattern::GradientPattern(Color a, Color b) : m_a(a), m_b(b) {}

Color GradientPattern::patternAt(const Point &point) const {
    auto distance = m_b - m_a;
    auto fraction = point.x - std::floor(point.x);
    return m_a + distance * fraction;
}

RingPattern::RingPattern(Color a, Color b) : m_a(a), m_b(b) {}

Color RingPattern::patternAt(const Point &point) const {
    return (int(std::floor(std::sqrt(point.x * point.x + point.z + point.z))) %
                2 ==
            0)
               ? m_a
               : m_b;
}

CheckersPattern::CheckersPattern(Color a, Color b) : m_a(a), m_b(b) {}

Color CheckersPattern::patternAt(const Point &point) const {
    int sum = std::abs(point.x) + std::abs(point.y) + std::abs(point.z);
    return (sum % 2 == 0 ? m_a : m_b);
}
