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
    const auto signal = std::vector<fftpp::ring30>(size, 999);

    const auto fft = fftpp::fft_t<fftpp::ring30>(size);
    auto result = std::vector<fftpp::ring30>(size);
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

    const auto fft = fftpp::fft_t<fftpp::ring30>(size);
    auto result = std::vector<fftpp::ring30>(size * 2, 333u);
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

TEST_CASE_TEMPLATE("Обратное БПФ возвращает сигнал в исходное состояние",
    ring, fftpp::ring8, fftpp::ring16, fftpp::ring30)
{
    const auto size = 128ul;
    auto signal = std::vector<typename ring::representation_type>(size);
    std::iota(signal.begin(), signal.end(), 1);

    const auto fft = fftpp::fft_t<ring>(size);
    auto result = std::vector<ring>(size);
    fft(signal.begin(), result.begin());

    auto inverse_result = std::vector<ring>(size);
    inverse(fft)(result.begin(), inverse_result.begin());
    for (auto i = 0ul; i < size; ++i)
    {
        CHECK(signal[i] == inverse_result[i]);
    }
}

TEST_CASE("Целочисленное БПФ может быть использовано для умножения многочленов")
{
    auto first = std::vector<unsigned>{1, 2, 3};
    auto second = std::vector<unsigned>{2, 3, 4, 5};

    const auto fft = fftpp::fft_t<fftpp::ring8>(8);

    first.resize(8);
    auto first_result = std::vector<fftpp::ring8>(first.size());
    fft(first.begin(), first_result.begin());

    second.resize(8);
    auto second_result = std::vector<fftpp::ring8>(second.size());
    fft(second.begin(), second_result.begin());

    std::transform(first_result.begin(), first_result.end(), second_result.begin(),
        first_result.begin(),
        [] (auto x, auto y)
        {
            return x * y;
        });
    inverse(fft)(first_result.begin(), second_result.begin());
    std::transform(second_result.begin(), second_result.end(), first.begin(),
        [] (auto x)
        {
            return static_cast<unsigned>(x);
        });

    const auto expected = std::vector<unsigned>{2, 7, 16, 22, 22, 15, 0, 0};
    CHECK(first == expected);
}
