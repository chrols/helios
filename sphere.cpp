#include "sphere.hpp"
#include <cmath>

Sphere::Sphere() {}

std::vector<Intersection> Sphere::intersect(const Ray &r) const {
    std::vector<Intersection> xs;
    if (!transform.hasInverse())
        return xs;

    auto tr = r.transform(transform.inverse());
    auto sphereToRay = tr.origin - Point(0, 0, 0);
    auto a = tr.direction.dot(tr.direction);
    auto b = 2 * tr.direction.dot(sphereToRay);
    auto c = sphereToRay.dot(sphereToRay) - 1;
    auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return std::vector<Intersection>();

    auto t1 = (-b - std::sqrt(discriminant)) / (2 * a);
    auto t2 = (-b + std::sqrt(discriminant)) / (2 * a);

    if (t1 > t2)
        std::swap(t1, t2);

    xs.push_back(Intersection(t1, this));
    xs.push_back(Intersection(t2, this));

    return xs;
}
