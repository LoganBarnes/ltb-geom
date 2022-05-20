// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#pragma once

// project
#include "ltb/geom/mesh.hpp"

namespace ltb::geom {

/// \brief Three colored axis arrows of unit length.
template <typename T = float>
auto axes_mesh(T scale = T(1)) -> Mesh<3, T>;

} // namespace ltb::geom
