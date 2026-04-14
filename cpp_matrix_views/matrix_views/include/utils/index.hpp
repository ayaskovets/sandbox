#pragma once

#include <cstddef>

namespace matrix_views::utils {

/*
 * 2-dimensional index
 */
struct index final {
  std::ptrdiff_t row;
  std::ptrdiff_t column;

  constexpr bool operator==(const index& that) const = default;
};

}  // namespace matrix_views::utils
