#pragma once

#include <concepts>

namespace fftpp
{
    template <typename K>
    struct inverse_power_of_2_t
    {
        template <std::integral N>
        auto operator () ([[maybe_unused]] N n) const
        {
            constexpr auto you_must_specialize_inverse_power_of_2_for_your_type =
                [] {
                    return sizeof(K) == 0;
                };
            static_assert
            (
                you_must_specialize_inverse_power_of_2_for_your_type(),
                "did you forget to #include <fftpp/complex.hpp> or <fftpp/ring.hpp>? "
                "inverse_power_of_2_t<K> must be specialized to use fftpp::inverse_fft<K>"
            );
        }
    };

    template <typename K>
    constexpr auto inverse_power_of_2 = inverse_power_of_2_t<K>{};
}
