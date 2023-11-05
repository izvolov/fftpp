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

TEST_CASE_TEMPLATE("Работает с классом `basic_ring`",
    ring, fftpp::ring8, fftpp::ring16, fftpp::ring30)
{
    CHECK(fftpp::binpow(ring{2u}, 8) == ring{256u});

    const auto max = std::numeric_limits<ring>::max();
    CHECK(fftpp::binpow(max, 2) == 1u);

    const auto modulo = ring::modulo;
    CHECK(fftpp::binpow(max, modulo - 1) == 1u);
}
