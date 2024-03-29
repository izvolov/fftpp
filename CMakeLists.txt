###################################################################################################
##
##      Информация о проекте
##
###################################################################################################

cmake_minimum_required(VERSION 3.25)
project(fftpp VERSION 0.1 LANGUAGES CXX)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

###################################################################################################
##
##      Опции проекта
##
###################################################################################################

if (IS_SUBPROJECT AND NOT DEFINED FFTPP_TESTING)
    message(STATUS "fftpp не тестируется в режиме подмодуля")
    set(FFTPP_TESTING OFF)
endif()

if (IS_SUBPROJECT AND NOT DEFINED FFTPP_BENCHMARKING)
    message(STATUS "Замеры производительности fftpp в режиме подмодуля выключены")
    set(FFTPP_BENCHMARKING OFF)
endif()

if (IS_SUBPROJECT AND NOT DEFINED FFTPP_DOC)
    message(STATUS "Автодокументация для fftpp выключена в режиме подмодуля")
    set(FFTPP_DOC OFF)
endif()

if (IS_SUBPROJECT AND NOT DEFINED FFTPP_WANDBOX)
    message(STATUS "Онлайн-песочница для fftpp выключена в режиме подмодуля")
    set(FFTPP_WANDBOX OFF)
endif()

option(FFTPP_TESTING "Включить модульное тестирование" ON)
option(FFTPP_BENCHMARKING "Включить замеры производительности" ON)
option(FFTPP_COVERAGE "Включить измерение покрытия кода тестами" OFF)
option(FFTPP_DOC "Включить документирование" ON)
option(FFTPP_WANDBOX "Включить онлайн-песочницу" ON)

###################################################################################################
##
##      Опции компиляции
##
###################################################################################################

if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    add_compile_options(
        -Werror

        -Wall
        -Wextra
        -Wpedantic

        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wctor-dtor-privacy
        -Wenum-compare
        -Wfloat-equal
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
        -Wredundant-decls
        -Wsign-conversion
        -Wsign-promo
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4 /WX)
endif()

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

###################################################################################################
##
##      Заголовочная библиотека
##
###################################################################################################

add_library(fftpp_headers INTERFACE)
target_include_directories(fftpp_headers INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(fftpp_headers INTERFACE cxx_std_20)
set_target_properties(fftpp_headers PROPERTIES EXPORT_NAME headers)

add_library(fftpp::headers ALIAS fftpp_headers)

###################################################################################################
##
##      Установка
##
###################################################################################################

install(DIRECTORY include/fftpp DESTINATION include)

install(TARGETS fftpp_headers EXPORT fftppConfig)
install(EXPORT fftppConfig NAMESPACE fftpp:: DESTINATION share/fftpp/cmake)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/fftppConfigVersion.cmake"
    VERSION
        ${PROJECT_VERSION}
    COMPATIBILITY
        AnyNewerVersion
)
install(FILES "${PROJECT_BINARY_DIR}/fftppConfigVersion.cmake" DESTINATION share/fftpp/cmake)

###################################################################################################
##
##      Тесты
##
###################################################################################################

if(NOT FFTPP_TESTING)
    message(STATUS "Тестирование проекта fftpp выключено")
else()
    add_subdirectory(test)
endif()

###################################################################################################
##
##      Замеры
##
###################################################################################################

if(NOT FFTPP_BENCHMARKING)
    message(STATUS "Замеры производительности fftpp выключены")
else()
    add_subdirectory(benchmark)
endif()

###################################################################################################
##
##      Документация
##
###################################################################################################

if(NOT FFTPP_DOC)
    message(STATUS "Автодокументация проекта fftpp выключена")
else()
    add_subdirectory(doc)
endif()

###################################################################################################
##
##      Онлайн-песочница
##
###################################################################################################

if(NOT FFTPP_WANDBOX)
    message(STATUS "Онлайн-песочница для проекта fftpp выключена")
else()
    add_subdirectory(online)
endif()
