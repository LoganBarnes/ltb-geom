// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#include "ltb/geom/transform.hpp"

// external
#include <doctest/doctest.h>
#include <glm/gtx/io.hpp>
#include <glm/gtx/matrix_operation.hpp>

namespace ltb::geom {

auto normals_matrix(glm::mat4 const& model_matrix) -> glm::mat3 {
    // https://github.com/graphitemaster/normals_revisited
    return glm::transpose(glm::adjugate(glm::mat3(model_matrix)));
}

TEST_CASE("[ltb][geom] normals_matrix math check") {

    SUBCASE("Mat2") {
        // clang-format off
            glm::mat2 m {
                2, 3,
                1, 5,
            };
        // clang-format on

        // https://github.com/graphitemaster/normals_revisited
        // (det M)(M-1)^T = (cof M)
        auto lhs = glm::determinant(m) * glm::transpose(glm::inverse(m));
        auto rhs = glm::transpose(glm::adjugate(m));

        CHECK(glm::all(glm::epsilonEqual(lhs[0], rhs[0], 1e-4f)));
        CHECK(glm::all(glm::epsilonEqual(lhs[1], rhs[1], 1e-4f)));
    }

    SUBCASE("Mat3") {
        // clang-format off
        glm::mat3 m {
            2, 3, 3,
            1, 5, 4,
            4, 6, 8,
        };
        // clang-format on

        // https://github.com/graphitemaster/normals_revisited
        // (det M)(M-1)^T = (cof M)
        auto lhs = glm::determinant(m) * glm::transpose(glm::inverse(m));
        auto rhs = glm::transpose(glm::adjugate(m));

        CHECK(glm::all(glm::epsilonEqual(lhs[0], rhs[0], 1e-4f)));
        CHECK(glm::all(glm::epsilonEqual(lhs[1], rhs[1], 1e-4f)));
        CHECK(glm::all(glm::epsilonEqual(lhs[2], rhs[2], 1e-4f)));
    }

    SUBCASE("Mat4") {
        // clang-format off
        glm::mat4 m {
            2,3,3,1,
            1,5,4,3,
            4,6,8,5,
            -2,-3,-3,4,
        };
        // clang-format on

        // https://github.com/graphitemaster/normals_revisited
        // (det M)(M-1)^T = (cof M)
        auto lhs = glm::determinant(m) * glm::transpose(glm::inverse(m));
        auto rhs = glm::transpose(glm::adjugate(m));

        CHECK(glm::all(glm::epsilonEqual(lhs[0], rhs[0], 1e-4f)));
        CHECK(glm::all(glm::epsilonEqual(lhs[1], rhs[1], 1e-4f)));
        CHECK(glm::all(glm::epsilonEqual(lhs[2], rhs[2], 1e-4f)));
        CHECK(glm::all(glm::epsilonEqual(lhs[3], rhs[3], 1e-4f)));
    }
}

} // namespace ltb::geom
