#pragma once

#include <format>
#include <numeric>
#include <ranges>
#include <vector>

#include "antidiagonal_iterator.hpp"
#include "column_iterator.hpp"
#include "concepts.hpp"
#include "diagonal_iterator.hpp"
#include "row_iterator.hpp"
#include "value.hpp"

namespace matrix_views {

struct kRow {};
struct kColumn {};
struct kDiagonal {};
struct kAntidiagonal {};

template <scalar T, std::size_t Rows, std::size_t Columns,
          container Container = std::vector<T>>
class matrix final {
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
   * Constructors for static-size matrix
   */
 public:
  constexpr explicit matrix(T fill = T{})
    requires(kStaticSize)
      : container_(*rows_ * *columns_, fill) {}

  template <std::size_t Size>
  constexpr explicit matrix(const T (&array)[Size], kRow)
    requires(kStaticSize)
      : container_(std::begin(array), std::end(array)) {}

  template <std::size_t Size>
  constexpr explicit matrix(const T (&array)[Size], kColumn)
    requires(kStaticSize)
      : container_(std::begin(array), std::end(array)) {}

  template <std::size_t Size>
  constexpr matrix(const T (&array)[Size], kDiagonal, T fill = T{})
    requires(kStaticSize)
  {
    container_.reserve(Size * Size);

    for (std::size_t row = 0; row < Size; ++row) {
      for (std::size_t column = 0; column < Size; ++column) {
        container_.push_back(row == column ? array[row] : fill);
      }
    }
  }

  template <std::size_t Size>
  constexpr matrix(const T (&array)[Size], kAntidiagonal, T fill = T{})
    requires(kStaticSize)
  {
    container_.reserve(Size * Size);

    for (std::size_t row = 0; row < Size; ++row) {
      for (std::size_t column = 0; column < Size; ++column) {
        container_.push_back(row + column == Size - 1 ? array[row] : fill);
      }
    }
  }

  template <std::size_t ArrayRows, std::size_t ArrayColumns>
  constexpr explicit matrix(const T (&array)[ArrayRows][ArrayColumns])
    requires(kStaticSize)
  {
    container_.reserve(ArrayRows * ArrayColumns);

    for (auto it = std::begin(array); it != std::end(array); ++it) {
      std::ranges::copy(*it, std::back_inserter(container_));
    }
  }

  /*
   * Constructors for mixed-size matrix
   */
 public:
  template <scalar_range R>
  constexpr explicit matrix(R&& range, kRow)
    requires(kMixedSize)
      : columns_(std::ranges::size(range)),
        container_(std::begin(range), std::end(range)) {}

  template <scalar_range R>
  constexpr explicit matrix(R&& range, kColumn)
    requires(kMixedSize)
      : rows_(std::ranges::size(range)),
        container_(std::begin(range), std::end(range)) {}

  template <scalar_range R, std::size_t Size>
  constexpr explicit matrix(const R (&array)[Size], kRow)
    requires(kMixedSize)
      : columns_(std::ranges::size(*std::begin(array))) {
    container_.reserve(Size * *columns_);

    for (auto it = std::begin(array); it != std::end(array); ++it) {
      if (std::ranges::size(*it) != *columns_) {
        throw std::runtime_error(
            std::format("data is expected to be {}by{}", Size, *columns_));
      }

      std::ranges::copy(*it, std::back_inserter(container_));
    }
  }

  template <scalar_range R, std::size_t Size>
  constexpr explicit matrix(const R (&array)[Size], kColumn)
    requires(kMixedSize)
      : rows_(std::ranges::size(*std::begin(array))) {
    container_.reserve(*rows_ * Size);

    for (std::size_t row = 0; row < *rows_; ++row) {
      for (auto it = std::begin(array); it != std::end(array); ++it) {
        if (std::ranges::size(*it) != *rows_) {
          throw std::runtime_error(
              std::format("data is expected to be {}by{}", *rows_, Size));
        }

        container_.push_back((*it)[row]);
      }
    }
  }

  /*
   * Constructors for dynamic-size matrix
   */
 public:
  template <scalar_matrix_range R>
  constexpr explicit matrix(R&& range)
    requires(kDynamicSize)
      : rows_(std::ranges::size(range)),
        columns_(*rows_ == 0 ? 0 : std::ranges::size(*std::begin(range))) {
    container_.reserve(*rows_ * *columns_);

    for (const auto& row : range) {
      if (std::ranges::size(row) != *columns_) {
        throw std::runtime_error(
            std::format("data is expected to be {}by{}", *rows_, *columns_));
      }

      std::ranges::copy(row, std::back_inserter(container_));
    }
  }

  template <scalar_range R>
  constexpr explicit matrix(R&& range, kDiagonal, T fill = T{})
    requires(kDynamicSize)
      : rows_(std::ranges::size(range)), columns_(std::ranges::size(range)) {
    container_.reserve(*rows_ * *columns_);

    auto it = std::begin(range);
    for (std::size_t row = 0; row < *rows_; ++row) {
      for (std::size_t column = 0; column < *columns_; ++column) {
        container_.push_back(row == column ? *it : fill);
      }
      std::advance(it, 1);
    }
  }

