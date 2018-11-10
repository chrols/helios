#pragma once

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "common.hpp"
#include "tuple.hpp"

class Matrix {
public:
    Matrix(unsigned width, unsigned height);
    // Brace initializer?
    // Type enforcement Matrix<double, 3> ??
    Point operator*(const Point &rhs) const;
    Vector operator*(const Vector &rhs) const;
    Matrix operator*(const Matrix &rhs) const;
    Matrix &operator*=(const Matrix &rhs);
    std::vector<double> &operator[](const int index);
    const std::vector<double> &operator[](const int index) const;
    bool operator==(const Matrix &rhs) const;

    Matrix transpose() const;
    Matrix subMatrix(unsigned skipRow, unsigned skipCol) const;
    bool hasInverse() const;
    Matrix inverse() const;

    double determinant() const;
    double minorn(unsigned row, unsigned col) const;
    double cofactor(unsigned row, unsigned col) const;

    static Matrix identity(int n);
    static Matrix translationMatrix(double x, double y, double z);
    static Matrix scalingMatrix(double w, double h, double d);
    static Matrix rotationMatrixX(double radians);
    static Matrix rotationMatrixY(double radians);
    static Matrix rotationMatrixZ(double radians);
    static Matrix viewTransform(Point from, Point to, Vector up);

    unsigned width() const;
    unsigned height() const;

private:
    unsigned m_width, m_height;
    std::vector<std::vector<double>> m_rows;
};
