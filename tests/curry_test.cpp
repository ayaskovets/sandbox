#include "curry.hpp"

#include <cassert>

// function pointer
constexpr auto ftest(int a, float b, char c)
{
  return a + b + c;
}

// lambda
constexpr auto const_ltest = [m = 1](int a, float b, char c)
{
  return a + b + c + m;
};

auto ltest = [m = 1](int a, float b, char c) mutable
{
  return a + b + c + (m *= 2);
};

// object
class CTest
{
  int m;
public:
  constexpr CTest(int m): m{m}
  {}
  constexpr auto const_test(int a, float b, char c) const
  {
    return a + b + c + m;
  }
  auto test(int a, float b, char c)
  {
    return a + b + c + (m *= 2);
  }
};

int main()
{
  { // function pointer
    { // const
      constexpr auto c = fun::curry(ftest);
      constexpr auto res = c(3)(3.f)('\3');
      static_assert(res == ftest(3, 3.f, '\3'));
    }
    { // mutable
      auto c = fun::curry(ftest);
      auto res = c(3)(3.f)('\3');
      assert(res == ftest(3, 3.f, '\3'));
    }
  }
  { // lambda
    { // const
      constexpr auto c = fun::curry(const_ltest);
      constexpr auto res = c(3)(3.f)('\3');
      static_assert(res == const_ltest(3, 3.f, '\3'));
    }
    { // mutable
      auto c = fun::curry(ltest);
      auto res = c(3)(3.f)('\3');
      assert(res == ltest(3, 3.f, '\3'));
    }
    { // pointer
      auto c = fun::curry(&ltest);
      auto res = c(3)(3.f)('\3');
      assert(res != ltest(3, 3.f, '\3'));
    }
  }
  { // object
    { // const
      constexpr auto c = fun::curry(&CTest::const_test);
      {
        constexpr auto ctest = CTest{1};
        constexpr auto res = c(ctest)(3)(3.f)('\3');
        static_assert(res == ctest.const_test(3, 3.f, '\3'));
      }
      {
        constexpr auto ctest = CTest{2};
        constexpr auto res = c(ctest)(3)(3.f)('\3');
        static_assert(res == ctest.const_test(3, 3.f, '\3'));
      }
    }
    { // mutable
        auto c = fun::curry(&CTest::test);
        {
          auto ctest = CTest{1};
          auto res = c(ctest)(3)(3.f)('\3');
          assert(res == ctest.test(3, 3.f, '\3'));
        }
        {
          auto ctest = CTest{2};
          auto res = c(ctest)(3)(3.f)('\3');
          assert(res == ctest.test(3, 3.f, '\3'));
        }
    }
    { // pointer
        auto c = fun::curry(&CTest::test);
        {
          auto ctest = CTest{1};
          auto res = c(&ctest)(3)(3.f)('\3');
          assert(res != ctest.test(3, 3.f, '\3'));
        }
        {
          auto ctest = CTest{2};
          auto res = c(&ctest)(3)(3.f)('\3');
          assert(res != ctest.test(3, 3.f, '\3'));
        }
    }
  }
}