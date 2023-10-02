#pragma once

#include <fftpp/unity.hpp>

#include <complex>
#include <concepts>

namespace fftpp
{
    template <std::floating_point F>
    struct unity_t<std::complex<F>>
    {
        constexpr auto operator () () const
        {
            return std::complex<F>(F{1.0});
        }
    };
}
