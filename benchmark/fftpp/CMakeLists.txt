add_executable(fftbench fft.cpp)
target_link_libraries(fftbench PRIVATE fftpp::headers)

add_executable(bitrev bit_reverse.cpp)
target_link_libraries(bitrev PRIVATE fftpp::headers)

add_executable(introot integral_roots.cpp)
target_link_libraries(introot PRIVATE fftpp::headers)

add_executable(inverse inverse_elements.cpp)
target_link_libraries(inverse PRIVATE fftpp::headers)

configure_file(fft.py.in fft.py @ONLY)
