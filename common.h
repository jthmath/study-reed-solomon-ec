#ifndef REED_SOLOMON_COMMON_H_
#define REED_SOLOMON_COMMON_H_

#include <cstdint>

#include <string>

using uint8 = uint8_t;
using byte = uint8_t;

namespace reedsolomon
{

void panicAndAbort(const std::string& s) noexcept;

}

#endif
