// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#pragma once

// project
#include "ltb/geom/vec.hpp"

// system
#include <vector>

namespace ltb::geom {

/// \ingroup shapes
/// \brief 2D Polygon
template <typename T>
struct Polygon {
    std::vector<glm::vec<2, T>> points = {};
};

} // namespace ltb::geom
