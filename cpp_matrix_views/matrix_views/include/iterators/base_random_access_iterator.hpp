#pragma once

#include <iterator>

#include "utils/index.hpp"

namespace matrix_views::iterators {

/*
 * Concept representing a type that inherints base_random_access_iterator and
 * implements its CRTP interface
 */
template <typename CRTP>
concept base_random_access_iterator_crtp = requires(
    const CRTP const_crtp, CRTP crtp, std::ptrdiff_t /* difference_type */ n) {
  { crtp += n } -> std::same_as<CRTP&>;
  { const_crtp.operator-(const_crtp) } -> std::same_as<decltype(n)>;
  { *const_crtp };

  requires !std::is_same_v<decltype(*const_crtp), void>;
};

/*
 * Base iterator class intended for internal use. Constructible only from
 * derived types
 *
 * Implements most of the std::random_access_iterator interface except for
 * indexing and dereferencing parts
 */
template <typename CRTP>
class base_random_access_iterator {
 protected:
  constexpr base_random_access_iterator() noexcept {
    static_assert(base_random_access_iterator_crtp<CRTP>,
                  "a type derived from base_random_access_iterator must "
                  "implement the base_random_access_iterator_crtp concept");
  }

  constexpr base_random_access_iterator(utils::index index) noexcept
      : base_random_access_iterator() {
    index_ = index;
  }

 private:
  constexpr CRTP* crtp_cast() noexcept { return static_cast<CRTP*>(this); }
  constexpr const CRTP* crtp_cast() const noexcept {
    return static_cast<const CRTP*>(this);
  }

 protected:
  utils::index index_;

 public:
  using iterator_category = std::random_access_iterator_tag;
  using difference_type = std::ptrdiff_t;

  constexpr CRTP& operator++() noexcept { return *crtp_cast() += 1; }
  constexpr CRTP& operator--() noexcept { return *crtp_cast() -= 1; }

  constexpr CRTP operator++(int) noexcept {
    const CRTP copy = *crtp_cast();
    return ++(*this), copy;
  }
  constexpr CRTP operator--(int) noexcept {
    const CRTP copy = *crtp_cast();
    return --(*this), copy;
  }

  constexpr bool operator==(
      const base_random_access_iterator& that) const noexcept = default;
  constexpr bool operator!=(
      const base_random_access_iterator& that) const noexcept {
    return !(*this == that);
  }

  constexpr bool operator<(const CRTP& that) const noexcept {
    return *crtp_cast() - that < 0;
  }
  constexpr bool operator>(const CRTP& that) const noexcept {
    return that - *crtp_cast() < 0;
  }
  constexpr bool operator<=(const CRTP& that) const noexcept {
    return !(*crtp_cast() > that);
  }
  constexpr bool operator>=(const CRTP& that) const noexcept {
    return !(*crtp_cast() < that);
  }

  constexpr CRTP operator+(difference_type n) const noexcept {
    CRTP copy = *crtp_cast();
    return copy += n, copy;
  }

  constexpr CRTP& operator-=(difference_type n) noexcept {
    return *crtp_cast() += -n;
  }

  constexpr decltype(auto) operator->() const { return &((*this)[0]); }
  constexpr decltype(auto) operator[](difference_type n) const {
    return *(*this + n);
  }
};

template <base_random_access_iterator_crtp CRTP>
constexpr CRTP operator-(
    const base_random_access_iterator<CRTP>& that,
    typename base_random_access_iterator<CRTP>::difference_type n) noexcept {
  return that + -n;
}

template <base_random_access_iterator_crtp CRTP>
constexpr CRTP operator+(
    typename base_random_access_iterator<CRTP>::difference_type n,
    const base_random_access_iterator<CRTP>& that) noexcept {
  return that + n;
}

}  // namespace matrix_views::iterators
