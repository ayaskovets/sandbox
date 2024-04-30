#pragma once

#include "concepts.hpp"
#include "value.hpp"

namespace matrix_views {

template <std::size_t Rows, std::size_t Columns, iterator Iterator>
class base_iterator {
  /*
   * Utility class-wide constants
   */
 protected:
  constexpr static inline bool kDynamicRows = Rows == std::dynamic_extent;
  constexpr static inline bool kDynamicColumns = Columns == std::dynamic_extent;
  constexpr static inline bool kStaticSize = !kDynamicRows && !kDynamicColumns;
  constexpr static inline bool kDynamicSize = kDynamicRows && kDynamicColumns;
  constexpr static inline bool kMixedSize = !kDynamicSize && !kStaticSize;

  /*
   * Disabled interface
   */
 public:
  constexpr base_iterator() = delete;

  /*
   * Inherited constructor
   */
 protected:
  constexpr base_iterator(Iterator it, std::size_t row, std::size_t column,
                          std::size_t rows, std::size_t columns) noexcept
      : row_(row),
        column_(column),
        rows_(_value_if<kDynamicRows>(rows)),
        columns_(_value_if<kDynamicColumns>(columns)),
        it_(it) {}

  /*
   * Common methods
   */
 public:
  constexpr bool operator==(const base_iterator& that) const noexcept {
    return this->row_ == that.row_ && this->column_ == that.column_ &&
           this->it_ == that.it_;
  }

  constexpr bool operator!=(const base_iterator& that) const noexcept {
    return !operator==(that);
  }

  /*
   * Class layout
   */
 protected:
  std::size_t row_;
  std::size_t column_;

  [[no_unique_address]] value<std::size_t, std::dynamic_extent, Rows> rows_;
  [[no_unique_address]] value<std::size_t, std::dynamic_extent, Columns>
      columns_;

  Iterator it_;
};

}  // namespace matrix_views
