#pragma once

#include <fftpp/utility/intlog2.hpp>
#include <fftpp/utility/reverse_lower_bits.hpp>

#include <cassert>
#include <concepts>
#include <iterator>

namespace fftpp::detail
{
    template
    <
        std::random_access_iterator I,
        std::integral D = std::iter_difference_t<I>,
        std::random_access_iterator J
    >
    void fft_dispose (I first, D distance, J result)
    {
        const auto power_of_2 = intlog2(distance);
        for (auto old_index = D{0}; old_index < distance; ++old_index)
        {
            const auto new_index = reverse_lower_bits(old_index, power_of_2);
            assert(new_index < distance);
            result[new_index] = first[old_index];
        }
    }
}
