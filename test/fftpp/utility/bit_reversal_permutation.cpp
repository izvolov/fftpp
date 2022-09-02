#include <fftpp/utility/bit_reversal_permutation.hpp>
#include <fftpp/utility/intlog2.hpp>
#include <fftpp/utility/reverse_lower_bits.hpp>

#include <doctest/doctest.h>

#include <cstdint>
#include <vector>

TEST_CASE("Генерирует индексы для побитово обратной перестановки")
{
    const auto size = 256;
    std::vector<std::uint32_t> indices(size);
    fftpp::bit_reversal_permutation(indices.begin(), size);

    for (auto old_index = 0ul; old_index < size; ++old_index)
    {
        const auto new_index =
            fftpp::reverse_lower_bits(old_index, fftpp::intlog2(indices.size()));
        CHECK(indices[old_index] == new_index);
    }
}

TEST_CASE("Исходный диапазон может быть заполнен чем угодно. На результат это не повлияет")
{
    const auto size = 128;
    std::vector<std::uint32_t> indices(size);
    fftpp::bit_reversal_permutation(indices.begin(), size);

    for (auto old_index = 0ul; old_index < size; ++old_index)
    {
        const auto new_index =
            fftpp::reverse_lower_bits(old_index, fftpp::intlog2(indices.size()));
        CHECK(indices[old_index] == new_index);
    }
}

TEST_CASE("Значения вне заданного диапазона не изменяеются")
{
    const auto size = 32u;
    const auto unused_value = 999;
    std::vector<std::uint32_t> indices(size * 2, unused_value);
    fftpp::bit_reversal_permutation(indices.begin(), size);

    for (auto index = size; index < indices.size(); ++index)
    {
        CHECK(indices[index] == unused_value);
    }
}

TEST_CASE("Возвращает итератор за последним заполненным элементом")
{
    const auto size = 16;
    std::vector<std::uint32_t> indices(size * 2);

    const auto end = fftpp::bit_reversal_permutation(indices.begin(), size);
    CHECK(end == indices.begin() + size);
}
