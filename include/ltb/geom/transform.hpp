// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#pragma once

// external
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

namespace ltb::geom {

auto normals_matrix(glm::mat4 const& model_matrix) -> glm::mat3;

} // namespace ltb::geom
