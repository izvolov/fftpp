[:uk: English version](README.en.md)

Шаблон проекта на основе системы сборки CMake для языка C++
===========================================================

Скопировать, поменять "fftpp" на нужное название — и в путь.

![Статус сборки под Linux](https://github.com/izvolov/fftpp/workflows/Linux/badge.svg) ![Статус сборки под macOS](https://github.com/izvolov/fftpp/workflows/macOS/badge.svg) ![Статус сборки под Виндой](https://github.com/izvolov/fftpp/workflows/Windows/badge.svg) [![Покрытие кода тестами](https://codecov.io/gh/izvolov/fftpp/branch/master/graph/badge.svg)](https://codecov.io/gh/izvolov/fftpp) [![Попробовать онлайн на Wandbox.org](https://img.shields.io/badge/try-online-blue.svg)](https://wandbox.org/permlink/QElvxuMzHgL9fqci)

Содержание
----------

1.  [Сборка](#сборка)
    1.  [Генерация](#генерация)
    2.  [Сборка](#сборка-проекта)
2.  [Опции](#опции)
    1.  [FFTPP_COVERAGE](#FFTPP_COVERAGE)
    2.  [FFTPP_TESTING](#FFTPP_TESTING)
    3.  [DOXYGEN_OUTPUT_LANGUAGE](#DOXYGEN_OUTPUT_LANGUAGE)
3.  [Сборочные цели](#сборочные-цели)
    1.  [По умолчанию](#по-умолчанию)
    2.  [fftpp_library](#fftpp_library)
    3.  [fftpp-unit-tests](#fftpp-unit-tests)
    4.  [check](#check)
    5.  [coverage](#coverage)
    6.  [doc](#doc)
    7.  [wandbox](#wandbox)
4.  [Примеры](#примеры)
5.  [Использование](#использование)
    1.  [Через установку](#через-установку)
    2.  [В качестве подмодуля](#в-качестве-подмодуля)
6.  [Инструменты](#инструменты)
7.  [Бонус](#бонус)

Сборка
------

Сборка данного проекта, как и любого другого проекта на системе сборки CMake, состоит из двух этапов:

### Генерация

```shell
cmake -S путь/к/исходникам -B путь/к/сборочной/директории [опции ...]
```

[Подробнее про опции](#опции).

### Сборка проекта

```shell
cmake --build путь/к/сборочной/директории [--target target]
```

[Подробнее про сборочные цели](#сборочные-цели).

Опции
-----

### FFTPP_COVERAGE

```shell
cmake -S ... -B ... -DFFTPP_COVERAGE=ON [прочие опции ...]
```

Включает цель [`coverage`](#coverage), с помощью которой можно запустить замер покрытия кода тестами.

### FFTPP_TESTING

```shell
cmake -S ... -B ... -DFFTPP_TESTING=OFF [прочие опции ...]
```

Предоставляет возможность выключить сборку модульных тестов и цель [`check`](#check). Как следствие, выключается замер покрытия кода тестами (см. [Покрытие](#FFTPP_COVERAGE)).

Также тестирование автоматически отключается в случае, если проект подключается в другой проект качестве подпроекта с помощью команды [`add_subdirectory`](https://cmake.org/cmake/help/v3.14/command/add_subdirectory.html).

### DOXYGEN_OUTPUT_LANGUAGE

```shell
cmake -S ... -B ... -DDOXYGEN_OUTPUT_LANGUAGE=English [прочие опции ...]
```

Переключает язык документации, которую генерирует цель [`doc`](#doc) на заданный. Список доступных языков см. на [сайте системы Doxygen](http://www.doxygen.nl/manual/config.html#cfg_output_language).

По умолчанию включён русский.

Сборочные цели
--------------

### По умолчанию

```shell
cmake --build путь/к/сборочной/директории
cmake --build путь/к/сборочной/директории --target all
```

Если цель не указана (что эквивалентно цели `all`), собирает всё, что можно, а также вызывает цель [`check`](#check).

### fftpp_library

```shell
cmake --build путь/к/сборочной/директории --target fftpp_library
```

Компилирует библиотеку `fftpp_library`. Включено по умолчанию.

### fftpp-unit-tests

```shell
cmake --build путь/к/сборочной/директории --target fftpp-unit-tests
```

Компилирует модульные тесты. Включено по умолчанию.

### check

```shell
cmake --build путь/к/сборочной/директории --target check
```

Запускает собранные (собирает, если ещё не) модульные тесты. Включено по умолчанию.

См. также [`fftpp-unit-tests`](#fftpp-unit-tests).

### coverage

```shell
cmake --build путь/к/сборочной/директории --target coverage
```

Анализирует запущенные (запускает, если ещё не) модульные тесты на предмет покрытия кода тестами при помощи программы [gcovr](https://gcovr.com).

Цель доступна только при включённой опции [`FFTPP_COVERAGE`](#FFTPP_COVERAGE).

См. также [`check`](#check).

### doc

```shell
cmake --build путь/к/сборочной/директории --target doc
```

Запускает генерацию документации к коду при помощи системы [Doxygen](http://doxygen.nl).

### wandbox

```shell
cmake --build путь/к/сборочной/директории --target wandbox
```

Для этого используется сервис [Wandbox](https://wandbox.org). Не злоупотребляйте этой штукой, сервера не резиновые.

Примеры
-------

#### Сборка проекта в отладочном режиме с замером покрытия

```shell
cmake -S путь/к/исходникам -B путь/к/сборочной/директории -DCMAKE_BUILD_TYPE=Debug -DFFTPP_COVERAGE=ON
cmake --build путь/к/сборочной/директории --target coverage --parallel 16
```

#### Установка проекта без предварительной сборки и тестирования

```shell
cmake -S путь/к/исходникам -B путь/к/сборочной/директории -DFFTPP_TESTING=OFF -DCMAKE_INSTALL_PREFIX=путь/к/установойной/директории
cmake --build путь/к/сборочной/директории --target install
```

#### Сборка в выпускном режиме заданным компилятором

```shell
cmake -S путь/к/исходникам -B путь/к/сборочной/директории -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++-8 -DCMAKE_PREFIX_PATH=путь/к/директории/куда/установлены/зависимости
cmake --build путь/к/сборочной/директории --parallel 4
```

#### Генерирование документации на английском

```shell
cmake -S путь/к/исходникам -B путь/к/сборочной/директории -DCMAKE_BUILD_TYPE=Release -DDOXYGEN_OUTPUT_LANGUAGE=English
cmake --build путь/к/сборочной/директории --target doc
```

Использование
-------------

### Через установку

Один из вариантов использования модуля — установить его в систему.

```shell
cmake --build путь/к/сборочной/директории --target install
```

После этого любой другой проект, вызвав команду [`find_package`](https://cmake.org/cmake/help/v3.14/command/find_package.html), получает возможность использовать все библиотеки из пространства имён `fftpp::`:

```cmake
find_package(fftpp 1.0 REQUIRED)

add_executable(some_executable some.cpp sources.cpp)
target_link_libraries(some_executable PRIVATE fftpp::library)
```

Библиотеку `fftpp::library` нужно подключать тогда, когда необходимо слинковаться с библиотекой `libfftpp_library`. Если достаточно заголовков, то тогда стоит использовать библиотеку `fftpp::headers`.

### В качестве подмодуля

Также проект может быть подключён к другому проекту в качестве подмодуля с помощью команды [`add_subdirectory`](https://cmake.org/cmake/help/v3.14/command/add_subdirectory.html).

В этом случае аналогичным образом будут доступны библиотеки `fftpp::library` и `fftpp::headers`.

Инструменты
-----------

1.  [CMake](https://cmake.org) 3.14

    CMake 3.14 требуется потому, что в предыдущих версиях некорректно работает команда `install(TARGETS ... EXPORT ...)`, а именно — не прописываются пути по умолчанию.

2.  Библиотека тестирования [doctest](https://github.com/onqtam/doctest)

    Тестирование можно отключать (см. [Тестирование](#FFTPP_TESTING)).

3.  [Doxygen](http://doxygen.nl)

    Для переключения языка, на котором будет сгенерирована документация, предусмотрена опция [`DOXYGEN_OUTPUT_LANGUAGE`](#DOXYGEN_OUTPUT_LANGUAGE).

4.  Интерпретатор ЯП [Python 3](https://www.python.org)

    Для автоматической генерации [онлайн-песочницы](#wandbox).

Бонус
-----

С помощью CMake и пары хороших инструментов можно обеспечить статический анализ с минимальными телодвижениями.

### Cppcheck

В CMake встроена поддержка инструмента для статического анализа [Cppcheck](http://cppcheck.sourceforge.net).

Для этого нужно воспользоваться опцией [`CMAKE_CXX_CPPCHECK`](https://cmake.org/cmake/help/v3.14/variable/CMAKE_LANG_CPPCHECK.html#variable:CMAKE_<LANG>_CPPCHECK):

```shell
cmake -S путь/к/исходникам -B путь/к/сборочной/директории -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_CPPCHECK="cppcheck;--enable=all;-Iпуть/к/исходникам/include"
```

После этого статический анализ будет автоматически запускаться каждый раз во время компиляции и перекомпиляции исходников. Ничего дополнительного делать не нужно.

### Clang

При помощи чудесного инструмента [`scan-build`](https://clang-analyzer.llvm.org/scan-build) тоже можно запускать статический анализ в два счёта:

```shell
scan-build cmake -S путь/к/исходникам -B путь/к/сборочной/директории -DCMAKE_BUILD_TYPE=Debug
scan-build cmake --build путь/к/сборочной/директории
```

Здесь, в отличие от случая с [Cppcheck](#cppcheck), требуется каждый раз запускать сборку через `scan-build`.
