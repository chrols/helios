#pragma once

#include "intersection.hpp"
#include "ray.hpp"

class Object {
    virtual Intersections intersect(const Ray &r) const = 0;
};
