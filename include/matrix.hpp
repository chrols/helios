#pragma once

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "common.hpp"
#include "tuple.hpp"

template <typename T>
class Matrix {
public:
    Matrix(unsigned width, unsigned height);
    // Brace initializer?
    // Type enforcement Matrix<double, 3> ??
    Point operator*(const Point &rhs) const;
    Vector operator*(const Vector &rhs) const;
    Matrix<T> operator*(const Matrix<T> &rhs) const;
    std::vector<T> &operator[](const int index);
    const std::vector<T> &operator[](const int index) const;
    bool operator==(const Matrix<T> &rhs) const;

    Matrix<T> transpose() const;
    Matrix<T> subMatrix(unsigned skipRow, unsigned skipCol) const;
    bool hasInverse() const;
    Matrix<T> inverse() const;
    // Matrix<T> translation(T x, T y, T z) const;

    T determinant() const;
    T minorn(unsigned row, unsigned col) const;
    T cofactor(unsigned row, unsigned col) const;

    static Matrix<T> identity(int n);
    static Matrix<T> translationMatrix(T x, T y, T z);
    static Matrix<T> scalingMatrix(T w, T h, T d);
    static Matrix<T> rotationMatrixX(double radians);
    static Matrix<T> rotationMatrixY(double radians);
    static Matrix<T> rotationMatrixZ(double radians);
    static Matrix<T> viewTransform(Point from, Point to, Vector up);

    unsigned width() const;
    unsigned height() const;

private:
    unsigned m_width, m_height;
    std::vector<std::vector<T>> m_rows;
};

template <typename T>
Matrix<T>::Matrix(unsigned width, unsigned height)
    : m_width(width), m_height(height) {
    m_rows.resize(m_height);

    for (auto &row : m_rows) {
        row = std::vector<T>(m_width, 0);
    }
}

template <typename T>
Point Matrix<T>::operator*(const Point &rhs) const {
    if (m_height != 4)
        throw std::out_of_range("* with incompatible types");

    auto x = rhs.x * (*this)[0][0] + rhs.y * (*this)[0][1] +
             rhs.z * (*this)[0][2] + (*this)[0][3];
    auto y = rhs.x * (*this)[1][0] + rhs.y * (*this)[1][1] +
             rhs.z * (*this)[1][2] + (*this)[1][3];
    auto z = rhs.x * (*this)[2][0] + rhs.y * (*this)[2][1] +
             rhs.z * (*this)[2][2] + (*this)[2][3];

    return Point(x, y, z);
}

template <typename T>
Vector Matrix<T>::operator*(const Vector &rhs) const {
    if (m_height != 4)
        throw std::out_of_range("* with incompatible types");

    auto x =
        rhs.x * (*this)[0][0] + rhs.y * (*this)[0][1] + rhs.z * (*this)[0][2];
    auto y =
        rhs.x * (*this)[1][0] + rhs.y * (*this)[1][1] + rhs.z * (*this)[1][2];
    auto z =
        rhs.x * (*this)[2][0] + rhs.y * (*this)[2][1] + rhs.z * (*this)[2][2];

    return Vector(x, y, z);
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix &rhs) const {
    Matrix<T> r(m_width, m_height);

    for (int row = 0; row < m_height; row++) {
        for (int col = 0; col < m_width; col++) {
            // FIXME Rewrite
            for (int i = 0; i < 4; i++) {
                r[row][col] += m_rows[row][i] * rhs[i][col];
            }
        }
    }

    return r;
}

template <typename T>
std::vector<T> &Matrix<T>::operator[](const int index) {
    return m_rows[index];
}

template <typename T>
const std::vector<T> &Matrix<T>::operator[](const int index) const {
    return m_rows[index];
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T> &rhs) const {
    for (int row = 0; row < m_width; row++) {
        for (int col = 0; col < m_height; col++) {
            if (!almostEqual(rhs[col][row], (*this)[col][row])) {
                std::cerr << rhs[col][row] << "!=" << (*this)[col][row]
                          << std::endl;
                std::cerr << col << " " << row << std::endl;
                return false;
            }
        }
    }

    return true;
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> r(m_height, m_width); // Note: transposed arguments
    for (int row = 0; row < m_width; row++) {
        for (int col = 0; col < m_height; col++) {
            r[row][col] = (*this)[col][row];
        }
    }

    return r;
}

