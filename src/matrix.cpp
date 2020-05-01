#include "matrix.hpp"

Matrix::Matrix(unsigned width, unsigned height)
    : m_width(width), m_height(height) {
    m_rows.resize(m_height);

    for (auto &row : m_rows) {
        row = std::vector<double>(m_width, 0);
    }
}

Matrix::Matrix(const Matrix &matrix)
    : m_width(matrix.m_width), m_height(matrix.m_height), m_rows(matrix.m_rows),
      m_inverse(matrix.m_inverse) {}

Matrix::Matrix(Matrix &&other) {
    m_width = other.m_width;
    m_height = other.m_height;
    m_rows = other.m_rows;
    m_inverse = other.m_inverse;
}

Matrix::~Matrix() {}

Matrix &Matrix::operator=(const Matrix &rhs) {
    std::lock_guard<std::mutex> lock(m_mutex);

    m_width = rhs.m_width;
    m_height = rhs.m_height;
    m_rows = rhs.m_rows;
    m_inverse = rhs.m_inverse;

    return *this;
}

Point Matrix::operator*(const Point &rhs) const {
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

Vector Matrix::operator*(const Vector &rhs) const {
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

Matrix Matrix::operator*(const Matrix &rhs) const {
    Matrix r(m_width, m_height);

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

Matrix &Matrix::operator*=(const Matrix &rhs) {
    std::lock_guard<std::mutex> lock(m_mutex);

    for (int row = 0; row < m_height; row++) {
        for (int col = 0; col < m_width; col++) {

            double sum = 0;

            for (int i = 0; i < 4; i++) {
                sum += m_rows[row][i] * rhs[i][col];
            }

            (*this)[row][col] = sum;
        }
    }

    m_inverse.reset();

    return *this;
}

std::vector<double> &Matrix::operator[](const int index) {
    // std::lock_guard<std::mutex> lock(m_mutex);
    m_inverse.reset();
    return m_rows[index];
}

const std::vector<double> &Matrix::operator[](const int index) const {
    return m_rows[index];
}

bool Matrix::operator==(const Matrix &rhs) const {
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

Matrix Matrix::transpose() const {
    Matrix r(m_height, m_width); // Note: transposed arguments
    for (int row = 0; row < m_width; row++) {
        for (int col = 0; col < m_height; col++) {
            r[row][col] = (*this)[col][row];
        }
    }

    return r;
}

Matrix Matrix::subMatrix(unsigned skipRow, unsigned skipCol) const {
    if (m_width <= 1 || m_height <= 1) {
        throw std::out_of_range("matrix is too small");
    }

    Matrix r(m_height - 1, m_width - 1);

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

bool Matrix::hasInverse() const {
    double det = determinant();
    return (det != 0);
}

Matrix Matrix::inverse() const {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_inverse) {
        return *m_inverse;
    }

    double det = determinant();
    if (det == 0)
        throw std::out_of_range("inverse called on non-inversable matrix");

    Matrix cm(4, 4);

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

    m_inverse = std::make_shared<Matrix>(m_width, m_height);
    *m_inverse = r;

    return r;
}

double Matrix::determinant() const {
    auto &m = (*this);

    if (m_width == 2 && m_height == 2) {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    } else {
        double r = 0;
        for (int i = 0; i < m_width; i++) {
            r += m[0][i] * cofactor(0, i);
        }

        return r;
    }
}

double Matrix::minorn(unsigned row, unsigned col) const {
    return subMatrix(row, col).determinant();
}

double Matrix::cofactor(unsigned row, unsigned col) const {
    auto r = subMatrix(row, col).determinant();
    ;
    return ((row + col) % 2 == 0) ? r : -r;
}

Matrix Matrix::identity(int n) {
    Matrix i(n, n);
    for (int y = 0; y < n; y++)
        for (int x = 0; x < n; x++)
            i[y][x] = 0;

    for (int x = 0; x < n; x++)
        i[x][x] = 1;

    return i;
}

Matrix Matrix::translationMatrix(double x, double y, double z) {
    auto t = Matrix::identity(4);
    t[0][3] = x;
    t[1][3] = y;
    t[2][3] = z;
    return t;
}

Matrix Matrix::scalingMatrix(double w, double h, double d) {
    auto t = Matrix::identity(4);
    t[0][0] = w;
    t[1][1] = h;
    t[2][2] = d;
    return t;
}

Matrix Matrix::rotationMatrixX(double radians) {
    auto t = Matrix::identity(4);
    t[1][1] = std::cos(radians);
    t[1][2] = -std::sin(radians);
    t[2][1] = std::sin(radians);
    t[2][2] = std::cos(radians);
    return t;
}

Matrix Matrix::rotationMatrixY(double radians) {
    auto t = Matrix::identity(4);
    t[0][0] = std::cos(radians);
    t[0][2] = std::sin(radians);
    t[2][0] = -std::sin(radians);
    t[2][2] = std::cos(radians);
    return t;
}

Matrix Matrix::rotationMatrixZ(double radians) {
    auto t = Matrix::identity(4);
    t[0][0] = std::cos(radians);
    t[0][1] = -std::sin(radians);
    t[1][0] = std::sin(radians);
    t[1][1] = std::cos(radians);
    return t;
}

Matrix Matrix::viewTransform(Point from, Point to, Vector up) {
    auto forward = (to - from).normalize();
    auto upn = up.normalize();
    auto left = forward.cross(upn);
    auto true_up = left.cross(forward);
    Matrix m(4, 4);
    m[0] = {left.x, left.y, left.z, 0};
    m[1] = {true_up.x, true_up.y, true_up.z, 0};
    m[2] = {-forward.x, -forward.y, -forward.z, 0};
    m[3] = {0, 0, 0, 1};
    return m * translationMatrix(-from.x, -from.y, -from.z);
}

unsigned Matrix::width() const {
    return m_width;
}

unsigned Matrix::height() const {
    return m_height;
}

std::ostream &operator<<(std::ostream &os, const Matrix &m) {
    for (unsigned y = 0; y < m.height(); y++) {
        std::cout << "[ ";
        for (unsigned x = 0; x < m.width(); x++) {
            std::cout << m[y][x] << " ";
        }

        std::cout << "]\n";
    }

    return os;
}
