#pragma once

#include <fftpp/concept/field.hpp>

#include <algorithm>
#include <concepts>
#include <iterator>

namespace fftpp::detail
{
    // Требуется size - 1 доступных позиций.
    template <std::random_access_iterator I, std::integral D = std::iter_difference_t<I>>
        requires(field<std::iter_value_t<I>, D>)
    I fill_w_nk (I first, D size)
    {
        using K = std::iter_value_t<I>;

        for (auto n = D{2}; n <= size; n *= 2)
        {
            const auto w_n = primitive_root_of_unity<K>(n);
            // assert(generator_of_group(w_n, n));

            *first = unity<K>();
            const auto last_for_n =
                std::next(first, static_cast<std::iter_difference_t<I>>(n / 2 - 1));
            first =
                std::transform(first, last_for_n, std::next(first),
                    [& w_n] (const auto & value)
                    {
                        return value * w_n;
                    });
        }

        return first;
    }
}
