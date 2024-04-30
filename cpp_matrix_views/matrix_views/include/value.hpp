#pragma once

#include <type_traits>
#include <utility>

namespace matrix_views {

class kCompileTimeValue {};

template <bool Condition>
constexpr auto _value_if = []([[maybe_unused]] auto&& value) {
  if constexpr (Condition) {
    return std::forward<decltype(value)>(value);
  } else {
    return kCompileTimeValue{};
  }
};

template <typename T, T Dynamic, T Value = Dynamic>
class value {
 protected:
  constexpr static inline bool kStatic = Value != Dynamic;
  constexpr static inline bool kDynamic = !kStatic;
  constexpr static inline bool kSimple = std::is_scalar_v<T>;

  /*
   * Static value interface
   */
 public:
  constexpr explicit value()
    requires(kStatic)
  = default;

  constexpr explicit value(kCompileTimeValue)
    requires(kStatic)
  {};

  constexpr std::conditional_t<kSimple, T, const T&> operator*() const noexcept
    requires(kStatic)
  {
    return Value_;
  }

  /*
   * Dynamic value interface
   */
 public:
  constexpr explicit value()
    requires(kDynamic)
  = delete;

  template <typename U = T>
    requires(!std::is_convertible_v<U, kCompileTimeValue>)
  constexpr explicit value(U&& value)
    requires(kDynamic)
      : value_(std::forward<U>(value)) {}

  constexpr std::conditional_t<kSimple, T, const T&> operator*() const noexcept
    requires(kDynamic)
  {
    return value_;
  }

  constexpr T& operator*() noexcept
    requires(kDynamic)
  {
    return value_;
  }

 private:
  [[no_unique_address]] std::conditional_t<kDynamic, T, kCompileTimeValue>
      value_;
  constexpr static inline T Value_ = Value;
};

}  // namespace matrix_views
