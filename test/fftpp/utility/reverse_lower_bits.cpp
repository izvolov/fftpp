#include <fftpp/utility/reverse_lower_bits.hpp>

#include <doctest/doctest.h>

#include <cstdint>

TEST_CASE("Разворачивает заданное количество младших битов")
{
    CHECK(fftpp::reverse_lower_bits(0b1101, 4) == 0b1011);
    CHECK(fftpp::reverse_lower_bits(0b0001, 1) == 0b0001);
    CHECK(fftpp::reverse_lower_bits(0b0001, 3) == 0b0100);
    CHECK(fftpp::reverse_lower_bits(0b0001, 2) == 0b0010);
}

TEST_CASE("Более старшие биты в процессе переворота теряются")
{
    CHECK(fftpp::reverse_lower_bits(0b101011010110, 5) == 0b01101);
    //                                [xxxxx][<->]
}
