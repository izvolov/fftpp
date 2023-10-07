#pragma once

#include <fftpp/ring/ring.hpp>

#include <array>
#include <concepts>

namespace fftpp::detail
{
    template <std::unsigned_integral N>
    constexpr auto primitive_roots_table =
        std::array
        {
            ring_t<N>{1},
            ring_t<N>{3221225472},
            ring_t<N>{1013946479},
            ring_t<N>{613406496},
            ring_t<N>{389840960},
            ring_t<N>{66931328},
            ring_t<N>{217962464},
            ring_t<N>{203410942},
            ring_t<N>{434673},
            ring_t<N>{14006295},
            ring_t<N>{713377},
            ring_t<N>{3985459},
            ring_t<N>{193854},
            ring_t<N>{602020},
            ring_t<N>{243624},
            ring_t<N>{843},
            ring_t<N>{15690},
            ring_t<N>{25001},
            ring_t<N>{12014},
            ring_t<N>{348},
            ring_t<N>{8181},
            ring_t<N>{1111},
            ring_t<N>{2412},
            ring_t<N>{86},
            ring_t<N>{89},
            ring_t<N>{11},
            ring_t<N>{9},
            ring_t<N>{3},
            ring_t<N>{8},
            ring_t<N>{14},
            ring_t<N>{13}
        };
}
