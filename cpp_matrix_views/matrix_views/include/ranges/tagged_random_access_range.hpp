#pragma once

#include <span>

#include "iterators/tagged_random_access_iterator.hpp"
#include "ranges/base_random_access_range.hpp"
#include "utils/conditionally_runtime.hpp"
#include "utils/tags.hpp"

namespace matrix_views::ranges {

/*
 * Concept representing the set of valid tags for tagged_random_access_range
 */
template <typename Tag>
concept tagged_random_access_range_tag =
    std::same_as<Tag, utils::kRowTag> || std::same_as<Tag, utils::kColumnTag> ||
    std::same_as<Tag, utils::kDiagonalTag> ||
    std::same_as<Tag, utils::kAntidiagonalTag>;

/*
 * Concept representing a callable that implements the storage access
 */
template <typename StorageProxy>
concept tagged_random_access_range_storage_proxy =
    std::invocable<const StorageProxy, utils::index>;

/*
 * Tagged range class with a set direction. Implements begin/end. Optionally
 * stores matrix dimensions in the type
 */
template <tagged_random_access_range_tag Tag,
          tagged_random_access_range_storage_proxy StorageProxy,
          std::size_t Rows = std::dynamic_extent,
          std::size_t Columns = std::dynamic_extent>
class tagged_random_access_range final
    : public base_random_access_range<
          tagged_random_access_range<Tag, StorageProxy, Rows, Columns>>,
      public StorageProxy {
 private:
  static inline const constinit bool kDynamicRows = Rows == std::dynamic_extent;
  static inline const constinit bool kDynamicColumns =
      Columns == std::dynamic_extent;

 private:
  static inline const constinit bool kRowTag =
      std::is_same_v<Tag, utils::kRowTag>;
  static inline const constinit bool kColumnTag =
      std::is_same_v<Tag, utils::kColumnTag>;
  static inline const constinit bool kDiagonalTag =
      std::is_same_v<Tag, utils::kDiagonalTag>;
  static inline const constinit bool kAntidiagonalTag =
      std::is_same_v<Tag, utils::kAntidiagonalTag>;

 public:
  constexpr tagged_random_access_range() noexcept = default;
  constexpr tagged_random_access_range(
      Tag, utils::index index, StorageProxy storage_proxy,
      std::size_t rows = std::dynamic_extent,
      std::size_t columns = std::dynamic_extent) noexcept
      : base_random_access_range<tagged_random_access_range>(),
        StorageProxy(std::move(storage_proxy)),
        index_(index),
        rows_(utils::runtime_if<kDynamicRows>(rows)),
        columns_(utils::runtime_if<kDynamicColumns>(columns)) {}

 public:
  constexpr decltype(auto) begin() const noexcept {
    return iterators::tagged_random_access_iterator(
        Tag{}, index_, static_cast<StorageProxy>(*this));
  }

  constexpr decltype(auto) end() const noexcept {
    if constexpr (kRowTag) {
      return begin() + (*columns_ - index_.row);
    } else if constexpr (kColumnTag) {
      return begin() + (*rows_ - index_.column);
    } else if constexpr (kDiagonalTag) {
      return begin() + std::min(*rows_ - index_.row, *columns_ - index_.column);
    } else {
      static_assert(kAntidiagonalTag);
      return begin() +
             std::min(static_cast<std::ptrdiff_t>(*rows_) - index_.row,
                      index_.column + 1);
    }
  }

 private:
  utils::index index_;

  [[no_unique_address]] utils::conditionally_runtime<std::size_t, kDynamicRows,
                                                     Rows> rows_;
  [[no_unique_address]] utils::conditionally_runtime<
      std::size_t, kDynamicColumns, Columns> columns_;
};

}  // namespace matrix_views::ranges
