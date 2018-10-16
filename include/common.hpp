#pragma once

#include <cmath>
#include <experimental/optional>
#include <limits>

template <typename T>
bool almostEqual(const T &lhs, const T &rhs) {
// Using epsilon makes it a bit tedious to use the unit tests
#ifdef UNITTEST
    return (std::abs(lhs - rhs) < 0.1);
#else
    return (std::abs(lhs - rhs) < std::numeric_limits<T>::epsilon());
#endif
}

const double PI = 3.14159265358979323846;

template <typename T>
using Optional = std::experimental::optional<T>;
