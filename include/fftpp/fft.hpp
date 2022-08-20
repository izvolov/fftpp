#pragma once

#include <fftpp/detail/fft_dispose.hpp>
#include <fftpp/detail/fft_impl.hpp>
#include <fftpp/detail/fill_w_nk.hpp>
#include <fftpp/field.hpp>
#include <fftpp/utility/is_power_of_2.hpp>

#include <cassert>
#include <concepts>
#include <iterator>
#include <vector>

namespace fftpp
{
    /*!
        \~english
            \brief
                A structure.

            \details
                Just a demo of documentation.

        \~russian
            \brief
                Структура.

            \details
                Для демонстрации автодокументирования.

        \~  \see myfunc
     */
    template <field K>
    class fft_t
    {
    public:
        template <std::integral I>
        explicit fft_t (I size):
            m_w_nk{},
            m_size(static_cast<std::size_t>(size))
        {
            assert(size > 0);
            assert(is_power_of_2(m_size));
            init_w_nk();
        }

        template <std::random_access_iterator I, std::random_access_iterator J>
            requires(std::convertible_to<std::iter_value_t<I>, K>)
        J operator () (I first, J result) const
        {
            const auto size = static_cast<std::iter_difference_t<I>>(m_size);

            if (size > 1)
            {
                detail::fft_dispose(first, size, result);
                detail::fft_impl(result, size, m_w_nk.begin());
            }

            return result + size;
        }

    private:
        void init_w_nk ()
        {
            m_w_nk.resize(m_size - 1);
            detail::fill_w_nk(m_w_nk.begin(), m_size);
        }

        std::vector<K> m_w_nk;
        std::size_t m_size;
    };
}
