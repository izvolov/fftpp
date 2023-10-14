#pragma once

#include <cstddef>
#include <concepts>

namespace fftpp
{
    template <typename T, typename D = std::ptrdiff_t>
    concept subscriptable =
        requires (T x, D pos)
        {
            x[pos];
        };
}
