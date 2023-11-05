#pragma once

#include <fftpp/inverse_power_of_2.hpp>
#include <fftpp/ring/basic_ring.hpp>
#include <fftpp/ring/detail/power_of_2_inverse_elements_table.hpp>
#include <fftpp/utility/intlog2.hpp>
#include <fftpp/utility/is_power_of_2.hpp>

#include <cassert>
#include <concepts>
#include <cstdint>

namespace fftpp
{
    template <std::uint32_t Mod, std::unsigned_integral Rep>
    struct inverse_power_of_2_t<basic_ring<Mod, Rep>>
    {
        using ring_type = basic_ring<Mod, Rep>;

        template <std::integral M>
        constexpr auto operator () (M n) const
        {
            assert(n > 0);
            assert(is_power_of_2(static_cast<std::make_unsigned_t<M>>(n)));

            const auto index = intlog2(static_cast<std::size_t>(n));
            assert(index < detail::power_of_2_inverse_elements_table_v<ring_type>.size());

            return detail::power_of_2_inverse_elements_table_v<ring_type>[index];
        }
    };
}
