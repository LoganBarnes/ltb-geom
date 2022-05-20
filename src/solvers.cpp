// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#include "ltb/geom/solvers.hpp"

namespace ltb::geom {

auto is_zero(float) -> bool;
auto is_zero(double) -> bool;

auto solve_quadratic(float, float, float, float*, float*) -> int;
auto solve_quadratic(double, double, double, double*, double*) -> int;

auto solve_cubic(float, float, float, float, float*, float*, float*) -> int;
auto solve_cubic(double, double, double, double, double*, double*, double*) -> int;

} // namespace ltb::geom
