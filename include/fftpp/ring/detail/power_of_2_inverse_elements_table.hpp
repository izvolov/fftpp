#pragma once

#include <fftpp/ring/ring.hpp>

#include <array>
#include <concepts>

namespace fftpp::detail
{
    template <typename Ring>
    struct power_of_2_inverse_elements_table
    {
    };

    template <typename Ring>
    inline constexpr auto power_of_2_inverse_elements_table_v =
        power_of_2_inverse_elements_table<Ring>::value;

    template <>
    struct power_of_2_inverse_elements_table<ring30>
    {
        static constexpr auto value =
            std::array
            {
                ring30{1},
                ring30{1610612737},
                ring30{2415919105},
                ring30{2818572289},
                ring30{3019898881},
                ring30{3120562177},
                ring30{3170893825},
                ring30{3196059649},
                ring30{3208642561},
                ring30{3214934017},
                ring30{3218079745},
                ring30{3219652609},
                ring30{3220439041},
                ring30{3220832257},
                ring30{3221028865},
                ring30{3221127169},
                ring30{3221176321},
                ring30{3221200897},
                ring30{3221213185},
                ring30{3221219329},
                ring30{3221222401},
                ring30{3221223937},
                ring30{3221224705},
                ring30{3221225089},
                ring30{3221225281},
                ring30{3221225377},
                ring30{3221225425},
                ring30{3221225449},
                ring30{3221225461},
                ring30{3221225467},
                ring30{3221225470}
            };
    };

    template <>
    struct power_of_2_inverse_elements_table<ring16>
    {
        static constexpr auto value =
            std::array
            {
                ring16{1},
                ring16{32769},
                ring16{49153},
                ring16{57345},
                ring16{61441},
                ring16{63489},
                ring16{64513},
                ring16{65025},
                ring16{65281},
                ring16{65409},
                ring16{65473},
                ring16{65505},
                ring16{65521},
                ring16{65529},
                ring16{65533},
                ring16{65535},
                ring16{65536}
            };
    };

    template <>
    struct power_of_2_inverse_elements_table<ring8>
    {
        static constexpr auto value =
            std::array
            {
                ring8{1},
                ring8{129},
                ring8{193},
                ring8{225},
                ring8{241},
                ring8{249},
                ring8{253},
                ring8{255},
                ring8{256}
            };
    };
}
