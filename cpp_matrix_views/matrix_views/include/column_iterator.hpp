#pragma once

#include <format>

#include "base_iterator.hpp"

namespace matrix_views {

template <std::size_t Rows, std::size_t Columns, iterator Iterator>
class column_iterator final : public base_iterator<Rows, Columns, Iterator> {
  /*
   * Constructors
   */
 public:
  constexpr column_iterator(Iterator it, std::size_t row, std::size_t column,
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

  constexpr column_iterator& operator++() noexcept {
    return this->operator+=(1);
  }
  constexpr column_iterator& operator--() noexcept {
    return this->operator-=(1);
  }

  constexpr column_iterator operator++(int) noexcept {
    const auto copy = *this;
    this->operator++();
    return copy;
  }

  constexpr column_iterator operator--(int) noexcept {
    const auto copy = *this;
    this->operator--();
    return copy;
  }

  constexpr column_iterator& operator+=(difference_type n) noexcept {
    return this->row_ += n, *this;
  }
  constexpr column_iterator& operator-=(difference_type n) noexcept {
    return this->row_ -= n, *this;
  }

  constexpr column_iterator operator+(difference_type n) const noexcept {
    return column_iterator(this->it_, this->row_ + n, this->column_,
                           *this->rows_, *this->columns_);
  }
  constexpr column_iterator operator-(difference_type n) const noexcept {
    return column_iterator(this->it_, this->row_ - n, this->column_,
                           *this->rows_, *this->columns_);
  }

  constexpr difference_type operator-(
      const column_iterator& that) const noexcept {
    return this->row_ > that.row_ ? this->row_ - that.row_
                                  : that.row_ - this->row_;
  }

  constexpr auto& operator[](difference_type n) const {
    return *std::next(this->it_,
                      this->row_ * *this->columns_ + this->column_ + n);
  }
  constexpr auto& operator*() const { return this->operator[](0); }
};

template <std::size_t Rows, std::size_t Columns, iterator Iterator>
class column_range final : public base_iterator<Rows, Columns, Iterator> {
  /*
   * Constructors
   */
 public:
  constexpr column_range(Iterator it, std::size_t column, std::size_t rows,
                         std::size_t columns) noexcept
      : base_iterator<Rows, Columns, Iterator>(it, 0, column, rows, columns) {}

  /*
   * std::random_access_iterator implementation
   */
 public:
  using value_type = column_iterator<Rows, Columns, Iterator>;
  using reference = column_range&;
  using difference_type = std::size_t;
  using iterator_category = std::random_access_iterator_tag;

  constexpr column_range& operator++() noexcept { return this->operator+=(1); }
  constexpr column_range& operator--() noexcept { return this->operator-=(1); }

  constexpr column_range operator++(int) noexcept {
    const auto copy = *this;
    return this->operator++(), copy;
  }
  constexpr column_range operator--(int) noexcept {
    const auto copy = *this;
    return this->operator--(), copy;
  }

  constexpr column_range operator+(difference_type n) const noexcept {
    return column_range(this->it_, this->column_ + n, *this->rows_,
                        *this->columns_);
  }
  constexpr column_range operator-(difference_type n) const noexcept {
    return column_range(this->it_, this->column_ - n, *this->rows_,
                        *this->columns_);
  }

  constexpr column_range& operator+=(difference_type n) noexcept {
    return this->column_ += n, *this;
  }
  constexpr column_range& operator-=(difference_type n) noexcept {
    return this->column_ -= n, *this;
  }

  constexpr bool operator==(const column_range& that) const noexcept {
    return this->column_ == that.column_ && this->it_ == that.it_;
  }
  constexpr bool operator!=(const column_range& that) const noexcept {
    return !this->operator==(that);
  }

  constexpr difference_type operator-(const column_range& that) const noexcept {
    return this->column_ > that.column_ ? this->column_ - that.column_
                                        : that.column_ - this->column_;
  }

  constexpr auto& operator*() const {
    if (this->column_ >= *this->columns_) {
      throw std::out_of_range(
          std::format("column {} is out of range", this->column_));
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
    return column_iterator<Rows, Columns, Iterator>(
        this->it_, n, this->column_, *this->rows_, *this->columns_);
  }

  constexpr std::size_t size() const noexcept { return *this->rows_; }
};

template <std::size_t Rows, std::size_t Columns, iterator Iterator>
class columns_range final : public base_iterator<Rows, Columns, Iterator> {
  /*
   * Constructors
   */
 public:
  constexpr columns_range(Iterator it, std::size_t rows,
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
    return column_range<Rows, Columns, Iterator>(this->it_, n, *this->rows_,
                                                 *this->columns_);
  }

  constexpr std::size_t size() const noexcept { return *this->columns_; }
};

}  // namespace matrix_views
