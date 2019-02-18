#pragma once

#include "common.hpp"
#include "intersection.hpp"
#include "material.hpp"
#include "matrix.hpp"
#include "ray.hpp"

#include <memory>
#include <vector>

class Object : public std::enable_shared_from_this<Object> {
public:
    Object();

    virtual std::vector<Intersection> localIntersect(const Ray &r) const = 0;
    virtual Optional<Vector> localNormal(const Point &p) const = 0;

    std::vector<Intersection> intersect(const Ray &r) const;
    Optional<Vector> normal(const Point &p) const;

    std::shared_ptr<Object> parent() const;
    void setParent(std::shared_ptr<Object> parent);

    Point worldToObject(const Point &worldPoint) const;
    Vector normalToWorld(const Vector &normal) const;

    void move(const Vector &v);
    void move(double x, double y, double z);

    void scale(double w, double h, double d);

    void rotateX(double rad);
    void rotateY(double rad);
    void rotateZ(double rad);

    Matrix transform() const;
    Matrix transformInverse() const;
    void setTransform(const Matrix &transform);

    Material material;

protected:
    Matrix m_transform;
    Matrix m_scale;
    Matrix m_rotation;
    Matrix m_translation;
    std::weak_ptr<Object> m_parent;
};
