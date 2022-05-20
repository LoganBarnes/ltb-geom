// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#include "ltb/geom/shapes/meshes/axes_mesh.hpp"

namespace ltb::geom {

template <typename T>
auto axes_mesh(T scale) -> Mesh<3, T> {
    auto mesh = Mesh<3, T>{GeometryFormat::Lines};

    mesh.positions.emplace_back(0, 0, 0);
    mesh.positions.emplace_back(glm::tvec3<T>(1, 0, 0) * scale);
    mesh.positions.emplace_back(glm::tvec3<T>(1, 0, 0) * scale);
    mesh.positions.emplace_back((glm::tvec3<T>(1, 0, 0) + glm::tvec3<T>(-0.15, +0.15, +0.15)) * scale);
    mesh.positions.emplace_back(glm::tvec3<T>(1, 0, 0) * scale);
    mesh.positions.emplace_back((glm::tvec3<T>(1, 0, 0) + glm::tvec3<T>(-0.15, -0.15, -0.15)) * scale);

    mesh.positions.emplace_back(0, 0, 0);
    mesh.positions.emplace_back(glm::tvec3<T>(0, 1, 0) * scale);
    mesh.positions.emplace_back(glm::tvec3<T>(0, 1, 0) * scale);
    mesh.positions.emplace_back((glm::tvec3<T>(0, 1, 0) + glm::tvec3<T>(+0.15, -0.15, +0.15)) * scale);
    mesh.positions.emplace_back(glm::tvec3<T>(0, 1, 0) * scale);
    mesh.positions.emplace_back((glm::tvec3<T>(0, 1, 0) + glm::tvec3<T>(-0.15, -0.15, -0.15)) * scale);

    mesh.positions.emplace_back(0, 0, 0);
    mesh.positions.emplace_back(glm::tvec3<T>(0, 0, 1) * scale);
    mesh.positions.emplace_back(glm::tvec3<T>(0, 0, 1) * scale);
    mesh.positions.emplace_back((glm::tvec3<T>(0, 0, 1) + glm::tvec3<T>(+0.15, +0.15, -0.15)) * scale);
    mesh.positions.emplace_back(glm::tvec3<T>(0, 0, 1) * scale);
    mesh.positions.emplace_back((glm::tvec3<T>(0, 0, 1) + glm::tvec3<T>(-0.15, -0.15, -0.15)) * scale);

    mesh.vertex_colors.resize(18);
    std::fill(mesh.vertex_colors.begin() + 0ul, mesh.vertex_colors.begin() + 6ul, glm::vec3{1.f, 0.f, 0.f});
    std::fill(mesh.vertex_colors.begin() + 6ul, mesh.vertex_colors.begin() + 12ul, glm::vec3{0.f, 1.f, 0.f});
    std::fill(mesh.vertex_colors.begin() + 12ul, mesh.vertex_colors.begin() + 18ul, glm::vec3{0.f, 0.f, 1.f});

    return mesh;
}

template auto axes_mesh(float) -> Mesh<3, float>;
template auto axes_mesh(double) -> Mesh<3, double>;

} // namespace ltb::geom
