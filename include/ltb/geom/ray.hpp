// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#pragma once

// project
#include "vec.hpp"

// standard
#include <type_traits>

namespace ltb::geom {
namespace detail {

template <glm::length_t L, typename T>
struct Ray {
    glm::vec<L, T> origin{0};
    glm::vec<L, T> direction{0};
    glm::vec<L, T> inverse_direction{inf<T>()};

    Ray() = delete;

    // Grown up rules here. Make sure to normalize d if your algorithm needs it.
    Ray(glm::vec<L, T> o, glm::vec<L, T> d) : origin{o}, direction{d}, inverse_direction(T(1) / direction) {
        static_assert(std::is_floating_point_v<T>, "Ray type must be floating point");
    }
};

} // namespace detail

template <glm::length_t L, typename T>
using Ray = typename detail::Ray<L, T>;

template <typename T>
using TRay2 = Ray<2, T>;
template <typename T>
using TRay3 = Ray<3, T>;

using Ray2 = TRay2<float>;
using Ray3 = TRay3<float>;

using DRay2 = TRay2<double>;
using DRay3 = TRay3<double>;

} // namespace ltb::geom
