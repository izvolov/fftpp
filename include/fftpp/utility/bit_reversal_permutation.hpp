#pragma once

#include <fftpp/utility/is_power_of_2.hpp>

#include <algorithm>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <iterator>

namespace fftpp
{
    namespace detail
    {
        template <std::forward_iterator I, std::sentinel_for<I> S>
        constexpr I bit_reversal_permutation_iteration (I chunk_first, S chunk_last)
        {
            std::for_each(chunk_first, chunk_last,
                [] (auto & x)
                {
                    x *= 2;
                });

            return
                std::transform(chunk_first, chunk_last, chunk_last,
                    [] (auto x)
                    {
                        return ++x;
                    });
        }
    }

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
                end = detail::bit_reversal_permutation_iteration(indices_first, end);
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
