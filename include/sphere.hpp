#pragma once

#include "intersection.hpp"
#include "object.hpp"
#include "ray.hpp"
#include <vector>

class Sphere : public Object {
public:
    Sphere();
    std::vector<Intersection> localIntersect(const Ray &r) const override;
    Optional<Vector> localNormal(const Point &p) const override;
};
