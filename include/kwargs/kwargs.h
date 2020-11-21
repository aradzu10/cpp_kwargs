#pragma once
#include <kwargs/value.h>

namespace kwargs {

template <KWargVal KWVal = void>
constexpr bool is_kwargs_appear_twice() {
    return false;
}

template <KWargVal KWValF, KWargVal KWValS, KWargVal... KWVals>
constexpr bool is_kwargs_appear_twice() {
    return std::is_same_v<typename KWValF::parent, typename KWValS::parent> ||
        is_kwargs_appear_twice<KWValF, KWVals...>();
}

template <KWargVal KWVal = void>
constexpr bool any_kwargs_appear_twice() {
    return false;
}

template <KWargVal KWValF, KWargVal KWValS, KWargVal... KWVals>
constexpr bool any_kwargs_appear_twice() {
    return is_kwargs_appear_twice<KWValF, KWValS, KWVals...>() ||
        any_kwargs_appear_twice<KWValS, KWVals...>();
}

template <class... T>
concept KWarg = KWargVal<T>... && !any_kwargs_appear_twice<T...>();

} // namespace kwargs
