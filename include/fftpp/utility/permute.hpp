#pragma once

#include <concepts>
#include <cstddef>
#include <iterator>

#ifndef NDEBUG
#include <algorithm>
#include <cassert>
#include <type_traits>
#include <vector>
#endif

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
#ifndef NDEBUG
        const auto size = static_cast<std::size_t>(length);
        std::vector<std::size_t> new_indices;
        new_indices.reserve(size);
#endif
        auto old_index = D{0};
        while (old_index < length)
        {
            const auto new_index =
                static_cast<std::iter_difference_t<J>>(index(old_index));
#ifndef NDEBUG
            new_indices.push_back(static_cast<std::size_t>(new_index));
#endif

            result[new_index] = *first;

            ++old_index;
            ++first;
        }

#ifndef NDEBUG
        // Проверяем, что произошла именно перестановка, т.е.:
        // - Все индексы уникальны;
        // - Все индексы попадают в размер исходного диапазона.
        std::sort(new_indices.begin(), new_indices.end());
        new_indices.erase(std::unique(new_indices.begin(), new_indices.end()), new_indices.end());
        assert(new_indices.size() == size);
        assert(std::ranges::all_of(new_indices, [size] (auto x) {return x < size;}));
#endif

        return result + static_cast<std::iter_difference_t<J>>(length);
    }
}
