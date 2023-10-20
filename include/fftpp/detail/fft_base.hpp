#pragma once

#include <fftpp/concept/field.hpp>
#include <fftpp/detail/fill_w_nk.hpp>
#include <fftpp/utility/is_power_of_2.hpp>
#include <fftpp/utility/table_bit_reversal_permutation.hpp>

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <concepts>
#include <vector>

namespace fftpp
{
    /*!
        \~english
            \brief
                Fast Fourier transform base

            \details
                Calculates on initialization and stores bit-reversal permutation indices and all
                the necessary roots of unity that are needed to perform fast Fourier transform.

            \tparam K
                The type of the elements that will make up the range to which the FFT will be
                applied.
                Must satisfy the requirements of `field` concept.

        \~russian
            \brief
                Базовый класс для быстрого преобразования Фурье

            \details
                Вычисляет при инициализации и хранит в себе индексы бит-реверсивной перестановки и
                корни из единицы, которые нужны для проведения непосредственно быстрого
                преобразования Фурье.

            \tparam K
                Тип элементов, к диапазону которых будет применяться БПФ.
                Должен удовлетворять требованиям концепции `field`.

        \~
            \see field
     */
    template <field K>
    class fft_base_t
    {
    public:
        /*!
            \~english
                \brief
                    FFT initialization

                \details
                    Precalculates and stores roots of unity for all powers of 2 up to `size` as well
                    as the indices of bit-reversal permutation of the given `size`.

                    Complexity:
                    -   Time: `O(size)`;
                    -   Memory (of the resulting object): `O(size)`.

                \param size
                    The size of FFT, i.e. size of a range to which the FFT will be applied to.

            \~russian
                \brief
                    Инициализация БПФ

                \details
                    Предпосчитывает и сохраняет корни из единицы для всех степеней двойки до `size`
                    включительно, а также индексы бит-реверсивной перестановки размера `size`.

                    Асимптотика:
                    -   Время: `O(size)`;
                    -   Память (занимаемая итоговым объектом): `O(size)`.

                \param size
                    Размер БПФ, т.е. количество элементов в диапазоне, к которому будет
                    применяться БПФ.

            \~
                \pre
                    `size = 2 ^ n, n ∈ ℕ`

                \see is_power_of_2
                \see detail::fill_w_nk
                \see table_bit_reversal_permutation
         */
        template <std::integral I>
        explicit fft_base_t (I size):
            m_w_nk{},
            m_bit_reverse_permutation_indices{},
            m_size(static_cast<std::size_t>(size))
        {
            assert(size > 0);
            assert(is_power_of_2(m_size));

            init_w_nk();
            init_bit_reverse_permutation_indices();
        }

        std::size_t size () const
        {
            return m_size;
        }

        const std::vector<K> & w_nk () const
        {
            return m_w_nk;
        }

        const std::vector<std::uint32_t> & bitrev () const
        {
            return m_bit_reverse_permutation_indices;
        }

    private:
        void init_w_nk ()
        {
            m_w_nk.resize(m_size - 1);
            detail::fill_w_nk(m_w_nk.begin(), m_size);
        }

        void init_bit_reverse_permutation_indices ()
        {
            m_bit_reverse_permutation_indices.resize(m_size, 0);
            table_bit_reversal_permutation(m_bit_reverse_permutation_indices.begin(), m_size);
        }

    protected:
        std::vector<K> m_w_nk;
        std::vector<std::uint32_t> m_bit_reverse_permutation_indices;
        std::size_t m_size;
    };
}
