// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#pragma once

// project
#include "ltb/geom/mesh.hpp"

namespace ltb::geom {

/// \brief A disc with diameter of 1.
/// \tparam T
/// \param spokes
/// \param rings
/// \return
template <typename T = float>
auto disc_mesh(unsigned spokes = 30u, unsigned rings = 15u) -> Mesh<3, T>;

} // namespace ltb::geom
