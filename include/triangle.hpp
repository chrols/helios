#pragma once

#include "object.hpp"
#include "tuple.hpp"

class Triangle : public Object {
public:
    Triangle();
    Triangle(Point p1, Point p2, Point p3);
    virtual ~Triangle() = default;

    std::vector<Intersection> localIntersect(const Ray &r) const override;
    Optional<Vector> localNormal(const Point &p) const override;

private:
    Point p1, p2, p3;
    Vector e1, e2;
    Vector cachedNormal;
};
