#pragma once

#include <fftpp/utility/intlog2.hpp>
#include <fftpp/utility/permute.hpp>
#include <fftpp/utility/reverse_lower_bits.hpp>

#include <concepts>
#include <iterator>

namespace fftpp::detail
{
    /*!
        \~english
            \brief
                Arrange the elements respect to the FFT algorithm

            \details
                Applies bit-reversal permutation to the input elements and write them to a
                range specified by `result` iterator.

            \param first
                Iterator to the beginning of a sequence to arrange.
            \param distance
                Amount of input elements.
            \param result
                Iterator to the beginning of a range where the result will be saved.

            \returns
                Iterator in the resulting range, one past the last element.

            \pre
                At least the `distance` of elements is available from the `first` iterator.
            \pre
                At least the `distance` of elements is available from the `result` iterator.
            \pre
                Ranges specified by `first` and `result` iterators do not overlap.

        \~russian
            \brief
                Расставить элементы в порядке, необходимом для работы алгоритма БПФ

            \details
                Применяет к исходным элементам бит-реверсивную перестановку, результат которой
                записывается в диапазон, заданный итератором `result`.

            \param first
                Итератор на первый из элементов, которые нужно расставить.
            \param distance
                Количество элементов.
            \param result
                Итератор на начало диапазона, в который будет записан результат.

            \returns
                Итератор за последним элементом в результирующем диапазоне.

            \pre
                Из итератора `first` доступно хотя бы `distance` элементов.
            \pre
                Из итератора `result` доступно хотя бы `distance` элементов.
            \pre
                Диапазоны, задаваемые итераторами `first` и `result`, не пересекаются.

        \~
            \see reverse_lower_bits
            \see permute
            \see intlog2
     */
    template
    <
        std::random_access_iterator I,
        std::integral D = std::iter_difference_t<I>,
        std::random_access_iterator J
    >
    constexpr J fft_dispose (I first, D distance, J result)
    {
        const auto power_of_2 = intlog2(distance);
        const auto reverse_bits =
            [power_of_2] (auto old_index)
            {
                return reverse_lower_bits(old_index, power_of_2);
            };

        return permute(first, distance, result, reverse_bits);
    }

    /*!
        \~english
            \brief
                Arrange the elements respect to the FFT algorithm. This is an overload with a
                precalculated range of indices

            \details
                Applies bit-reversal permutation to the input elements and write them to a
                range specified by `result` iterator.

                    result[indices[i]] = first[i], i = [0, ..., distance - 1]

            \param first
                Iterator to the beginning of a sequence to arrange.
            \param distance
                Amount of input elements.
            \param result
                Iterator to the beginning of a range where the result will be saved.
            \param indices
                Iterator in a range of indices specifying the order of elements in the resulting
                range.

            \returns
                Iterator in the resulting range, one past the last element.

            \pre
                At least the `distance` of elements is available from the `first` iterator.
            \pre
                At least the `distance` of elements is available from the `result` iterator.
            \pre
                At least the `distance` of elements is available from the `indices` iterator.
            \pre
                Ranges specified by `first` and `result` iterators do not overlap.

        \~russian
            \brief
                Расставить элементы в порядке, необходимом для работы алгоритма БПФ.
                Перегрузка с готовым набором индексов

            \details
                Применяет к исходным элементам бит-реверсивную перестановку, результат которой
                записывается в диапазон, заданный итератором `result`.

                    result[indices[i]] = first[i], i = [0, ..., distance - 1]

            \param first
                Итератор на первый из элементов, которые нужно расставить.
            \param distance
                Количество элементов.
            \param result
                Итератор на начало диапазона, в который будет записан результат.
            \param indices
                Итератор на диапазон с готовыми индексами, задающими позиции элементов
                исходного диапазона в результирующем диапазоне.

            \returns
                Итератор за последним элементом в результирующем диапазоне.

            \pre
                Из итератора `first` доступно хотя бы `distance` элементов.
            \pre
                Из итератора `result` доступно хотя бы `distance` элементов.
            \pre
                Из итератора `indices` доступно хотя бы `distance` элементов.
            \pre
                Диапазоны, задаваемые итераторами `first` и `result`, не пересекаются.

        \~
            \see bit_reversal_permutation
            \see permute
     */
    template
    <
        std::random_access_iterator I,
        std::integral D = std::iter_difference_t<I>,
        std::random_access_iterator J,
        std::random_access_iterator K
    >
    constexpr J fft_dispose (I first, D distance, J result, K indices)
    {
        const auto reverse_bits =
            [indices] (auto old_index)
            {
                return indices[old_index];
            };

        return permute(first, distance, result, reverse_bits);
    }
}
