#pragma once

#include <cassert>
#include <concepts>
#include <cstdint>
#include <ostream>

namespace fftpp
{
    template <std::unsigned_integral N>
    class ring_t
    {
    public:
        static constexpr auto modulo = std::uint64_t{3221225473};
        // Разрешены только такие целые, в которые влезает наш модуль.
        static_assert(N{modulo} == modulo);

        constexpr ring_t () = default;

        template <std::integral M>
        constexpr ring_t (M value):
            m_value
            (
                static_cast<N>(static_cast<std::uint64_t>(value) >= modulo ?
                    static_cast<std::uint64_t>(value) % modulo :
                    static_cast<std::uint64_t>(value))
            )
        {
            assert(value >= 0);
        }

        constexpr ring_t & operator += (ring_t that)
        {
            m_value = static_cast<N>(raw_sum(this->m_value, that.m_value));
            return *this;
        }

        constexpr ring_t & operator -= (ring_t that)
        {
            m_value = static_cast<N>(raw_difference(this->m_value, that.m_value));
            return *this;
        }

        constexpr ring_t & operator *= (ring_t that)
        {
            m_value = static_cast<N>(raw_product(this->m_value, that.m_value));
            return *this;
        }

        constexpr ring_t & operator ++ ()
        {
            ++m_value;
            if (m_value >= modulo)
            {
                m_value -= modulo;
            }

            return *this;
        }

        constexpr bool operator == (ring_t that) const
        {
            return this->m_value == that.m_value;
        }

        template <std::unsigned_integral M>
        constexpr bool operator == (M value) const
        {
            return static_cast<std::uint64_t>(m_value) == static_cast<std::uint64_t>(value);
        }

        constexpr bool operator < (ring_t that) const
        {
            return this->m_value < that.m_value;
        }

    private:
        friend std::ostream & operator << (std::ostream & stream, ring_t x)
        {
            return stream << "ring_t<" << typeid(N).name() << ">{" << x.m_value << "}";
        }

        static constexpr std::uint64_t raw_sum (std::uint64_t x, std::uint64_t y)
        {
            assert(x < modulo);
            assert(y < modulo);

            const auto sum = x + y;
            return sum >= modulo ? sum - modulo : sum;
        }

        static constexpr std::uint64_t raw_difference (std::uint64_t x, std::uint64_t y)
        {
            assert(x < modulo);
            assert(y < modulo);

            if (x < y)
            {
                x += modulo;
            }
            return x - y;
        }

        static constexpr std::uint64_t raw_product (std::uint64_t x, std::uint64_t y)
        {
            assert(x < modulo);
            assert(y < modulo);

            const auto product = x * y;
            return product >= modulo ? product % modulo : product;
        }

        N m_value;
    };

    template <std::integral N>
    ring_t (N) -> ring_t<std::make_unsigned_t<std::common_type_t<N, std::uint32_t>>>;

    template <std::unsigned_integral N>
    constexpr ring_t<N> operator + (ring_t<N> x, ring_t<N> y)
    {
        x += y;
        return x;
    }

    template <std::unsigned_integral N>
    constexpr ring_t<N> operator - (ring_t<N> x, ring_t<N> y)
    {
        x -= y;
        return x;
    }

    template <std::unsigned_integral N>
    constexpr ring_t<N> operator * (ring_t<N> x, ring_t<N> y)
    {
        x *= y;
        return x;
    }
}
