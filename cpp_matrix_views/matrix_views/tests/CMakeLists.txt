find_package(GTest REQUIRED)

set(TARGET thelibtests)
set(SOURCES
    antidiagonal_iterator_test.cpp
    column_iterator_test.cpp
    diagonal_iterator_test.cpp
    matrix_test.cpp
    row_iterator_test.cpp
    value_test.cpp)
set(CXXOPTIONS -Wall -Wextra -pedantic -Werror -O3 -std=c++20)

add_executable(${TARGET})
target_sources(${TARGET}
    PRIVATE ${SOURCES})
target_compile_options(${TARGET}
    PRIVATE ${CXXOPTIONS})
target_link_libraries(${TARGET}
    PRIVATE matrix_views
    PUBLIC GTest::gtest_main)

gtest_discover_tests(${TARGET})
