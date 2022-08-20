#pragma once

#include <bit>
#include <concepts>

namespace fftpp
{
    template <std::unsigned_integral N>
    constexpr bool is_power_of_2 (N x)
    {
        return std::has_single_bit(x);
    }
}
