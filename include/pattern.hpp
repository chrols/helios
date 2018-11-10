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
    Matrix transform;
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

class GradientPattern : public Pattern {
public:
    GradientPattern(Color a, Color b);
    Color patternAt(const Point &point) const override;

private:
    Color m_a, m_b;
};

class RingPattern : public Pattern {
public:
    RingPattern(Color a, Color b);
    Color patternAt(const Point &point) const override;

private:
    Color m_a, m_b;
};

class CheckersPattern : public Pattern {
public:
    CheckersPattern(Color a, Color b);
    Color patternAt(const Point &point) const override;

private:
    Color m_a, m_b;
};
