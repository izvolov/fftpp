#include <fftpp/complex.hpp>
#include <fftpp/fft.hpp>

#include <doctest/doctest.h>

#include <cmath>
#include <complex>
#include <cstddef>
#include <set>
#include <vector>

namespace
{
    std::vector<double> make_signal (std::size_t size, const std::set<std::size_t> & frequencies)
    {
        auto signal = std::vector<double>(size);

        for (auto i = 0ul; i < signal.size(); ++i)
        {
            const auto t =
                2.0 * 3.1415926 * static_cast<double>(i) / static_cast<double>(signal.size());
            for (auto frequency: frequencies)
            {
                signal[i] += std::sin(static_cast<double>(frequency) * t);
            }
        }

        return signal;
    }
}

TEST_CASE("БПФ выделяет именно те частоты, которые были в исходном сигнале")
{
    const auto size = 128ul;
    const auto frequencies = std::set<std::size_t>{1, 3, 15, 44};
    const auto signal = make_signal(size, frequencies);

    const auto fft = fftpp::fft_t<std::complex<double>>(size);
    auto result = std::vector<std::complex<double>>(size);
    fft(signal.begin(), result.begin());

    for (auto i = 0ul; i < result.size() / 2; ++i)
    {
        const auto energy = std::abs(result[i]) / (size / 2);

        if (frequencies.contains(i))
        {
            CHECK(energy == doctest::Approx(1.0).epsilon(1e-4));
        }
        else
        {
            CHECK(energy == doctest::Approx(0.0).epsilon(1e-4));
        }
    }

    SUBCASE("причём частоты симметричны относительно середины массива")
    {
        for (auto i = result.size() / 2; i < result.size(); ++i)
        {
            const auto energy = std::abs(result[i]) / (size / 2);

            if (frequencies.contains(signal.size() - i))
            {
                CHECK(energy == doctest::Approx(1.0).epsilon(1e-4));
            }
            else
            {
                CHECK(energy == doctest::Approx(0.0).epsilon(1e-4));
            }
        }
    }
}

TEST_CASE("Исходный диапазон не изменяется")
{
    const auto size = 64ul;
    const auto signal = std::vector<double>(size, 999);

    const auto fft = fftpp::fft_t<std::complex<double>>(size);
    auto result = std::vector<std::complex<double>>(size);
    fft(signal.begin(), result.begin());

    for (auto i = 0ul; i < signal.size(); ++i)
    {
        CHECK(signal[i] == 999);
    }
}

TEST_CASE("Используется только необходимая часть диапазона результата")
{
    const auto size = 256ul;
    const auto signal = std::vector<double>(size);

    const auto fft = fftpp::fft_t<std::complex<double>>(size);
    auto result = std::vector<std::complex<double>>(size * 2, 333);
    fft(signal.begin(), result.begin());

    for (auto i = 0ul; i < result.size() / 2; ++i)
    {
        CHECK(result[i] != 333.0);
    }
    for (auto i = result.size() / 2; i < result.size(); ++i)
    {
        CHECK(result[i] == 333.0);
    }
}
