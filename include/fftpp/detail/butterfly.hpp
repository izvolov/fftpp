#pragma once

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

    template <std::forward_iterator I, std::sentinel_for<I> S, std::forward_iterator J>
    void multi_butterfly (I first1, S last1, I first2, J w_nk)
    {
        while (first1 != last1)
        {
            butterfly(*first1, *first2, *w_nk);

            ++first1;
            ++first2;
            ++w_nk;
        }
    }
}
