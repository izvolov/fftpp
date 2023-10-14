#pragma once

#include <fftpp/concept/subscriptable.hpp>

#include <cstddef>
#include <iterator>
#include <tuple>

namespace fftpp::detail
{
    template <typename V, typename C>
    void butterfly (V & left, V & right, const C & w)
    {
        right *= w;
        std::tie(left, right) = std::make_tuple(left + right, left - right);
    }

    template <std::forward_iterator I, std::sentinel_for<I> S, subscriptable J>
    void multi_butterfly (I first1, S last1, I first2, J w_n)
    {
        auto k = std::ptrdiff_t{0};
        while (first1 != last1)
        {
            butterfly(*first1, *first2, w_n[k]);

            ++first1;
            ++first2;
            ++k;
        }
    }
}
