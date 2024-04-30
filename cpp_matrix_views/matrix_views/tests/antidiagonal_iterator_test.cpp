#include "antidiagonal_iterator.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace tests {

using namespace matrix_views;

TEST(antidiagonals_range, shape) {
  {
    const std::vector<double> data{1., 2., 3., 4., 5., 6.};
    const auto range = antidiagonals_range<2, 3, decltype(std::begin(data))>(
        std::begin(data), 2, 3);

    EXPECT_EQ(std::size(range), 4);
    EXPECT_EQ(std::begin(range) - std::end(range), 4);
    EXPECT_EQ(std::begin(range) + 4, std::end(range));
  }
  {
    const std::vector<double> data{1., 2., 3., 4., 5., 6.};
    const auto range =
        antidiagonals_range<std::dynamic_extent, std::dynamic_extent,
                            decltype(std::begin(data))>(std::begin(data), 3, 2);

    EXPECT_EQ(std::size(range), 4);
    EXPECT_EQ(std::begin(range) - std::end(range), 4);
    EXPECT_EQ(std::begin(range) + 4, std::end(range));
  }
}

TEST(antidiagonals_range, iterators) {
  {
    const std::vector<double> data{1., 2., 3., 4., 5., 6.};
    const auto range =
        antidiagonals_range<std::dynamic_extent, std::dynamic_extent,
                            decltype(std::begin(data))>(std::begin(data), 2, 3);

    static_assert(
        std::is_same_v<decltype(std::begin(range)), decltype(std::end(range))>);
    static_assert(std::is_same_v<decltype(std::cbegin(range)),
                                 decltype(std::cend(range))>);
    static_assert(std::is_same_v<decltype(std::rbegin(range)),
                                 decltype(std::rend(range))>);
    static_assert(std::is_same_v<decltype(std::crbegin(range)),
                                 decltype(std::crend(range))>);

    EXPECT_EQ(std::distance(std::begin(range), std::end(range)), 4);
    EXPECT_EQ(std::distance(std::cbegin(range), std::cend(range)), 4);
    EXPECT_EQ(std::distance(std::rbegin(range), std::rend(range)), 4);
    EXPECT_EQ(std::distance(std::crbegin(range), std::crend(range)), 4);

    using Expected =
        antidiagonal_range<std::dynamic_extent, std::dynamic_extent,
                           std::vector<double>::const_iterator>;
    static_assert(std::is_same_v<decltype(std::begin(range)), Expected>);
    static_assert(std::is_same_v<decltype(std::cbegin(range)), Expected>);
    static_assert(std::is_same_v<decltype(std::rbegin(range)),
                                 std::reverse_iterator<Expected>>);
    static_assert(std::is_same_v<decltype(std::crbegin(range)),
                                 std::reverse_iterator<Expected>>);
  }
  {
    const std::vector<double> data{1., 2., 3., 4., 5., 6.};
    auto range =
        antidiagonals_range<std::dynamic_extent, std::dynamic_extent,
                            decltype(std::begin(data))>(std::begin(data), 2, 3);

    static_assert(
        std::is_same_v<decltype(std::begin(range)), decltype(std::end(range))>);
    static_assert(std::is_same_v<decltype(std::cbegin(range)),
                                 decltype(std::cend(range))>);
    static_assert(std::is_same_v<decltype(std::rbegin(range)),
                                 decltype(std::rend(range))>);
    static_assert(std::is_same_v<decltype(std::crbegin(range)),
                                 decltype(std::crend(range))>);

    EXPECT_EQ(std::distance(std::begin(range), std::end(range)), 4);
    EXPECT_EQ(std::distance(std::cbegin(range), std::cend(range)), 4);
    EXPECT_EQ(std::distance(std::rbegin(range), std::rend(range)), 4);
    EXPECT_EQ(std::distance(std::crbegin(range), std::crend(range)), 4);

    using Expected =
        antidiagonal_range<std::dynamic_extent, std::dynamic_extent,
                           std::vector<double>::const_iterator>;
    static_assert(std::is_same_v<decltype(std::begin(range)), Expected>);
    static_assert(std::is_same_v<decltype(std::cbegin(range)), Expected>);
    static_assert(std::is_same_v<decltype(std::rbegin(range)),
                                 std::reverse_iterator<Expected>>);
    static_assert(std::is_same_v<decltype(std::crbegin(range)),
                                 std::reverse_iterator<Expected>>);
  }
  {
    std::vector<double> data{1., 2., 3., 4., 5., 6.};
    const auto range =
        antidiagonals_range<std::dynamic_extent, std::dynamic_extent,
                            decltype(std::begin(data))>(std::begin(data), 2, 3);

    static_assert(
        std::is_same_v<decltype(std::begin(range)), decltype(std::end(range))>);
    static_assert(std::is_same_v<decltype(std::cbegin(range)),
                                 decltype(std::cend(range))>);
    static_assert(std::is_same_v<decltype(std::rbegin(range)),
                                 decltype(std::rend(range))>);
    static_assert(std::is_same_v<decltype(std::crbegin(range)),
                                 decltype(std::crend(range))>);

    EXPECT_EQ(std::distance(std::begin(range), std::end(range)), 4);
    EXPECT_EQ(std::distance(std::cbegin(range), std::cend(range)), 4);
    EXPECT_EQ(std::distance(std::rbegin(range), std::rend(range)), 4);
    EXPECT_EQ(std::distance(std::crbegin(range), std::crend(range)), 4);

    using Expected =
        antidiagonal_range<std::dynamic_extent, std::dynamic_extent,
                           std::vector<double>::iterator>;
    static_assert(std::is_same_v<decltype(std::begin(range)), Expected>);
    static_assert(std::is_same_v<decltype(std::cbegin(range)), Expected>);
    static_assert(std::is_same_v<decltype(std::rbegin(range)),
                                 std::reverse_iterator<Expected>>);
    static_assert(std::is_same_v<decltype(std::crbegin(range)),
                                 std::reverse_iterator<Expected>>);
  }
  {
    std::vector<double> data{1., 2., 3., 4., 5., 6.};
    auto range =
        antidiagonals_range<std::dynamic_extent, std::dynamic_extent,
                            decltype(std::begin(data))>(std::begin(data), 2, 3);

    static_assert(
        std::is_same_v<decltype(std::begin(range)), decltype(std::end(range))>);
    static_assert(std::is_same_v<decltype(std::cbegin(range)),
                                 decltype(std::cend(range))>);
    static_assert(std::is_same_v<decltype(std::rbegin(range)),
                                 decltype(std::rend(range))>);
    static_assert(std::is_same_v<decltype(std::crbegin(range)),
                                 decltype(std::crend(range))>);

    EXPECT_EQ(std::distance(std::begin(range), std::end(range)), 4);
    EXPECT_EQ(std::distance(std::cbegin(range), std::cend(range)), 4);
    EXPECT_EQ(std::distance(std::rbegin(range), std::rend(range)), 4);
    EXPECT_EQ(std::distance(std::crbegin(range), std::crend(range)), 4);

    using Expected =
        antidiagonal_range<std::dynamic_extent, std::dynamic_extent,
                           std::vector<double>::iterator>;
    static_assert(std::is_same_v<decltype(std::begin(range)), Expected>);
    static_assert(std::is_same_v<decltype(std::cbegin(range)), Expected>);
    static_assert(std::is_same_v<decltype(std::rbegin(range)),
                                 std::reverse_iterator<Expected>>);
    static_assert(std::is_same_v<decltype(std::crbegin(range)),
                                 std::reverse_iterator<Expected>>);
  }
}

