#include "object.hpp"

Object::Object() : m_transform(Matrix::identity(4)) {
    _updateInverse();
}

std::vector<Intersection> Object::intersect(const Ray &r) const {
    if (!m_inverse)
        return {};
    auto localRay = r.transform(*m_inverse);
    return localIntersect(localRay);
}

Optional<Vector> Object::normal(const Point &p) const {
    if (!m_inverse)
        return {};

    auto localPoint = *m_inverse * p;
    auto potentialLocalNormal = localNormal(localPoint);
    if (!potentialLocalNormal) {
        std::cerr << "No potential!" << std::endl;
        return {};
    }
    auto worldNormal = m_inverse->transpose() * (*potentialLocalNormal);
    return worldNormal.normalize();
}

void Object::move(const Vector &v) {
    m_transform *= Matrix::translationMatrix(v.x, v.y, v.z);
    _updateInverse();
}

void Object::move(double x, double y, double z) {
    m_transform *= Matrix::translationMatrix(x, y, z);
    _updateInverse();
}

void Object::scale(double w, double h, double d) {
    m_transform *= Matrix::scalingMatrix(w, h, d);
    _updateInverse();
}

void Object::rotateX(double rad) {
    m_transform *= Matrix::rotationMatrixX(rad);
    _updateInverse();
}

void Object::rotateY(double rad) {
    m_transform *= Matrix::rotationMatrixY(rad);
    _updateInverse();
}

void Object::rotateZ(double rad) {
    m_transform *= Matrix::rotationMatrixZ(rad);
    _updateInverse();
}

Matrix Object::transform() const {
    return m_transform;
}

Matrix Object::transformInverse() const {
    return *m_inverse;
}

void Object::setTransform(const Matrix &transform) {
    m_transform = transform;
    _updateInverse();
}

void Object::_updateInverse() {
    if (m_transform.hasInverse()) {
        m_inverse =
            std::make_shared<Matrix>(m_transform.width(), m_transform.height());
        *m_inverse = m_transform.inverse();
    }
}
