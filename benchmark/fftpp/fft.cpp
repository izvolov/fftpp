#include <fftpp/fft.hpp>
#include <fftpp/complex.hpp>

#include <chrono>
#include <complex>
#include <iostream>
#include <random>
#include <string>

int main (int /*argc*/, const char * argv[])
{
    const auto size = std::stoul(argv[1]);
    const auto repetitions = std::stoul(argv[2]);

    auto distribution = std::normal_distribution<>(0, 1.0);
    auto generator = std::default_random_engine{};


    std::vector<std::complex<double>> before(size);
    std::vector<std::complex<double>> after(size);

    const auto fft = fftpp::fft_t<std::complex<double>>(size);

    auto total = std::chrono::steady_clock::duration{0};
    for (auto iteration = 0ul; iteration < repetitions; ++iteration)
    {
        std::generate(before.begin(), before.end(),
            [& distribution, & generator]
            {
                return std::complex<double>{distribution(generator), 0};
            });

        const auto iteration_start_time = std::chrono::steady_clock::now();
        fft(before.begin(), after.begin());
        const auto iteration_end_time = std::chrono::steady_clock::now();

        std::clog << std::accumulate(after.begin(), after.end(), std::complex{0.0}) << std::endl;

        total += (iteration_end_time - iteration_start_time);
    }

    std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(total).count() / static_cast<double>(repetitions) << std::endl;
}
