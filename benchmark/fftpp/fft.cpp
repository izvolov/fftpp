#include <fftpp/complex.hpp>
#include <fftpp/fft.hpp>
#include <fftpp/inverse_fft.hpp>
#include <fftpp/ring.hpp>

#if defined FFTPP_BENCH_FFTW
#include <fftw3.h>
#endif

#include <algorithm>
#include <chrono>
#include <complex>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>
#include <variant>

using clock_type = std::chrono::steady_clock;

template <typename F, typename UnaryFunction, typename Value, typename G>
void
    test_base
    (
        std::string name,
        const F & fft,
        std::size_t size,
        std::size_t repetitions,
        UnaryFunction statistic,
        std::vector<Value> & before,
        std::vector<Value> & after,
        const G & gen
    )
{
    using namespace std::chrono;
    std::vector<clock_type::duration> times;
    times.reserve(repetitions);

    for (auto iteration = 0ul; iteration < repetitions; ++iteration)
    {
        gen(before.begin(), before.end());

        const auto iteration_start_time = std::chrono::steady_clock::now();
        fft(size, before.begin(), after.begin());
        const auto iteration_end_time = std::chrono::steady_clock::now();

        const auto repetition_time = iteration_end_time - iteration_start_time;
        times.push_back(repetition_time);

        std::clog << std::accumulate(after.begin(), after.end(), Value{0}) << std::endl;
    }

    const auto stat = statistic(times);
    std::cout << name << ' ' << duration_cast<duration<double>>(stat).count() << std::endl;
}

template <typename F, typename UnaryFunction>
void
    test_complex
    (
        std::string name,
        const F & f,
        std::size_t size,
        std::size_t repetitions,
        UnaryFunction statistic
    )
{
    auto distribution = std::normal_distribution<>(0, 1.0);
    auto generator = std::default_random_engine{};

    std::vector<std::complex<double>> before(size);
    std::vector<std::complex<double>> after(size);

    test_base(name, f, size, repetitions, statistic, before, after,
        [& distribution, & generator] (auto first, auto last)
        {
            std::generate(first, last,
                [& distribution, & generator]
                {
                    return std::complex<double>{distribution(generator), 0.0};
                });
        });
}

template <typename F, typename UnaryFunction>
void
    test_mod
    (
        std::string name,
        const F & f,
        std::size_t size,
        std::size_t repetitions,
        UnaryFunction statistic
    )
{
    auto distribution = std::uniform_int_distribution<std::uint16_t>(0, 65535);
    auto generator = std::default_random_engine{};

    std::vector<fftpp::ring_t<std::uint32_t>> before(size);
    std::vector<fftpp::ring_t<std::uint32_t>> after(size);

    test_base(name, f, size, repetitions, statistic, before, after,
        [& distribution, & generator] (auto first, auto last)
        {
            std::generate(first, last,
                [& distribution, & generator]
                {
                    return fftpp::ring_t<std::uint32_t>{distribution(generator)};
                });
        });
}

template <typename UnaryFunction>
void test_all (std::size_t size, std::size_t repetitions, UnaryFunction statistic)
{
    const auto fft_from_scratch =
        [] (auto size, auto from, auto to)
        {
            const auto fft = fftpp::fft_t<std::complex<double>>(size);
            fft(from, to);
        };
    test_complex("fftpp.complex.from_scratch", fft_from_scratch, size, repetitions, statistic);

    const auto ready_fft = fftpp::fft_t<std::complex<double>, 65536>(size);
    const auto fft_prepared =
        [& ready_fft] (auto /*size*/, auto from, auto to)
        {
            ready_fft(from, to);
        };
    test_complex("fftpp.complex.forward", fft_prepared, size, repetitions, statistic);

    const auto inverse_ready_fft = inverse(ready_fft);
    const auto inverse_fft_prepared =
        [& inverse_ready_fft] (auto /*size*/, auto from, auto to)
        {
            inverse_ready_fft(from, to);
        };
    test_complex("fftpp.complex.inverse", inverse_fft_prepared, size, repetitions, statistic);

    const auto mod_fft = fftpp::fft_t<fftpp::ring_t<std::uint32_t>, 65536>(size);
    const auto mod_fft_prepared =
        [& mod_fft] (auto /*size*/, auto from, auto to)
        {
            mod_fft(from, to);
        };
    test_mod("fftpp.integral.forward", mod_fft_prepared, size, repetitions, statistic);

    const auto inverse_mod_fft_prepared =
        [& mod_fft] (auto /*size*/, auto from, auto to)
        {
            inverse(mod_fft)(from, to);
        };
    test_mod("fftpp.integral.inverse", inverse_mod_fft_prepared, size, repetitions, statistic);

#if defined FFTPP_BENCH_FFTW
    fftw_complex * in = static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * size));
    fftw_complex * out = static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * size));
    fftw_plan p = fftw_plan_dft_1d(static_cast<int>(size), in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    const auto fftw =
        [& p, in, out] (auto size, auto from, auto to)
        {
            std::copy_n(from, size, reinterpret_cast<std::complex<double> *>(in));
            fftw_execute(p);
            std::copy_n(reinterpret_cast<std::complex<double> *>(out), size, to);
        };
    test_complex("FFTW", fftw, size, repetitions, statistic);
    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);
#endif
}

struct min_fn
{
    template <typename Container>
    auto operator () (const Container & c) const
    {
        return *std::min_element(c.begin(), c.end());
    }
};

struct max_fn
{
    template <typename Container>
    auto operator () (const Container & c) const
    {
        return *std::max_element(c.begin(), c.end());
    }
};

struct sum_fn
{
    template <typename Container>
    auto operator () (Container c) const
    {
        using value_type = typename Container::value_type;
        std::sort(c.begin(), c.end());
        return std::accumulate(c.begin(), c.end(), value_type{});
    }
};

struct median_fn
{
    template <typename Container>
    auto operator () (Container c) const
    {
        using difference_type = typename Container::difference_type;
        auto n = static_cast<difference_type>(c.size() / 2);
        auto nth = c.begin() + n;
        std::nth_element(c.begin(), nth, c.end());
        return *nth;
    }
};

struct mean_fn
{
    template <typename Container>
    auto operator () (const Container & c) const
    {
        using rep_type = clock_type::rep;
        return sum_fn{}(c) / static_cast<rep_type>(c.size());
    }
};

struct stat_fn
{
    explicit stat_fn (std::string_view statistic)
    {
        if (statistic == "min")
        {
            fn = min_fn{};
        }
        else if (statistic == "max")
        {
            fn = max_fn{};
        }
        else if (statistic == "median")
        {
            fn = median_fn{};
        }
        else if (statistic == "mean")
        {
            fn = mean_fn{};
        }
        else
        {
            const auto error_message = "Неверная статистика: " + std::string(statistic);
            throw std::invalid_argument(error_message);
        }
    }

    template <typename Container>
    auto operator () (const Container & c) const
    {
        return std::visit([& c] (const auto & f) {return f(c);}, fn);
    }

    std::variant<min_fn, max_fn, sum_fn, median_fn, mean_fn> fn;
};

int main (int argc, const char * argv[])
{
    if (argc == 1 + 3)
    {
        const auto size = std::stoul(argv[1]);
        const auto repetitions = std::stoul(argv[2]);
        const auto statistic = std::string(argv[3]);

        test_all(size, repetitions, stat_fn(statistic));
    }
    else
    {
        std::cout
            << "Использование: " << argv[0]
            << " <размер:число> <число повторений:число> <статистика:{min, max, mean, median, sum}>"
            << std::endl;
    }
}
