add_executable(fftbench fft.cpp)
target_link_libraries(fftbench PRIVATE fftpp::headers)
