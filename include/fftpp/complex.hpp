#pragma once

#include <fftpp/primitive_root_of_unity.hpp>
#include <fftpp/unity.hpp>

#include <cmath>
#include <complex>
#include <concepts>

namespace fftpp
{
    template <std::floating_point F>
    struct primitive_root_of_unity_t<std::complex<F>>
    {
        template <std::integral I>
        constexpr auto operator () (I degree) const
        {
            constexpr auto pi = std::acos(F{-1.0});
            const auto angle = F{-2.0} * pi / static_cast<F>(degree);
            return std::complex<F>(std::cos(angle), std::sin(angle));
        }
    };

    template <std::floating_point F>
    struct unity_t<std::complex<F>>
    {
        constexpr auto operator () () const
        {
            return std::complex<F>(F{1.0});
        }
    };
}
