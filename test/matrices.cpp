#include <gtest/gtest.h>

#include "matrix.hpp"
#include <iostream>

TEST(Matrix, TransformationMatrixForDefaultOrientation) {
    Point from(0, 0, 0);
    Point to(0, 0, -1);
    Vector up(0, 1, 0);
    auto t = Matrix<double>::viewTransform(from, to, up);
    ASSERT_TRUE(t == Matrix<double>::identity(4));
}

TEST(Matrix, ViewTransformationMatrixLookingInPositiveZDirection) {
    Point from(0, 0, 0);
    Point to(0, 0, 1);
    Vector up(0, 1, 0);
    auto t = Matrix<double>::viewTransform(from, to, up);
    ASSERT_TRUE(t == Matrix<double>::scalingMatrix(-1, 1, -1));
}

TEST(Matrix, ViewTransformationMovesWorld) {
    Point from(0, 0, 8);
    Point to(0, 0, 0);
    Vector up(0, 1, 0);
    auto t = Matrix<double>::viewTransform(from, to, up);
    std::cerr << t;
    std::cerr << Matrix<double>::translationMatrix(0, 0, -8);
    std::cerr << std::endl;

    ASSERT_TRUE(t == Matrix<double>::translationMatrix(0, 0, -8));
}

TEST(Matrix, ArbitraryViewTransformation) {
    Point from(1, 3, 2);
    Point to(4, -2, 8);
    Vector up(1, 1, 0);
    auto t = Matrix<double>::viewTransform(from, to, up);
    std::cerr << t;
    ASSERT_TRUE(t[0] ==
                std::vector<double>({-0.50709, 0.50709, 0.67612, -2.36643}));
    ASSERT_TRUE(t[1] ==
                std::vector<double>({0.76772, 0.60609, 0.12122, -2.82843}));
    ASSERT_TRUE(t[2] ==
                std::vector<double>({-0.35857, 0.59761, -0.71714, 0.00000}));
    ASSERT_TRUE(t[3] ==
                std::vector<double>({0.00000, 0.00000, 0.00000, 1.00000}));
}
