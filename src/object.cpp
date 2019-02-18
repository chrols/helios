#include "object.hpp"

Object::Object()
    : m_transform(Matrix::identity(4)), m_scale(Matrix::identity(4)),
      m_rotation(Matrix::identity(4)), m_translation(Matrix::identity(4)) {}

std::vector<Intersection> Object::intersect(const Ray &r) const {
    if (!m_transform.hasInverse())
        return {};
    auto localRay = r.transform(m_transform.inverse());
    return localIntersect(localRay);
}

Optional<Vector> Object::normal(const Point &p) const {
    if (!m_transform.hasInverse())
        return {};

    auto localPoint = worldToObject(p);
    auto normal = localNormal(localPoint);

    if (normal) {
        return normalToWorld(*normal);
    } else {
        return {};
    }
}

std::shared_ptr<Object> Object::parent() const {
    return m_parent.lock();
}

void Object::setParent(std::shared_ptr<Object> parent) {
    m_parent = parent;
}

Point Object::worldToObject(const Point &worldPoint) const {
    Point p = worldPoint;

    auto parent = m_parent.lock();

    if (parent) {
        p = parent->worldToObject(p);
    }

    return (m_transform.inverse() * p);
}

/**
 * Convert normal vector to world space from object space
 */
Vector Object::normalToWorld(const Vector &normal) const {
    auto worldNormal = m_transform.inverse().transpose() * normal;
    worldNormal = worldNormal.normalize();

    auto parent = m_parent.lock();

    // if (parent) {
    //     worldNormal = parent->normalToWorld(worldNormal);
    // }

    return worldNormal;
}

void Object::move(const Vector &v) {
    m_transform *= Matrix::translationMatrix(v.x, v.y, v.z);
}

void Object::move(double x, double y, double z) {
    m_translation[0][3] += x;
    m_translation[1][3] += y;
    m_translation[2][3] += z;
    m_transform = m_scale * m_rotation * m_translation;
}

void Object::scale(double w, double h, double d) {
    m_scale[0][0] *= w;
    m_scale[1][1] *= h;
    m_scale[2][2] *= d;
    m_transform = m_scale * m_rotation * m_translation;
}

void Object::rotateX(double rad) {
    m_rotation *= Matrix::rotationMatrixX(rad);
    m_transform = m_scale * m_rotation * m_translation;
}

void Object::rotateY(double rad) {
    m_rotation *= Matrix::rotationMatrixY(rad);
    m_transform = m_scale * m_rotation * m_translation;
}

void Object::rotateZ(double rad) {
    m_rotation *= Matrix::rotationMatrixZ(rad);
    m_transform = m_scale * m_rotation * m_translation;
}

Matrix Object::transform() const {
    return m_transform;
}

Matrix Object::transformInverse() const {
    return m_transform.inverse();
}

void Object::setTransform(const Matrix &transform) {
    m_transform = transform;
}
