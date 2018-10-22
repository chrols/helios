#include "world.hpp"

#include <algorithm>

World::World() {}

std::vector<Intersection> World::intersect(const Ray &ray) const {
    std::vector<Intersection> xs;

    for (auto &e : m_object) {
        auto subXs = e.intersect(ray);
        xs.insert(xs.end(), subXs.begin(), subXs.end());
    }

    std::sort(xs.begin(), xs.end(),
              [](auto &e1, auto &e2) { return e1.t < e2.t; });

    return xs;
}

void World::addLight(const PointLight &light) {
    m_light.push_back(light);
}

void World::addObject(const Sphere &object) {
    m_object.push_back(object);
}

Color World::colorAt(const Ray &ray) const {
    auto xs = intersect(ray);
    if (xs.size() == 0)
        return Color(0, 0, 0);

    for (auto &e : xs) {
        if (e.t >= 0) {
            e.precompute(ray);
            return _shadeHit(e);
        }
    }

    return Color(0, 0, 0);
}

bool World::isShadowed(const Point &point) const {
    if (m_light.size() < 1)
        return false;

    auto v = m_light[0].position - point;
    auto distance = v.magnitude();
    auto direction = v.normalize();

    Ray r(point, direction);
    auto xs = intersect(r);
    auto hit = Intersection::hit(xs);

    return (hit && hit->t < distance);
}

World World::testWorld() {
    PointLight light(Point(-10, 10, -10), Color(1, 1, 1));
    Sphere s1, s2;
    s1.material.color = Color(0.8, 1.0, 0.6);
    s1.material.diffuse = 0.7;
    s1.material.specular = 0.2;
    s2.transform = Matrix<double>::scalingMatrix(0.5, 0.5, 0.5);

    World w;
    w.addLight(light);
    w.addObject(s1);
    w.addObject(s2);
    return w;
}

Color World::_shadeHit(const Intersection &hit) const {
    return Phong::lighting(hit.object->material, m_light[0], hit.point,
                           hit.eyeVector, hit.normalVector,
                           isShadowed(hit.point));
}
