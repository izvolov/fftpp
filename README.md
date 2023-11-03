[:uk: English version](README.en.md)

FFT++
=====

БПФ (быстрое преобразование Фурье), приготовленное по-плюсовому.

![Статус сборки под Linux](https://github.com/izvolov/fftpp/workflows/Linux/badge.svg) ![Статус сборки под macOS](https://github.com/izvolov/fftpp/workflows/macOS/badge.svg) ![Статус сборки под Виндой](https://github.com/izvolov/fftpp/workflows/Windows/badge.svg) [![Покрытие кода тестами](https://codecov.io/gh/izvolov/fftpp/branch/master/graph/badge.svg)](https://codecov.io/gh/izvolov/fftpp) [![Попробовать онлайн на Wandbox.org](https://img.shields.io/badge/try-online-blue.svg)](https://wandbox.org/permlink/XvaU2j9UzDP9SzzR)

О проекте
---------

FFT++ — это заголовочная библиотека, реализующая классическое БПФ на C++ так, как это должно быть сделано на C++. Интерфейс, красота и понятность кода, а также простота в подключении и использовании не приносятся в жертву эффективности.

Текущая функциональность включает прямое и обратное БПФ [в комплексных числах](#комплексное-бпф) и [в модульной арифметике](#целочисленное-бпф). Для целочисленного преобразования реализован класс [`fftpp::ring_t`](include/fftpp/ring/ring.hpp).

Содержание
----------

1.  [Комплексное БПФ](#комплексное-бпф)
2.  [Целочисленное БПФ](#целочисленное-бпф)
3.  [Установка](#установка)
    1.  [Вариант 1: CMake FetchContent](#вариант-1-cmake-fetchcontent)
    2.  [Вариант 2: Установить с помощью CMake](#вариант-2-установить-с-помощью-cmake)
    3.  [Вариант 3: Скопировать исходники](#вариант-3-скопировать-исходники)
    4.  [Вариант 4: Подключить папку с проектом в CMake](#вариант-4-подключить-папку-с-проектом-в-cmake)
5.  [Требования](#требования)

Комплексное БПФ
---------------

>   *Примечание:*
>   В алгоритме используются комплексные числа из STL.
>   Заголовок [`fftpp/complex.hpp`](include/fftpp/complex.hpp) нужен для специальных функций, требуемых для БПФ:
>   -   Получения единицы;
>   -   Получения первообразного корня степени `n` из единицы;
>   -   Получения обратного элемента к `n`.

```cpp
#include <fftpp/complex.hpp>
#include <fftpp/fft.hpp>
#include <fftpp/inverse_fft.hpp>

#include <complex>
#include <vector>

int main ()
{
    const auto in = std::vector{1, 2, 3, 4};

    // Фунциональный объект, хранящий (при необходимости) предпосчитанные
    // значения, необходимые для эффективной работы алгоритма.
    const auto fft = fftpp::fft_t<std::complex<double>>(in.size());

    // Прямое БПФ
    auto out = std::vector<std::complex<double>>(in.size());
    fft(in.begin(), out.begin());

    // Обратное БПФ
    auto inv = std::vector<std::complex<double>>(out.size());
    inverse(fft)(out.begin(), inv.begin());
}
```

Целочисленное БПФ
-----------------

>   *Примечание:*
>   Для БПФ в модульной арифметике необходимо подключить класс, реализующий кольцо по простому модулю, а также все необходимые для БПФ специальные функции. Удобнее всего это сделать с помощью
подключения заголовка [`fftpp/ring.hpp`](include/fftpp/ring.hpp).

```cpp
#include <fftpp/ring.hpp>
#include <fftpp/fft.hpp>
#include <fftpp/inverse_fft.hpp>

#include <cstdint>
#include <vector>

int main ()
{
    const auto in = std::vector{1, 2, 3, 4};

    // Фунциональный объект, хранящий (при необходимости) предпосчитанные
    // значения, необходимые для эффективной работы алгоритма.
    const auto fft = fftpp::fft_t<fftpp::ring_t<std::uint32_t>>(in.size());

    // Прямое БПФ
    auto out = std::vector<fftpp::ring_t<std::uint32_t>>(in.size());
    fft(in.begin(), out.begin());

    // Обратное БПФ
    auto inv = std::vector<fftpp::ring_t<std::uint32_t>>(out.size());
    inverse(fft)(out.begin(), inv.begin());
}
```

Установка
---------

Возможны следующие четыре варианта установки.

### Вариант 1: CMake FetchContent

Начиная с версии CMake 3.14 можно скачать и подключить репозиторий с зависимостью прямо во время сборки с помощью модуля [FetchContent](https://cmake.org/cmake/help/v3.14/module/FetchContent.html). В случае с FFT++ это можно записать тремя командами:

```cmake
include(FetchContent)
FetchContent_Declare(fftpp GIT_REPOSITORY https://github.com/izvolov/fftpp.git)
FetchContent_MakeAvailable(fftpp)
```

Этот набор команд породит интерфейсную библиотеку `fftpp::headers`, которую можно использовать при подключении библиотек:

```cmake
add_executable(program program.cpp)
target_link_libraries(program PRIVATE fftpp::headers)
```

### Вариант 2: Установить с помощью CMake

```shell
cd path/to/build/directory
cmake -DCMAKE_BUILD_TYPE=Release path/to/fftpp
make
make install
```

После этого в системе сборки CMake будет доступен пакет `fftpp`:

```cmake
find_package(fftpp)
```

Эта команда породит интерфейсную библиотеку `fftpp::headers`, которую можно использовать при подключении библиотек:

```cmake
add_executable(program program.cpp)
target_link_libraries(program PRIVATE fftpp::headers)
```

### Вариант 3: Скопировать исходники

Поскольку FFT++ — полностью заголовочная библиотека, то достаточно скопировать в нужную директорию все заголовки из папки `include` из [репозитория](https://github.com/izvolov/fftpp) и подключить их в свой проект.

### Вариант 4: Подключить папку с проектом в CMake

```cmake
add_subdirectory("path/to/fftpp")
```

После этого в системе сборки CMake будет доступна цель `fftpp::headers`, которую можно использовать при подключении библиотек:

```cmake
add_executable(program program.cpp)
target_link_libraries(program PRIVATE fftpp::headers)
```

Требования
----------

0.  Система сборки [CMake](https://cmake.org) версии 3.25 или выше;
1.  Любой компилятор, который сносно поддерживает стандарт C++20, например, GCC 10 или Clang 13. Заведомо работающие конфигурации перечислены в [интеграционных скриптах](.github/workflows);
2.  Библиотека [FFTW](http://fftw.org) для проведения замеров [не обязательно\*].
3.  Библиотека тестирования [doctest](https://github.com/doctest/doctest) [Не обязательно\*\*];
4.  [Doxygen](http://doxygen.nl) [Не обязательно].

> \*) Можно включить сравнительные замеры с библиотекой FFTW. Для этого нужно при сборке с помощью `CMake` включить опцию `FFTPP_BENCH_FFTW` (по умолчанию она выключена):
>
> ```shell
> cmake -DCMAKE_BUILD_TYPE=Release path/to/fftpp -FFTPP_BENCH_FFTW=ON
> ```
> \*\*) Можно миновать этап сборки и тестирования, если при сборке с помощью `CMake` выключить опцию `FFTPP_TESTING`:
>
> ```shell
> cmake -DCMAKE_BUILD_TYPE=Release path/to/fftpp -DFFTPP_TESTING=OFF
> ```
>
> Также тестирование автоматически отключается в случае, если FFT++ подключается в качестве подпроекта.
