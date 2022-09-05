#pragma once

#include <cassert>
#include <concepts>
#include <cstddef>
#include <iterator>

namespace fftpp
{
    /*!
        \~english
            \brief
                Apply permutation given by function

            \details
                Writes each `i`th element of the input sequent to position `f(i)` of the resulting
                sequence, i.e. `result[f(i)] = first[i], i = [0, ..., length - 1]`.

            \param first
                Iterator to the beginning of a sequence to apply the permutation to.
            \param length
                Length of the permutation.
            \param result
                Iterator to the beginning of a range where the resulting permutation will be saved.
            \param index
                Function that maps indices of the original sequence to indices of the resulting
                sequence.

            \returns
                Iterator in the resulting range, one past the last element of the permutation.

            \pre
                At least the `length` of elements is available from the `first` iterator.
            \pre
                At least the `length` of elements is available from the `result` iterator.
            \pre
                `index` function sets a permutation, i.e. bijection from set of indices
                `[0, ..., length - 1]` to itselt.

        \~russian
            \brief
                Применить перестановку, заданную функцией

            \details
                Записывает каждый `i`-й элемент исходной последовательности на позицию `f(i)`
                результирующей так, что `result[f(i)] = first[i], i = [0, ..., length - 1]`.

            \param first
                Итератор на первый из элементов, к которым нужно применить перестановку.
            \param length
                Длина перестановки.
            \param result
                Итератор на первый элемент диапазона, куда будет записан результат перестановки.
            \param index
                Функция, отображающая индексы исходной последовательности в индексы результирующей
                последовательности.

            \returns
                Итератор за последним элементом результирующей перестановки.

            \pre
                Из итератора `first` доступно хотя бы `length` элементов.
            \pre
                Из итератора `result` доступно хотя бы `length` элементов.
            \pre
                Функция `index` задаёт перестановку, то есть биекцию множества
                индексов `[0, ..., length - 1]` на себя.
     */
    template
    <
        std::forward_iterator I,
        std::integral D,
        std::random_access_iterator J,
        std::regular_invocable<D> F
    >
    constexpr J permute (I first, D length, J result, F index)
    {
        auto old_index = D{0};
        while (old_index < length)
        {
            const auto new_index =
                static_cast<std::iter_difference_t<J>>(index(old_index));
            assert(static_cast<D>(new_index) < length);

            result[new_index] = *first;

            ++old_index;
            ++first;
        }

        return result + static_cast<std::iter_difference_t<J>>(length);
    }
}
