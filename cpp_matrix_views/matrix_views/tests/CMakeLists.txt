find_package(GTest REQUIRED)

set(TARGET thelibtests)
set(SOURCES
    iterators/antidiagonal_tagged_random_access_iterator_test.cpp
    iterators/column_tagged_random_access_iterator_test.cpp
    iterators/diagonal_tagged_random_access_iterator_test.cpp
    iterators/row_tagged_random_access_iterator_test.cpp
    ranges/row_tagged_random_access_range_test.cpp
    ranges/column_tagged_random_access_range_test.cpp
    ranges/diagonal_tagged_random_access_range_test.cpp
    ranges/antidiagonal_tagged_random_access_range_test.cpp
    utils/conditionally_runtime_test.cpp
)
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
