#include <fftpp/utility/bit_reversal_permutation.hpp>
#include <fftpp/utility/table_bit_reversal_permutation.hpp>
#include <fftpp/utility/intlog2.hpp>
#include <fftpp/utility/reverse_lower_bits.hpp>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

template <typename F>
void test (std::string name, std::size_t size, std::size_t repetitions, const F & f)
{
    auto total = std::chrono::steady_clock::duration{0};
    for (auto iteration = 0ul; iteration < repetitions; ++iteration)
    {
        std::vector<std::uint16_t> indices(size);

        const auto iteration_start_time = std::chrono::steady_clock::now();

        f(size, indices);

        const auto iteration_end_time = std::chrono::steady_clock::now();

        total += (iteration_end_time - iteration_start_time);

        std::sort(indices.begin(), indices.end());

        std::vector<std::uint16_t> expected(size);
        std::iota(expected.begin(), expected.end(), 0);
        assert(indices == expected);
    }

    const auto total_duration =
        std::chrono::duration_cast<std::chrono::duration<double>>(total).count();
    const auto average_duration = total_duration / static_cast<double>(repetitions);

    std::cout << name << ": " << average_duration << std::endl;
}

void test_all (std::size_t size, std::size_t repetitions)
{
    const auto naive_bit_reverse =
        [] (auto size, auto & indices)
        {
            const auto size_log = fftpp::intlog2(size);
            for (auto k = 0ul; k < size; ++k)
            {
                indices[k] = fftpp::reverse_lower_bits(static_cast<std::uint16_t>(k), size_log);
            }
        };
    test("В лоб", size, repetitions, naive_bit_reverse);

    const auto iterative_bit_reverse =
        [] (auto /*size*/, auto & indices)
        {
            fftpp::bit_reversal_permutation(indices.begin(), indices.size());
        };
    test("Итеративно", size, repetitions, iterative_bit_reverse);

    const auto hybrid_bit_reverse =
        [] (auto /*size*/, auto & indices)
        {
            fftpp::table_bit_reversal_permutation(indices.begin(), indices.size());
        };
    test("Гибридно", size, repetitions, hybrid_bit_reverse);
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