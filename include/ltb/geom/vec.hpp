// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#pragma once

// external
#include <glm/gtc/vec1.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

// standard
#include <limits>

namespace ltb::geom {

template <typename T>
constexpr auto inf() {
    return std::numeric_limits<T>::infinity();
}

template <glm::length_t L = 4, typename T>
constexpr auto identity_mat() {
    return glm::mat<L, L, T>(1);
}

template <glm::length_t L = 4, typename T>
constexpr auto transform_point(glm::mat<L + 1, L + 1, T> const& transform, glm::vec<L, T> const& point) {
    return glm::vec<L, T>(transform * glm::vec<L + 1, T>(point, T(1)));
}

template <glm::length_t L = 4, typename T>
constexpr auto transform_vector(glm::mat<L + 1, L + 1, T> const& transform, glm::vec<L, T> const& point) {
    return glm::vec<L, T>(transform * glm::vec<L + 1, T>(point, T(0)));
}

template <glm::length_t L, typename T>
constexpr auto make_zeroed_vec(T x) {
    auto result = glm::vec<L, T>(T(0));
    result[0]   = x;
    return result;
}

template <glm::length_t L, typename T>
constexpr auto make_zeroed_vec(T x, T y) {
    static_assert(L >= 2);
    auto result = glm::vec<L, T>(T(0));
    result[0]   = x;
    result[1]   = y;
    return result;
}

template <glm::length_t L, typename T>
constexpr auto make_zeroed_vec(T x, T y, T z) {
    static_assert(L >= 3);
    auto result = glm::vec<L, T>(T(0));
    result[0]   = x;
    result[1]   = y;
    result[2]   = z;
    return result;
}

} // namespace ltb::geom
