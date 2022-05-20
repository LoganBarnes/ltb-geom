// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#pragma once

// project
#include "fwd.hpp"
#include "ltb/geom/vec.hpp"

namespace ltb::geom {

/// \ingroup shapes
/// \brief A round object.
template <glm::length_t L, typename T>
struct Ball {
    glm::vec<L, T> center = glm::vec<L, T>(0);
    T              radius = T(1);
};

} // namespace ltb::geom
