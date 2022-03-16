// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#pragma once

// project
#include "vec.hpp"

// standard
#include <algorithm>
#include <ostream>
#include <vector>

namespace ltb::geom {

enum class GeometryFormat {
    Points,
    Lines,
    LineStrip,
    Triangles,
    TriangleStrip,
    TriangleFan,
};

auto operator<<(std::ostream& os, GeometryFormat const& format) -> std::ostream&;

auto is_triangle_format(GeometryFormat const& format) -> bool;

template <glm::length_t L, typename T>
struct Mesh {
    GeometryFormat geometry_format = GeometryFormat::Points;

    std::vector<glm::vec<L, T>>     positions     = {};
    std::vector<glm::vec<L, T>>     normals       = {};
    std::vector<glm::vec<L - 1, T>> uv_coords     = {};
    std::vector<glm::vec3>          vertex_colors = {};

    std::vector<std::uint32_t> indices = {};

    explicit Mesh(GeometryFormat type);

    auto append(Mesh<L, T> const& other) -> void;
};

template <glm::length_t L, typename T>
struct MeshAndTransform {
    Mesh<L, T>                mesh;
    glm::mat<L + 1, L + 1, T> transform;

    explicit MeshAndTransform(GeometryFormat mesh_type) : MeshAndTransform(mesh_type, identity_mat<L + 1, T>()) {}
    MeshAndTransform(GeometryFormat mesh_type, glm::mat<L + 1, L + 1, T> trans) : mesh(mesh_type), transform(trans) {}

    explicit MeshAndTransform(Mesh<L, T> m) : MeshAndTransform(std::move(m), identity_mat<L + 1, T>()) {}
    MeshAndTransform(Mesh<L, T> m, glm::mat<L + 1, L + 1, T> trans) : mesh(m), transform(trans) {}
};

template <glm::length_t L, typename T>
auto transform(Mesh<L, T> mesh, glm::mat<L + 1, L + 1, T> const& transformation) -> Mesh<L, T> {
    std::transform(mesh.positions.begin(),
                   mesh.positions.end(),
                   mesh.positions.begin(),
                   [&transformation](auto const& point) { return transform_point(transformation, point); });
    std::transform(mesh.normals.begin(),
                   mesh.normals.end(),
                   mesh.normals.begin(),
                   [&transformation](auto const& normal) { return transform_vector(transformation, normal); });
    return mesh;
}

template <glm::length_t L, typename T>
auto operator==(Mesh<L, T> const& lhs, Mesh<L, T> const& rhs) {
    return lhs.geometry_format == rhs.geometry_format
        && std::equal(lhs.positions.begin(), lhs.positions.end(), rhs.positions.begin(), rhs.positions.end())
        && std::equal(lhs.normals.begin(), lhs.normals.end(), rhs.normals.begin(), rhs.normals.end())
        && std::equal(lhs.uv_coords.begin(), lhs.uv_coords.end(), rhs.uv_coords.begin(), rhs.uv_coords.end())
        && std::equal(lhs.vertex_colors.begin(),
                      lhs.vertex_colors.end(),
                      rhs.vertex_colors.begin(),
                      rhs.vertex_colors.end())
        && std::equal(lhs.indices.begin(), lhs.indices.end(), rhs.indices.begin(), rhs.indices.end());
}

using Mesh2  = Mesh<2, float>;
using Mesh3  = Mesh<3, float>;
using dMesh2 = Mesh<2, double>;
using dMesh3 = Mesh<3, double>;

using Mesh2AndTransform  = MeshAndTransform<2, float>;
using Mesh3AndTransform  = MeshAndTransform<3, float>;
using dMesh2AndTransform = MeshAndTransform<2, double>;
using dMesh3AndTransform = MeshAndTransform<3, double>;

} // namespace ltb::geom
