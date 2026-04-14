#pragma once

#include <concepts>
#include <optional>

#include "utils/index.hpp"

namespace matrix_views::storage {

/*
 * Concept representing a callable that implements data access for
 * callable_storage_proxy
 */
template <typename StorageProxy>
concept callable_storage_proxy_callable =
    std::invocable<const StorageProxy, utils::index>;

/*
 * Tagged iterator class with a set direction. Implements iterator movement but
 * leaves dereferencing unimplemented
 */
template <callable_storage_proxy_callable Callable>
class callable_storage_proxy {
 public:
  constexpr callable_storage_proxy() noexcept = default;
  constexpr callable_storage_proxy(Callable storage_proxy) noexcept
      : storage_proxy_(std::move(storage_proxy)) {}

  constexpr callable_storage_proxy(const callable_storage_proxy& that) =
      default;
  constexpr callable_storage_proxy& operator=(
      const callable_storage_proxy& that) {
    this->storage_proxy_ = that.storage_proxy_;
    return *this;
  }

  constexpr callable_storage_proxy(callable_storage_proxy&& that) = default;
  constexpr callable_storage_proxy& operator=(callable_storage_proxy&& that) {
    this->storage_proxy_ = std::move(that.storage_proxy_);
    return *this;
  }

 public:
  using reference = std::invoke_result_t<Callable, utils::index>;
  using value_type = std::remove_cvref_t<reference>;

  constexpr reference operator()(utils::index index) const {
    return storage_proxy_.value()(index);
  }

 private:
  std::optional<Callable> storage_proxy_;
};

}  // namespace matrix_views::storage
