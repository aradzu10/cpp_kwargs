#pragma once
#include <kwargs/value.h>

namespace kwargs {

template <KWargDef KWDef>
constexpr auto get() {
    // TODO(arad) - add KWDef type
    static_assert(sizeof(KWDef) == 0, "Property not found");
}

template <KWargDef KWDef, KWargVal KWVal, KWargVal... KWVals>
constexpr auto get(KWVal&& first_val, KWVals&&... values) {
    if constexpr (std::is_base_of_v<KWDef, KWVal>) {
        return std::forward(first_val.value);
    }
    return get<KWDef, KWVals...>(std::forward<KWVals>(kws)...);
}

} // namespace kwargs
