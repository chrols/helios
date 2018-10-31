#pragma once

#include "pattern.hpp"
#include "tuple.hpp"

class Material {
public:
    Material();

    bool operator==(const Material &rhs) const;

    Color color;
    StripePattern pattern;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
};
