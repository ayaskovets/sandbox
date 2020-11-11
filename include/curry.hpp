#include <cassert>

#include <utility>

namespace
{
template<class... Ls>
struct lambda_overload : Ls...
{
  using Ls::operator()...;
};
template<class... Ls>
lambda_overload(Ls...) -> lambda_overload<Ls...>;
}

namespace fun
{
template<typename Ret, typename C, typename Arg, typename... Args>
constexpr auto curry(Ret(C::*f)(Arg, Args...))
{
  const auto copy = [f](C c){
    return [f, c](Arg arg) mutable{
      if constexpr (sizeof...(Args) == 0)
        return (c.*f)(arg);
      else
        return curry([f, c, arg](Args... args) mutable{ return (c.*f)(arg, args...); });
    };
  };
  const auto pointer = [f](C* c) {
    return [f, c](Arg arg) mutable{
      if constexpr (sizeof...(Args) == 0)
        return (c->*f)(arg);
      else
        return curry([f, c, arg](Args... args) mutable{ return (c->*f)(arg, args...); });
    };
  };
  return lambda_overload{copy, pointer};
}

template<typename Ret, typename C, typename Arg, typename... Args>
constexpr auto curry(Ret(C::*f)(Arg, Args...) const)
{
  const auto copy = [f](const C c){
    return [f, c](Arg arg){
      if constexpr (sizeof...(Args) == 0)
        return (c.*f)(arg);
      else
        return curry([f, c, arg](Args... args){ return (c.*f)(arg, args...); });
    };
  };
  const auto pointer = [f](const C* c){
    return [f, c](Arg arg){
      if constexpr (sizeof...(Args) == 0)
        return (c->*f)(arg);
      else
        return curry([f, c, arg](Args... args){ return (c->*f)(arg, args...); });
    };
  };
  return lambda_overload{copy, pointer};
}

template<typename Ld>
constexpr auto curry(Ld l)
{
  return curry(&Ld::operator())(l);
}

template<typename Ld>
constexpr auto curry(Ld* l)
{
  return curry(&Ld::operator())(l);
}

template<typename Ret, typename Arg, typename... Args>
constexpr auto curry(Ret(*f)(Arg, Args...))
{
  return [f](Arg arg){ return curry([f, arg](Args... args){ return f(arg, args...); }); };
}
} // namespace fun
