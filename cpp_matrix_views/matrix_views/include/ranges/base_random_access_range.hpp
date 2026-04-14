#pragma once

#include <ranges>

namespace matrix_views::ranges {

/*
 * Concept representing a type that inherints base_random_access_range and
 * implements its CRTP interface
 */
template <typename CRTP>
concept base_random_access_range_crtp = requires(const CRTP crtp) {
  { crtp.begin() } -> std::random_access_iterator;
  { crtp.end() } -> std::random_access_iterator;
};

/*
 * Base range class intended for internal use. Constructible only from
 * derived types
 *
 * Implements most of the std::random_access_range interface except for
 * the begin/end acquisition
 */
template <typename CRTP>
class base_random_access_range {
 protected:
  constexpr base_random_access_range() noexcept {
    static_assert(base_random_access_range_crtp<CRTP>,
                  "a type derived from base_random_access_range must "
                  "implement the base_random_access_range_crtp concept");
  }

 private:
  constexpr CRTP* crtp_cast() noexcept { return static_cast<CRTP*>(this); }
  constexpr const CRTP* crtp_cast() const noexcept {
    return static_cast<const CRTP*>(this);
  }

 public:
  constexpr decltype(auto) rbegin() const noexcept {
    return std::make_reverse_iterator(crtp_cast()->end());
  }

  constexpr decltype(auto) rend() const noexcept {
    return std::make_reverse_iterator(crtp_cast()->begin());
  }

  constexpr std::size_t size() const noexcept {
    return static_cast<std::size_t>(this->ssize());
  }
  constexpr decltype(auto) ssize() const noexcept {
    return std::distance(crtp_cast()->begin(), crtp_cast()->end());
  }
  constexpr bool empty() const noexcept { return this->size() == 0; }
};

}  // namespace matrix_views::ranges
