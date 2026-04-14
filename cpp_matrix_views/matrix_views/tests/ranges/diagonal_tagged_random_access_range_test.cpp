#include <gtest/gtest.h>

#include "ranges/tagged_random_access_range.hpp"
#include "storage/const_callable_storage_proxy.hpp"

namespace tests {

using namespace matrix_views::ranges;
using namespace matrix_views::storage;
using namespace matrix_views::utils;

namespace {

auto kTag = kDiagonal;
auto kEchoIndex = index{};
auto kEchoStorageProxy = const_callable_storage_proxy(
    [](index index) -> index& { return kEchoIndex = index; });

using mock_dynamic_tagged_random_access_range_t =
    tagged_random_access_range<decltype(kTag), decltype(kEchoStorageProxy),
                               std::dynamic_extent, std::dynamic_extent>;

using mock_static_tagged_random_access_range_t =
    tagged_random_access_range<decltype(kTag), decltype(kEchoStorageProxy), 3,
                               4>;

}  // namespace

TEST(diagonal_tagged_random_access_range, enforce_concept) {
  static_assert(std::ranges::random_access_range<
                mock_dynamic_tagged_random_access_range_t>);
  static_assert(std::ranges::random_access_range<
                mock_static_tagged_random_access_range_t>);
}

TEST(diagonal_tagged_random_access_range, default_constructor) {
  mock_static_tagged_random_access_range_t();
}

TEST(diagonal_tagged_random_access_range, constructor) {
  mock_dynamic_tagged_random_access_range_t(kTag, kEchoIndex,
                                            std::move(kEchoStorageProxy), 3, 4);
  mock_static_tagged_random_access_range_t(kTag, kEchoIndex,
                                           std::move(kEchoStorageProxy));
}

TEST(diagonal_tagged_random_access_range, range_methods_dynamic) {
  const auto rng = mock_dynamic_tagged_random_access_range_t(
      kTag, {0, 0}, std::move(kEchoStorageProxy), 3, 4);

  EXPECT_EQ(std::distance(std::begin(rng), std::end(rng)), 3);
  EXPECT_EQ(std::distance(std::rbegin(rng), std::rend(rng)), 3);
  EXPECT_EQ(std::size(rng), 3);
  EXPECT_EQ(std::ssize(rng), 3);
  EXPECT_EQ(std::empty(rng), false);
}

TEST(diagonal_tagged_random_access_range, range_methods_static) {
  const auto rng = mock_static_tagged_random_access_range_t(
      kTag, {0, 0}, std::move(kEchoStorageProxy));

  EXPECT_EQ(std::distance(std::begin(rng), std::end(rng)), 3);
  EXPECT_EQ(std::distance(std::rbegin(rng), std::rend(rng)), 3);
  EXPECT_EQ(std::size(rng), 3);
  EXPECT_EQ(std::ssize(rng), 3);
  EXPECT_EQ(std::empty(rng), false);
}

TEST(diagonal_tagged_random_access_range, begin_end_dynamic) {
  const auto rng = mock_dynamic_tagged_random_access_range_t(
      kTag, {0, 0}, std::move(kEchoStorageProxy), 4, 3);

  EXPECT_EQ(*std::begin(rng), (index{0, 0}));
  EXPECT_EQ(*std::end(rng), (index{3, 3}));
  EXPECT_EQ(*std::rbegin(rng), (index{2, 2}));
  EXPECT_EQ(*std::rend(rng), (index{-1, -1}));
}

TEST(diagonal_tagged_random_access_range, begin_end_static) {
  const auto rng = mock_static_tagged_random_access_range_t(
      kTag, {0, 0}, std::move(kEchoStorageProxy));

  EXPECT_EQ(*std::begin(rng), (index{0, 0}));
  EXPECT_EQ(*std::end(rng), (index{3, 3}));
  EXPECT_EQ(*std::rbegin(rng), (index{2, 2}));
  EXPECT_EQ(*std::rend(rng), (index{-1, -1}));
}

}  // namespace tests
