// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#pragma once

// project
#include "vec.hpp"
#include "ltb/util/comparison_utils.hpp"

namespace ltb::geom {

template <glm::length_t L, typename T>
auto constexpr almost_equal(glm::vec<L, T> const& lhs, glm::vec<L, T> const& rhs) ->
    typename std::enable_if_t<std::is_floating_point<T>::value, bool> {

    for (glm::length_t i = 0; i < L; ++i) {
        if (!util::almost_equal(lhs[i], rhs[i])) {
            return false;
        }
    }
    return true;
}

} // namespace ltb::geom
