#pragma once

#include <fftpp/primitive_root_of_unity.hpp>
#include <fftpp/ring/detail/primitive_roots_table.hpp>
#include <fftpp/ring/ring.hpp>
#include <fftpp/utility/intlog2.hpp>
#include <fftpp/utility/is_power_of_2.hpp>

#include <cassert>
#include <concepts>
#include <cstddef>

namespace fftpp
{
    template <std::unsigned_integral N>
    struct primitive_root_of_unity_t<ring_t<N>>
    {
        template <std::integral I>
        constexpr auto operator () (I degree) const
        {
            assert(degree > 0);
            assert(is_power_of_2(static_cast<std::size_t>(degree)));

            const auto index = intlog2(static_cast<std::size_t>(degree));
            assert(index < detail::primitive_roots_table<N>.size());

            return detail::primitive_roots_table<N>[index];
        }
    };
}
