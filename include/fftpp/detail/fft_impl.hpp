#pragma once

#include <fftpp/detail/butterfly.hpp>
#include <fftpp/utility/first_of.hpp>

#include <cassert>
#include <concepts>
#include <iterator>

namespace fftpp::detail
{
    template
    <
        std::random_access_iterator I,
        std::integral D = std::iter_difference_t<I>,
        std::random_access_iterator J,
        std::regular_invocable<J, D> P = first_of_t
    >
        requires(subscriptable<std::invoke_result_t<P, J, D>>)
    void fft_impl (I first, D size, J w_nk, P proj = {})
    {
        assert(size >= 0);

        for (auto n = D{2}; n <= size; n *= 2)
        {
            for (auto k = D{0}; k < size; k += n)
            {
                auto begin = first + k;
                auto end = begin + n / 2;
                multi_butterfly(begin, end, end, proj(w_nk, n));
            }

            using std::advance;
            advance(w_nk, n / 2 + 1);
        }
    }
}
