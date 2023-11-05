#pragma once

#include <fftpp/ring/basic_ring.hpp>

#include <concepts>
#include <cstdint>
#include <limits>

template <std::uint32_t Mod, std::unsigned_integral Rep>
class std::numeric_limits<fftpp::basic_ring<Mod, Rep>>: public std::numeric_limits<Rep>
{
public:
    static constexpr fftpp::basic_ring<Mod, Rep> max () noexcept
    {
        return fftpp::basic_ring<Mod, Rep>(fftpp::basic_ring<Mod, Rep>::modulo - 1);
    }
};
