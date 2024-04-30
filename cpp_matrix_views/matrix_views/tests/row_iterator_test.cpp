#include "row_iterator.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace tests {

using namespace matrix_views;

TEST(rows_range, shape) {
  {
    const std::vector<double> data{1., 2., 3., 4., 5., 6.};
    const auto range =
        rows_range<2, 3, decltype(std::begin(data))>(std::begin(data), 2, 3);

    EXPECT_EQ(std::size(range), 2);
    EXPECT_EQ(std::begin(range) - std::end(range), 2);
    EXPECT_EQ(std::begin(range) + 2, std::end(range));
  }
  {
    const std::vector<double> data{1., 2., 3., 4., 5., 6.};
    const auto range =
        rows_range<std::dynamic_extent, std::dynamic_extent,
                   decltype(std::begin(data))>(std::begin(data), 3, 2);

    EXPECT_EQ(std::size(range), 3);
    EXPECT_EQ(std::begin(range) - std::end(range), 3);
    EXPECT_EQ(std::begin(range) + 3, std::end(range));
  }
}

TEST(rows_range, iterators) {
  {
    const std::vector<double> data{1., 2., 3., 4., 5., 6.};
    const auto range =
        rows_range<std::dynamic_extent, std::dynamic_extent,
                   decltype(std::begin(data))>(std::begin(data), 2, 3);

    static_assert(
        std::is_same_v<decltype(std::begin(range)), decltype(std::end(range))>);
    static_assert(std::is_same_v<decltype(std::cbegin(range)),
                                 decltype(std::cend(range))>);
    static_assert(std::is_same_v<decltype(std::rbegin(range)),
                                 decltype(std::rend(range))>);
    static_assert(std::is_same_v<decltype(std::crbegin(range)),
                                 decltype(std::crend(range))>);

    EXPECT_EQ(std::distance(std::begin(range), std::end(range)), 2);
    EXPECT_EQ(std::distance(std::cbegin(range), std::cend(range)), 2);
    EXPECT_EQ(std::distance(std::rbegin(range), std::rend(range)), 2);
    EXPECT_EQ(std::distance(std::crbegin(range), std::crend(range)), 2);

    using Expected = row_range<std::dynamic_extent, std::dynamic_extent,
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
    auto range = rows_range<std::dynamic_extent, std::dynamic_extent,
                            decltype(std::begin(data))>(std::begin(data), 2, 3);

    static_assert(
        std::is_same_v<decltype(std::begin(range)), decltype(std::end(range))>);
    static_assert(std::is_same_v<decltype(std::cbegin(range)),
                                 decltype(std::cend(range))>);
    static_assert(std::is_same_v<decltype(std::rbegin(range)),
                                 decltype(std::rend(range))>);
    static_assert(std::is_same_v<decltype(std::crbegin(range)),
                                 decltype(std::crend(range))>);

    EXPECT_EQ(std::distance(std::begin(range), std::end(range)), 2);
    EXPECT_EQ(std::distance(std::cbegin(range), std::cend(range)), 2);
    EXPECT_EQ(std::distance(std::rbegin(range), std::rend(range)), 2);
    EXPECT_EQ(std::distance(std::crbegin(range), std::crend(range)), 2);

    using Expected = row_range<std::dynamic_extent, std::dynamic_extent,
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
        rows_range<std::dynamic_extent, std::dynamic_extent,
                   decltype(std::begin(data))>(std::begin(data), 2, 3);

    static_assert(
        std::is_same_v<decltype(std::begin(range)), decltype(std::end(range))>);
    static_assert(std::is_same_v<decltype(std::cbegin(range)),
                                 decltype(std::cend(range))>);
    static_assert(std::is_same_v<decltype(std::rbegin(range)),
                                 decltype(std::rend(range))>);
    static_assert(std::is_same_v<decltype(std::crbegin(range)),
                                 decltype(std::crend(range))>);

    EXPECT_EQ(std::distance(std::begin(range), std::end(range)), 2);
    EXPECT_EQ(std::distance(std::cbegin(range), std::cend(range)), 2);
    EXPECT_EQ(std::distance(std::rbegin(range), std::rend(range)), 2);
    EXPECT_EQ(std::distance(std::crbegin(range), std::crend(range)), 2);

    using Expected = row_range<std::dynamic_extent, std::dynamic_extent,
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
    auto range = rows_range<std::dynamic_extent, std::dynamic_extent,
                            decltype(std::begin(data))>(std::begin(data), 2, 3);

    static_assert(
        std::is_same_v<decltype(std::begin(range)), decltype(std::end(range))>);
    static_assert(std::is_same_v<decltype(std::cbegin(range)),
                                 decltype(std::cend(range))>);
    static_assert(std::is_same_v<decltype(std::rbegin(range)),
                                 decltype(std::rend(range))>);
    static_assert(std::is_same_v<decltype(std::crbegin(range)),
                                 decltype(std::crend(range))>);

    EXPECT_EQ(std::distance(std::begin(range), std::end(range)), 2);
    EXPECT_EQ(std::distance(std::cbegin(range), std::cend(range)), 2);
    EXPECT_EQ(std::distance(std::rbegin(range), std::rend(range)), 2);
    EXPECT_EQ(std::distance(std::crbegin(range), std::crend(range)), 2);

    using Expected = row_range<std::dynamic_extent, std::dynamic_extent,
                               std::vector<double>::iterator>;
    static_assert(std::is_same_v<decltype(std::begin(range)), Expected>);
    static_assert(std::is_same_v<decltype(std::cbegin(range)), Expected>);
    static_assert(std::is_same_v<decltype(std::rbegin(range)),
                                 std::reverse_iterator<Expected>>);
    static_assert(std::is_same_v<decltype(std::crbegin(range)),
                                 std::reverse_iterator<Expected>>);
  }
}

