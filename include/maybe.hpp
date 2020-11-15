#pragma once

#include "control.hpp"

#include <optional>

namespace fun
{
template<typename T>
using Maybe = std::optional<T>;

template<typename T>
constexpr auto Just(T val) -> Maybe<T>
{
  return Maybe<T>{std::move(val)};
}

struct Nothing
{
  template<typename T>
  constexpr operator Maybe<T>() const
  {
    return Maybe<T>{};
  }
};

// Maybe Functor
template<typename A, typename B>
constexpr auto fmap(B(*f)(A), Maybe<A> m) -> Maybe<B>
{
  return m.has_value() ? Just(f(m.value())) : Nothing();
}

// Maybe Applicative
template<typename A, typename B>
constexpr auto apply(Maybe<B(*)(A)> f, Maybe<A> m) -> Maybe<B>
{
  return f.has_value() ? fmap(f.value(), m) : Nothing();
}

// Maybe Monad
template<typename A, typename B>
constexpr auto bind(Maybe<A> m, Maybe<B>(*f)(A)) -> Maybe<B>
{
  return m.has_value() ? f(m.value()) : Nothing();
}
} // namespace fun
