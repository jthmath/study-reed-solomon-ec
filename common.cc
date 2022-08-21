#include "common.h"

#include <iostream>

namespace reedsolomon
{

void panicAndAbort(const std::string& s) noexcept
{
    std::cout << s << std::endl;
    std::terminate();
}

void panicForDividedByZero() noexcept
{
    panicAndAbort("divided by zero");
}

}
