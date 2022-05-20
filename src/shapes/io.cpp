// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#include "ltb/geom/shapes/io.hpp"

// project
#include "ltb/geom/shapes/ball.hpp"
#include "ltb/geom/shapes/box.hpp"

namespace ltb::geom {

template <glm::length_t L, typename T>
auto operator<<(std::ostream& os, Ball<L, T> const& ball) -> std::ostream& {
    os << ball.center[0];
    for (auto i = 1ul; i < L; ++i) {
        os << " " << ball.center[i];
    }
    return os << " " << ball.radius;
}

template auto operator<<(std::ostream&, Ball2 const&) -> std::ostream&;
template auto operator<<(std::ostream&, Ball3 const&) -> std::ostream&;
template auto operator<<(std::ostream&, DBall2 const&) -> std::ostream&;
template auto operator<<(std::ostream&, DBall3 const&) -> std::ostream&;

template <glm::length_t L, typename T>
auto operator>>(std::istream& is, Ball<L, T>& ball) -> std::istream& {
    is >> ball.center[0];
    for (auto i = 1ul; i < L; ++i) {
        is >> ball.center[i];
    }
    return is >> ball.radius;
}

template auto operator>>(std::istream&, Ball2&) -> std::istream&;
template auto operator>>(std::istream&, Ball3&) -> std::istream&;
template auto operator>>(std::istream&, DBall2&) -> std::istream&;
template auto operator>>(std::istream&, DBall3&) -> std::istream&;

template <glm::length_t L, typename T>
auto operator<<(std::ostream& os, Box<L, T> const& box) -> std::ostream& {
    os << box.min_point[0];
    for (auto i = 1ul; i < L; ++i) {
        os << " " << box.min_point[i];
    }
    for (auto i = 0ul; i < L; ++i) {
        os << " " << box.max_point[i];
    }
    return os;
}

template auto operator<<(std::ostream&, Box2 const&) -> std::ostream&;
template auto operator<<(std::ostream&, Box3 const&) -> std::ostream&;
template auto operator<<(std::ostream&, DBox2 const&) -> std::ostream&;
template auto operator<<(std::ostream&, DBox3 const&) -> std::ostream&;

template <glm::length_t L, typename T>
auto operator>>(std::istream& is, Box<L, T>& box) -> std::istream& {
    for (auto i = 0ul; i < L; ++i) {
        is >> box.min_point[i];
    }
    for (auto i = 0ul; i < L; ++i) {
        is >> box.max_point[i];
    }
    return is;
}

template auto operator>>(std::istream&, Box2&) -> std::istream&;
template auto operator>>(std::istream&, Box3&) -> std::istream&;
template auto operator>>(std::istream&, DBox2&) -> std::istream&;
template auto operator>>(std::istream&, DBox3&) -> std::istream&;

} // namespace ltb::geom
