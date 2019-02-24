#include "cube.hpp"

Cube::Cube() {}

std::vector<Intersection> Cube::localIntersect(const Ray &r) const {
    auto pairX = _checkAxis(r.origin.x, r.direction.x);
    auto pairY = _checkAxis(r.origin.y, r.direction.y);
    auto pairZ = _checkAxis(r.origin.z, r.direction.z);

    auto tmin = std::max(pairX.first, std::max(pairY.first, pairZ.first));
    auto tmax = std::min(pairX.second, std::min(pairY.second, pairZ.second));

    if (tmin > tmax)
        return {};

    return {Intersection(tmin, shared_from_this()),
            Intersection(tmax, shared_from_this())};
}

Optional<Vector> Cube::localNormal(const Point &p) const {
    auto maxc = std::max(std::abs(p.x), std::max(std::abs(p.y), std::abs(p.z)));

    if (maxc == std::abs(p.x)) {
        return Vector(p.x, 0, 0);
    } else if (maxc == std::abs(p.y)) {
        return Vector(0, p.y, 0);
    }

    return Vector(0, 0, p.z);
}

std::pair<double, double> Cube::_checkAxis(double origin,
                                           double direction) const {

    double tmin, tmax = 0.0;

    if (std::abs(direction) > std::numeric_limits<double>::epsilon()) {
        tmin = (-1 - origin) / direction;
        tmax = (1 - origin) / direction;

        if (tmin > tmax)
            std::swap(tmin, tmax);

    } else {
        tmin = (-1 - origin) * std::numeric_limits<double>::infinity();
        tmax = (1 - origin) * std::numeric_limits<double>::infinity();
    }

    return std::make_pair(tmin, tmax);
}
