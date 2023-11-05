#pragma once

#include <fftpp/primitive_root_of_unity.hpp>
#include <fftpp/ring/basic_ring.hpp>
#include <fftpp/ring/detail/primitive_roots_table.hpp>
#include <fftpp/utility/intlog2.hpp>
#include <fftpp/utility/is_power_of_2.hpp>

#include <cassert>
#include <concepts>
#include <cstddef>
#include <cstdint>

namespace fftpp
{
    template <std::uint32_t Mod, std::unsigned_integral Rep>
    struct primitive_root_of_unity_t<basic_ring<Mod, Rep>>
    {
        using ring_type = basic_ring<Mod, Rep>;

        template <std::integral I>
        constexpr auto operator () (I degree) const
        {
            assert(degree > 0);
            assert(is_power_of_2(static_cast<std::size_t>(degree)));

            const auto index = intlog2(static_cast<std::size_t>(degree));
            assert(index < detail::primitive_roots_table_v<ring_type>.size());

            return detail::primitive_roots_table_v<ring_type>[index];
        }
    };
}
