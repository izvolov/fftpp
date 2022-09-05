#pragma once

#include <complex>
#include <concepts>

namespace fftpp
{
    template <typename K>
    struct unity_t
    {
        K operator () () const
        {
            constexpr auto you_must_specialize_unity_for_you_type =
                [] {
                    return sizeof(K) == 0;
                };
            static_assert
            (
                you_must_specialize_unity_for_you_type(),
                "specialize unity_t<K> to use fftpp::fft<K>"
            );
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

    template <typename K>
    constexpr auto unity = unity_t<K>{};
}
