#pragma once

#include <fftpp/primitive_root_of_unity.hpp>
#include <fftpp/unity.hpp>

#include <cmath>
#include <complex>
#include <concepts>

namespace fftpp
{
    template <>
    struct primitive_root_of_unity_t<std::complex<double>>
    {
        template <std::integral I>
        constexpr auto operator () (I degree) const
        {
            constexpr auto pi = 3.1415926;
            const auto angle = -2.0 * pi / static_cast<double>(degree);
            return std::complex<double>(std::cos(angle), std::sin(angle));
        }
    };

    template <>
    constexpr auto unity<std::complex<double>> ()
    {
        return std::complex<double>(1.0);
    }
}
