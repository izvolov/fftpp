#include <fftpp/complex.hpp>
#include <fftpp/fft.hpp>
#include <fftpp/inverse_fft.hpp>
#include <fftpp/ring.hpp>

#include <algorithm>
#include <chrono>
#include <complex>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

template <typename F, typename Value, typename G>
void
    test_base
    (
        std::string name,
        const F & fft,
        std::size_t size,
        std::size_t repetitions,
        std::vector<Value> & before,
        std::vector<Value> & after,
        const G & gen
    )
{
    auto total = std::chrono::steady_clock::duration{0};
    for (auto iteration = 0ul; iteration < repetitions; ++iteration)
    {
        gen(before.begin(), before.end());

        const auto iteration_start_time = std::chrono::steady_clock::now();
        fft(size, before.begin(), after.begin());
        const auto iteration_end_time = std::chrono::steady_clock::now();

        std::clog << std::accumulate(after.begin(), after.end(), Value{0}) << std::endl;

        total += (iteration_end_time - iteration_start_time);
    }

    const auto duration_seconds =
        std::chrono::duration_cast<std::chrono::duration<double>>(total).count();
    std::cout << name << ": \t" << duration_seconds / static_cast<double>(repetitions) << std::endl;
}

template <typename F>
void
    test_complex
    (
        std::string name,
        const F & f,
        std::size_t size,
        std::size_t repetitions
    )
{
    auto distribution = std::normal_distribution<>(0, 1.0);
    auto generator = std::default_random_engine{};

    std::vector<std::complex<double>> before(size);
    std::vector<std::complex<double>> after(size);

    test_base(name, f, size, repetitions, before, after,
        [& distribution, & generator] (auto first, auto last)
        {
            std::generate(first, last,
                [& distribution, & generator]
                {
                    return std::complex<double>{distribution(generator), 0.0};
                });
        });
}

template <typename F>
void
    test_mod
    (
        std::string name,
        const F & f,
        std::size_t size,
        std::size_t repetitions
    )
{
    auto distribution = std::uniform_int_distribution<std::uint16_t>(0, 65535);
    auto generator = std::default_random_engine{};

    std::vector<fftpp::ring_t<std::uint32_t>> before(size);
    std::vector<fftpp::ring_t<std::uint32_t>> after(size);

    test_base(name, f, size, repetitions, before, after,
        [& distribution, & generator] (auto first, auto last)
        {
            std::generate(first, last,
                [& distribution, & generator]
                {
                    return fftpp::ring_t<std::uint32_t>{distribution(generator)};
                });
        });
}

void test_all (std::size_t size, std::size_t repetitions)
{
    const auto fft_from_scratch =
        [] (auto size, auto from, auto to)
        {
            const auto fft = fftpp::fft_t<std::complex<double>>(size);
            fft(from, to);
        };
    test_complex("Без предпосчёта", fft_from_scratch, size, repetitions);

    const auto ready_fft = fftpp::fft_t<std::complex<double>, 65536>(size);
    const auto fft_prepared =
        [& ready_fft] (auto /*size*/, auto from, auto to)
        {
            ready_fft(from, to);
        };
    test_complex("С предпосчётом", fft_prepared, size, repetitions);

    const auto inverse_ready_fft = inverse(ready_fft);
    const auto inverse_fft_prepared =
        [& inverse_ready_fft] (auto /*size*/, auto from, auto to)
        {
            inverse_ready_fft(from, to);
        };
    test_complex("Обратное", inverse_fft_prepared, size, repetitions);

    const auto mod_fft = fftpp::fft_t<fftpp::ring_t<std::uint32_t>, 65536>(size);
    const auto mod_fft_prepared =
        [& mod_fft] (auto /*size*/, auto from, auto to)
        {
            mod_fft(from, to);
        };
    test_mod("Целочисленное", mod_fft_prepared, size, repetitions);

    const auto inverse_mod_fft_prepared =
        [& mod_fft] (auto /*size*/, auto from, auto to)
        {
            inverse(mod_fft)(from, to);
        };
    test_mod("Обратное целочисленное", inverse_mod_fft_prepared, size, repetitions);
}

int main (int argc, const char * argv[])
{
    if (argc == 1 + 2)
    {
        const auto size = std::stoul(argv[1]);
        const auto repetitions = std::stoul(argv[2]);

        test_all(size, repetitions);
    }
    else
    {
        std::cout << "Использование: " << argv[0] << " <размер> <число повторений>" << std::endl;
    }
}
