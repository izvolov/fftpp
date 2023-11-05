#pragma once

#include <fftpp/ring/basic_ring.hpp>
#include <fftpp/unity.hpp>

#include <concepts>
#include <cstdint>

namespace fftpp
{
    template <std::uint32_t Mod, std::unsigned_integral Rep>
    struct unity_t<basic_ring<Mod, Rep>>
    {
        constexpr auto operator () () const
        {
            return basic_ring<Mod, Rep>(1);
        }
    };
}
