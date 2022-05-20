// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#pragma once

// project
#include "ltb/geom/vec.hpp"

namespace ltb::geom {

/// \ingroup shapes
/// \brief A line with a radius.
template <glm::length_t L, typename T>
struct Capsule {
    glm::vec<L, T> start_point = glm::vec<L, T>(glm::vec<2, T>(0, -0.5));
    glm::vec<L, T> end_point   = glm::vec<L, T>(glm::vec<2, T>(0, +0.5));
    T              radius      = T(0.5);
};

} // namespace ltb::geom
