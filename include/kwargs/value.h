#pragma once
#include <type_traits>

namespace kwargs {

struct KWargValueBase {};
struct KWargDefineBase {};

// TODO(arad) - test if T needs to std::remove_reference_t
template <class T>
concept KWargDef = std::is_base_of_v<KWargDefineBase, T> &&
    !std::is_same_v<T, KWargDefineBase>;

template <class T>
concept KWargVal = std::is_base_of_v<KWargValueBase, T> &&
    std::is_same_v<typename T::parent::parent, KWargValueBase>;

} // namespace kwargs

#define DEFINE_KWARG(kw)                                    \
    namespace kwargs::define::details {                       \
    struct KWargValueBase_##kw : kwargs::KWargValueBase {   \
        using parent = kwargs::KWargValueBase;                \
    };                                                \
                                                      \
    template <class T>                                \
    struct KWargValue_##kw : KWargValueBase_##kw {\
    public:                                           \
        KWargValue_##kw(T&& value) :                \
            value(std::forward<T>(value))             \
        {}                                            \
                                                      \
        using parent = KWargValueBase_##kw;         \
                                                      \
        using type = T;                               \
        T value;                                      \
    };                                                \
                                                      \
    struct KWargDefine_##kw : kwargs::KWargDefineBase {     \
    public:                                           \
        using value_type = KWargValueBase_##kw;     \
                                                      \
        template <class T>                            \
        using rv_t = KWargValue_##kw<T>;            \
                                                      \
        template <class T>                            \
        rv_t<T> operator=(T&& value) const {          \
            return rv_t(std::forward<T>(value));      \
        }                                             \
    };                                                \
                                                      \
    }                                                 \
    constexpr KWargDefine_##kw kw;                \
