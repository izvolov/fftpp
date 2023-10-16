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
            ring_t<N>{2207278994},
            ring_t<N>{613406496},
            ring_t<N>{741264833},
            ring_t<N>{122509875},
            ring_t<N>{2746140649},
            ring_t<N>{1068583503},
            ring_t<N>{708503697},
            ring_t<N>{1363205573},
            ring_t<N>{746485901},
            ring_t<N>{494608121},
            ring_t<N>{3162603993},
            ring_t<N>{1590401422},
            ring_t<N>{2831319379},
            ring_t<N>{2823078715},
            ring_t<N>{1003735924},
            ring_t<N>{1287601835},
            ring_t<N>{896867674},
            ring_t<N>{1045839643},
            ring_t<N>{1852389738},
            ring_t<N>{212052632},
            ring_t<N>{52829935},
            ring_t<N>{882575513},
            ring_t<N>{3098264284},
            ring_t<N>{891569319},
            ring_t<N>{498210922},
            ring_t<N>{815730721},
            ring_t<N>{28561},
            ring_t<N>{169},
            ring_t<N>{13}
        };
}
