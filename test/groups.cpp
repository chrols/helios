#include "catch.hpp"

#include "group.hpp"
#include "sphere.hpp"

TEST_CASE("Creating a new group") {
    Group g;

    REQUIRE(g.transform() == Matrix::identity(4));
    REQUIRE(g.size() == 0);
}

TEST_CASE("Adding a child to a group") {
    auto g = std::make_shared<Group>();
    auto s = std::make_shared<Sphere>();
    g->addChild(s);

    REQUIRE(g->children()[0].get() == s.get());
    REQUIRE(s->parent().get() == g.get());
}

TEST_CASE("Intersecting a ray with an empty group") {
    Group g;
    Ray r(Point(0, 0, 0), Vector(0, 0, 1));
    auto xs = g.localIntersect(r);

    REQUIRE(xs.size() == 0);
}

TEST_CASE("Intersecting a ray with a non-empty group") {
    auto g = std::make_shared<Group>();
    auto s1 = std::make_shared<Sphere>();
    auto s2 = std::make_shared<Sphere>();
    auto s3 = std::make_shared<Sphere>();
    s2->move(0, 0, -3);
    s3->move(5, 0, 0);
    g->addChild(s1);
    g->addChild(s2);
    g->addChild(s3);

    Ray r(Point(0, 0, -5), Vector(0, 0, 1));
    auto xs = g->localIntersect(r);
    REQUIRE(xs.size() == 4);
    REQUIRE(xs[0].object == s2.get());
    REQUIRE(xs[1].object == s2.get());
    REQUIRE(xs[2].object == s1.get());
    REQUIRE(xs[3].object == s1.get());
}

TEST_CASE("Group transformations") {
    auto g = std::make_shared<Group>();
    g->scale(2, 2, 2);
    auto s = std::make_shared<Sphere>();
    s->move(5, 0, 0);
    g->addChild(s);
    Ray r(Point(10, 0, -10), Vector(0, 0, 1));
    auto xs = g->intersect(r);
    REQUIRE(xs.size() == 2);
}
