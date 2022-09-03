#pragma once

#include <fftpp/utility/bit_reversal_permutation.hpp>
#include <fftpp/utility/intlog2.hpp>
#include <fftpp/utility/is_power_of_2.hpp>

#include <algorithm>
#include <array>
#include <concepts>
#include <cstddef>
#include <iterator>
#include <limits>

namespace fftpp
{
    constexpr auto base_table =
        []{
            std::array<unsigned char, 256> indices;
            bit_reversal_permutation(indices.begin(), indices.size());
            return indices;
        }();

    // https://en.wikipedia.org/wiki/Bit-reversal_permutation
    template <std::random_access_iterator I>
        requires(std::integral<std::iter_value_t<I>>)
    constexpr I table_bit_reversal_permutation (I indices_first, I indices_last)
    {
        using std::distance;
        const auto size = distance(indices_first, indices_last);

        assert(size >= 0);
        assert(is_power_of_2(static_cast<std::size_t>(size)));

        constexpr auto table_size = static_cast<std::iter_difference_t<I>>(base_table.size());

        if (size >= table_size)
        {
            auto end = std::copy_n(base_table.begin(), table_size, indices_first);

            while (end != indices_last)
            {
                end = detail::bit_reversal_permutation_iteration(indices_first, end);
            }

            return end;
        }
        else
        {
            const auto bit_difference = intlog2(table_size) - intlog2(size);
            return
                std::transform(base_table.begin(), base_table.begin() + size, indices_first,
                    [bit_difference] (auto x)
                    {
                        return x >> bit_difference;
                    });
        }
    }

    // https://en.wikipedia.org/wiki/Bit-reversal_permutation
    template <std::random_access_iterator I, std::integral D>
        requires(std::integral<std::iter_value_t<I>>)
    constexpr I table_bit_reversal_permutation (I indices, D size)
    {
        assert(size >= 0);
        assert(is_power_of_2(static_cast<std::size_t>(size)));

        const auto distance = static_cast<std::iter_difference_t<I>>(size);
        return table_bit_reversal_permutation(indices, indices + distance);
    }
}
