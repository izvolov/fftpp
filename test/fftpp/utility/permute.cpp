#include <fftpp/utility/permute.hpp>

#include <doctest/doctest.h>

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

TEST_CASE("Копирует элементы последовательности в новый диапазон в соответствии с индексами, "
    "заданными функцией")
{
    const auto initial = std::vector<std::string>{"1", "2", "3"};

    auto result = std::vector<std::string>(initial.size());
    fftpp::permute(initial.begin(), initial.size(), result.begin(),
        [size = initial.size()] (auto old_index)
        {
            return (old_index + 1) % size;
        });

    CHECK(result == std::vector<std::string>{"3", "1", "2"});
}

TEST_CASE("Возвращает итератор за последним заполненным элементом")
{
    const auto initial = std::vector<char>{'a', 'b', 'c', 'd'};

    auto result = std::vector<char>(100500);
    const auto pemutation_end =
        fftpp::permute(initial.begin(), initial.size(), result.begin(),
            [] (auto old_index)
            {
                return old_index;
            });

    CHECK(std::distance(result.begin(), pemutation_end) == initial.size());
}

TEST_CASE("Значения вне заданного диапазона не изменяеются")
{
    const auto initial = std::vector<std::uint32_t>{6, 5, 4};

    auto result = std::vector<std::uint32_t>(6, 17);
    fftpp::permute(initial.begin(), 3, result.begin(),
        [] (auto old_index)
        {
            switch (old_index)
            {
                case 0: return 2;
                case 1: return 0;
                case 2: return 1;
                default: throw std::runtime_error("Невозможный индекс");
            }
        });

    CHECK(result == std::vector<std::uint32_t>{5, 4, 6, 17, 17, 17});
}
