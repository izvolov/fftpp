include(${PROJECT_SOURCE_DIR}/cmake/doctest.cmake)

add_executable(fftpp-unit-tests test_main.cpp)
target_sources(fftpp-unit-tests
    PRIVATE
        fftpp/concept/subscriptable.cpp
        fftpp/fft_complex.cpp
        fftpp/ring.cpp
        fftpp/utility/binpow.cpp
        fftpp/utility/bit_reversal_permutation.cpp
        fftpp/utility/permute.cpp
        fftpp/utility/reverse_lower_bits.cpp
)
target_link_libraries(fftpp-unit-tests
    PRIVATE
        fftpp::headers
        doctest::doctest
)

find_program(GCOVR_EXECUTABLE gcovr)
if(FFTPP_COVERAGE AND GCOVR_EXECUTABLE)
    message(STATUS "Измерение покрытия кода тестами включено")

    target_compile_options(fftpp-unit-tests PUBLIC --coverage)
    target_link_options(fftpp-unit-tests PUBLIC -fprofile-arcs)

    add_custom_target(coverage
        COMMAND
            ${GCOVR_EXECUTABLE}
                --root=${PROJECT_SOURCE_DIR}/
                --filter=${PROJECT_SOURCE_DIR}/include
                --filter=${PROJECT_SOURCE_DIR}/src
                --object-directory=${PROJECT_BINARY_DIR}
        DEPENDS
            check
    )
elseif(FFTPP_COVERAGE AND NOT GCOVR_EXECUTABLE)
    set(FFTPP_COVERAGE OFF)
    message(WARNING "Для замеров покрытия кода тестами требуется программа gcovr")
endif()

add_custom_target(check ALL COMMAND fftpp-unit-tests)
