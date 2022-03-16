// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#include "ltb/geom/mesh.hpp"

// external
#include <doctest/doctest.h>
#include <magic_enum.hpp>

// standard
#include <sstream>

namespace ltb::geom {

auto operator<<(std::ostream& os, GeometryFormat const& format) -> std::ostream& {
    return os << "GeometryFormat::" << magic_enum::enum_name(format);
}

TEST_CASE("[ltb][geom][mesh] GeometryFormat string") {
    auto to_string = [](GeometryFormat value) -> std::string {
        auto ss = std::stringstream{};
        ss << value;
        return ss.str();
    };

    CHECK(to_string(GeometryFormat::Points) == "GeometryFormat::Points");
    CHECK(to_string(GeometryFormat::Lines) == "GeometryFormat::Lines");
    CHECK(to_string(GeometryFormat::LineStrip) == "GeometryFormat::LineStrip");
    CHECK(to_string(GeometryFormat::Triangles) == "GeometryFormat::Triangles");
    CHECK(to_string(GeometryFormat::TriangleStrip) == "GeometryFormat::TriangleStrip");
    CHECK(to_string(GeometryFormat::TriangleFan) == "GeometryFormat::TriangleFan");
}

auto is_triangle_format(GeometryFormat const& format) -> bool {
    return format == GeometryFormat::Triangles //
        || format == GeometryFormat::TriangleFan //
        || format == GeometryFormat::TriangleStrip;
}

template <glm::length_t L, typename T>
Mesh<L, T>::Mesh(GeometryFormat type) : geometry_format(type) {}

template <glm::length_t L, typename T>
void Mesh<L, T>::append(Mesh<L, T> const& other) {

    indices.reserve(indices.size() + other.indices.size());
    std::transform(other.indices.begin(),
                   other.indices.end(),
                   std::back_inserter(indices),
                   [add = static_cast<std::uint32_t>(positions.size())](std::uint32_t index) { return index + add; });

    positions.insert(positions.end(), other.positions.begin(), other.positions.end());
    normals.insert(normals.end(), other.normals.begin(), other.normals.end());
    uv_coords.insert(uv_coords.end(), other.uv_coords.begin(), other.uv_coords.end());
    vertex_colors.insert(vertex_colors.end(), other.vertex_colors.begin(), other.vertex_colors.end());
}

template struct Mesh<2, float>;
template struct Mesh<3, float>;
template struct Mesh<2, double>;
template struct Mesh<3, double>;

} // namespace ltb::geom
