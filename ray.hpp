#pragma once

#include "tuple.hpp"

class Ray {
public:
    Ray(Point origin, Vector direction)
        : origin(origin), direction(direction) {}

    Point position(double t) const {
        return origin + direction * t;
    }

    Point origin;
    Vector direction;
};
