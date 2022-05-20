// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#pragma once

// project
#include "ltb/geom/vec.hpp"

namespace ltb::geom {

/// \brief Performs bilinear or trilinear interpolation
///        for a point in a 2D or 3D box, respectively.
template <glm::length_t L, typename T>
struct Interpolator;

} // namespace ltb::geom
