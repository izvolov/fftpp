#pragma once

#include <fftpp/primitive_root_of_unity.hpp>
#include <fftpp/utility/cos.hpp>
#include <fftpp/utility/pi.hpp>
#include <fftpp/utility/sin.hpp>

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
            const auto angle = F{-2.0} * pi_v<F> / static_cast<F>(degree);
            return std::complex<F>(cos(angle), sin(angle));
        }
    };
}
