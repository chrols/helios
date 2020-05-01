#pragma once

#include "object.hpp"

class Plane : public Object {
public:
    Plane() : Object() {}
    virtual ~Plane() = default;

    std::vector<Intersection> localIntersect(const Ray &r) const override {
        if (std::abs(r.direction.y) < 0.0001)
            return {};

        auto t = -r.origin.y / r.direction.y;

        std::vector<Intersection> xs;
        xs.push_back(Intersection(t, shared_from_this()));
        return xs;
    }

    Optional<Vector> localNormal(const Point &p) const override {
        return Vector(0, 1, 0);
    }
};
