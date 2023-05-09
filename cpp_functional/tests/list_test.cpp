#include "list.hpp"

#include <cassert>

auto split_float(float x) -> fun::List<int>
{
  return fun::List<int>{static_cast<int>(x), static_cast<int>(x * 10) % 10};
}

constexpr auto negate(int x) -> int
{
  return -x;
}

constexpr auto mul3(int x) -> int
{
  return x * 3;
}

constexpr auto sub5(int x) -> int
{
  return x - 5;
}

template<typename T>
bool operator==(const fun::List<T>& lhs, const fun::List<T>& rhs)
{
  if (lhs.size() != rhs.size())
    return false;
  for (std::size_t i = 0; i < lhs.size(); ++i)
    if (lhs[i] != rhs[i])
      return false;
  return true;
}

int main()
{
  auto l1 = fun::List<float>{1.2f, 3.4f};
  l1 = fun::Append(5.6f, std::move(l1));
  assert((l1 == fun::List<float>{1.2f, 3.4f, 5.6f}));
  assert((l1 == fun::Append(5.6f, fun::Append(3.4f, fun::Append(1.2f, fun::Nil{})))));

  auto l2 = fun::bind(l1, split_float);
  assert((l2 == fun::List<int>{1, 2, 3, 4, 5, 6}));
  assert((fun::fmap(negate, l2) == fun::List<int>{-1, -2, -3, -4, -5, -6}));

  auto lf = fun::List<int(*)(int)>{negate, mul3, sub5};
  auto l3 = fun::apply(lf, fun::List<int>{7, 8});
  assert((l3 == fun::List<int>{-7, -8, 21, 24, 2, 3}));
}
