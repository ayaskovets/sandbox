#include "compose.hpp"

#include <cassert>

constexpr double plus4(int x)
{
  return x + 4;
}

constexpr auto mul2(int x)
{
  return x * 2;
}

constexpr auto const_sum = [m = 1](auto a, auto b){
  return a + b + m;
};

auto sum = [m = 1](auto a, auto b) mutable{
  return a + b + (m *= 2);
};

int main()
{
  {// const
    {// copy
      constexpr auto c = fun::compose(plus4, mul2, const_sum);
      constexpr auto res = c(3, 3.f);
      static_assert(res == plus4(mul2(const_sum(3, 3.f))));
    }
    {// pointer
      constexpr auto c = fun::compose(plus4, mul2, &const_sum);
      constexpr auto res = c(3, 3.f);
      static_assert(res == plus4(mul2(const_sum(3, 3.f))));
    }
  }
  {// mutable
    {// copy
      auto c = fun::compose(plus4, mul2, sum);
      auto res = c(3, 3.f);
      assert(res == plus4(mul2(sum(3, 3.f))));
    }
  }
  {// mutable pointer
    {
      auto c = fun::compose(plus4, mul2, &sum);
      auto res = c(3, 3.f);
      assert(res != plus4(mul2(sum(3, 3.f))));
    }
  }
}
