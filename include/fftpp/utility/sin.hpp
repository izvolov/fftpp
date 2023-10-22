#pragma once

// TODO: Заменить на соответствующий макрос из <version>
// Будет что-то типа __cpp_lib_constexpr_math
#if defined __GNUC__ && __GNUC__ >= 10
#include <cmath>
#endif

namespace fftpp
{
#if defined __GNUC__ && __GNUC__ >= 10
    using std::sin;
#else
    // Использовать только для primitive_roots_of_unity!
    constexpr double sin (double x)
    {
        auto result = x;

        const auto x_2 = x * x;
        auto fact = 1ul;
        auto summand = x;

        for (auto i = 0; i < 20; ++i)
        {
            summand *= -x_2;
            summand /= static_cast<double>((fact + 1) * (fact + 2));

            fact += 2;
            result += summand;
        }

        return result;
    }
#endif
}
