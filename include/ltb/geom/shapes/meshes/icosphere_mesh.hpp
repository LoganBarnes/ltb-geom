// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#pragma once

// project
#include "ltb/geom/mesh.hpp"

namespace ltb::geom {

/// \brief
/// \tparam T
/// \param iterations
/// \return
template <typename T = float>
auto icosphere_mesh(unsigned iterations = 0) -> Mesh<3, T>;

} // namespace ltb::geom
