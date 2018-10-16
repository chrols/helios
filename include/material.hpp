#pragma once

#include "tuple.hpp"

class Material {
public:
    Material();

    bool operator==(const Material &rhs) const;

    Color color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
};
