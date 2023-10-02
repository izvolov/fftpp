#pragma once

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
                "did you forget to #include <fftpp/complex.hpp>? "
                "primitive_root_of_unity_t<K> must be specialized to use fftpp::fft<K>"
            );
        }
    };

    template <typename K>
    constexpr auto primitive_root_of_unity = primitive_root_of_unity_t<K>{};
}
