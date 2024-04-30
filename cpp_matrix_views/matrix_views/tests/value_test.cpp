#include "value.hpp"

#include <gtest/gtest.h>

#include <span>

namespace tests {

using namespace matrix_views;

TEST(value, compile_time) {
  class Empty {};

  {
    const auto v = value<std::size_t, std::dynamic_extent, 1>();
    static_assert(sizeof(v) == sizeof(Empty));
    EXPECT_EQ(*v, 1);
    EXPECT_EQ(*v + 3, 4);
  }
  {
    auto v = value<std::size_t, std::dynamic_extent, 1>();
    static_assert(sizeof(v) == sizeof(Empty));
    EXPECT_EQ(*v, 1);
    EXPECT_EQ(*v + 3, 4);
  }
  {
    const auto v =
        value<std::size_t, std::dynamic_extent, 1>(kCompileTimeValue{});
    EXPECT_EQ(*v, 1);
  }
}

TEST(value, run_time) {
  {
    const auto v = value<std::size_t, std::dynamic_extent>(1);
    static_assert(sizeof(v) == sizeof(std::size_t));
    EXPECT_EQ(*v, 1);
    EXPECT_EQ(*v + 3, 4);
  }
  {
    auto v = value<std::size_t, std::dynamic_extent>(1);
    static_assert(sizeof(v) == sizeof(std::size_t));
    *v += 2;
    EXPECT_EQ(*v, 3);
  }
  {
    auto v = value<std::size_t, std::dynamic_extent>(1);
    static_assert(sizeof(v) == sizeof(std::size_t));
    v = value<std::size_t, std::dynamic_extent>(2);
    EXPECT_EQ(*v, 2);
  }
}

}  // namespace tests