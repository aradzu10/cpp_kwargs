#include <iostream>
#include "kwargs.h"

#define PRETTY_PRINT(x) (#x) << " = " << (x)

KWARGS_DEFINE(divide)
KWARGS_DEFINE(mult)

template <FuncKWargs... KWs>
auto add(int x, int y, KWs&&... kws) {
    if constexpr (HAS(kws, mult, divide)) {
        auto [mul, divd] = GET(kws, mult, divide);
        return ((x + y) * mul) / divd;
    } else if constexpr (HAS(kws, mult)) {
        auto mul = GET(kws, mult);
        return (x + y) * mul;
    } else if constexpr (HAS(kws, divide)) {
        auto divd = GET(kws, divide);
        return (x + y) / divd;
    } else {
        return x + y;
    }
}

int main() {
    // compilation error:
    // add(3, 3, 2);                     # 2 isn't a kwargs value
    // add(3, 3, mult);                  # mult isn't a kwargs value
    // add(3, 3, mult = 2, mult = 300);  # mult appear twice
    // add(3, 3, mult = 2, mult = 3.5);  # mult appear twice
    
    std::cout << PRETTY_PRINT(add(3, 3, mult = 2)) << std::endl;
    std::cout << PRETTY_PRINT(add(3, 3, mult = 2.5)) << std::endl;
    std::cout << PRETTY_PRINT(add(3, 3, divide = 4)) << std::endl;
    std::cout << PRETTY_PRINT(add(3, 3, mult = 2, divide = 7)) << std::endl;
    std::cout << PRETTY_PRINT(add(3, 3, divide = 7, mult = 2.5)) << std::endl;
};

