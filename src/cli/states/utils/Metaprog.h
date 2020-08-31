//
// Created by denis on 31.08.20.
//

#ifndef TODOLIST_METAPROG_H
#define TODOLIST_METAPROG_H


template<template <typename...> typename T, template <typename...> typename... Ts>
struct pack {
    template <class... X>
    using head = T<X...>;
    using tail = pack<Ts...>;
};

template <template <typename...> typename T>
struct pack<T> {
    template <typename ... X>
    using head = T<X...>;
    using tail = void;
};

template <typename P, typename N, typename E>
struct nest {
    // induction :
    // nest<P, N, E> = P.head<nest<P.tail, N, E>, E>
    using type = typename P::template head<typename nest<typename P::tail, N, E>::type, E>;
};

template <template <typename...> typename T, typename N, typename E>
struct nest<pack<T>, N, E> {
    // base case :
    // nest<pack<T>, N, E> = T<N, E>
    using type = typename pack<T>::template head<N, E>;
};




#endif //TODOLIST_METAPROG_H
