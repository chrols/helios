#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>

#include "tuple.hpp"

template <typename T>
class Matrix {
public:
    Matrix(unsigned width, unsigned height);
    // Brace initializer?
    // Type enforcement Matrix<double, 3> ??
    Point operator*(const Point &rhs) const;
    Matrix<T> operator*(const Matrix<T> &rhs) const;
    std::vector<T> &operator[](const int index);
    const std::vector<T> &operator[](const int index) const;

    Matrix<T> transpose() const;
    Matrix<T> subMatrix(unsigned skipRow, unsigned skipCol) const;
    Matrix<T> inverse() const;
    // Matrix<T> translation(T x, T y, T z) const;

    T determinant() const;
    T minorn(unsigned row, unsigned col) const;
    T cofactor(unsigned row, unsigned col) const;

    static Matrix<T> identity(int n);
    static Matrix<T> translationMatrix(T x, T y, T z);

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
    // FIXME Ugly hack
    if (m_height < 3 || m_height > 4)
        throw std::out_of_range("* with incompatible types");

    return Point(rhs.x + (*this)[0][3], rhs.y + (*this)[1][3],
                 rhs.z + (*this)[2][3]);
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
}