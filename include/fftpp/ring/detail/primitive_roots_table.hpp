#pragma once

#include <fftpp/ring/ring.hpp>

#include <array>
#include <concepts>
#include <cstdint>

namespace fftpp::detail
{
    template <typename Ring>
    struct primitive_roots_table
    {
    };

    template <typename Ring>
    inline constexpr auto primitive_roots_table_v = primitive_roots_table<Ring>::value;

    template <>
    struct primitive_roots_table<ring30>
    {
        static constexpr auto value =
            std::array
            {
                ring30{1},
                ring30{3221225472},
                ring30{2207278994},
                ring30{613406496},
                ring30{741264833},
                ring30{122509875},
                ring30{2746140649},
                ring30{1068583503},
                ring30{708503697},
                ring30{1363205573},
                ring30{746485901},
                ring30{494608121},
                ring30{3162603993},
                ring30{1590401422},
                ring30{2831319379},
                ring30{2823078715},
                ring30{1003735924},
                ring30{1287601835},
                ring30{896867674},
                ring30{1045839643},
                ring30{1852389738},
                ring30{212052632},
                ring30{52829935},
                ring30{882575513},
                ring30{3098264284},
                ring30{891569319},
                ring30{498210922},
                ring30{815730721},
                ring30{28561},
                ring30{169},
                ring30{13}
            };
    };

    template <>
    struct primitive_roots_table<ring16>
    {
        static constexpr auto value =
            std::array
            {
                ring16{1},
                ring16{65536},
                ring16{65281},
                ring16{4096},
                ring16{64},
                ring16{65529},
                ring16{8224},
                ring16{13987},
                ring16{282},
                ring16{15028},
                ring16{19139},
                ring16{61869},
                ring16{54449},
                ring16{6561},
                ring16{81},
                ring16{9},
                ring16{3}
            };
    };

    template <>
    struct primitive_roots_table<ring8>
    {
        static constexpr auto value =
            std::array
            {
                ring8{1},
                ring8{256},
                ring8{241},
                ring8{64},
                ring8{249},
                ring8{136},
                ring8{81},
                ring8{9},
                ring8{3}
            };
    };
}
