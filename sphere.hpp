#pragma once

#include "intersection.hpp"
#include "object.hpp"
#include "ray.hpp"
#include <vector>

class Sphere : public Object {
public:
    Sphere();
    std::vector<Intersection> intersect(const Ray &r) const override;
};
