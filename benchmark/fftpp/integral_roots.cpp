#include <fftpp/ring.hpp>

#include <concepts>
#include <iostream>
#include <stdexcept>
#include <string>

template <std::unsigned_integral N>
constexpr fftpp::ring_t<N> primitive_root (N degree)
{
    for (auto x = fftpp::ring_t<N>{2}; ; ++x)
    {
        auto y = x;
        for (auto power = N{2}; power <= degree; ++power)
        {
            y *= y;
        }

        if (y == fftpp::ring_t<N>::modulo - 1)
        {
            return x;
        }
    }

    const auto error_message =
        "Не удалось вычислить первообразный корень степени " + std::to_string(degree);
    throw std::runtime_error(error_message);
}

int main (int /*argc*/, const char * argv[])
{
    auto max_power_of_2 = std::stoul(argv[1]);
    for (auto i = 1ul; i <= max_power_of_2; ++i)
    {
        const auto primitive_root_i = primitive_root(i);
        std::cout << "Кандидат для степени " << i << ": " << primitive_root_i << std::endl;

        auto x = primitive_root_i;
        for (auto j = 1; j < (1 << i); ++j)
        {
            if (x == 1u)
            {
                const auto error_message =
                    "Никакая промежуточная степень корня не может быть единицей";
                throw std::runtime_error(error_message);
            }
            x *= primitive_root_i;
        }

        if (x != 1u)
        {
            const auto error_message = "После последней степени не идёт единица";
            throw std::runtime_error(error_message);
        }

        std::cout
            << "Первообразный корень для степени " << i << ": " << primitive_root_i
            << std::endl;
    }
}
