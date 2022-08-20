#pragma once

#include <bit>
#include <concepts>
#include <stdexcept>
#include <type_traits>

namespace fftpp
{
    namespace detail
    {
        template <std::integral D>
        constexpr D intlog2_impl (D n)
        {
            const auto signed_n = static_cast<std::make_unsigned_t<D>>(n);
            const auto power_of_2 = std::bit_width(signed_n) - 1;
            return static_cast<D>(power_of_2);
        }
    }

    template <std::integral D>
    constexpr D intlog2 (D n)
    {
        constexpr auto error_message = "Двоичный логарифм не определён на неположительных числах.";
        return n > 0 ? detail::intlog2_impl(n) : throw std::domain_error(error_message);
    }
}
