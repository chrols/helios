#pragma once

#include "object.hpp"

class Cylinder : public Object {
public:
    Cylinder();
    virtual ~Cylinder() = default;
    std::vector<Intersection> localIntersect(const Ray &r) const override;
    Optional<Vector> localNormal(const Point &p) const override;

    double minimum() const;
    void setMinimum(double minimum);

    double maximum() const;
    void setMaximum(double maximum);

private:
    double m_minimum;
    double m_maximum;
};
