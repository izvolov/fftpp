#include <fftpp/complex.hpp>
#include <fftpp/fft.hpp>
#include <fftpp/inverse_fft.hpp>

#include <algorithm>
#include <chrono>
#include <complex>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

template <typename F>
void test (std::string name, std::size_t size, std::size_t repetitions, const F & f)
{
    auto distribution = std::normal_distribution<>(0, 1.0);
    auto generator = std::default_random_engine{};

    std::vector<std::complex<double>> before(size);
    std::vector<std::complex<double>> after(size);

    auto total = std::chrono::steady_clock::duration{0};
    for (auto iteration = 0ul; iteration < repetitions; ++iteration)
    {
        std::generate(before.begin(), before.end(),
            [& distribution, & generator]
            {
                return std::complex<double>{distribution(generator), 0};
            });

        const auto iteration_start_time = std::chrono::steady_clock::now();
        f(size, before.begin(), after.begin());
        const auto iteration_end_time = std::chrono::steady_clock::now();

        std::clog << std::accumulate(after.begin(), after.end(), std::complex{0.0}) << std::endl;

        total += (iteration_end_time - iteration_start_time);
    }

    const auto duration_seconds =
        std::chrono::duration_cast<std::chrono::duration<double>>(total).count();
    std::cout << name << ": \t" << duration_seconds / static_cast<double>(repetitions) << std::endl;
}

void test_all (std::size_t size, std::size_t repetitions)
{
    const auto fft_from_scratch =
        [] (auto size, auto from, auto to)
        {
            const auto fft = fftpp::fft_t<std::complex<double>>(size);
            fft(from, to);
        };
    test("Без предпосчёта", size, repetitions, fft_from_scratch);

    const auto ready_fft = fftpp::fft_t<std::complex<double>>(size);
    const auto fft_prepared =
        [& ready_fft] (auto /*size*/, auto from, auto to)
        {
            ready_fft(from, to);
        };
    test("С предпосчётом", size, repetitions, fft_prepared);

    const auto inverse_ready_fft = inverse(ready_fft);
    const auto inverse_fft_prepared =
        [& inverse_ready_fft] (auto /*size*/, auto from, auto to)
        {
            inverse_ready_fft(from, to);
        };
    test("Обратное", size, repetitions, inverse_fft_prepared);
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
