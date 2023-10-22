#pragma once

#include <fftpp/concept/field.hpp>
#include <fftpp/detail/fill_w_nk.hpp>
#include <fftpp/utility/is_power_of_2.hpp>

#include <algorithm>
#include <array>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <iterator>

namespace fftpp::detail
{
    template <field K>
    constexpr auto base_w_nk_table =
        []{
            constexpr auto size = 256ul;
            std::array<K, size - 1> coefficients;
            fill_w_nk(coefficients.begin(), size);
            return coefficients;
        }();

    template <std::random_access_iterator I, std::integral D = std::iter_difference_t<I>>
        requires(field<std::iter_value_t<I>, D>)
    constexpr I table_fill_w_nk (I first, D size)
    {
        assert(size > 0);
        assert(is_power_of_2(static_cast<std::size_t>(size)));

        using K = std::iter_value_t<I>;

        constexpr const auto & table_n = base_w_nk_table<K>;
        const auto common_part = std::min(table_n.size() + 1, size);
        first = std::copy_n(table_n.begin(), common_part - 1, first);

        for (auto n = common_part * 2; n <= size; n *= 2)
        {
            first = fill_w_nk_iteration(first, n);
        }

        return first;
    }
}
