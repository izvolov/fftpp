#pragma once

#include <concepts>

namespace fftpp
{
    template <typename K>
    struct primitive_root_of_unity_t
    {
        template <std::integral I>
        auto operator () (I degree) const;
    };

    template <typename K>
    constexpr auto primitive_root_of_unity = primitive_root_of_unity_t<K>{};
}
