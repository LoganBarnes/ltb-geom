// ///////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2021 Logan Barnes - All Rights Reserved
// ///////////////////////////////////////////////////////////////////////////////////////
#pragma once

// external
#include <glm/gtc/constants.hpp>

// standard
#include <cmath>

namespace ltb::geom {

template <typename T>
auto is_zero(T x) -> bool {
    constexpr auto eqn_eps = T(1e-16);
    return x > -eqn_eps && x < eqn_eps;
}

/// \brief Solves an equation of the form ax^2 + bx + c = 0
template <typename T>
auto solve_quadratic(T a, T b, T c, T* root1_out, T* root2_out) -> int {
    T p, q, D;

    /* normal form: x^2 + px + q = 0 */

    p = b / (T(2) * a);
    q = c / a;

    D = p * p - q;

    if (is_zero(D)) {
        *root1_out = -p;
        return 1;

    } else if (D < T(0)) {
        return 0;

    } else { /* if (D > 0) */
        float sqrt_D = std::sqrt(D);

        *root1_out = sqrt_D - p;
        *root2_out = -sqrt_D - p;
        return 2;
    }
}

/// \brief Solves an equation of the form ax^3 + bx^2 + cx + d = 0
template <typename T>
auto solve_cubic(T a, T b, T c, T d, T* root1_out, T* root2_out, T* root3_out) -> int {
    int num;
    T   sub;
    T   A, B, C;
    T   sq_A, p, q;
    T   cb_p, D;

    /* normal form: x^3 + Ax^2 + Bx + C = 0 */

    A = b / a;
    B = c / a;
    C = d / a;

    /*  substitute x = y - A/3 to eliminate quadric term:
	x^3 +px + q = 0 */

    sq_A = A * A;
    p    = T(1) / T(3) * (-T(1) / T(3) * sq_A + B);
    q    = T(1) / T(2) * (T(2) / T(27) * A * sq_A - T(1) / T(3) * A * B + C);

    /* use Cardano's formula */

    cb_p = p * p * p;
    D    = q * q + cb_p;

    if (is_zero(D)) {
        if (is_zero(q)) /* one triple solution */
        {
            *root1_out = T(0);
            num        = 1;
        } else /* one single and one double solution */
        {
            auto u     = std::cbrt(-q);
            *root1_out = T(2) * u;
            *root2_out = -u;
            num        = 2;
        }
    } else if (D < 0) /* Casus irreducibilis: three real solutions */
    {
        auto phi = T(1) / T(3) * std::acos(-q / std::sqrt(-cb_p));
        auto t   = T(2) * std::sqrt(-p);

        *root1_out = t * std::cos(phi);
        *root2_out = -t * std::cos(phi + glm::pi<T>() / T(3));
        *root3_out = -t * std::cos(phi - glm::pi<T>() / T(3));
        num        = 3;
    } else /* one real solution */
    {
        auto sqrt_D = std::sqrt(D);
        auto u      = std::cbrt(sqrt_D - q);
        auto v      = -std::cbrt(sqrt_D + q);

        *root1_out = u + v;
        num        = 1;
    }

    /* resubstitute */

    sub = T(1) / T(3) * A;

    switch (num) {
    case 3:
        *root3_out -= sub;

        /* fall-through */
    case 2:
        *root2_out -= sub;

        /* fall-through */
    case 1:
        *root1_out -= sub;
        break;

    default:
        break;
    }

    return num;
}

} // namespace ltb::geom
