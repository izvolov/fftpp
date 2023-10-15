#pragma once

#include <cassert>
#include <concepts>

namespace fftpp
{
    // http://e-maxx.ru/algo/binary_pow
    template <typename N, std::integral M>
    constexpr N binpow (N x, M power)
    {
        assert(power > 0);

        auto result = N{1};
        while (power > 0)
        {
            if ((power & M{1}) != M{0})
            {
                result *= x;
                --power;
            }
            else
            {
                x *= x;
                power /= 2;
            }
        }

        return result;
    }
}
