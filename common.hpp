#pragma once

#include <cmath>
#include <experimental/optional>
#include <limits>

template <typename T>
bool almostEqual(const T &lhs, const T &rhs) {
    // FIXME Using epsilon makes it a bit tedious to use the unit tests
    return (std::abs(lhs - rhs) < 0.001); // std::numeric_limits<T>::epsilon());
}

template <typename T>
using Optional = std::experimental::optional<T>;
