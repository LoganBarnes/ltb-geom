// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#pragma once

/// \defgroup shapes Shapes

// external
#include <glm/fwd.hpp>

namespace ltb::geom {

template <glm::length_t L, typename T>
struct Ball;

using Ball2  = Ball<2, float>;
using Ball3  = Ball<3, float>;
using DBall2 = Ball<2, double>;
using DBall3 = Ball<3, double>;

template <glm::length_t L, typename T>
struct Box;

using Box2  = Box<2, float>;
using Box3  = Box<3, float>;
using DBox2 = Box<2, double>;
using DBox3 = Box<3, double>;

template <glm::length_t L, typename T>
struct Capsule;

using Capsule2  = Capsule<2, float>;
using Capsule3  = Capsule<3, float>;
using DCapsule2 = Capsule<2, double>;
using DCapsule3 = Capsule<3, double>;

template <glm::length_t L, typename T>
struct Polygon;

using Polygon2  = Polygon<2, float>;
using DPolygon2 = Polygon<2, double>;

} // namespace ltb::geom
