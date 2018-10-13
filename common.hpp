#pragma once

#include <cmath>
#include <experimental/optional>
#include <limits>

template <typename T>
bool almostEqual(const T &lhs, const T &rhs) {
    return (std::abs(lhs - rhs) < std::numeric_limits<T>::epsilon());
}

template <typename T>
using Optional = std::experimental::optional<T>;
