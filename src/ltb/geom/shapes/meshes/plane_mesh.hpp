// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#pragma once

// project
#include "ltb/geom/mesh.hpp"

namespace ltb::geom {

/// \brief A 1x1 plane.
/// \tparam T
/// \param u_divisions
/// \param v_divisions
/// \return
template <typename T = float>
auto plane_mesh(unsigned u_divisions = 0u, unsigned v_divisions = 0u) -> Mesh<3, T>;

} // namespace ltb::geom
