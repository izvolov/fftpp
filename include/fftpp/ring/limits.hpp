#pragma once

#include <fftpp/ring/ring.hpp>

#include <concepts>
#include <limits>

template <std::unsigned_integral N>
class std::numeric_limits<fftpp::ring_t<N>>: public std::numeric_limits<N>
{
public:
    static constexpr fftpp::ring_t<N> max () noexcept
    {
        return fftpp::ring_t<N>(fftpp::ring_t<N>::modulo - 1);
    }
};
