#include "object.hpp"

#include <memory>
#include <vector>

class Group : public Object {
public:
    Group();
    virtual ~Group() = default;

    std::vector<Intersection> localIntersect(const Ray &r) const override;
    Optional<Vector> localNormal(const Point &p) const override;

    void addChild(std::shared_ptr<Object> child);
    std::vector<std::shared_ptr<Object>> children() const;

    unsigned size() const;

private:
    std::vector<std::shared_ptr<Object>> m_children;
};
