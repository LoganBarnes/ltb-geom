// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#include "ltb/geom/shapes/meshes/cube_mesh.hpp"

// project
#include "ltb/geom/shapes/meshes/plane_mesh.hpp"

// external
#include <glm/gtc/matrix_transform.hpp>

// standard
#include <array>

namespace ltb::geom {

template <typename T>
auto cube_mesh(unsigned u_divisions, unsigned v_divisions) -> Mesh<3, T> {
    auto mesh = Mesh<3, T>{GeometryFormat::Triangles};

    auto const face_mesh = plane_mesh<T>(u_divisions, v_divisions);

    constexpr auto I = glm::mat<4, 4, T>(1);

    auto transforms = std::array<glm::mat<4, 4, T>, 6>{
        glm::translate(I, {T(0), T(0), T(0.5)}),
        glm::rotate(I, glm::radians(T(+90)), {0, 1, 0}) * glm::translate(I, {T(0), T(0), T(0.5)}),
        glm::rotate(I, glm::radians(T(180)), {0, 1, 0}) * glm::translate(I, {T(0), T(0), T(0.5)}),
        glm::rotate(I, glm::radians(T(-90)), {0, 1, 0}) * glm::translate(I, {T(0), T(0), T(0.5)}),
        glm::rotate(I, glm::radians(T(+90)), {1, 0, 0}) * glm::translate(I, {T(0), T(0), T(0.5)}),
        glm::rotate(I, glm::radians(T(-90)), {1, 0, 0}) * glm::translate(I, {T(0), T(0), T(0.5)}),
    };

    for (auto const& transformation : transforms) {
        mesh.append(transform(face_mesh, transformation));
    }

    return mesh;
}

template auto cube_mesh(unsigned, unsigned) -> Mesh<3, float>;
template auto cube_mesh(unsigned, unsigned) -> Mesh<3, double>;

} // namespace ltb::geom
