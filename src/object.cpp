#include "object.hpp"

Object::Object() : m_transform(Matrix::identity(4)) {}

std::vector<Intersection> Object::intersect(const Ray &r) const {
    if (!m_transform.hasInverse())
        return {};
    auto localRay = r.transform(m_transform.inverse());
    return localIntersect(localRay);
}

Optional<Vector> Object::normal(const Point &p) const {
    if (!m_transform.hasInverse())
        return {};

    auto inverse = m_transform.inverse();
    auto localPoint = inverse * p;
    auto potentialLocalNormal = localNormal(localPoint);
    if (!potentialLocalNormal) {
        std::cerr << "No potential!" << std::endl;
        return {};
    }
    auto worldNormal = inverse.transpose() * (*potentialLocalNormal);
    return worldNormal.normalize();
}

void Object::move(const Vector &v) {
    m_transform *= Matrix::translationMatrix(v.x, v.y, v.z);
}

void Object::move(double x, double y, double z) {
    m_transform *= Matrix::translationMatrix(x, y, z);
}

void Object::scale(double w, double h, double d) {
    m_transform *= Matrix::scalingMatrix(w, h, d);
}

void Object::rotateX(double rad) {
    m_transform *= Matrix::rotationMatrixX(rad);
}

void Object::rotateY(double rad) {
    m_transform *= Matrix::rotationMatrixY(rad);
}

void Object::rotateZ(double rad) {
    m_transform *= Matrix::rotationMatrixZ(rad);
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
