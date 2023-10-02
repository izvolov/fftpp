#include <fftpp/complex.hpp>
#include <fftpp/fft.hpp>

#include <complex>
#include <vector>

int main ()
{
    const auto in = std::vector{1, 2, 3, 4};
    auto out = std::vector<std::complex<double>>(in.size());

    const auto fft = fftpp::fft_t<std::complex<double>>(in.size());
    fft(in.begin(), out.begin());
}
