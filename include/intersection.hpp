#pragma once

#include "common.hpp"
#include "ray.hpp"
#include "tuple.hpp"

#include <memory>
#include <vector>

class World;
class Object;

class Intersection {
public:
    Intersection(double t, std::shared_ptr<const Object> object);
    Intersection(const Intersection &i);

    void precompute(const Ray &ray, const std::vector<Intersection> &xs =
                                        std::vector<Intersection>());

    double reflectance() const;

    Intersection &operator=(const Intersection &rhs);
    bool operator==(const Intersection &rhs) const;
    static Optional<Intersection>
    hit(const std::vector<Intersection> &intersections);

    double t;
    std::shared_ptr<const Object> object;
    Point point;
    Vector eyeVector;
    Vector normalVector;
    Vector reflectVector;
    bool inside;
    double n1;
    double n2;
    Point underPoint;
};
