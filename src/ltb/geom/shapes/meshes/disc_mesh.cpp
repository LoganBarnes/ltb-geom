// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#include "ltb/geom/shapes/meshes/disc_mesh.hpp"

#include <cmath>

namespace ltb::geom {

template <typename T>
auto disc_mesh(unsigned /*spokes*/, unsigned /*rings*/) -> Mesh<3, T> {
    auto mesh = Mesh<3, T>{GeometryFormat::Triangles};
    return mesh;
}

template auto disc_mesh(unsigned, unsigned) -> Mesh<3, float>;
template auto disc_mesh(unsigned, unsigned) -> Mesh<3, double>;

} // namespace ltb::geom