TEST(rows_range, constness) {
  {
    std::vector<double> data{1., 2., 3., 4., 5., 6.};
    auto range = rows_range<std::dynamic_extent, std::dynamic_extent,
                            decltype(std::begin(data))>(std::begin(data), 2, 3);

    static_assert(
        std::is_same_v<decltype(*std::begin(std::begin(range))), double&>);
  }
  {
    const std::vector<double> data{1., 2., 3., 4., 5., 6.};
    auto range = rows_range<std::dynamic_extent, std::dynamic_extent,
                            decltype(std::begin(data))>(std::begin(data), 2, 3);

    static_assert(std::is_same_v<decltype(*std::begin(std::begin(range))),
                                 const double&>);
  }
  {
    std::vector<double> data{1., 2., 3., 4., 5., 6.};
    const auto range =
        rows_range<std::dynamic_extent, std::dynamic_extent,
                   decltype(std::begin(data))>(std::begin(data), 2, 3);

    static_assert(
        std::is_same_v<decltype(*std::begin(*std::begin(range))), double&>);
  }
}

TEST(rows_range, correct_order) {
  {
    const std::vector<int> data{1, 2, 3, 4, 5, 6};
    const auto range =
        rows_range<std::dynamic_extent, std::dynamic_extent,
                   decltype(std::begin(data))>(std::begin(data), 2, 3);

    {
      std::vector<std::vector<int>> rows;
      for (const auto row : range) {
        EXPECT_EQ(std::size(row), 3);

        std::vector<int> output_row;
        for (const auto cell : row) {
          output_row.push_back(cell);
        }
        rows.push_back(std::move(output_row));
      }
      EXPECT_EQ(rows, (std::vector<std::vector<int>>{{1, 2, 3}, {4, 5, 6}}));
    }
    {
      std::vector<std::vector<int>> rows;
      std::transform(std::begin(range), std::end(range),
                     std::back_inserter(rows), [](const auto& row) {
                       return std::vector<int>(std::begin(row), std::end(row));
                     });
      EXPECT_EQ(rows, (std::vector<std::vector<int>>{{1, 2, 3}, {4, 5, 6}}));
    }
  }
}

TEST(rows_range, edit_range) {
  {
    std::vector<double> data{1., 2., 3., 4., 5., 6.};
    const auto range =
        rows_range<std::dynamic_extent, std::dynamic_extent,
                   decltype(std::begin(data))>(std::begin(data), 2, 3);

    *range[0][0] = 98;
    *range[1][2] = 99;

    std::vector<std::vector<int>> rows;
    std::transform(std::begin(range), std::end(range), std::back_inserter(rows),
                   [](const auto& row) {
                     return std::vector<int>(std::begin(row), std::end(row));
                   });
    EXPECT_EQ(rows, (std::vector<std::vector<int>>{{98, 2, 3}, {4, 5, 99}}));
  }
}

}  // namespace tests
