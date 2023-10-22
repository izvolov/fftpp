#include <fftpp/utility/pi.hpp>
#include <fftpp/utility/cos.hpp>

#include <doctest/doctest.h>

#include <cmath>
#include <cstdint>
#include <limits>

TEST_CASE("Значения косинуса, требуемые для первообразных корней из единицы, не отличаются от "
    "библиотечных функций с точностью до машинного эпсилон")
{
    constexpr auto eps = std::numeric_limits<double>::epsilon();

    for (auto degree = std::uint64_t{2}; degree <= (std::uint64_t{1} << 62u); degree *= 2)
    {
        const auto angle = -2.0 * fftpp::pi / static_cast<double>(degree);
        CHECK(fftpp::cos(angle) == doctest::Approx(std::cos(angle)).epsilon(eps));
    }
}
