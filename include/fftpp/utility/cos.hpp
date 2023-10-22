#pragma once

// TODO: Заменить на соответствующий макрос из <version>
// Будет что-то типа __cpp_lib_constexpr_math
#if defined __GNUC__ && __GNUC__ >= 10
#include <cmath>
#else
#include <fftpp/utility/sin.hpp>
#include <fftpp/utility/pi.hpp>
#endif

namespace fftpp
{
#if defined __GNUC__ && __GNUC__ >= 10
    using std::cos;
#else
    // Использовать только для primitive_roots_of_unity!
    constexpr double cos (double x)
    {
        return sin(x + pi / 2.0);
    }
#endif
}
