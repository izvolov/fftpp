#pragma once

#include <cassert>
#include <concepts>
#include <cstdint>
#include <limits>
#include <ostream>

namespace fftpp
{
    /*!
        \~english
            \brief
                Modulo ring

            \details
                Implements sum, difference, product, compare and output operations.

            \tparam Modulo
                `Modulo` of the ring.
                Ring elements take values in range `[0, Modulo)`.
            \param Rep
                Actual type of the ring representation.

            \pre
                `Modulo` can be represented by `Rep`.
            \pre
                `(Modulo - 1) ^ 2` can be represented by `Rep`.

        \~russian
            \brief
                Кольцо вычетов по модулю

            \details
                Реализует кольцо и операции сложения, вычитания, умножения, сравнения и вывода.

            \tparam Modulo
                Модуль кольца.
                Элементы кольца принимают значения в диапазоне `[0, Modulo)`.
            \param Rep
                Реальный тип, которым будет представлено кольцо.

            \pre
                `Modulo` представим типом `Rep`.
            \pre
                Число `(Modulo - 1) ^ 2` представимо типом `Rep`.
     */
    template <std::uint32_t Modulo, std::unsigned_integral Rep>
        requires
        (
            Modulo <= static_cast<std::uint32_t>(std::numeric_limits<Rep>::max()) &&
            static_cast<std::uint64_t>(Modulo - 1) * static_cast<std::uint64_t>(Modulo - 1) <=
                static_cast<std::uint64_t>(std::numeric_limits<Rep>::max())
        )
    class basic_ring
    {
    public:
        using representation_type = Rep;
        static constexpr auto modulo = static_cast<representation_type>(Modulo);

        constexpr basic_ring () = default;

        constexpr basic_ring (representation_type value):
            m_value(value >= modulo ? value % modulo : value)
        {
            assert(value >= 0);
        }

        constexpr basic_ring & operator += (basic_ring that)
        {
            m_value = raw_sum(this->m_value, that.m_value);
            return *this;
        }

        constexpr basic_ring & operator -= (basic_ring that)
        {
            m_value = raw_difference(this->m_value, that.m_value);
            return *this;
        }

        constexpr basic_ring & operator *= (basic_ring that)
        {
            m_value = raw_product(this->m_value, that.m_value);
            return *this;
        }

        constexpr basic_ring & operator ++ ()
        {
            ++m_value;
            if (m_value >= modulo)
            {
                m_value -= modulo;
            }

            return *this;
        }

        constexpr bool operator == (basic_ring that) const
        {
            return this->m_value == that.m_value;
        }

        template <std::unsigned_integral M>
        constexpr bool operator == (M value) const
        {
            using common_type = std::common_type_t<M, representation_type>;
            return static_cast<common_type>(m_value) == static_cast<common_type>(value);
        }

        constexpr bool operator < (basic_ring that) const
        {
            return this->m_value < that.m_value;
        }

    private:
        friend std::ostream & operator << (std::ostream & stream, basic_ring x)
        {
            return
                stream
                    << "basic_ring<" << modulo << ", " << typeid(Rep).name() << ">"
                    "{" << x.m_value << "}";
        }

        template <typename M>
        static constexpr M raw_sum (M x, M y)
        {
            assert(x < modulo);
            assert(y < modulo);

            const auto sum = x + y;
            return sum >= modulo ? sum - modulo : sum;
        }

        template <typename M>
        static constexpr M raw_difference (M x, M y)
        {
            assert(x < modulo);
            assert(y < modulo);

            if (x < y)
            {
                x += modulo;
            }
            return x - y;
        }

        template <typename M>
        static constexpr M raw_product (M x, M y)
        {
            assert(x < modulo);
            assert(y < modulo);

            const auto product = x * y;
            return product >= modulo ? product % modulo : product;
        }

        representation_type m_value;
    };

    template <std::uint32_t Mod, std::unsigned_integral Rep>
    constexpr basic_ring<Mod, Rep>
        operator + (basic_ring<Mod, Rep> x, basic_ring<Mod, Rep> y)
    {
        x += y;
        return x;
    }

    template <std::uint32_t Mod, std::unsigned_integral Rep>
    constexpr basic_ring<Mod, Rep>
        operator - (basic_ring<Mod, Rep> x, basic_ring<Mod, Rep> y)
    {
        x -= y;
        return x;
    }

    template <std::uint32_t Mod, std::unsigned_integral Rep>
    constexpr basic_ring<Mod, Rep>
        operator * (basic_ring<Mod, Rep> x, basic_ring<Mod, Rep> y)
    {
        x *= y;
        return x;
    }

    template <std::uint32_t Mod, std::unsigned_integral Rep, std::integral M>
    constexpr basic_ring<Mod, Rep> operator + (basic_ring<Mod, Rep> x, M y)
    {
        assert(y > 0);
        assert(static_cast<std::uint64_t>(y) < static_cast<std::uint64_t>(Mod));

        x += basic_ring<Mod, Rep>(static_cast<Rep>(y));
        return x;
    }

    template <std::uint32_t Mod, std::unsigned_integral Rep, std::integral M>
    constexpr basic_ring<Mod, Rep> operator - (basic_ring<Mod, Rep> x, M y)
    {
        assert(y > 0);
        assert(static_cast<std::uint64_t>(y) < static_cast<std::uint64_t>(Mod));

        x -= basic_ring<Mod, Rep>(static_cast<Rep>(y));
        return x;
    }

    template <std::uint32_t Mod, std::unsigned_integral Rep, std::integral M>
    constexpr basic_ring<Mod, Rep> operator * (basic_ring<Mod, Rep> x, M y)
    {
        assert(y > 0);
        assert(static_cast<std::uint64_t>(y) < static_cast<std::uint64_t>(Mod));

        x *= basic_ring<Mod, Rep>(static_cast<Rep>(y));
        return x;
    }
}
