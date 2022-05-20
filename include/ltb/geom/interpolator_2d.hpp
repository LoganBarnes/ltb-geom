// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#pragma once

// project
#include "interpolator.hpp"
#include "solvers.hpp"

#include "ltb/geom/range.hpp"
#include "ltb/geom/ray.hpp"
#include "ltb/geom/shapes/box.hpp"

// standard
#include <algorithm>
#include <array>

namespace ltb::geom {

enum Corner2d {
    C00,
    C10,
    C01,
    C11,
};

/// \brief Performs bilinear interpolation for a point in a quad.
///
/// \code
/// Box Q:
///
///  y2 -- Q12 ------ Q22    ---
///         |          |      |
///         |          |      | yd
///         |          |      |
///  y1 -- Q11 ------ Q21    ---
///         |          |
///         x1         x2
///
///         | -------- |
///              xd
///
/// The value of some function f(x,y) at some point (x,y) in the box Q can
/// be approximated with bilinear interpolation defined as:
///
/// f(x,y) = a0 + a1 * x + a2 * y + a3 * x * y
///
/// where :
/// a0 = (+f(Q11) * x2 * y2 - f(Q12) * x2 * y1 - f(Q21) * x1 * y2 + f(Q22) * x1 * y1) / (xd * yd)
/// a1 = (-f(Q11)      * y2 + f(Q12)      * y1 + f(Q21)      * y2 - f(Q22)      * y1) / (xd * yd)
/// a2 = (-f(Q11) * x2      + f(Q12) * x2      + f(Q21) * x1      - f(Q22) * x1     ) / (xd * yd)
/// a3 = (+f(Q11)           - f(Q12)           - f(Q21)           + f(Q22)          ) / (xd * yd)
/// \endcode
///
template <typename T>
struct Interpolator<2, T> {

    explicit Interpolator(Box<2, T> const& box, std::array<T, 4> const& values) : a_{} {
        auto const& x1 = box.min_point.x;
        auto const& x2 = box.max_point.x;
        auto const& y1 = box.min_point.y;
        auto const& y2 = box.max_point.y;

        auto const xd    = x2 - x1;
        auto const yd    = y2 - y1;
        auto const denom = xd * yd;

        auto const& q11 = values[Corner2d::C00];
        auto const& q21 = values[Corner2d::C10];
        auto const& q12 = values[Corner2d::C01];
        auto const& q22 = values[Corner2d::C11];

        a_ = {(+q11 * x2 * y2 - q12 * x2 * y1 - q21 * x1 * y2 + q22 * x1 * y1) / denom,
              (-q11 * y2 + q12 * y1 + q21 * y2 - q22 * y1) / denom,
              (-q11 * x2 + q12 * x2 + q21 * x1 - q22 * x1) / denom,
              (+q11 - q12 - q21 + q22) / denom};
    }

    /// \brief Interpolate the value at `point`
    auto operator()(glm::vec<2, T> const& point) -> T {
        auto const& x = point.x;
        auto const& y = point.y;

        return a_[0] + a_[1] * x + a_[2] * y + a_[3] * x * y;
    }

    /// \brief Find the intersection point with `ray`
    auto operator()(Ray<2, T> const& ray, Range<T> const& t_range) -> T {
        auto const& o = ray.origin;
        auto const& d = ray.direction;

        auto const coeff_a = a_[3] * d.x * d.y;
        auto const coeff_b = a_[1] * d.x + a_[2] * d.y + a_[3] * o.x * d.y + a_[3] * o.y * d.x;
        auto const coeff_c = a_[0] + a_[1] * o.x + a_[2] * o.y + a_[3] * o.x * o.y;

        std::array<T, 2> roots;
        for (auto& root : roots) {
            root = inf<float>();
        }

        if (is_zero(coeff_a)) {
            // Linear: bt + c = 0
            roots[0] = -coeff_c / coeff_b;
        } else {
            // Quadratic: at^2 + bt + c = 0
            solve_quadratic(coeff_a, coeff_b, coeff_c, &roots[0], &roots[1]);
        }

        std::sort(roots.begin(), roots.end());

        for (auto const& root : roots) {
            if (t_range.min <= root && root <= t_range.max) {
                return root;
            }
        }

        return inf<float>();
    }

private:
    std::array<T, 4> a_ = {};
};

} // namespace ltb::geom
