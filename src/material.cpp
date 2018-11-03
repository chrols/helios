#include "material.hpp"

#include "common.hpp"

Material::Material()
    : color(Color::White), pattern(nullptr), ambient(0.1), diffuse(0.9),
      specular(0.9), shininess(200.0) {}

bool Material::operator==(const Material &rhs) const {
    // FIXME Deal with patterns
    return (color == rhs.color && almostEqual(ambient, rhs.ambient) &&
            almostEqual(diffuse, rhs.diffuse) &&
            almostEqual(specular, rhs.specular) &&
            almostEqual(shininess, rhs.shininess));
}
