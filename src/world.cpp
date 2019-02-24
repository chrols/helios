#include "world.hpp"

#include <algorithm>

World::World() {}

std::vector<Intersection> World::intersect(const Ray &ray) const {
    std::vector<Intersection> xs;

    for (auto &e : m_object) {
        auto subXs = e->intersect(ray);
        xs.insert(xs.end(), subXs.begin(), subXs.end());
    }

    std::sort(xs.begin(), xs.end(),
              [](auto &e1, auto &e2) { return e1.t < e2.t; });

    return xs;
}

void World::addLight(const PointLight &light) {
    m_light.push_back(light);
}

void World::addObject(std::shared_ptr<Object> object) {
    m_object.push_back(object);
}

// FIXME Move to intersection?
Color World::colorAt(const Ray &ray, unsigned remaining) const {
    auto xs = intersect(ray);
    if (xs.size() == 0)
        return Color(0, 0, 0);

    for (auto &e : xs) {
        if (e.t >= 0) {
            e.precompute(ray, xs);
            return _shadeHit(e, remaining);
        }
    }

    return Color(0, 0, 0);
}

// FIXME Move to intersection?
Color World::reflectedColor(const Intersection &hit, unsigned remaining) const {

    if (remaining == 0 || (!hit.object) ||
        hit.object->material.reflective == 0) {
        return Color::Black;
    }

    // std::cerr << "ACTUAL" << remaining << std::endl;

    Ray reflectRay(hit.point, hit.reflectVector);
    auto color = colorAt(reflectRay, --remaining);
    return color * hit.object->material.reflective;
}

Color World::refractedColor(const Intersection &hit, unsigned remaining) const {
    if (remaining == 0)
        return Color::Black;

    // if (!hit.object)
    //     return Color::Black;

    if (hit.object->material.transparency == 0)
        return Color::Black;

    double nRatio = hit.n1 / hit.n2;
    double cosI = hit.eyeVector.dot(hit.normalVector);
    double sin2t = nRatio * nRatio * (1 - cosI * cosI);

    if (sin2t > 1.0)
        return Color::Black;

    double cosT = std::sqrt(1.0 - sin2t);

    auto direction =
        hit.normalVector * (nRatio * cosI - cosT) - hit.eyeVector * nRatio;

    Ray refractRay(hit.underPoint, direction);

    return colorAt(refractRay, remaining - 1) *
           hit.object->material.transparency;
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

void World::clearObjects() {
    m_object.clear();
}

std::shared_ptr<Object> World::firstObject() const {
    return m_object[0];
}

World World::testWorld() {
    PointLight light(Point(-10, 10, -10), Color(1, 1, 1));

    auto s1 = std::make_shared<Sphere>();
    s1->material.color = Color(0.8, 1.0, 0.6);
    s1->material.diffuse = 0.7;
    s1->material.specular = 0.2;

    auto s2 = std::make_shared<Sphere>();
    s2->setTransform(Matrix::scalingMatrix(0.5, 0.5, 0.5));

    World w;
    w.addLight(light);
    w.addObject(s1);
    w.addObject(s2);

    return w;
}

Color World::_shadeHit(const Intersection &hit, unsigned remaining) const {
    auto surface = Phong::lighting(hit.object->material, m_light[0], hit.point,
                                   hit.eyeVector, hit.normalVector,
                                   isShadowed(hit.point), *hit.object);

    auto reflected = reflectedColor(hit, remaining);

    auto refracted = refractedColor(hit, remaining);

    auto material = hit.object->material;

    if (material.reflective > 0 && material.transparency > 0) {
        double reflectance = hit.reflectance();
        return (surface + reflected * reflectance +
                refracted * (1 - reflectance));
    } else {
        return (surface + reflected + refracted);
    }
}