  template <scalar_range R>
  constexpr explicit matrix(R&& range, kAntidiagonal, T fill = T{})
    requires(kDynamicSize)
      : rows_(std::ranges::size(range)), columns_(std::ranges::size(range)) {
    container_.reserve(*rows_ * *columns_);

    auto it = std::begin(range);
    for (std::size_t row = 0; row < *rows_; ++row) {
      for (std::size_t column = 0; column < *columns_; ++column) {
        container_.push_back(row + column == *rows_ ? *it : fill);
      }
      std::advance(it, 1);
    }
  }

  /*
   * Utility access methods
   */
 public:
  constexpr auto rows() const noexcept {
    return rows_range<Rows, Columns, decltype(std::begin(container_))>(
        std::begin(container_), *rows_, *columns_);
  }

  constexpr auto columns() const noexcept {
    return columns_range<Rows, Columns, decltype(std::begin(container_))>(
        std::begin(container_), *rows_, *columns_);
  }

  constexpr auto diagonals() const noexcept {
    return diagonals_range<Rows, Columns, decltype(std::begin(container_))>(
        std::begin(container_), *rows_, *columns_);
  }

  constexpr auto antidiagonals() const noexcept {
    return antidiagonals_range<Rows, Columns, decltype(std::begin(container_))>(
        std::begin(container_), *rows_, *columns_);
  }

  constexpr auto row(std::size_t number) const noexcept {
    return row_range<Rows, Columns, decltype(std::begin(container_))>(
        std::begin(container_), number, *rows_, *columns_);
  }

  constexpr auto column(std::size_t number) const noexcept {
    return column_range<Rows, Columns, decltype(std::begin(container_))>(
        std::begin(container_), number, *rows_, *columns_);
  }

  constexpr auto diagonal(std::size_t number) const noexcept {
    return diagonal_range<Rows, Columns, decltype(std::begin(container_))>(
        std::begin(container_), number, *rows_, *columns_);
  }

  constexpr auto antidiagonal(std::size_t number) const noexcept {
    return antidiagonal_range<Rows, Columns, decltype(std::begin(container_))>(
        std::begin(container_), number, *rows_, *columns_);
  }

  /*
   * Informational methods
   */
 public:
  constexpr std::pair<std::size_t, std::size_t> shape() const noexcept {
    return {*rows_, *columns_};
  }

  /*
   * Class layout
   */
 private:
  [[no_unique_address]] value<std::size_t, std::dynamic_extent, Rows> rows_;
  [[no_unique_address]] value<std::size_t, std::dynamic_extent, Columns>
      columns_;
  Container container_;
};

/*
 * Deduction guides for static-size matrix
 */
template <scalar T, std::size_t Size>
matrix(const T (&)[Size], kRow) -> matrix<T, 1, Size>;

template <scalar T, std::size_t Size>
matrix(const T (&)[Size], kColumn) -> matrix<T, Size, 1>;

template <scalar T, std::size_t Size>
matrix(const T (&)[Size], kDiagonal, T fill = T{}) -> matrix<T, Size, Size>;

template <scalar T, std::size_t Size>
matrix(const T (&)[Size], kAntidiagonal, T fill = T{}) -> matrix<T, Size, Size>;

template <scalar T, std::size_t Rows, std::size_t Columns>
matrix(const T (&)[Rows][Columns]) -> matrix<T, Rows, Columns>;

/*
 * Deduction guides for mixed-size matrix
 */
template <scalar_range R, std::size_t Size,
          scalar T = std::ranges::range_value_t<R>>
matrix(const R (&)[Size], kRow) -> matrix<T, Size, std::dynamic_extent>;

template <scalar_range R, std::size_t Size,
          scalar T = std::ranges::range_value_t<R>>
matrix(const R (&)[Size], kColumn) -> matrix<T, std::dynamic_extent, Size>;

template <scalar_range R, scalar T = std::ranges::range_value_t<R>>
matrix(R&&, kRow) -> matrix<T, 1, std::dynamic_extent>;

template <scalar_range R, scalar T = std::ranges::range_value_t<R>>
matrix(R&&, kColumn) -> matrix<T, std::dynamic_extent, 1>;

/*
 * Deduction guides for dynamic-size matrix
 */
template <scalar_matrix_range R,
          scalar T = std::ranges::range_value_t<std::ranges::range_value_t<R>>>
matrix(R&&) -> matrix<T, std::dynamic_extent, std::dynamic_extent>;

template <scalar_range R, scalar T = std::ranges::range_value_t<R>>
matrix(R&&, kDiagonal, T fill = T{})
    -> matrix<T, std::dynamic_extent, std::dynamic_extent>;

template <scalar_range R, scalar T = std::ranges::range_value_t<R>>
matrix(R&&, kAntidiagonal, T fill = T{})
    -> matrix<T, std::dynamic_extent, std::dynamic_extent>;

}  // namespace matrix_views
