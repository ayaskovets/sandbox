#pragma once

#include <iostream>

namespace util
{
namespace log
{

template<typename S, typename D>
void write(S& out, D&& delim)
{}
template<typename S, typename D, typename Arg>
void write(S& out, D&& delim, Arg&& arg)
{
    out << std::forward<Arg>(arg);
}
template<typename S, typename D, typename Arg, typename ...Args>
void write(S& out, D&& delim, Arg&& arg, Args&&... args)
{
    out << std::forward<Arg>(arg);
    ((out << std::forward<D>(delim) << std::forward<Args>(args)), ...);
}

template<typename S, typename D>
void writeln(S& out, D&& delim)
{}
template<typename S, typename D, typename Arg>
void writeln(S& out, D&& delim, Arg&& arg)
{
    out << std::forward<Arg>(arg) << '\n';
}
template<typename S, typename D, typename Arg, typename ...Args>
void writeln(S& out, D&& delim, Arg&& arg, Args&&... args)
{
    out << std::forward<Arg>(arg);
    ((out << std::forward<D>(delim) << std::forward<Args>(args)), ...) << '\n';
}

constexpr auto cerr = [](auto&&... args)
{ writeln(std::cerr, ' ', std::forward<decltype(args)>(args)...); };
constexpr auto cout = [](auto&&... args)
{ writeln(std::cout, ' ', std::forward<decltype(args)>(args)...); };
constexpr auto wcerr = [](auto&&... args)
{ writeln(std::wcerr, ' ', std::forward<decltype(args)>(args)...); };
constexpr auto wcout = [](auto&&... args)
{ writeln(std::wcout, ' ', std::forward<decltype(args)>(args)...); };

}
}
