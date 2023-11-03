option(FFTPP_BENCH_FFTW "Включить в замеры производительности библиотеку FFTW" OFF)

add_executable(fftbench fft.cpp)
target_link_libraries(fftbench PRIVATE fftpp::headers)

if (FFTPP_BENCH_FFTW)
    find_package(fftw3 REQUIRED)
    target_link_libraries(fftbench PRIVATE FFTW3::fftw3)
    target_compile_definitions(fftbench PRIVATE FFTPP_BENCH_FFTW)
endif()

add_executable(bitrev bit_reverse.cpp)
target_link_libraries(bitrev PRIVATE fftpp::headers)

add_executable(introot integral_roots.cpp)
target_link_libraries(introot PRIVATE fftpp::headers)

add_executable(inverse inverse_elements.cpp)
target_link_libraries(inverse PRIVATE fftpp::headers)

configure_file(fft.py.in fft.py @ONLY)
