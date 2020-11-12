#pragma once

#include <utility>

namespace fun
{
template<typename F, typename... Fs>
constexpr auto compose(F f, Fs... fs)
{
  if constexpr (sizeof...(Fs) == 0)
    return f;
  else
    return [f, fs...](auto&&... args) mutable{
      return f(compose(fs...)(std::forward<decltype(args)>(args)...));
    };
}

template<typename F, typename... Fs>
constexpr auto compose(F* f, Fs... fs)
{
  if constexpr (sizeof...(Fs) == 0)
    return [f](auto&&... args){ return f->operator()(std::forward<decltype(args)>(args)...); };
  else
    return [f, fs...](auto&&... args) mutable{
      return f->operator()(compose(fs...)(std::forward<decltype(args)>(args)...));
    };
}

template<typename Ret, typename...Args, typename... Fs>
constexpr auto compose(Ret(*f)(Args...), Fs... fs)
{
  if constexpr (sizeof...(Fs) == 0)
    return f;
  else
    return [f, fs...](auto&&... args){
      return f(compose(fs...)(std::forward<decltype(args)>(args)...));
    };
}
} // namespace fun
