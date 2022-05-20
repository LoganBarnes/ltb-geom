// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#pragma once

// project
#include "fwd.hpp"

namespace ltb::geom {

template <typename T>
struct Shape;

template <template <glm::length_t, typename> class S, glm::length_t L, typename T>
struct Shape<S<L, T>> {
    using Type = T;
    constexpr static auto dimensions() { return L; }
};

template <template <glm::length_t, typename, glm::qualifier> class S, glm::length_t L, typename T, glm::qualifier Q>
struct Shape<S<L, T, Q>> {
    using Type = T;
    constexpr static auto dimensions() { return L; }
};

template <typename S>
using shape_type_t = typename Shape<S>::Type;

template <typename S>
constexpr auto shape_dimensions_v = Shape<S>::dimensions();

} // namespace ltb::geom
