#include <fftpp/header.hpp>

#include <doctest/doctest.h>

TEST_CASE("Функция myfunc делает классные штуки со структурой mystruct")
{
    CHECK(fftpp::myfunc(fftpp::mystruct{}));
}
