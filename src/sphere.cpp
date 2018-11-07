#include "sphere.hpp"
#include <cmath>

Sphere::Sphere() {}

std::vector<Intersection> Sphere::localIntersect(const Ray &r) const {
    auto sphereToRay = r.origin - Point(0, 0, 0);
    auto a = r.direction.dot(r.direction);
    auto b = 2 * r.direction.dot(sphereToRay);
    auto c = sphereToRay.dot(sphereToRay) - 1;
    auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return {};

    auto t1 = (-b - std::sqrt(discriminant)) / (2 * a);
    auto t2 = (-b + std::sqrt(discriminant)) / (2 * a);

    if (t1 > t2)
        std::swap(t1, t2);

    std::vector<Intersection> xs;
    xs.push_back(Intersection(t1, this));
    xs.push_back(Intersection(t2, this));
    return xs;
}

Optional<Vector> Sphere::localNormal(const Point &p) const {
    return (p - Point(0, 0, 0));
}

Sphere Sphere::glassSphere() {
    Sphere s;
    s.material.color = Color::Black;
    s.material.transparency = 1.0;
    s.material.refraction = 1.5;
    return s;
}
