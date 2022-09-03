#include <fftpp/utility/bit_reversal_permutation.hpp>
#include <fftpp/utility/intlog2.hpp>
#include <fftpp/utility/reverse_lower_bits.hpp>
#include <fftpp/utility/table_bit_reversal_permutation.hpp>

#include <doctest/doctest.h>

#include <cstdint>
#include <vector>

struct iterative_permutation
{
    template <typename... Xs>
    static decltype(auto) apply (Xs &&... xs)
    {
        return fftpp::bit_reversal_permutation(std::forward<Xs>(xs)...);
    }
};

struct table_permutation
{
    template <typename... Xs>
    static decltype(auto) apply (Xs &&... xs)
    {
        return fftpp::table_bit_reversal_permutation(std::forward<Xs>(xs)...);
    }
};

#define PERMUTATION_ALGORITHMS\
    iterative_permutation,\
    table_permutation

TEST_CASE_TEMPLATE("Генерирует индексы для побитово обратной перестановки",
    permutation, PERMUTATION_ALGORITHMS)
{
    const auto size = 512;
    std::vector<std::uint32_t> indices(size);
    permutation::apply(indices.begin(), size);

    for (auto old_index = 0ul; old_index < size; ++old_index)
    {
        const auto new_index =
            fftpp::reverse_lower_bits(old_index, fftpp::intlog2(indices.size()));
        CHECK(indices[old_index] == new_index);
    }
}

TEST_CASE_TEMPLATE("Исходный диапазон может быть заполнен чем угодно. На результат это не повлияет",
    permutation, PERMUTATION_ALGORITHMS)
{
    const auto size = 128;
    std::vector<std::uint32_t> indices(size);
    permutation::apply(indices.begin(), size);

    for (auto old_index = 0ul; old_index < size; ++old_index)
    {
        const auto new_index =
            fftpp::reverse_lower_bits(old_index, fftpp::intlog2(indices.size()));
        CHECK(indices[old_index] == new_index);
    }
}

TEST_CASE_TEMPLATE("Значения вне заданного диапазона не изменяеются",
    permutation, PERMUTATION_ALGORITHMS)
{
    const auto size = 32u;
    const auto unused_value = 999;
    std::vector<std::uint32_t> indices(size * 2, unused_value);
    permutation::apply(indices.begin(), size);

    for (auto index = size; index < indices.size(); ++index)
    {
        CHECK(indices[index] == unused_value);
    }
}

TEST_CASE_TEMPLATE("Возвращает итератор за последним заполненным элементом",
    permutation, PERMUTATION_ALGORITHMS)
{
    const auto size = 16;
    std::vector<std::uint32_t> indices(size * 2);

    const auto end = permutation::apply(indices.begin(), size);
    CHECK(end == indices.begin() + size);
}
