#pragma once

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
                "did you forget to #include <fftpp/complex.hpp>? "
                "unity_t<K> must be specialized to use fftpp::fft<K>"
            );
        }
    };

    template <typename K>
    constexpr auto unity = unity_t<K>{};
}
