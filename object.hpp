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

    virtual std::vector<Intersection> intersect(const Ray &r) const = 0;
    virtual Optional<Vector> normal(const Point &p) const = 0;

    Matrix<double> transform;
    Material material;
};
