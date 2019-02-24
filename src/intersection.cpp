#include "intersection.hpp"

#include <algorithm>
#include <iostream>

#include "object.hpp"
#include "ray.hpp"

Intersection::Intersection(double t, std::shared_ptr<const Object> object)
    : t(t), object(object) {}

Intersection::Intersection(const Intersection &i) : t(i.t), object(i.object) {}

void Intersection::precompute(const Ray &ray,
                              const std::vector<Intersection> &xs) {
    point = ray.position(t);
    eyeVector = -ray.direction;
    normalVector = object->normal(point).value_or(Vector());
    inside = (normalVector.dot(eyeVector) < 0);

    if (inside)
        normalVector = -normalVector;

    underPoint = point - normalVector * 0.000000001;
    point = point + normalVector * 0.000000001;

    reflectVector = ray.direction.reflect(normalVector);

    std::vector<std::shared_ptr<const Object>> containers;

    for (auto &e : xs) {
        if (e == *this) {
            n1 = containers.empty() ? 1.0
                                    : containers.back()->material.refraction;
        }

        auto it = std::find(containers.begin(), containers.end(), e.object);

        if (it != containers.end()) {
            containers.erase(it);
        } else {
            containers.push_back(e.object);
        }

        if (e == *this) {
            n2 = containers.empty() ? 1.0
                                    : containers.back()->material.refraction;
            break;
        }
    }
}

double Intersection::reflectance() const {
    // Schlick

    auto cos = eyeVector.dot(normalVector);

    if (n1 > n2) {
        auto n = n1 / n2;
        auto sin2t = n * n * (1.0 - cos * cos);
        if (sin2t > 1.0)
            return 1.0;
        cos = std::sqrt(1.0 - sin2t);
    }

    auto r0 = (n1 - n2) / (n1 + n2);
    r0 *= r0;
    return r0 + (1 - r0) * std::pow((1 - cos), 5.0);
}

Intersection &Intersection::operator=(const Intersection &rhs) {
    t = rhs.t;
    object = rhs.object;
    return (*this);
}

bool Intersection::operator==(const Intersection &rhs) const {
    return (almostEqual(t, rhs.t) && object == rhs.object);
}

Optional<Intersection>
Intersection::hit(const std::vector<Intersection> &intersections) {
    Intersection i(999, nullptr);

    for (auto &e : intersections) {
        if (e.t >= 0 && e.t < i.t) {
            i = e;
        }
    }

    if (i.t != 999) {
        return i;
    }
    return {};
}
