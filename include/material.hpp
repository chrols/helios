#pragma once

#include "common.hpp"
#include "pattern.hpp"
#include "tuple.hpp"

class Material {
public:
    Material();

    bool operator==(const Material &rhs) const;

    Color color;
    Pattern *pattern;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
    double reflective;
};
