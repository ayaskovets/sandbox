#pragma once

#include "storage/callable_storage_proxy.hpp"

namespace matrix_views::storage {

/*
 * Const version of callable_storage_proxy
 */
template <callable_storage_proxy_callable Callable>
class const_callable_storage_proxy : public callable_storage_proxy<Callable> {
 protected:
  using invoke_result = std::invoke_result_t<Callable, utils::index>;

 public:
  constexpr const_callable_storage_proxy() = default;
  constexpr const_callable_storage_proxy(Callable storage_proxy) noexcept
      : callable_storage_proxy<Callable>(std::move(storage_proxy)) {}

  using reference =
      std::conditional_t<std::is_lvalue_reference_v<invoke_result>,
                         std::add_lvalue_reference_t<std::add_const_t<
                             std::remove_reference_t<invoke_result>>>,
                         std::add_const_t<invoke_result>>;
  using value_type = std::remove_cvref_t<reference>;

  constexpr decltype(auto) operator()(utils::index index) const {
    return callable_storage_proxy<Callable>::operator()(index);
  }
};

}  // namespace matrix_views::storage
