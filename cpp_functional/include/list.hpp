#pragma once

#include "control.hpp"

#include <vector>

namespace fun
{
template<typename T>
using List = std::vector<T>;

template<typename T>
constexpr auto Append(T&& v, List<T>&& l) -> List<T>
{
  l.push_back(std::forward<T>(v));
  return std::move(l);
}

template<typename T>
constexpr auto Append(T&& v, const List<T>& l) -> List<T>
{
  List<T> copy = l;
  copy.push_back(std::forward<T>(v));
  return copy;
}

struct Nil
{
  template<typename T>
  constexpr operator List<T>() const
  {
    return List<T>{};
  }
};

template<typename T>
constexpr auto Append(T&& v, Nil) -> List<T>
{
  return Append(std::forward<T>(v), List<T>{});
}

// List Functor
template<typename A, typename B>
constexpr auto fmap(B(*f)(A), const List<A>& la) -> List<B>
{
  List<B> lb;
  for (const auto& a : la)
    lb = Append(std::move(f(a)), std::move(lb));
  return lb;
}

// List Applicative
template<typename A, typename B>
constexpr auto apply(const List<B(*)(A)>& lf, const List<A>& la) -> List<B>
{
  List<B> lb;
  for (const auto f : lf)
    for (const auto& a : la)
      lb = Append(std::move(f(a)), std::move(lb));
  return lb;
}

// List Monad
template<typename A, typename B>
constexpr auto bind(const List<A>& la, List<B>(*f)(A)) -> List<B>
{
  List<B> lb;
  for (const auto& a : la)
    for (auto&& b : f(a))
      lb = Append(std::move(b), std::move(lb));
  return lb;
}
} // namespace fun
