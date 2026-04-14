#pragma once

#include <utility>

#include "utils/tags.hpp"

namespace matrix_views::utils {

/*
 * Utility wrapper for constructing conditionally_runtime in template code. Used
 * to simplify construction of compile time values without adding a no-op
 * constructor that takes a runtime parameter
 */
template <bool IsRuntime>
constexpr auto runtime_if = []([[maybe_unused]] auto&& value) {
  if constexpr (IsRuntime) {
    return std::forward<decltype(value)>(value);
  } else {
    return kCompileTime;
  }
};

/*
 * Wrapper for a trivial type T that is optionally stored in the type signature.
 * Provides uniform access to the wrapped value via operator*()
 */
template <typename T, bool IsRuntime, T CompileTimeValue = T()>
class conditionally_runtime;

template <typename T, T CompileTimeValue>
class conditionally_runtime<T, true, CompileTimeValue> final {
 public:
  constexpr conditionally_runtime() = delete;
  constexpr conditionally_runtime(T&& value) : value_(std::move(value)) {}

 public:
  constexpr T& operator*() noexcept { return value_; }
  constexpr const T& operator*() const noexcept { return value_; }

 private:
  T value_;
};

template <typename T, T CompileTimeValue>
class conditionally_runtime<T, false, CompileTimeValue> final {
 public:
  constexpr conditionally_runtime() = default;
  constexpr conditionally_runtime(kCompileTimeTag) {}

 public:
  constexpr const T& operator*() const noexcept { return value_; }

 private:
  static inline const constinit T value_ = CompileTimeValue;
};

}  // namespace matrix_views::utils
