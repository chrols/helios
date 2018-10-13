#include "intersection.hpp"
#include <iostream>

Intersection::Intersection(double t, const Object *object)
    : t(t), object(object) {}

Intersection::Intersection(const Intersection &i) : t(i.t), object(i.object) {}

Intersection &Intersection::operator=(const Intersection &rhs) {
    t = rhs.t;
    object = rhs.object;
}

bool Intersection::operator==(const Intersection &rhs) const {
    return (almostEqual(t, rhs.t) && object == rhs.object);
}

Optional<Intersection>
Intersection::hit(std::vector<Intersection> intersections) {
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
