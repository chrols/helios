#pragma once

#include <cmath>

#include "matrix.hpp"
#include "tuple.hpp"

class Object;

class Pattern {
public:
    Pattern();
    virtual Color patternAt(const Point &point) const = 0;
    Color patternAtObject(const Point &point, const Object &object) const;
    Matrix<double> transform;
};

class TestPattern : public Pattern {
    Color patternAt(const Point &point) const override;
};

class StripePattern : public Pattern {
public:
    StripePattern(Color a, Color b);
    Color patternAt(const Point &point) const override;

private:
    Color m_a, m_b;
};
