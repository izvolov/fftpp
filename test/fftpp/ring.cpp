#include <fftpp/ring.hpp>

#include <doctest/doctest.h>

#include <cstdint>
#include <limits>
#include <type_traits>
#include <iostream>

TEST_CASE("Реализует модульную арифметику со сложением")
{
    CHECK(fftpp::ring8{256} + 1u == fftpp::ring8{0});
    CHECK(fftpp::ring8{200} + fftpp::ring8{100} == fftpp::ring8{43});

    CHECK(fftpp::ring16{65536} + 2 == fftpp::ring16{1});
    CHECK(fftpp::ring16{60000} + fftpp::ring16{10000} == fftpp::ring16{4463});

    CHECK(fftpp::ring30{fftpp::ring30::modulo - 1} + 2l == fftpp::ring30{1});
    CHECK(fftpp::ring30{3000000000} + fftpp::ring30{1000000000} == fftpp::ring30{778774527});
}

TEST_CASE("Реализует модульную арифметику с вычитанием")
{
    CHECK(fftpp::ring8{0} - 1ul == fftpp::ring8{256});
    CHECK(fftpp::ring8{123} - fftpp::ring8{234} == fftpp::ring8{146});

    CHECK(fftpp::ring16{1} - 3u == fftpp::ring16{65535});
    CHECK(fftpp::ring16{12345} - fftpp::ring16{34567} == fftpp::ring16{43315});

    CHECK(fftpp::ring30{5} - 20 == fftpp::ring30{3221225458});
    CHECK(fftpp::ring30{1000000000} - fftpp::ring30{1234567890} == fftpp::ring30{2986657583});
}

TEST_CASE("Реализует модульную арифметику с умножением")
{
    CHECK(fftpp::ring8{128} * 2u == fftpp::ring8{256});
    CHECK(fftpp::ring8{128} * 3ul == fftpp::ring8{127});

    CHECK(fftpp::ring16{2} * 1u == fftpp::ring16{2});
    CHECK(fftpp::ring16{1000} * fftpp::ring16{1000} == fftpp::ring16{16945});

    CHECK(fftpp::ring30{1u << 31} * 2 == fftpp::ring30{1073741823});
    CHECK(fftpp::ring30{1u << 31} * fftpp::ring30{1u << 31} == fftpp::ring30{2863311532});
}

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
