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

enum Corner3d {
    C000,
    C100,
    C010,
    C110,
    C001,
    C101,
    C011,
    C111,
};

/// \brief Performs trilinear interpolation for a point in a cube.
///
/// \code
/// Box Q:
///
///          Q122------Q222
///          / :       / |
///  y2 -- Q121------ Q221  ---
///         |  :      |  |   |
///         |Q112 - - |Q212  | yd     --- z2      ---
///         |         | /    |                    / zd
///  y1 -- Q111------Q211   ---     --- z1      ---
///         |          |
///         x1         x2
///
///         | -------- |
///              xd
///
/// The value of some function f(x,y,z) at some point (x,y,z) in the box Q can
/// be approximated with trilinear interpolation defined as:
///
/// f(x,y,z) = a0
///          + a1 * x
///          + a2 * y
///          + a3 * z
///          + a4 * x * y
///          + a5 * x * z
///          + a6 * y * z
///          + a7 * x * y * z
///
/// where:
/// a0 = (+f(Q11) * x2 * y2 - f(Q12) * x2 * y1 - f(Q21) * x1 * y2 + f(Q22) * x1 * y1) / (xd * yd * zd)
/// a1 = (-f(Q11)      * y2 + f(Q12)      * y1 + f(Q21)      * y2 - f(Q22)      * y1) / (xd * yd * zd)
/// a2 = (-f(Q11) * x2      + f(Q12) * x2      + f(Q21) * x1      - f(Q22) * x1     ) / (xd * yd * zd)
/// a3 = (+f(Q11)           - f(Q12)           - f(Q21)           + f(Q22)          ) / (xd * yd * zd)
///
/// and
/// d = (x1 - x2) * (y1 - y2) * (z1 - z2)
/// \endcode
///
template <typename T>
struct Interpolator<3, T> {

    explicit Interpolator(geom::Box<3, T> const& box, std::array<T, 8> const& values) {
        auto const& x0 = box.min_point.x;
        auto const& x1 = box.max_point.x;
        auto const& y0 = box.min_point.y;
        auto const& y1 = box.max_point.y;
        auto const& z0 = box.min_point.z;
        auto const& z1 = box.max_point.z;

        auto const xd    = x0 - x1;
        auto const yd    = y0 - y1;
        auto const zd    = z0 - z1;
        auto const denom = xd * yd * zd;

        auto const& c000 = values[Corner3d::C000];
        auto const& c100 = values[Corner3d::C100];
        auto const& c010 = values[Corner3d::C010];
        auto const& c110 = values[Corner3d::C110];
        auto const& c001 = values[Corner3d::C001];
        auto const& c101 = values[Corner3d::C101];
        auto const& c011 = values[Corner3d::C011];
        auto const& c111 = values[Corner3d::C111];

        a_ = {
            (-c000 * x1 * y1 * z1 + c001 * x1 * y1 * z0 + c010 * x1 * y0 * z1 - c011 * x1 * y0 * z0 // a0
             + c100 * x0 * y1 * z1 - c101 * x0 * y1 * z0 - c110 * x0 * y0 * z1 + c111 * x0 * y0 * z0)
                / denom,
            (+c000 * y1 * z1 - c001 * y1 * z0 - c010 * y0 * z1 + c011 * y0 * z0 // a1
             - c100 * y1 * z1 + c101 * y1 * z0 + c110 * y0 * z1 - c111 * y0 * z0)
                / denom,
            (+c000 * x1 * z1 - c001 * x1 * z0 - c010 * x1 * z1 + c011 * x1 * z0 // a2
             - c100 * x0 * z1 + c101 * x0 * z0 + c110 * x0 * z1 - c111 * x0 * z0)
                / denom,
            (+c000 * x1 * y1 - c001 * x1 * y1 - c010 * x1 * y0 + c011 * x1 * y0 // a3
             - c100 * x0 * y1 + c101 * x0 * y1 + c110 * x0 * y0 - c111 * x0 * y0)
                / denom,
            (-c000 * z1 + c001 * z0 + c010 * z1 - c011 * z0 + c100 * z1 - c101 * z0 - c110 * z1 + c111 * z0) // a4
                / denom,
            (-c000 * y1 + c001 * y1 + c010 * y0 - c011 * y0 + c100 * y1 - c101 * y1 - c110 * y0 + c111 * y0) // a5
                / denom,
            (-c000 * x1 + c001 * x1 + c010 * x1 - c011 * x1 + c100 * x0 - c101 * x0 - c110 * x0 + c111 * x0) // a6
                / denom,
            (c000 - c001 - c010 + c011 - c100 + c101 + c110 - c111) // a7
                / denom,
        };
    }

    /// \brief Interpolate the value at `point`
    auto operator()(glm::vec<3, T> const& point) -> T {
        auto const& x = point.x;
        auto const& y = point.y;
        auto const& z = point.z;

        return a_[0] //
            + a_[1] * x //
            + a_[2] * y //
            + a_[3] * z //
            + a_[4] * x * y //
            + a_[5] * x * z //
            + a_[6] * y * z //
            + a_[7] * x * y * z;
    }

    /// \brief Find the intersection point with `ray`
    auto operator()(Ray<3, T> const& ray, Range<T> const& t_range) -> T {
        auto const& o = ray.origin;
        auto const& d = ray.direction;

        auto const coeff_a = a_[7] * d.x * d.y * d.z;
        auto const coeff_b = a_[4] * d.x * d.y //
            + a_[5] * d.x * d.z //
            + a_[6] * d.y * d.z //
            + a_[7] * (o.x * d.y * d.z + d.x * o.y * d.z + d.x * d.y * o.z);
        auto const coeff_c = a_[1] * d.x //
            + a_[2] * d.y //
            + a_[3] * d.z //
            + a_[4] * (d.x * o.y + o.x * d.y) //
            + a_[5] * (d.x * o.z + o.x * d.z) //
            + a_[6] * (d.y * o.z + o.y * d.z) //
            + a_[7] * (d.x * o.y * o.z + o.x * d.y * o.z + o.x * o.y * d.z);
        auto const coeff_d = a_[0] //
            + a_[1] * o.x //
            + a_[2] * o.y //
            + a_[3] * o.z //
            + a_[4] * o.x * o.y //
            + a_[5] * o.x * o.z //
            + a_[6] * o.y * o.z //
            + a_[7] * o.x * o.y * o.z;

        std::array<T, 3> roots;
        for (auto& root : roots) {
            root = inf<float>();
        }

        if (is_zero(coeff_a)) {
            if (is_zero(coeff_b)) {
                // Linear: ct + d = 0
                roots[0] = -coeff_d / coeff_c;
            } else {
                // Quadratic: bt^2 + ct + d = 0
                solve_quadratic(coeff_b, coeff_c, coeff_d, &roots[0], &roots[1]);
            }
        } else {
            // Cubic: at^3 + bt^2 + ct + d = 0
            solve_cubic(coeff_a, coeff_b, coeff_c, coeff_d, &roots[0], &roots[1], &roots[2]);
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
    std::array<T, 8> a_ = {};
};

} // namespace ltb::geom
