#include <fftpp/ring.hpp>
#include <fftpp/utility/binpow.hpp>

#include <doctest/doctest.h>

#include <cstdint>
#include <limits>

TEST_CASE("Возводит число в степень")
{
    CHECK(fftpp::binpow(2, 4) == 16);
    CHECK(fftpp::binpow(3u, 5u) == 243u);
    CHECK(fftpp::binpow(4l, 7l) == 16384l);
}

TEST_CASE("Работает с классом `ring_t`")
{
    CHECK(fftpp::binpow(fftpp::ring_t{2u}, 10) == fftpp::ring_t{1024u});

    const auto max = std::numeric_limits<fftpp::ring_t<std::uint32_t>>::max();
    CHECK(fftpp::binpow(max, 2) == 1u);

    const auto modulo = fftpp::ring_t<std::uint32_t>::modulo;
    CHECK(fftpp::binpow(max, modulo - 1) == 1u);
}