TEST(antidiagonals_range, constness) {
  {
    std::vector<double> data{1., 2., 3., 4., 5., 6.};
    auto range =
        antidiagonals_range<std::dynamic_extent, std::dynamic_extent,
                            decltype(std::begin(data))>(std::begin(data), 2, 3);

    static_assert(
        std::is_same_v<decltype(*std::begin(std::begin(range))), double&>);
  }
  {
    const std::vector<double> data{1., 2., 3., 4., 5., 6.};
    auto range =
        antidiagonals_range<std::dynamic_extent, std::dynamic_extent,
                            decltype(std::begin(data))>(std::begin(data), 2, 3);

    static_assert(std::is_same_v<decltype(*std::begin(std::begin(range))),
                                 const double&>);
  }
  {
    std::vector<double> data{1., 2., 3., 4., 5., 6.};
    const auto range =
        antidiagonals_range<std::dynamic_extent, std::dynamic_extent,
                            decltype(std::begin(data))>(std::begin(data), 2, 3);

    static_assert(
        std::is_same_v<decltype(*std::begin(*std::begin(range))), double&>);
  }
}

TEST(antidiagonals_range, correct_order) {
  {
    const std::vector<int> data{1, 2, 3, 4, 5, 6};
    const auto range =
        antidiagonals_range<std::dynamic_extent, std::dynamic_extent,
                            decltype(std::begin(data))>(std::begin(data), 2, 3);

    {
      std::vector<std::vector<int>> diagonals;
      std::vector<std::size_t> sizes;
      for (const auto diagonal : range) {
        sizes.push_back(std::size(diagonal));

        std::vector<int> output_diagonal;
        for (const auto cell : diagonal) {
          output_diagonal.push_back(cell);
        }
        diagonals.push_back(std::move(output_diagonal));
      }
      EXPECT_EQ(diagonals,
                (std::vector<std::vector<int>>{{1}, {2, 4}, {3, 5}, {6}}));
      EXPECT_EQ(sizes, (std::vector<std::size_t>{1, 2, 2, 1}));
    }
    {
      std::vector<std::vector<int>> rows;
      std::transform(std::begin(range), std::end(range),
                     std::back_inserter(rows), [](const auto& row) {
                       return std::vector<int>(std::begin(row), std::end(row));
                     });
      EXPECT_EQ(rows,
                (std::vector<std::vector<int>>{{1}, {2, 4}, {3, 5}, {6}}));
    }
  }
}

TEST(antidiagonals_range, edit_range) {
  {
    std::vector<double> data{1., 2., 3., 4., 5., 6., 7., 8., 9.};
    const auto range =
        antidiagonals_range<std::dynamic_extent, std::dynamic_extent,
                            decltype(std::begin(data))>(std::begin(data), 3, 3);

    *range[0][0] = 98;
    *range[2][2] = 99;

    std::vector<std::vector<int>> rows;
    std::transform(std::begin(range), std::end(range), std::back_inserter(rows),
                   [](const auto& row) {
                     return std::vector<int>(std::begin(row), std::end(row));
                   });
    EXPECT_EQ(rows, (std::vector<std::vector<int>>{
                        {98}, {2, 4}, {3, 5, 99}, {6, 8}, {9}}));
  }
}

}  // namespace tests
