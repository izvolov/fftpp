#pragma once

#include <fftpp/inverse_power_of_2.hpp>
#include <fftpp/utility/is_power_of_2.hpp>

#include <cassert>
#include <complex>
#include <concepts>

namespace fftpp
{
    template <std::floating_point F>
    struct inverse_power_of_2_t<std::complex<F>>
    {
        template <std::integral N>
        constexpr auto operator () (N n) const
        {
            assert(n > 0);
            assert(is_power_of_2(static_cast<std::make_unsigned_t<N>>(n)));

            return std::complex<F>(F{1.0} / static_cast<F>(n));
        }
    };
}
