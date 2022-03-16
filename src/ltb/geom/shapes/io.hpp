// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#pragma once

// project
#include "fwd.hpp"

// standard
#include <istream>
#include <ostream>

namespace ltb::geom {

template <glm::length_t L, typename T>
auto operator<<(std::ostream& os, Ball<L, T> const& ball) -> std::ostream&;

template <glm::length_t L, typename T>
auto operator>>(std::istream& is, Ball<L, T>& ball) -> std::istream&;

template <glm::length_t L, typename T>
auto operator<<(std::ostream& os, Box<L, T> const& box) -> std::ostream&;

template <glm::length_t L, typename T>
auto operator>>(std::istream& is, Box<L, T>& box) -> std::istream&;

} // namespace ltb::geom
