// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#pragma once

// external
#include <glm/glm.hpp>

namespace ltb::geom {

template <typename T>
struct Range {
    T min = {};
    T max = {};
};

using Range2Di = Range<glm::ivec2>;
using Range2D  = Range<glm::vec2>;

template <typename T>
auto dimensions(Range<T> const& range) {
    return range.max - range.min;
}

template <glm::length_t L, typename T>
auto contains(Range<glm::vec<L, T>> const& range, glm::vec<L, T> const& p) {
    for (auto i = 0; i < L; ++i) {
        if (range.min[i] > p[i] || p[i] > range.max[i]) {
            return false;
        }
    }
    return true;
}

} // namespace ltb::geom
