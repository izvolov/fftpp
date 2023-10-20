#pragma once

#include <fftpp/ring/ring.hpp>

#include <array>
#include <concepts>

namespace fftpp::detail
{
    template <std::unsigned_integral N>
    constexpr auto power_of_2_inverse_elements_table =
        std::array
        {
            ring_t<N>{1},
            ring_t<N>{1610612737},
            ring_t<N>{2415919105},
            ring_t<N>{2818572289},
            ring_t<N>{3019898881},
            ring_t<N>{3120562177},
            ring_t<N>{3170893825},
            ring_t<N>{3196059649},
            ring_t<N>{3208642561},
            ring_t<N>{3214934017},
            ring_t<N>{3218079745},
            ring_t<N>{3219652609},
            ring_t<N>{3220439041},
            ring_t<N>{3220832257},
            ring_t<N>{3221028865},
            ring_t<N>{3221127169},
            ring_t<N>{3221176321},
            ring_t<N>{3221200897},
            ring_t<N>{3221213185},
            ring_t<N>{3221219329},
            ring_t<N>{3221222401},
            ring_t<N>{3221223937},
            ring_t<N>{3221224705},
            ring_t<N>{3221225089},
            ring_t<N>{3221225281},
            ring_t<N>{3221225377},
            ring_t<N>{3221225425},
            ring_t<N>{3221225449},
            ring_t<N>{3221225461},
            ring_t<N>{3221225467},
            ring_t<N>{3221225470}
        };
}
