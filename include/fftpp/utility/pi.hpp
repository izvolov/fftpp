#pragma once

#include <version>

#ifdef __cpp_lib_math_constants
#include <numbers>
#else
#include <concepts>
#endif

namespace fftpp
{
#ifdef __cpp_lib_math_constants
    using std::numbers::pi_v;
    using std::numbers::pi;
#else
    template <std::floating_point F>
    inline constexpr auto pi_v = F{3.141592653589793238462643383279502884L};

    inline constexpr auto pi = pi_v<double>;
#endif
}
