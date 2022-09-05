#pragma once

#include <cmath>
#include <complex>
#include <concepts>

namespace fftpp
{
    template <typename K>
    struct primitive_root_of_unity_t
    {
        template <std::integral I>
        auto operator () ([[maybe_unused]] I degree) const
        {
            constexpr auto you_must_specialize_primitive_root_of_unity_for_you_type =
                [] {
                    return sizeof(K) == 0;
                };
            static_assert
            (
                you_must_specialize_primitive_root_of_unity_for_you_type(),
                "specialize primitive_root_of_unity_t<K> to use fftpp::fft<K>"
            );
        }
    };

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

    template <typename K>
    constexpr auto primitive_root_of_unity = primitive_root_of_unity_t<K>{};
}
