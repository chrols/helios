#include "intersection.hpp"

#include <algorithm>
#include <iostream>

#include "object.hpp"
#include "ray.hpp"

Intersection::Intersection(double t, const Object *object)
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

    std::vector<const Object *> containers;

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
