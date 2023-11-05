#pragma once

#include <fftpp/ring/basic_ring.hpp>

#include <concepts>
#include <cstdint>

namespace fftpp
{
    /*!
        \~english
            \brief
                Modulo ring up to `2 ^ 8`

            \details
                Eight means that the maximum size of the array to which the FFT is applicable
                is `2 ^ 8'.

        \~russian
            \brief
                Кольцо вычетов до `2 ^ 8`

            \details
                Восьмёрка означает, что максимальный размер массива с элементами данного типа,
                к которому применимо БПФ, — `2 ^ 8`.

        \~
            \see basic_ring
     */
    using ring8 = basic_ring<257, std::uint32_t>;

    /*!
        \~english
            \brief
                Modulo ring up to `2 ^ 16`

            \details
                Sixteen means that the maximum size of the array to which the FFT is applicable
                is `2 ^ 16'.

        \~russian
            \brief
                Кольцо вычетов до `2 ^ 16`

            \details
                Шестнадцать означает, что максимальный размер массива с элементами данного типа,
                к которому применимо БПФ, — `2 ^ 16`.

        \~
            \see basic_ring
     */
    using ring16 = basic_ring<65537, std::uint64_t>;

    /*!
        \~english
            \brief
                Modulo ring up to `2 ^ 30`

            \details
                Thirty means that the maximum size of the array to which the FFT is applicable
                is `2 ^ 30'.

        \~russian
            \brief
                Кольцо вычетов до `2 ^ 30`

            \details
                Тридцать означает, что максимальный размер массива с элементами данного типа,
                к которому применимо БПФ, — `2 ^ 30`.

        \~
            \warning
                `30 < 32`

            \see basic_ring
     */
    using ring30 = basic_ring<3221225473, std::uint64_t>;
}