template <typename T>
Matrix<T> Matrix<T>::subMatrix(unsigned skipRow, unsigned skipCol) const {
    if (m_width <= 1 || m_height <= 1) {
        throw std::out_of_range("matrix is too small");
    }

    Matrix<T> r(m_height - 1, m_width - 1);

    unsigned subRow = 0, subCol = 0;

    for (int row = 0; row < m_height; row++) {
        if (row == skipRow)
            continue;
        for (int col = 0; col < m_width; col++) {
            if (col == skipCol)
                continue;
            r[subRow][subCol++] = (*this)[row][col];
        }
        subCol = 0;
        subRow++;
    }

    return r;
}

template <typename T>
bool Matrix<T>::hasInverse() const {
    T det = determinant();
    return (det != 0);
}

template <typename T>
Matrix<T> Matrix<T>::inverse() const {
    T det = determinant();
    if (det == 0)
        throw std::out_of_range("inverse called on non-inversable matrix");

    Matrix<T> cm(4, 4);

    for (int row = 0; row < m_height; row++) {
        for (int col = 0; col < m_width; col++) {
            cm[row][col] = cofactor(row, col);
        }
    }

    auto r = cm.transpose();

    for (int row = 0; row < m_height; row++) {
        for (int col = 0; col < m_width; col++) {
            r[row][col] /= det;
        }
    }

    return r;
}

template <typename T>
T Matrix<T>::determinant() const {
    auto &m = (*this);

    if (m_width == 2 && m_height == 2) {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    } else {
        T r = 0;
        for (int i = 0; i < m_width; i++) {
            r += m[0][i] * cofactor(0, i);
        }

        return r;
    }
}

template <typename T>
T Matrix<T>::minorn(unsigned row, unsigned col) const {
    return subMatrix(row, col).determinant();
}

template <typename T>
T Matrix<T>::cofactor(unsigned row, unsigned col) const {
    auto r = subMatrix(row, col).determinant();
    ;
    return ((row + col) % 2 == 0) ? r : -r;
}

template <typename T>
Matrix<T> Matrix<T>::identity(int n) {
    Matrix<T> i(n, n);
    for (int y = 0; y < n; y++)
        for (int x = 0; x < n; x++)
            i[y][x] = 0;

    for (int x = 0; x < n; x++)
        i[x][x] = 1;

    return i;
}

template <typename T>
Matrix<T> Matrix<T>::translationMatrix(T x, T y, T z) {
    auto t = Matrix<T>::identity(4);
    t[0][3] = x;
    t[1][3] = y;
    t[2][3] = z;
    return t;
}

template <typename T>
Matrix<T> Matrix<T>::scalingMatrix(T w, T h, T d) {
    auto t = Matrix<T>::identity(4);
    t[0][0] = w;
    t[1][1] = h;
    t[2][2] = d;
    return t;
}

template <typename T>
Matrix<T> Matrix<T>::rotationMatrixX(double radians) {
    auto t = Matrix<T>::identity(4);
    t[1][1] = std::cos(radians);
    t[1][2] = -std::sin(radians);
    t[2][1] = std::sin(radians);
    t[2][2] = std::cos(radians);
    return t;
}

template <typename T>
Matrix<T> Matrix<T>::rotationMatrixY(double radians) {
    auto t = Matrix<T>::identity(4);
    t[0][0] = std::cos(radians);
    t[0][2] = std::sin(radians);
    t[2][0] = -std::sin(radians);
    t[2][2] = std::cos(radians);
    return t;
}

template <typename T>
Matrix<T> Matrix<T>::rotationMatrixZ(double radians) {
    auto t = Matrix<T>::identity(4);
    t[0][0] = std::cos(radians);
    t[0][1] = -std::sin(radians);
    t[1][0] = std::sin(radians);
    t[1][1] = std::cos(radians);
    return t;
}

template <typename T>
Matrix<T> Matrix<T>::viewTransform(Point from, Point to, Vector up) {
    auto forward = (to - from).normalize();
    auto upn = up.normalize();
    auto left = forward.cross(upn);
    auto true_up = left.cross(forward);
    Matrix<T> m(4, 4);
    m[0] = {left.x, left.y, left.z, 0};
    m[1] = {true_up.x, true_up.y, true_up.z, 0};
    m[2] = {-forward.x, -forward.y, -forward.z, 0};
    m[3] = {0, 0, 0, 1};
    return m * translationMatrix(-from.x, -from.y, -from.z);
}

template <typename T>
unsigned Matrix<T>::width() const {
    return m_width;
}

template <typename T>
unsigned Matrix<T>::height() const {
    return m_height;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &m) {
    for (unsigned y = 0; y < m.height(); y++) {
        std::cout << "[ ";
        for (unsigned x = 0; x < m.width(); x++) {
            std::cout << m[y][x] << " ";
        }

        std::cout << "]\n";
    }

    return os;
}
