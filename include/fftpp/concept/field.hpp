#pragma once

#include <fftpp/primitive_root_of_unity.hpp>
#include <fftpp/unity.hpp>

#include <cstddef>
#include <concepts>

namespace fftpp
{
    template <typename K, typename I = std::size_t>
    concept field =
        std::integral<I> &&
        requires (I n)
        {
            {primitive_root_of_unity<K>(n)} -> std::convertible_to<K>;
            {unity<K>()} -> std::convertible_to<K>;
        };
}
