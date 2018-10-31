#pragma once

#include "tuple.hpp"

#include <cmath>

class Pattern {
public:
    virtual Color stripeAt(const Point &point) const = 0;
};

class StripePattern : public Pattern {
public:
    StripePattern(Color a, Color b) : m_a(a), m_b(b) {}
    Color stripeAt(const Point &point) const override {
        Color a = m_a;
        Color b = m_b;

        if (int(std::floor(point.x)) % 2 == 0) {
            std::cerr << "A" << std::endl;
            return a;
        } else {
            return b;
        }
    }

private:
    Color m_a, m_b;
};
