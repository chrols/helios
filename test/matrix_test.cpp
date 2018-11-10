#include <gtest/gtest.h>

#include <cmath>

#include "tuple.hpp"

TEST(Point, MainStuff) {
    // ASSERT_EQ(Point(1, 1, 6), a1 + a2);
    ASSERT_EQ(Vector(0, 1, 0).magnitude(), 1);
    ASSERT_EQ(Vector(0, 1, 0).magnitude(), 1);
    ASSERT_EQ(Vector(4, 0, 0).normalize(), Vector(1, 0, 0));
    ASSERT_LT(std::abs(Vector(1, 2, 3).normalize().magnitude() - 1), 0.00001f);
}

// int width = 800;
// int height = 600;

// Canvas c(width, height);
// Color c1 = Point(1, 1, 1);

// Point p0 = Point(0, height-1, 0);

// Vector vec = Point(1, -1.8, 0).normal() * 11.25;
// Vector g = Point(0, 0.1, 0);
// Vector wind = Point(-0.01, 0, 0);

// while (!(p0.x >= width || p0.y >= height || p0.x < 0 || p0.y < 0)) {
//     c.setPixel(p0.x, p0.y, c1);
//     p0 = p0 + vec;
//     vec = vec + wind + g;
//     std::cerr << p0.x << ":" << p0.y << std::endl;
// }

// c.write();

// Matrix<float> a(4, 4);
// a[0] = {0, 9, 3, 0};
// a[1] = {9, 8, 0, 8};
// a[2] = {1, 8, 5, 3};
// a[3] = {0, 0, 5, 8};

// // auto b = a * Matrix<float>::identity(4);
// auto b = a.subMatrix(0, 2);

// std::cout << a;
// std::cout << std::endl;

// std::cout << b;

// Matrix<float> gaak(3, 3);
// gaak[0] = {3, 5, 0};
// gaak[1] = {2, -1, -7};
// gaak[2] = {6, -1, 5};

// std::cout << gaak.minorn(1, 0) << std::endl;

// Matrix<float> gruk(4, 4);
// gruk[0] = {-2, -8, 3, 5};
// gruk[1] = {-3, 1, 7, 3};
// gruk[2] = {1, 2, -9, 6};
// gruk[3] = {-6, 7, 7, -9};

// std::cout << gruk.determinant() << std::endl;

// Matrix<float> grub(4, 4);
// grub[0] = {-5, 2, 6, -8};
// grub[1] = {1, -5, 1, 8};
// grub[2] = {7, 7, -6, -7};
// grub[3] = {1, -3, 7, 4};

// b = grub.inverse();

// for (unsigned y = 0; y < b.height(); y++) {
//     std::cout << "[ ";
//     for (unsigned x = 0; x < b.width(); x++) {
//         std::cout << b[y][x] << " ";
//     }

//     std::cout << "]\n";
// }

// auto transform = Matrix::translationMatrix(5, -3, 2);

// Point p(-3, 4, 5);
// Point r(2, 1, 7);

// std::cout << p << std::endl;
// std::cout << (transform * p) << std::endl;
// std::cout << r << std::endl;

// std::cout << ((transform * p) == r) << std::endl;
