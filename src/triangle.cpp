#include "triangle.hpp"

Triangle::Triangle() : Triangle(Point(), Point(), Point()) {}

Triangle::Triangle(Point p1, Point p2, Point p3) : p1(p1), p2(p2), p3(p3) {
    e1 = p2 - p1;
    e2 = p3 - p1;
    cachedNormal = e2.cross(e1).normalize();
}

std::vector<Intersection> Triangle::localIntersect(const Ray &r) const {
    auto dirCrossE2 = r.direction.cross(e2);
    auto det = e1.dot(dirCrossE2);

    if (almostEqual(std::abs(det), 0.0)) {
        return {};
    }

    auto f = 1.0 / det;

    auto p1ToOrigin = r.origin - p1;
    auto u = f * p1ToOrigin.dot(dirCrossE2);

    if (u < 0 || u > 1) {
        return {};
    }

    auto originCrossE1 = p1ToOrigin.cross(e1);
    auto v = f * r.direction.dot(originCrossE1);

    if (v < 0.0 || (u + v) > 1.0) {
        return {};
    }

    auto t = f * e2.dot(originCrossE1);

    return {Intersection(t, this)};
}

Optional<Vector> Triangle::localNormal(const Point &p) const {
    return cachedNormal;
}
