#include "group.hpp"

#include <algorithm>
#include <vector>

Group::Group() {}

std::vector<Intersection> Group::localIntersect(const Ray &r) const {
    std::vector<Intersection> xs;

    for (auto &e : m_children) {
        auto subXs = e->intersect(r);
        xs.insert(xs.end(), subXs.begin(), subXs.end());
    }

    std::sort(xs.begin(), xs.end(),
              [](auto &e1, auto &e2) { return e1.t < e2.t; });

    return xs;
}

Optional<Vector> Group::localNormal(const Point &p) const {
    throw std::domain_error("localNormal called on group");
}

void Group::addChild(std::shared_ptr<Object> child) {
    m_children.push_back(child);
    child->setParent(shared_from_this());
}

std::vector<std::shared_ptr<Object>> Group::children() const {
    return m_children;
}

unsigned Group::size() const {
    return m_children.size();
}
