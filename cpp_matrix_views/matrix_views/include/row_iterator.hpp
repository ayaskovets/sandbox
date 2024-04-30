#pragma once

#include <format>

#include "base_iterator.hpp"

namespace matrix_views {

template <std::size_t Rows, std::size_t Columns, iterator Iterator>
class row_iterator final : public base_iterator<Rows, Columns, Iterator> {
  /*
   * Constructors
   */
 public:
  constexpr row_iterator(Iterator it, std::size_t row, std::size_t column,
                         std::size_t rows, std::size_t columns) noexcept
      : base_iterator<Rows, Columns, Iterator>(it, row, column, rows, columns) {
  }

  /*
   * std::random_access_iterator implementation
   */
 public:
  using value_type = Iterator::value_type;
  using pointer = Iterator::pointer;
  using reference = Iterator::reference;
  using difference_type = std::size_t;
  using iterator_category = std::random_access_iterator_tag;

  constexpr row_iterator& operator++() noexcept { return this->operator+=(1); }
  constexpr row_iterator& operator--() noexcept { return this->operator-=(1); }

  constexpr row_iterator operator++(int) noexcept {
    const auto copy = *this;
    this->operator++();
    return copy;
  }

  constexpr row_iterator operator--(int) noexcept {
    const auto copy = *this;
    this->operator--();
    return copy;
  }

  constexpr row_iterator& operator+=(difference_type n) noexcept {
    return this->column_ += n, *this;
  }
  constexpr row_iterator& operator-=(difference_type n) noexcept {
    return this->column_ -= n, *this;
  }

  constexpr row_iterator operator+(difference_type n) const noexcept {
    return row_iterator(this->it_, this->row_, this->column_ + n, *this->rows_,
                        *this->columns_);
  }
  constexpr row_iterator operator-(difference_type n) const noexcept {
    return row_iterator(this->it_, this->row_, this->column_ - n, *this->rows_,
                        *this->columns_);
  }

  constexpr difference_type operator-(const row_iterator& that) const noexcept {
    return this->column_ > that.column_ ? this->column_ - that.column_
                                        : that.column_ - this->column_;
  }

  constexpr auto& operator[](difference_type n) const {
    return *std::next(this->it_,
                      this->row_ * *this->columns_ + this->column_ + n);
  }
  constexpr auto& operator*() const { return this->operator[](0); }
};

template <std::size_t Rows, std::size_t Columns, iterator Iterator>
class row_range final : public base_iterator<Rows, Columns, Iterator> {
  /*
   * Constructors
   */
 public:
  constexpr row_range(Iterator it, std::size_t row, std::size_t rows,
                      std::size_t columns) noexcept
      : base_iterator<Rows, Columns, Iterator>(it, row, 0, rows, columns) {}

  /*
   * std::random_access_iterator implementation
   */
 public:
  using value_type = row_iterator<Rows, Columns, Iterator>;
  using reference = row_range&;
  using difference_type = std::size_t;
  using iterator_category = std::random_access_iterator_tag;

  constexpr row_range& operator++() noexcept { return this->operator+=(1); }
  constexpr row_range& operator--() noexcept { return this->operator-=(1); }

  constexpr row_range operator++(int) noexcept {
    const auto copy = *this;
    return this->operator++(), copy;
  }
  constexpr row_range operator--(int) noexcept {
    const auto copy = *this;
    return this->operator--(), copy;
  }

  constexpr row_range operator+(difference_type n) const noexcept {
    return row_range(this->it_, this->row_ + n, *this->rows_, *this->columns_);
  }
  constexpr row_range operator-(difference_type n) const noexcept {
    return row_range(this->it_, this->row_ - n, *this->rows_, *this->columns_);
  }

  constexpr row_range& operator+=(difference_type n) noexcept {
    return this->row_ += n, *this;
  }
  constexpr row_range& operator-=(difference_type n) noexcept {
    return this->row_ -= n, *this;
  }

  constexpr bool operator==(const row_range& that) const noexcept {
    return this->row_ == that.row_ && this->it_ == that.it_;
  }
  constexpr bool operator!=(const row_range& that) const noexcept {
    return !this->operator==(that);
  }

  constexpr difference_type operator-(const row_range& that) const noexcept {
    return this->row_ > that.row_ ? this->row_ - that.row_
                                  : that.row_ - this->row_;
  }

  constexpr auto& operator*() const {
    if (this->row_ >= *this->rows_) {
      throw std::out_of_range(
          std::format("row {} is out of range", this->row_));
    }
    return *this;
  }

  /*
   * std::random_access_range implementation
   */
 public:
  constexpr auto begin() const noexcept { return this->operator[](0); }
  constexpr auto cbegin() const noexcept { return begin(); }
  constexpr auto rbegin() const noexcept {
    return std::make_reverse_iterator(this->end());
  }
  constexpr auto crbegin() const noexcept { return rbegin(); }

  constexpr auto end() const noexcept { return this->operator[](this->size()); }
  constexpr auto cend() const noexcept { return end(); }
  constexpr auto rend() const noexcept {
    return std::make_reverse_iterator(this->begin());
  }
  constexpr auto crend() const noexcept { return rend(); }

  constexpr auto operator[](std::size_t n) const noexcept {
    return row_iterator<Rows, Columns, Iterator>(this->it_, this->row_, n,
                                                 *this->rows_, *this->columns_);
  }

  constexpr std::size_t size() const noexcept { return *this->columns_; }
};

template <std::size_t Rows, std::size_t Columns, iterator Iterator>
class rows_range final : public base_iterator<Rows, Columns, Iterator> {
  /*
   * Constructors
   */
 public:
  constexpr rows_range(Iterator it, std::size_t rows,
                       std::size_t columns) noexcept
      : base_iterator<Rows, Columns, Iterator>(it, 0, 0, rows, columns) {}

  /*
   * std::random_access_range implementation
   */
 public:
  constexpr auto begin() const noexcept { return this->operator[](0); }
  constexpr auto cbegin() const noexcept { return begin(); }
  constexpr auto rbegin() const noexcept {
    return std::make_reverse_iterator(this->end());
  }
  constexpr auto crbegin() const noexcept { return rbegin(); }

  constexpr auto end() const noexcept { return this->operator[](this->size()); }
  constexpr auto cend() const noexcept { return end(); }
  constexpr auto rend() const noexcept {
    return std::make_reverse_iterator(this->begin());
  }
  constexpr auto crend() const noexcept { return rend(); }

  constexpr auto operator[](std::size_t n) const noexcept {
    return row_range<Rows, Columns, Iterator>(this->it_, n, *this->rows_,
                                              *this->columns_);
  }

  constexpr std::size_t size() const noexcept { return *this->rows_; }
};

}  // namespace matrix_views
