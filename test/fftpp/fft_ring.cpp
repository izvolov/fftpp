#include <fftpp/fft.hpp>
#include <fftpp/inverse_fft.hpp>
#include <fftpp/ring.hpp>

#include <doctest/doctest.h>

#include <cstdint>
#include <numeric>
#include <vector>

TEST_CASE("Исходный диапазон не изменяется")
{
    const auto size = 64ul;
    const auto signal = std::vector<fftpp::ring_t<std::uint32_t>>(size, 999);

    const auto fft = fftpp::fft_t<fftpp::ring_t<std::uint32_t>>(size);
    auto result = std::vector<fftpp::ring_t<std::uint32_t>>(size);
    fft(signal.begin(), result.begin());

    for (auto i = 0ul; i < signal.size(); ++i)
    {
        CHECK(signal[i] == 999);
    }
}

TEST_CASE("Используется только необходимая часть диапазона результата")
{
    const auto size = 256ul;
    const auto signal = std::vector<std::uint32_t>(size);

    const auto fft = fftpp::fft_t<fftpp::ring_t<std::uint32_t>>(size);
    auto result = std::vector<fftpp::ring_t<std::uint32_t>>(size * 2, 333u);
    fft(signal.begin(), result.begin());

    for (auto i = 0ul; i < result.size() / 2; ++i)
    {
        CHECK(result[i] != 333u);
    }
    for (auto i = result.size() / 2; i < result.size(); ++i)
    {
        CHECK(result[i] == 333u);
    }
}

TEST_CASE("Обратное БПФ возвращает сигнал в исходное состояние")
{
    const auto size = 128ul;
    auto signal = std::vector<std::uint32_t>(size);
    std::iota(signal.begin(), signal.end(), 1);

    const auto fft = fftpp::fft_t<fftpp::ring_t<std::uint32_t>>(size);
    auto result = std::vector<fftpp::ring_t<std::uint32_t>>(size);
    fft(signal.begin(), result.begin());

    auto inverse_result = std::vector<fftpp::ring_t<std::uint32_t>>(size);
    inverse(fft)(result.begin(), inverse_result.begin());
    for (auto i = 0ul; i < size; ++i)
    {
        CHECK(signal[i] == inverse_result[i]);
    }
}
