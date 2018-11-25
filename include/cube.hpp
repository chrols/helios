#pragma once

#include "object.hpp"

class Cube : public Object {
public:
    Cube();
    std::vector<Intersection> localIntersect(const Ray &r) const override;
    Optional<Vector> localNormal(const Point &p) const override;

private:
    std::pair<double, double> _checkAxis(double origin, double direction) const;
};
