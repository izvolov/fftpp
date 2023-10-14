#pragma once

#include <fftpp/concept/field.hpp>
#include <fftpp/detail/fft_base.hpp>
#include <fftpp/detail/fft_dispose.hpp>
#include <fftpp/detail/fft_impl.hpp>

#include <concepts>
#include <iterator>

namespace fftpp
{
    /*!
        \~english
            \brief
                Fast Fourier transform

            \tparam K
                The type of the elements that will make up the range to which the FFT will be
                applied.
                Must satisfy the requirements of `field` concept.

        \~russian
            \brief
                Быстрое преобразование Фурье

            \tparam K
                Тип элементов, к диапазону которых будет применяться БПФ.
                Должен удовлетворять требованиям концепции `field`.

        \~
            \see field
     */
    template <field K>
    class fft_t: public fft_base_t<K>
    {
    private:
        using base_type = fft_base_t<K>;

    public:
        using base_type::base_type;

        /*!
            \~english
                \brief
                    Apply FFT

                \details
                    Uses the precalculated roots of unity and the indices of bit-reversal
                    permutation to apply the FFT to the input range.

                    Complexity:
                    -   Time: `O(size() * log(size()))`;
                    -   Memory (to store the result): `O(size())`.

                \param first
                    Iterator to the beginning of a sequence to apply the FFT to.
                \param result
                    Iterator to the beginning of a range where the result will be stored.

                \pre
                    At least the `size()` of elements is available from the `first` iterator.
                \pre
                    At least the `size()` of elements is available from the `result` iterator.

            \~russian
                \brief
                    Вычисление БПФ

                \details
                    Использует предпосчитанные корни из единицы и индексы бит-реверсивной
                    перестановки для применения БПФ к входному диапазону.

                    Асимптотика:
                    -   Время: `O(size() * log(size()))`;
                    -   Память (для хранения результата): `O(size())`.

                \param first
                    Итератор на первый из элементов, к которым нужно применить БПФ.
                \param result
                    Итератор на первый элемент диапазона, куда будет записан результат.

                \pre
                    Из итератора `first` доступно хотя бы `size()` элементов.
                \pre
                    Из итератора `result` доступно хотя бы `size()` элементов.

            \~
                \see size
                \see detail::fft_dispose
                \see detail::fft_impl
         */
        template <std::random_access_iterator I, std::random_access_iterator J>
            requires(std::convertible_to<std::iter_value_t<I>, K>)
        J operator () (I first, J result) const
        {
            const auto size = static_cast<std::iter_difference_t<I>>(base_type::size());

            if (size > 1)
            {
                detail::fft_dispose(first, size, result, base_type::bitrev().begin());
                detail::fft_impl(result, size, base_type::w_nk().begin());
            }

            return result + size;
        }
    };
}
