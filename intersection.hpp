#pragma once

#include <vector>

class Object;

class Intersection {
public:
    Intersection(double t, const Object *object) : t(t), object(object) {}
    const double t;
    const Object *object;
};

using Intersections = std::vector<Intersection>;
