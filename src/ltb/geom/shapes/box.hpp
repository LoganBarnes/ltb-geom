// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#pragma once

// project
#include "fwd.hpp"
#include "ltb/geom/vec.hpp"

// external
#include <glm/common.hpp>

namespace ltb::geom {

/// \ingroup shapes
/// \brief Axis Aligned Bounding Box
template <glm::length_t L, typename T>
struct Box {
    glm::vec<L, T> min_point = glm::vec<L, T>(+inf<T>());
    glm::vec<L, T> max_point = glm::vec<L, T>(-inf<T>());
};

template <glm::length_t L, typename T>
constexpr auto center(Box<L, T> const& aabb) {
    return (aabb.min_point + aabb.max_point) / T(2);
}

template <glm::length_t L, typename T>
constexpr auto dimensions(Box<L, T> const& aabb) {
    // glm::max to avoid negative dimensions since that doesn't make sense.
    return glm::max(glm::vec<L, T>(0), aabb.max_point - aabb.min_point);
}

} // namespace ltb::geom
