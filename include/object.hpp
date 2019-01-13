#pragma once

#include "common.hpp"
#include "intersection.hpp"
#include "material.hpp"
#include "matrix.hpp"
#include "ray.hpp"
#include <vector>

class Object {
public:
    Object() : transform(Matrix::identity(4)) {}

    virtual std::vector<Intersection> localIntersect(const Ray &r) const = 0;
    virtual Optional<Vector> localNormal(const Point &p) const = 0;

    std::vector<Intersection> intersect(const Ray &r) const;
    Optional<Vector> normal(const Point &p) const;

    void move(const Vector &v);
    void move(double x, double y, double z);

    void scale(double w, double h, double d);

    void rotateX(double rad);
    void rotateY(double rad);
    void rotateZ(double rad);

    Matrix transform;
    mutable Optional<Matrix> inverse;
    Material material;
};
