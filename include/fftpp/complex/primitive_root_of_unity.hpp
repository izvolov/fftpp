#pragma once

#include <fftpp/primitive_root_of_unity.hpp>

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
            constexpr auto pi = F{3.141592653589793238462643383279502884};
            const auto angle = F{-2.0} * pi / static_cast<F>(degree);
            return std::complex<F>(std::cos(angle), std::sin(angle));
        }
    };
}
