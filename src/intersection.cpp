#include "intersection.hpp"

#include "object.hpp"
#include "ray.hpp"
#include <iostream>

Intersection::Intersection(double t, const Object *object)
    : t(t), object(object) {}

Intersection::Intersection(const Intersection &i) : t(i.t), object(i.object) {}

void Intersection::precompute(const Ray &ray) {
    point = ray.position(t);
    eyeVector = -ray.direction;
    normalVector = object->normal(point).value_or(Vector());
    inside = (normalVector.dot(eyeVector) < 0);

    if (inside)
        normalVector = -normalVector;

    point = point + normalVector * 0.000001;
}

Intersection &Intersection::operator=(const Intersection &rhs) {
    t = rhs.t;
    object = rhs.object;
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
