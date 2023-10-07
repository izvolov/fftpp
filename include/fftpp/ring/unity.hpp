#pragma once

#include <fftpp/ring/ring.hpp>
#include <fftpp/unity.hpp>

#include <concepts>

namespace fftpp
{
    template <std::integral N>
    struct unity_t<ring_t<N>>
    {
        constexpr auto operator () () const
        {
            return ring_t<N>(1);
        }
    };
}
