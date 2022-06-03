add_executable(fftpp-example fftpp_example.cpp)
target_link_libraries(fftpp-example
    PRIVATE
        fftpp::library
)

add_custom_target(run-fftpp-example ALL COMMAND fftpp-example)

find_package(Python3 COMPONENTS Interpreter)
if(Python3_FOUND)
    set(WANDBOX_URL "https://wandbox.org/api/compile.json")

    add_custom_target(wandbox
        COMMAND
            Python3::Interpreter wandbox.py fftpp_example.cpp "${PROJECT_SOURCE_DIR}" include |
            curl -H "Content-type: application/json" -d @- ${WANDBOX_URL}
        WORKING_DIRECTORY
            ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS
            fftpp-unit-tests
    )
else()
    message(WARNING "Для создания онлайн-песочницы требуется интерпретатор ЯП python 3-й версии")
endif()
