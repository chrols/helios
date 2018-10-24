#pragma once

#include "common.hpp"
#include "intersection.hpp"
#include "material.hpp"
#include "matrix.hpp"
#include "ray.hpp"
#include <vector>

class Object {
public:
    Object() : transform(Matrix<double>::identity(4)) {}

    void setTransform(const Matrix<double> &transform) {
        this->transform = transform;
    }

    virtual std::vector<Intersection> localIntersect(const Ray &r) const = 0;
    virtual Optional<Vector> localNormal(const Point &p) const = 0;

    std::vector<Intersection> intersect(const Ray &r) const {
        if (!transform.hasInverse())
            return {};

        auto localRay = r.transform(transform.inverse());
        return localIntersect(localRay);
    }

    Optional<Vector> normal(const Point &p) const {
        if (!transform.hasInverse()) {
            std::cerr << "No INVERSE!" << std::endl;
            return {};
        }

        auto inverse = transform.inverse();
        auto localPoint = inverse * p;
        auto potentialLocalNormal = localNormal(localPoint);
        if (!potentialLocalNormal) {
            std::cerr << "No potential!" << std::endl;
            return {};
        }
        auto worldNormal = inverse.transpose() * (*potentialLocalNormal);
        return worldNormal.normalize();
    }

    Matrix<double> transform;
    Material material;
};
