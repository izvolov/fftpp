#pragma once

namespace fftpp
{
    template <typename K>
    struct unity_t
    {
        K operator () () const;
    };

    template <typename K>
    constexpr auto unity = unity_t<K>{};
}
