#pragma once

#include <format>

#include "base_iterator.hpp"

namespace matrix_views {

template <std::size_t Rows, std::size_t Columns, iterator Iterator>
class diagonal_iterator final : public base_iterator<Rows, Columns, Iterator> {
  /*
   * Constructors
   */
 public:
  constexpr diagonal_iterator(Iterator it, std::size_t row, std::size_t column,
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

  constexpr diagonal_iterator& operator++() noexcept {
    return this->operator+=(1);
  }
  constexpr diagonal_iterator& operator--() noexcept {
    return this->operator-=(1);
  }

  constexpr diagonal_iterator operator++(int) noexcept {
    const auto copy = *this;
    this->operator++();
    return copy;
  }

  constexpr diagonal_iterator operator--(int) noexcept {
    const auto copy = *this;
    this->operator--();
    return copy;
  }

  constexpr diagonal_iterator& operator+=(difference_type n) noexcept {
    this->row_ += n;
    this->column_ += n;
    return *this;
  }
  constexpr diagonal_iterator& operator-=(difference_type n) noexcept {
    this->row_ -= n;
    this->column_ -= n;
    return *this;
  }

  constexpr diagonal_iterator operator+(difference_type n) const noexcept {
    return diagonal_iterator(this->it_, this->row_ + n, this->column_ + n,
                             *this->rows_, *this->columns_);
  }
  constexpr diagonal_iterator operator-(difference_type n) const noexcept {
    return diagonal_iterator(this->it_, this->row_ - n, this->column_ - n,
                             *this->rows_, *this->cbolumns_);
  }

  constexpr difference_type operator-(
      const diagonal_iterator& that) const noexcept {
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
class diagonal_range final : public base_iterator<Rows, Columns, Iterator> {
  /*
   * Diagonal matrix utils
   */
 public:
  constexpr std::size_t diagonal() const noexcept {
    return this->row_ > 0 ? *this->rows_ - 1 - this->row_
                          : *this->rows_ - 1 + this->column_;
  }

  constexpr static std::size_t diagonal_to_row(std::size_t diagonal,
                                               std::size_t rows) noexcept {
    return diagonal >= rows - 1 ? 0 : rows - 1 - diagonal;
  }

  constexpr static std::size_t diagonal_to_column(std::size_t diagonal,
                                                  std::size_t rows) noexcept {
    return diagonal < rows - 1 ? 0 : diagonal - rows + 1;
  }

  /*
   * Constructors
   */
 public:
  constexpr diagonal_range(Iterator it, std::size_t diagonal, std::size_t rows,
                           std::size_t columns) noexcept
      : base_iterator<Rows, Columns, Iterator>(
            it, diagonal_to_row(diagonal, rows),
            diagonal_to_column(diagonal, rows), rows, columns) {}

  /*
   * std::random_access_iterator implementation
   */
 public:
  using value_type = diagonal_iterator<Rows, Columns, Iterator>;
  using reference = diagonal_range&;
  using difference_type = std::size_t;
  using iterator_category = std::random_access_iterator_tag;

  constexpr diagonal_range& operator++() noexcept {
    return this->operator+=(1);
  }
  constexpr diagonal_range& operator--() noexcept {
    return this->operator-=(1);
  }

  constexpr diagonal_range operator++(int) noexcept {
    const auto copy = *this;
    return this->operator++(), copy;
  }
  constexpr diagonal_range operator--(int) noexcept {
    const auto copy = *this;
    return this->operator--(), copy;
  }

  constexpr diagonal_range operator+(difference_type n) const noexcept {
    return diagonal_range(this->it_, diagonal() + n, *this->rows_,
                          *this->columns_);
  }
  constexpr diagonal_range operator-(difference_type n) const noexcept {
    return diagonal_range(this->it_, diagonal() - n, *this->rows_,
                          *this->columns_);
  }

  constexpr diagonal_range& operator+=(difference_type n) noexcept {
    const auto changed_diagonal = diagonal() + n;
    this->row_ = diagonal_to_row(changed_diagonal, *this->rows_);
    this->column_ = diagonal_to_column(changed_diagonal, *this->rows_);
    return *this;
  }
  constexpr diagonal_range& operator-=(difference_type n) noexcept {
    const auto changed_diagonal = diagonal() + n;
    this->row_ = diagonal_to_row(changed_diagonal, *this->rows_);
    this->column_ = diagonal_to_column(changed_diagonal, *this->rows_);
    return *this;
  }

  constexpr bool operator==(const diagonal_range& that) const noexcept {
    return this->row_ == that.row_ && this->column_ == that.column_ &&
           this->it_ == that.it_;
  }
  constexpr bool operator!=(const diagonal_range& that) const noexcept {
    return !this->operator==(that);
  }

  constexpr difference_type operator-(
      const diagonal_range& that) const noexcept {
    const auto this_diagonal = this->diagonal();
    const auto that_diagonal = that.diagonal();
    return this_diagonal > that_diagonal ? this_diagonal - that_diagonal
                                         : that_diagonal - this_diagonal;
  }

  constexpr auto& operator*() const noexcept { return *this; }

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
    return diagonal_iterator<Rows, Columns, Iterator>(
        this->it_, this->row_ + n, this->column_ + n, *this->rows_,
        *this->columns_);
  }

  constexpr std::size_t size() const noexcept {
    return std::min(*this->rows_ - this->row_, *this->columns_ - this->column_);
  }
};

template <std::size_t Rows, std::size_t Columns, iterator Iterator>
class diagonals_range final : public base_iterator<Rows, Columns, Iterator> {
  /*
   * Constructors
   */
 public:
  constexpr diagonals_range(Iterator it, std::size_t rows,
                            std::size_t columns) noexcept
      : base_iterator<Rows, Columns, Iterator>(it, rows - 1, 0, rows, columns) {
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
    return diagonal_range<Rows, Columns, Iterator>(this->it_, n, *this->rows_,
                                                   *this->columns_);
  }

  constexpr std::size_t size() const noexcept {
    return *this->rows_ + *this->columns_ - 1;
  }
};

}  // namespace matrix_views
