#include "catch.hpp"

#include "matrix.hpp"
#include <iostream>

TEST_CASE("TransformationMatrixForDefaultOrientation", "[Matrix]") {
    Point from(0, 0, 0);
    Point to(0, 0, -1);
    Vector up(0, 1, 0);
    auto t = Matrix::viewTransform(from, to, up);
    REQUIRE(t == Matrix::identity(4));
}

TEST_CASE("ViewTransformationMatrixLookingInPositiveZDirection", "[Matrix]") {
    Point from(0, 0, 0);
    Point to(0, 0, 1);
    Vector up(0, 1, 0);
    auto t = Matrix::viewTransform(from, to, up);
    REQUIRE(t == Matrix::scalingMatrix(-1, 1, -1));
}

TEST_CASE("ViewTransformationMovesWorld", "[Matrix]") {
    Point from(0, 0, 8);
    Point to(0, 0, 0);
    Vector up(0, 1, 0);
    auto t = Matrix::viewTransform(from, to, up);
    REQUIRE(t == Matrix::translationMatrix(0, 0, -8));
}

TEST_CASE("ArbitraryViewTransformation", "[Matrix]") {
    Point from(1, 3, 2);
    Point to(4, -2, 8);
    Vector up(1, 1, 0);
    auto t = Matrix::viewTransform(from, to, up);

    Matrix out(4, 4);
    out[0] = std::vector<double>({-0.507093, 0.507093, 0.676123, -2.36643});
    out[1] = std::vector<double>({0.76772, 0.60609, 0.12122, -2.82843});
    out[2] = std::vector<double>({-0.35857, 0.59761, -0.71714, 0.00000});
    out[3] = std::vector<double>({0.00000, 0.00000, 0.00000, 1.00000});

    REQUIRE(t == out);
}
