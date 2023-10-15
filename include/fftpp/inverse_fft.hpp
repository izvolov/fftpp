#pragma once

#include <fftpp/concept/field.hpp>
#include <fftpp/detail/fft_dispose.hpp>
#include <fftpp/detail/fft_impl.hpp>
#include <fftpp/detail/inverse_w_nk.hpp>
#include <fftpp/fft.hpp>
#include <fftpp/inverse_power_of_2.hpp>

#include <algorithm>
#include <concepts>
#include <iterator>

namespace fftpp
{
    /*!
        \~english
            \brief
                Inverse FFT

            \tparam K
                The type of the elements that will make up the range to which the inverse FFT
                will be applied.
                Must satisfy the requirements of `field` concept.

        \~russian
            \brief
                Обратное БПФ

            \tparam K
                Тип элементов, к диапазону которых будет применяться обратное БПФ.
                Должен удовлетворять требованиям концепции `field`.

        \~
            \see fft_t
            \see field
     */
    template <field K>
    class inverse_fft_t
    {
    public:
        explicit inverse_fft_t (const fft_t<K> & fft):
            m_fft(fft)
        {
        }

        /*!
            \~english
                \brief
                    Apply inverse FFT

                \details
                    In contrast to the direct FFT uses the inverse coefficients `w_nk`, and
                    multiplies each element of the result by the inverse element of `size()`.

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
                    Вычисление обратного БПФ

                \details
                    В отличие от прямого БПФ использует обратные коэффициенты `w_nk`, а также
                    домножает каджый элемент результата на обратный к `size()` элемент.

                    Асимптотика:
                    -   Время: `O(size() * log(size()))`;
                    -   Память (для хранения результата): `O(size())`.

                \param first
                    Итератор на первый из элементов, к которым нужно применить обратное БПФ.
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
                \see detail::inverse_w_nk_t
                \see inverse_power_of_2
         */
        template <std::random_access_iterator I, std::random_access_iterator J>
            requires(std::convertible_to<std::iter_value_t<I>, K>)
        J operator () (I first, J result) const
        {
            const auto size = static_cast<std::iter_difference_t<I>>(m_fft.size());

            if (size > 1)
            {
                detail::fft_dispose(first, size, result, m_fft.bitrev().begin());
                detail::fft_impl(result, size, m_fft.w_nk().begin(),
                    [] (auto w_nk, auto n)
                    {
                        return detail::inverse_w_nk_t(w_nk, n);
                    });
            }

            return
                std::transform(result, result + size, result,
                    [inverse_n = inverse_power_of_2<K>(size)] (auto x)
                    {
                        return x * inverse_n;
                    });
        }

    private:
        const fft_t<K> & m_fft;
    };

    template <field K>
    inverse_fft_t (const fft_t<K> &) -> inverse_fft_t<K>;

    template <field K>
    inverse_fft_t<K> inverse (const fft_t<K> & fft)
    {
        return inverse_fft_t<K>(fft);
    }
}
