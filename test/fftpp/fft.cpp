#include <fftpp/complex.hpp>
#include <fftpp/fft.hpp>

#include <doctest/doctest.h>

#include <complex>

TEST_CASE("test")
{
    const auto size = 16ul;

    const auto fft = fftpp::fft_t<std::complex<double>>(size);

    const auto input = std::vector<double>(size, 17);
    auto result = std::vector<std::complex<double>>(size);

    fft(input.begin(), result.begin());
}
