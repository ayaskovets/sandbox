#pragma once

namespace fun
{
template<typename A, typename B, template<typename> class Functor>
constexpr auto fmap(B(*)(A), Functor<A>) -> Functor<B> = delete;

template<typename A, typename B, template<typename> class Applicative>
constexpr auto apply(Applicative<B(*)(A)>, Applicative<A>) -> Applicative<B> = delete;

template<template<typename> class Monad, typename A, typename B>
constexpr auto bind(Monad<A>, Monad<B>(*)(A)) -> Monad<B> = delete;
} // namespace fun
