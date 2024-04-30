#include "matrix.hpp"

#include <gtest/gtest.h>

#include <array>
#include <string>
#include <vector>

namespace tests {

using namespace matrix_views;

TEST(matrix, static_constructors_deduction_guides) {
  {
    using Result = decltype(matrix<int, 1, 3>());
    using Expected = matrix<int, 1, 3>;
    static_assert(std::is_same_v<Result, Expected>);
  }
  {
    using Result = decltype(matrix({1.f, 2.f, 3.f}, kRow{}));
    using Expected = matrix<float, 1, 3>;
    static_assert(std::is_same_v<Result, Expected>);
  }
  {
    using Result = decltype(matrix({1.f, 2.f, 3.f}, kColumn{}));
    using Expected = matrix<float, 3, 1>;
    static_assert(std::is_same_v<Result, Expected>);
  }
  {
    using Result = decltype(matrix({1.f, 2.f, 3.f}, kDiagonal{}));
    using Expected = matrix<float, 3, 3>;
    static_assert(std::is_same_v<Result, Expected>);
  }
  {
    using Result = decltype(matrix({1.f, 2.f, 3.f}, kAntidiagonal{}));
    using Expected = matrix<float, 3, 3>;
    static_assert(std::is_same_v<Result, Expected>);
  }
  {
    using Result = decltype(matrix({{1., 2., 3.}, {4., 5., 6.}}));
    using Expected = matrix<double, 2, 3>;
    static_assert(std::is_same_v<Result, Expected>);
  }
}

TEST(matrix, mixed_constructors_deduction_guides) {
  {
    const auto data = std::string{"abcdef"};

    using Result = decltype(matrix(data, kRow{}));
    using Expected = matrix<char, 1, std::dynamic_extent>;
    static_assert(std::is_same_v<Result, Expected>);
  }
  {
    const auto data = std::vector<float>{1, 2, 3, 4, 5};

    using Result = decltype(matrix(data, kRow{}));
    using Expected = matrix<float, 1, std::dynamic_extent>;
    static_assert(std::is_same_v<Result, Expected>);
  }
  {
    const auto data = std::array{1, 2, 3};

    using Result = decltype(matrix(data, kColumn{}));
    using Expected = matrix<int, std::dynamic_extent, 1>;
    static_assert(std::is_same_v<Result, Expected>);
  }
  {
    const std::string data[2] = {std::string{"abc"}, std::string{"def"}};

    using Result = decltype(matrix(data, kRow{}));
    using Expected = matrix<char, 2, std::dynamic_extent>;
    static_assert(std::is_same_v<Result, Expected>);
  }
  {
    const std::vector<int> data[2] = {{1, 2}, {3, 4}};

    using Result = decltype(matrix(data, kColumn{}));
    using Expected = matrix<int, std::dynamic_extent, 2>;
    static_assert(std::is_same_v<Result, Expected>);
  }
  {
    const auto data = std::vector<float>{1, 2, 3, 4, 5};

    using Result = decltype(matrix(data, kDiagonal{}));
    using Expected = matrix<float, std::dynamic_extent, std::dynamic_extent>;
    static_assert(std::is_same_v<Result, Expected>);
  }
  {
    const auto data = std::vector<float>{1, 2, 3, 4, 5};

    using Result = decltype(matrix(data, kAntidiagonal{}));
    using Expected = matrix<float, std::dynamic_extent, std::dynamic_extent>;
    static_assert(std::is_same_v<Result, Expected>);
  }
}

TEST(matrix, dynamic_constructors_deduction_guides) {
  {
    const auto data = std::vector<std::vector<float>>{{1, 2, 3}, {3, 4, 5}};

    using Result = decltype(matrix(data));
    using Expected = matrix<float, std::dynamic_extent, std::dynamic_extent>;
    static_assert(std::is_same_v<Result, Expected>);
  }
  {
    const auto data = std::array{std::array{1, 2, 3}, std::array{3, 4, 5}};

    using Result = decltype(matrix(data));
    using Expected = matrix<int, std::dynamic_extent, std::dynamic_extent>;
    static_assert(std::is_same_v<Result, Expected>);
  }
}

TEST(matrix, shape) {
  { EXPECT_EQ((matrix<int, 1, 1>().shape()), (std::pair{1, 1})); }
  {
    const int data[2][1] = {{1}, {2}};

    EXPECT_EQ((matrix(data).shape()), (std::pair{2, 1}));
  }
  {
    const int data[3] = {1, 2, 3};

    EXPECT_EQ((matrix(data, kRow{}).shape()), (std::pair{1, 3}));
    EXPECT_EQ((matrix(data, kColumn{}).shape()), (std::pair{3, 1}));
    EXPECT_EQ((matrix(data, kDiagonal{}).shape()), (std::pair{3, 3}));
    EXPECT_EQ((matrix(data, kAntidiagonal{}).shape()), (std::pair{3, 3}));
  }
  {
    const std::vector<int> data[3] = {{1}, {2}, {3}};

    EXPECT_EQ((matrix(data, kRow{}).shape()), (std::pair{3, 1}));
    EXPECT_EQ((matrix(data, kColumn{}).shape()), (std::pair{1, 3}));
  }
  {
    const std::vector<int> data = {1, 2};

    EXPECT_EQ((matrix(data, kRow{}).shape()), (std::pair{1, 2}));
    EXPECT_EQ((matrix(data, kColumn{}).shape()), (std::pair{2, 1}));
    EXPECT_EQ((matrix(data, kDiagonal{}).shape()), (std::pair{2, 2}));
    EXPECT_EQ((matrix(data, kAntidiagonal{}).shape()), (std::pair{2, 2}));
  }
  {
    const std::vector<std::vector<int>> data = {{1, 2}, {3, 4}};

    EXPECT_EQ((matrix(data).shape()), (std::pair{2, 2}));
  }
}

TEST(matrix, object_size) {
  {
    const int static_data[1][1] = {{1}};
    const std::vector<int> mixed_data = {1};
    const std::vector<std::vector<int>> dynamic_data = {{1}};

    static_assert(sizeof(matrix(static_data)) <
                  sizeof(matrix(mixed_data, kRow{})));
    static_assert(sizeof(matrix(mixed_data, kRow{})) ==
                  sizeof(matrix(mixed_data, kColumn{})));
    static_assert(sizeof(matrix(mixed_data, kRow{})) <
                  sizeof(matrix(dynamic_data)));
  }
}

TEST(matrix, iterators) {
  {
    const std::vector<std::vector<int>> data{
        {1, 2, 3, 4}, {5, 6, 7, 8}, {10, 11, 12, 13}};

    const auto m = matrix(data);

    EXPECT_EQ((std::vector(std::begin(m.rows()[0]), std::end(m.rows()[0]))),
              (std::vector(std::begin(m.row(0)), std::end(m.row(0)))));
    EXPECT_EQ((std::vector(std::begin(m.row(0)), std::end(m.row(0)))),
              (std::vector<int>{1, 2, 3, 4}));

    EXPECT_EQ(
        (std::vector(std::begin(m.columns()[0]), std::end(m.columns()[0]))),
        (std::vector(std::begin(m.column(0)), std::end(m.column(0)))));
    EXPECT_EQ((std::vector(std::begin(m.column(0)), std::end(m.column(0)))),
              (std::vector<int>{1, 5, 10}));

    EXPECT_EQ(
        (std::vector(std::begin(m.diagonals()[2]), std::end(m.diagonals()[2]))),
        (std::vector(std::begin(m.diagonal(2)), std::end(m.diagonal(2)))));
    EXPECT_EQ((std::vector(std::begin(m.diagonal(2)), std::end(m.diagonal(2)))),
              (std::vector<int>{1, 6, 12}));

    EXPECT_EQ((std::vector(std::begin(m.antidiagonals()[2]),
                           std::end(m.antidiagonals()[2]))),
              (std::vector(std::begin(m.antidiagonal(2)),
                           std::end(m.antidiagonal(2)))));
    EXPECT_EQ((std::vector(std::begin(m.antidiagonal(2)),
                           std::end(m.antidiagonal(2)))),
              (std::vector<int>{3, 6, 10}));
  }
}

}  // namespace tests
