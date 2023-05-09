#include "maybe.hpp"

constexpr auto divide(int a, int b) -> fun::Maybe<float>
{
  return b == 0 ? fun::Nothing() : fun::Just(static_cast<float>(a) / b);
}

constexpr auto is_magical(float x) -> bool
{
  return x == 42.f;
}

constexpr auto get_function(bool for_real) -> fun::Maybe<char(*)(bool)>
{
  return for_real ? fun::Just(+[](bool x){ return x ? 'y' : 'n'; }) : fun::Nothing();
}

int main()
{
  static_assert(fun::apply(fun::bind(fun::fmap(is_magical, divide(42, 1)), get_function), fun::Just(true)) == fun::Just('y'));
  static_assert(fun::apply(fun::bind(fun::fmap(is_magical, divide(42, 1)), get_function), fun::Just(false)) == fun::Just('n'));
}
