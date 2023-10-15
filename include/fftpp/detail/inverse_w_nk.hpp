#pragma once

#include <concepts>
#include <iterator>

namespace fftpp::detail
{
    /*!
        \~english
            \brief
                A fast search for inverse element to w_nk

            \details
                Roots of unity of power `n` forms a group of size `n`. For each element of that
                group `w_n^k, k ∈ {1, ..., n / 2 - 1}` it is true that:

                    `w_n^(n / 2) * w_n^(n / 2 - k) * w_n^k = 1`

                I.e. product of `w_n^(n / 2)` and `w_n^(n / 2 - k)` is the inverse element
                to `w_n^k`.

                Thus, having elements of powers up to and including `n / 2`, one can calculate
                the inverse to any element of degree up to `n / 2` using just one multiplication.

        \~russian
            \brief
                Быстрый поиск обратного элемента к w_nk

            \details
                Корни из единицы степени `n` образуют группу размера `n`. Для каждого элемента
                этой группы `w_n^k, k ∈ {1, ..., n / 2 - 1}` верно следующее утверждение:

                    `w_n^(n / 2) * w_n^(n / 2 - k) * w_n^k = 1`

                То есть произведение элементов `w_n^(n / 2)` и `w_n^(n / 2 - k)` является
                обратным элементом к `w_n^k`.

                Таким образом, имея на руках элементы степеней до `n / 2` включительно, можно
                за одно произведение вычислить обратный к любому элементу степени до `n / 2`.

        \~
            \see detail::fill_w_nk
     */
    template <std::random_access_iterator I>
    class inverse_w_nk_t
    {
    public:
        using D = std::iter_difference_t<I>;

        /*!
            \~english
                \brief
                    Creates an instance of the fast search for inverse element to w_nk

                \param w_n
                    Iterator to the beginning of group of roots of unity of power `size`.
                \param size
                    Size of the group.

                \pre
                    At least the `size / 2 + 1` of elements is available from the `w_n` iterator.

            \~russian
                \brief
                    Создание экземпляра быстрого поиск обратного элемента к w_nk

                \param w_n
                    Итератор на первый из элементов группы корней из единицы размера `size`.
                \param size
                    Размер группы.

                \pre
                    Из итератора `w_n` доступно хотя бы `size / 2 + 1` элементов.

            \~
                \see detail::fill_w_nk
         */
        inverse_w_nk_t (I w_n, D size):
            m_w_n(w_n),
            m_size_2(size / 2)
        {
        }

        constexpr auto operator [] (D k) const
        {
            if (k == 0)
            {
                return m_w_n[0];
            }
            else
            {
                return m_w_n[m_size_2] * m_w_n[m_size_2 - k];
            }
        }

    private:
        I m_w_n;
        D m_size_2;
    };
}
