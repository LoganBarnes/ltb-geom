// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#include "ltb/geom/shapes/box.hpp"

// project
#include "ltb/geom/comparison_utils.hpp"
#include "ltb/geom/shapes/shape_info.hpp"

// external
#include <doctest/doctest.h>
#include <glm/gtx/io.hpp> // pretty printing of failed tests

namespace {

using namespace ltb::geom;

TEST_CASE_TEMPLATE("[ltb][geom][shapes] Box center", Box, Box2, Box3, DBox2, DBox3) {
    using T          = shape_type_t<Box>;
    constexpr auto L = shape_dimensions_v<Box>;
    using Vec        = glm::vec<L, T>;

    constexpr auto zero_vec = Vec{0};
    constexpr auto zero_box = Box{zero_vec, zero_vec};

    auto nonsensical_center = center(Box{});
    for (auto i = glm::length_t(0); i < L; ++i) {
        CHECK(std::isnan(nonsensical_center[i]));
    }

    CHECK(center(zero_box) == zero_vec);

    auto box = Box{make_zeroed_vec<L, T>(0, -2), make_zeroed_vec<L, T>(0, +2)};
    CHECK(almost_equal(center(box), Vec(0)));

    if constexpr (L == 3) {
        box = Box{Vec{-1, -2, -3}, Vec{3, 2, 1}};
        CHECK(almost_equal(center(box), Vec{1, 0, -1}));
    }
}

TEST_CASE_TEMPLATE("[ltb][geom][shapes] Box dimensions", Box, Box2, Box3, DBox2, DBox3) {
    using T                   = shape_type_t<Box>;
    constexpr auto L = shape_dimensions_v<Box>;
    using Vec                 = glm::vec<L, T>;

    constexpr auto zero_vec = Vec{0};
    constexpr auto zero_box = Box{zero_vec, zero_vec};

    CHECK(dimensions(Box{}) == zero_vec);
    CHECK(dimensions(zero_box) == zero_vec);

    auto min = Vec{0};
    min.x    = 0;
    min.y    = -2;

    auto max = Vec{0};
    min.x    = 0;
    min.y    = +2;

    auto dims = Vec{0};
    min.x    = 0;
    min.y    = +4;

    // "auto box, roll out!" - Optimus Prime
    auto box = Box{min, max};
    CHECK(almost_equal(dimensions(box), dims));

    if constexpr (L == 3) {
        box = Box{Vec{-1, -2, -3}, Vec{3, 2, 1}};
        CHECK(almost_equal(dimensions(box), Vec{4}));
    }
}

} // namespace
