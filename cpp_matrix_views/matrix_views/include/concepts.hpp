#pragma once

#include <concepts>
#include <ranges>

namespace matrix_views {

template <typename T>
concept scalar = std::is_scalar_v<T>;

template <typename T>
concept scalar_range = requires(T) {
  requires std::ranges::range<T>;
  requires scalar<std::ranges::range_value_t<T>>;
};

template <typename T>
concept scalar_matrix_range = requires(T) {
  requires std::ranges::range<T>;
  requires scalar_range<std::ranges::range_value_t<T>>;
};

template <typename T>
concept container = requires(T container) {
  { container.reserve(std::size_t{}) } -> std::same_as<void>;

  requires std::ranges::range<T>;
};

template <typename T>
concept iterator = requires(T iterator) { requires std::forward_iterator<T>; };

}  // namespace matrix_views
