#include "light.hpp"

#include <cmath>

Color Phong::lighting(const Material &material, const Light &light,
                      const Point &point, const Vector &eyev,
                      const Vector &normalv, bool inShadow) {
    auto effectiveColor = material.color * light.intensity;
    auto ambient = effectiveColor * material.ambient;

    if (inShadow)
        return ambient;

    auto lightv = (light.position - point).normalize();
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
