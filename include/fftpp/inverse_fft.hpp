#pragma once

#include <fftpp/concept/field.hpp>
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
                    To calculate the inverse FFT, we need to take advantage of the fact that we
                    need to find

                        InverseDFT = 1/n * (A(w_n^-0), A(w_n^-1), ..., A(w_n^-(n-1)), n = size()

                    At the same time,

                        w_n^-k = w_n^(n-k)

                    Therefore,

                        InverseDFT = 1/n * (A(w_n^0), A(w_n^(n-1)), ..., A(w_n^1)

                    In another words, we need to reverse positions [1, n) of the resulting
                    range and multiply each element of the result by the inverse element of
                    `size()`.

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
                    Для вычисления обратного БПФ нужно воспользоваться тем фактом, что требуется
                    найти

                        InverseDFT = 1/n * (A(w_n^-0), A(w_n^-1), ..., A(w_n^-(n-1)), n = size()

                    При этом

                        w_n^-k = w_n^(n-k)

                    Значит,

                        InverseDFT = 1/n * (A(w_n^0), A(w_n^(n-1)), ..., A(w_n^1)

                    Иными словами, нужно развернуть массив на позициях [1, n) задом наперёд
                    и домножить каждый элемент результата на обратный к `size()` элемент.

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
                \see fft_t::size
                \see inverse_power_of_2
         */
        template <std::random_access_iterator I, std::random_access_iterator J>
            requires(std::convertible_to<std::iter_value_t<I>, K>)
        J operator () (I first, J result) const
        {
            const auto result_end = m_fft(first, result);

            std::reverse(result + 1, result_end);
            return
                std::transform(result, result_end, result,
                    [inverse_n = inverse_power_of_2<K>(m_fft.size())] (auto x)
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
