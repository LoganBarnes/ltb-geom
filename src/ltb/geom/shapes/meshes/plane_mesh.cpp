// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#include "ltb/geom/shapes/meshes/plane_mesh.hpp"

// external
#include "glm/glm.hpp"

// standard
#include <cmath>

namespace ltb::geom {

template <typename T>
auto plane_mesh(unsigned u_divisions, unsigned v_divisions) -> Mesh<3, T> {
    auto mesh = Mesh<3, T>{GeometryFormat::Triangles};

    // num_y_points = 3
    //         rows = 2
    //
    //     y2 *-----*-----*-----*-----*
    // r1     | \   | \   | \   | \   |
    //        |   \ |   \ |   \ |   \ |
    //     y1 *-----*-----*-----*-----*
    // r0     | \   | \   | \   | \   |
    //        |   \ |   \ |   \ |   \ |
    //     y0 *-----*-----*-----*-----*
    //       x0    x1    x2    x3    x4    num_x_points = 5
    //          c0    c1    c2    c3               cols = 4

    auto const rows = v_divisions + 1u;
    auto const cols = u_divisions + 1u;

    auto const num_x_points = cols + 1u;
    auto const num_y_points = rows + 1u;

    mesh.positions.reserve(num_x_points * num_y_points);
    mesh.uv_coords.reserve(num_x_points * num_y_points);

    for (auto yi = 0u; yi <= rows; ++yi) {
        auto v = T(yi) / T(rows);
        auto y = glm::mix(T(-0.5), T(0.5), v);

        for (auto xi = 0u; xi <= cols; ++xi) {
            auto u = T(xi) / T(cols);
            auto x = glm::mix(T(-0.5), T(0.5), u);

            mesh.positions.emplace_back(x, y, T(0));
            mesh.uv_coords.emplace_back(u, v);
        }
    }

    mesh.normals = {mesh.positions.size(), glm::vec<3, T>{0, 0, 1}};

    auto const num_triangles = rows * cols;
    auto const num_indices   = num_triangles * 3u;
    mesh.indices.reserve(num_indices);

    for (auto ri = 0u; ri < rows; ++ri) {
        auto row_offset_below = (ri + 0u) * num_x_points;
        auto row_offset_above = (ri + 1u) * num_x_points;

        for (auto ci = 0u; ci < cols; ++ci) {
            // p1     p3
            //  *-----*
            //  | \   |
            //  |   \ |
            //  *-----*
            // p0     p2
            auto p0 = row_offset_below + (ci + 0u);
            auto p1 = row_offset_above + (ci + 0u);
            auto p2 = row_offset_below + (ci + 1u);
            auto p3 = row_offset_above + (ci + 1u);

            // first triangle
            mesh.indices.emplace_back(p0);
            mesh.indices.emplace_back(p2);
            mesh.indices.emplace_back(p1);

            // second triangle
            mesh.indices.emplace_back(p1);
            mesh.indices.emplace_back(p2);
            mesh.indices.emplace_back(p3);
        }
    }

    return mesh;
}

template auto plane_mesh(unsigned, unsigned) -> Mesh<3, float>;
template auto plane_mesh(unsigned, unsigned) -> Mesh<3, double>;

} // namespace ltb::geom
