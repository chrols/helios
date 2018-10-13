#include "light.hpp"

#include <cmath>

Color lighting(const Material &material, const Light &light, const Point &point,
               const Vector &eyev, const Vector &normalv) {
    auto effectiveColor = material.color * light.intensity;
    auto lightv = (light.position - point).normalize();
    auto ambient = effectiveColor * material.ambient;
    auto lightDotNormal = lightv.dot(normalv);

    Color diffuse, specular;
    if (lightDotNormal < 0) {
        diffuse = Color();
        specular = Color();
    } else {
        diffuse = effectiveColor * material.diffuse * lightDotNormal;

        auto rlightv = -lightv;
        auto reflectv = rlightv.reflect(normalv);
        auto reflectDotEye = std::pow(reflectv.dot(eyev), material.shininess);

        if (reflectDotEye <= 0) {
            specular = Color();
        } else {
            specular = light.intensity * material.specular * reflectDotEye;
        }
    }

    return (ambient + diffuse + specular);
}
