// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#include "ltb/geom/shapes/meshes/icosphere_mesh.hpp"

#include <cmath>

namespace ltb::geom {

template <typename T>
auto icosphere_mesh(unsigned /*iterations*/) -> Mesh<3, T> {
    // set up a 20-triangle icosahedron
    auto const f = (T(1) + std::sqrt(T(5))) / T(2);
    // auto const t = std::pow<T>(4, iterations);

    auto mesh = Mesh<3, T>{GeometryFormat::Triangles};

    mesh.positions = {
        {-1, f, 0},
        {1, f, 0},
        {-1, -f, 0},
        {1, -f, 0},
        {0, -1, f},
        {0, 1, f},
        {0, -1, -f},
        {0, 1, -f},
        {f, 0, -1},
        {f, 0, 1},
        {-f, 0, -1},
        {-f, 0, 1},
    };
    mesh.indices = {
        0, 11, 5, 0, 5, 1, 0, 1, 7, 0, 7, 10, 0, 10, 11, 11, 10, 2, 5, 11, 4, 1, 5, 9,  7, 1, 8,  10, 7, 6,
        3, 9,  4, 3, 4, 2, 3, 2, 6, 3, 6, 8,  3, 8,  9,  9,  8,  1, 4, 9,  5, 2, 4, 11, 6, 2, 10, 8,  6, 7,
    };

    // let v = 12;
    // const midCache = order ? new Map() : null; // midpoint vertices cache to avoid duplicating shared vertices
    //
    // function addMidPoint(a, b) {
    //     const key = Math.floor((a + b) * (a + b + 1) / 2) + Math.min(a, b); // Cantor's pairing function
    //     let i = midCache.get(key);
    //     if (i !== undefined) { midCache.delete(key); return i; }
    //     midCache.set(key, v);
    //     for (let k = 0; k < 3; k++) vertices[3 * v + k] = (vertices[3 * a + k] + vertices[3 * b + k]) / 2;
    //     i = v++;
    //     return i;
    // }

    return mesh;
}

template auto icosphere_mesh(unsigned) -> Mesh<3, float>;
template auto icosphere_mesh(unsigned) -> Mesh<3, double>;

} // namespace ltb::geom
