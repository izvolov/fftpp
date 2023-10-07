#include <fftpp/ring.hpp>

#include <doctest/doctest.h>

#include <cstdint>
#include <limits>
#include <type_traits>
#include <iostream>

TEST_CASE_TEMPLATE("\"ring_t\" конструируется из любого целочисленного типа",
    type,
    std::int8_t, std::uint8_t, std::uint16_t, std::uint16_t, std::int32_t, std::uint32_t,
    std::int64_t, std::uint64_t)
{
    auto r = fftpp::ring_t{type{123}};
    CHECK(r == 123u);
}

TEST_CASE_TEMPLATE("Допустимые значения \"ring_t\" лежат в диапазоне [0, ring_t::modulo)",
    type, std::uint32_t, std::uint64_t)
{
    using ring_type = fftpp::ring_t<type>;

    static_assert(std::numeric_limits<ring_type>::min() == 0);
    static_assert(std::numeric_limits<ring_type>::max() == ring_type(ring_type::modulo - 1));
    CHECK(std::numeric_limits<ring_type>::min() == 0);
    CHECK(std::numeric_limits<ring_type>::max() == ring_type(ring_type::modulo - 1));
}

TEST_CASE_TEMPLATE("Тип значения \"ring_t\" выводится в uint32, если входной тип не больше",
    type, std::int8_t, std::uint8_t, std::uint16_t, std::uint16_t, std::int32_t, std::uint32_t)
{
    auto r = fftpp::ring_t{type{12}};

    CHECK(std::is_same_v<decltype(r), fftpp::ring_t<std::uint32_t>>);
}

TEST_CASE_TEMPLATE("Тип значения \"ring_t\" выводится в uint64, если входной тип 64-битный",
    type, std::int64_t, std::uint64_t)
{
    auto r = fftpp::ring_t{type{13}};

    CHECK(std::is_same_v<decltype(r), fftpp::ring_t<std::uint64_t>>);
}
