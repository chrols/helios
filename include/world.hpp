#pragma once

#include "intersection.hpp"
#include "light.hpp"
#include "object.hpp"
#include "ray.hpp"
#include "sphere.hpp"

class World {
public:
    World();
    std::vector<Intersection> intersect(const Ray &ray) const;
    void addLight(const Light &light);
    void addObject(const Sphere &object);
    Color colorAt(const Ray &ray) const;
    bool isShadowed(const Point &point) const;

    static World testWorld();

private:
    Color _shadeHit(const Intersection &hit) const;

    std::vector<Light> m_light;
    std::vector<Sphere> m_object;
};
