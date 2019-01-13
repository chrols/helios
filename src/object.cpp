#include "object.hpp"

std::vector<Intersection> Object::intersect(const Ray &r) const {
    if (inverse) {
        auto localRay = r.transform(*inverse);
        return localIntersect(localRay);
    } else if (!transform.hasInverse()) {
        return {};
    } else {
        inverse = std::experimental::make_optional(transform.inverse());
        auto localRay = r.transform(*inverse);
        return localIntersect(localRay);
    }
}

Optional<Vector> Object::normal(const Point &p) const {
    if (!transform.hasInverse()) {
        std::cerr << "No INVERSE!" << std::endl;
        return {};
    }

    auto inverse = transform.inverse();
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
    transform *= Matrix::translationMatrix(v.x, v.y, v.z);
}

void Object::move(double x, double y, double z) {
    transform *= Matrix::translationMatrix(x, y, z);
}

void Object::scale(double w, double h, double d) {
    transform *= Matrix::scalingMatrix(w, h, d);
}

void Object::rotateX(double rad) {
    transform *= Matrix::rotationMatrixX(rad);
}

void Object::rotateY(double rad) {
    transform *= Matrix::rotationMatrixY(rad);
}

void Object::rotateZ(double rad) {
    transform *= Matrix::rotationMatrixZ(rad);
}
