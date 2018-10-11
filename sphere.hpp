#pragma once

#include "object.hpp"
#include "ray.hpp"
#include <vector>

class Sphere : public Object {
public:
    Sphere();
    Intersections intersect(const Ray &r) const override;
};
