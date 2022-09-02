#pragma once

#include <fftpp/utility/is_power_of_2.hpp>

#include <algorithm>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <iterator>

namespace fftpp
{
    // https://en.wikipedia.org/wiki/Bit-reversal_permutation
    template <std::forward_iterator I, std::sentinel_for<I> S>
        requires(std::integral<std::iter_value_t<I>>)
    constexpr I bit_reversal_permutation (I indices_first, S indices_last)
    {

        if (indices_first != indices_last)
        {
            *indices_first = std::iter_value_t<I>{0};
            auto end = std::next(indices_first);

            while (end != indices_last)
            {
                std::for_each(indices_first, end,
                    [] (auto & x)
                    {
                        x *= 2;
                    });

                end =
                    std::transform(indices_first, end, end,
                        [] (auto x)
                        {
                            return ++x;
                        });
            }

            return end;
        }

        return indices_first;
    }

    // https://en.wikipedia.org/wiki/Bit-reversal_permutation
    template <std::random_access_iterator I, std::integral D>
        requires(std::integral<std::iter_value_t<I>>)
    constexpr I bit_reversal_permutation (I indices, D size)
    {
        assert(size >= 0);
        assert(is_power_of_2(static_cast<std::size_t>(size)));

        const auto distance = static_cast<std::iter_difference_t<I>>(size);
        return bit_reversal_permutation(indices, indices + distance);
    }
}
