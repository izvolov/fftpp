#include <fftpp/ring.hpp>

#include <doctest/doctest.h>

#include <cstdint>
#include <limits>
#include <type_traits>
#include <iostream>

TEST_CASE_TEMPLATE("ring8 конструируется из любого целочисленного типа, который может быть неявно "
    "преобразован к типу представления (ring8::representation_type)",
    type,
    std::uint8_t, std::int8_t, std::uint16_t, std::int16_t, std::uint32_t, std::int32_t)
{
    auto r = fftpp::ring8{type{123}};
    CHECK(r == 123u);
}

TEST_CASE_TEMPLATE("ring16 конструируется из любого целочисленного типа, который может быть неявно "
    "преобразован к типу представления (ring16::representation_type)",
    type,
    std::uint8_t, std::int8_t, std::uint16_t, std::int16_t,
    std::uint32_t, std::int32_t, std::uint64_t)
{
    auto r = fftpp::ring16{type{123}};
    CHECK(r == 123u);
}

TEST_CASE_TEMPLATE("ring30 конструируется из любого целочисленного типа, который может быть неявно "
    "преобразован к типу представления (ring30::representation_type)",
    type,
    std::uint8_t, std::int8_t, std::uint16_t, std::int16_t,
    std::uint32_t, std::int32_t, std::uint64_t)
{
    auto r = fftpp::ring30{type{123}};
    CHECK(r == 123u);
}

TEST_CASE_TEMPLATE("Допустимые значения \"ring\" лежат в диапазоне [0, ring::modulo)",
    ring, fftpp::ring8, fftpp::ring16, fftpp::ring30)
{
    static_assert(std::numeric_limits<ring>::min() == 0);
    static_assert(std::numeric_limits<ring>::max() == ring(ring::modulo - 1));
    CHECK(std::numeric_limits<ring>::min() == 0);
    CHECK(std::numeric_limits<ring>::max() == ring(ring::modulo - 1));
}
