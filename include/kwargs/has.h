#pragma once
#include <kwargs/value.h>

namespace kwargs {

template <KWargDef KWDef>
constexpr bool has() {
    return false;
}

template <KWargDef KWDef, KWargVal KWVal, KWargVal... KWVals>
constexpr bool has() {
    if constexpr (std::is_base_of_v<KWDef::value_type, KWVal>) {
        return true;
    }
    return has<KWDef, KWVals...>();
}

} // namespace kwargs
