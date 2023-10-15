#include <fftpp/ring.hpp>
#include <fftpp/utility/binpow.hpp>

#include <concepts>
#include <iostream>
#include <stdexcept>
#include <string>

template <std::unsigned_integral N>
constexpr fftpp::ring_t<N> inverse (fftpp::ring_t<N> n)
{
    return fftpp::binpow(n, fftpp::ring_t<N>::modulo - 2);
}

int main (int /*argc*/, const char * argv[])
{
    auto max_power_of_2 = std::stoul(argv[1]);
    for (auto i = 1ul; i <= max_power_of_2; ++i)
    {
        const auto n = fftpp::ring_t{1u << i};
        std::cout << "Элемент, для которого ищется обратное: " << n << std::endl;

        const auto inverse_n = inverse(n);
        if (n * inverse_n == 1u)
        {
            std::cout << "Обратный элемент к " << n << ": " << inverse_n << std::endl;
        }
        else
        {
            const auto error_message = "Не удалось найти обратный элемент";
            throw std::runtime_error(error_message);
        }
    }
}
