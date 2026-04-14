#include "utils/conditionally_runtime.hpp"

#include <gtest/gtest.h>

#include <span>

namespace tests {

using namespace matrix_views::utils;

TEST(conditionally_runtime, compile_time_sizeof) {
  conditionally_runtime<std::size_t, false, 0> v;
  static_assert(sizeof(v) == sizeof(kCompileTime));
}

TEST(conditionally_runtime, compile_time_special_constructor) {
  [[maybe_unused]] conditionally_runtime<std::size_t, false, 0> v(kCompileTime);
}

TEST(conditionally_runtime, compile_time_star_operator) {
  conditionally_runtime<int, false, 1> v;
  static_assert(std::is_same_v<decltype(*v), const int&>);
  EXPECT_EQ(*v, 1);
}

TEST(conditionally_runtime, runtime_sizeof) {
  conditionally_runtime<std::size_t, true> v(2);
  static_assert(sizeof(v) == sizeof(std::size_t));
  EXPECT_EQ(*v, 2);
}

TEST(conditionally_runtime, runtime_star_operator) {
  conditionally_runtime<int, true> v(3);
  static_assert(std::is_same_v<decltype(*v), int&>);
  EXPECT_EQ(*v, 3);
}

TEST(conditionally_runtime, runtime_const_star_operator) {
  const conditionally_runtime<int, true> v(3);
  static_assert(std::is_same_v<decltype(*v), const int&>);
  EXPECT_EQ(*v, 3);
}

TEST(conditionally_runtime, runtime_assignment) {
  conditionally_runtime<int, true> v(4);
  EXPECT_EQ(*v, 4);
  *v = 5;
  EXPECT_EQ(*v, 5);
}

TEST(conditionally_runtime, runtime_copy_assignment) {
  conditionally_runtime<int, true> v1(4);
  conditionally_runtime<int, true> v2(5);
  EXPECT_EQ(*v1, 4);
  v1 = v2;

  EXPECT_EQ(*v1, 5);
}

TEST(conditionally_runtime, runtime_if) {
  EXPECT_EQ(runtime_if<true>(6), 6);
  static_assert(std::is_same_v<decltype(runtime_if<false>(7)),
                               std::decay_t<decltype(kCompileTime)>>);
}

}  // namespace tests