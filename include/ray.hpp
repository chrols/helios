#pragma once

#include "matrix.hpp"
#include "tuple.hpp"

class Ray {
public:
    Ray(Point origin, Vector direction)
        : origin(origin), direction(direction) {}

    Point position(double t) const {
        return origin + direction * t;
    }

    Ray transform(Matrix tm) const {
        return Ray(tm * origin, tm * direction);
    }

    Point origin;
    Vector direction;
};
