#pragma once

#include <concepts>

namespace fftpp
{
    template <std::integral I, std::integral J>
    constexpr I reverse_lower_bits (I n, J count)
    {
        auto result = I{0};
        for (auto bit = J{0}; bit < count; ++bit)
        {
            result <<= 1;
            result |= (n & 0b1);
            n >>= 1;
        }

        return result;
    }
}
