#include <fftpp/ring.hpp>

#include <concepts>
#include <iostream>
#include <stdexcept>
#include <string>

template <std::unsigned_integral N>
constexpr fftpp::ring30 primitive_root (N degree)
{
    for (auto x = fftpp::ring30{2}; x < std::numeric_limits<fftpp::ring30>::max(); ++x)
    {
        auto y = x;
        for (auto power = N{2}; power <= degree; ++power)
        {
            y *= y;
        }

        if (y == fftpp::ring30::modulo - 1)
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
    const auto max_power_of_2 = std::stoul(argv[1]);
    auto root = primitive_root(max_power_of_2);

    auto x = root;
    for (auto j = 1; j < (1 << max_power_of_2); ++j)
    {
        if (x == 1u)
        {
            const auto error_message =
                "Никакая промежуточная степень корня не может быть единицей";
            throw std::runtime_error(error_message);
        }
        x *= root;
    }

    if (x != 1u)
    {
        const auto error_message = "После последней степени не идёт единица";
        throw std::runtime_error(error_message);
    }

    for (auto i = max_power_of_2; i > 0; --i)
    {
        std::cout
            << "Первообразный корень для степени " << i << ": " << root
            << std::endl;
        root *= root;
    }
}
