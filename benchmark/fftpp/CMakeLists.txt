add_executable(fftbench fft.cpp)
target_link_libraries(fftbench PRIVATE fftpp::headers)

add_executable(bitrev bit_reverse.cpp)
target_link_libraries(bitrev PRIVATE fftpp::headers)
