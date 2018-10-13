#pragma once

#include "common.hpp"
#include <experimental/optional>
#include <vector>

class Object;

class Intersection {
public:
    Intersection(double t, const Object *object);
    Intersection(const Intersection &i);
    double t;
    const Object *object;
    Intersection &operator=(const Intersection &rhs);
    bool operator==(const Intersection &rhs) const;
    static Optional<Intersection> hit(std::vector<Intersection> intersections);
};

// using Intersections = std::vector<Intersection>;
