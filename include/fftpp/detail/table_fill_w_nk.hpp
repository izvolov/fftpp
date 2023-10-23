#pragma once

#include <fftpp/concept/field.hpp>
#include <fftpp/detail/fill_w_nk.hpp>
#include <fftpp/utility/is_power_of_2.hpp>

#include <algorithm>
#include <array>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <iterator>

namespace fftpp::detail
{
    template <field K, std::size_t Size>
#if defined __GNUC__ && __GNUC__ >= 10
    constexpr
#endif
    inline const auto base_w_nk_table =
        []{
            std::array<K, Size - 1> coefficients;
            fill_w_nk(coefficients.begin(), Size);
            return coefficients;
        }();

    /*!
        \~english
            \brief
                Gathers `w_n^k` elements for FFT based on a precalculated table

            \details
                If `size <= PrecalcSize`, then copies ready elements from the table.
                In other case, copies ready elements and then calculated the rest using
                `detail::fill_w_nk_iteration` function.

                All the elements are being written to the same range, one after another.

                Complexity:
                -   Time: `O(size)`;
                -   Memory: `O(1)`, excluding preallocated memory.

            \tparam PrecalsSize
                Size of the table to be calculated at compile time.
            \param first
                Iterator to the beginning of a range to write the result to.
            \param size
                Size of the FFT.

            \returns
                Iterator in the given range, one past the last written element.

            \pre
                At least the `size - 1` elements is available from the `first`
                iterator.
            \pre
                `size = 2 ^ m, m ∈ ℕ`
            \pre
                `PrecalcSize = 2 ^ m, m ∈ ℕ`

        \~russian
            \brief
                Собрать коэффициенты `w_n^k` для БПФ на основе предпосчитанной таблицы

            \details
                Если `size <= PrecalcSize`, то просто копирует готовые элементы из таблицы. В
                противном случае копирует имеющиеся элементы, а затем досчитывает остальные с
                помощью `detail::fill_w_nk_iteration`.

                Все элементы записываются подряд в один и тот же диапазон.

                Асимптотика:
                -   Время: `O(size)`;
                -   Память: `O(1)`, не считая заранее выделенной памяти.

            \tparam PrecalcSize
                Размер таблицы, которая будет предпосчитана на этапе компиляции.
            \param first
                Итератор на начало диапазона, в который нужно записать результат.
            \param size
                Размер БПФ.

            \returns
                Итератор за последним записанным элементом.

            \pre
                Из итератора `first` доступно хотя бы `size - 1` элементов.
            \pre
                `size = 2 ^ m, m ∈ ℕ`
            \pre
                `PrecalcSize = 2 ^ m, m ∈ ℕ`

        \~
            \see detail::fill_w_nk_iteration
            \see detail::base_w_nk_table
            \see detail::fill_w_nk
     */
    template
    <
        std::size_t PrecalcSize,
        std::random_access_iterator I,
        std::integral D = std::iter_difference_t<I>
    >
        requires(field<std::iter_value_t<I>, D>)
    constexpr I table_fill_w_nk (I first, D size)
    {
        assert(size > 0);
        assert(is_power_of_2(static_cast<std::size_t>(size)));

        using K = std::iter_value_t<I>;

        constexpr const auto & table_n = base_w_nk_table<K, PrecalcSize>;
        const auto common_part = std::min(PrecalcSize, size);
        first = std::copy_n(table_n.begin(), common_part - 1, first);

        for (auto n = common_part * 2; n <= size; n *= 2)
        {
            first = fill_w_nk_iteration(first, n);
        }

        return first;
    }
}
