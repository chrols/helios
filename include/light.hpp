#pragma once

#include "material.hpp"
#include "tuple.hpp"

class PointLight {
public:
    PointLight(const Point &position, const Color &intensity)
        : position(position), intensity(intensity) {}

    Point position;
    Color intensity;
};

using Light = PointLight;

Color lighting(const Material &material, const Light &light,
               const Point &position, const Vector &eyev,
               const Vector &normalv);
