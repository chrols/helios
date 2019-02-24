#pragma once

#include "intersection.hpp"
#include "light.hpp"
#include "object.hpp"
#include "ray.hpp"
#include "sphere.hpp"

#include <memory>

class World {
public:
    World();
    std::vector<Intersection> intersect(const Ray &ray) const;
    void addLight(const Light &light);
    void addObject(std::shared_ptr<Object> object);

    Color colorAt(const Ray &ray,
                  unsigned remaining = DEFAULT_RECUR_LIMIT) const;
    Color reflectedColor(const Intersection &hit,
                         unsigned remaining = DEFAULT_RECUR_LIMIT) const;
    Color refractedColor(const Intersection &hit,
                         unsigned remaining = DEFAULT_RECUR_LIMIT) const;
    bool isShadowed(const Point &point) const;

    void clearObjects();

    std::shared_ptr<Object> firstObject() const;

    static World testWorld();

    static constexpr unsigned DEFAULT_RECUR_LIMIT = 5;

public: // FIXME Rewrite test?
    Color _shadeHit(const Intersection &hit,
                    unsigned remaining = DEFAULT_RECUR_LIMIT) const;

    std::vector<Light> m_light;
    std::vector<std::shared_ptr<Object>> m_object;
};
