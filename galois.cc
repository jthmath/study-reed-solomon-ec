#include "galois.h"

namespace reedsolomon
{

GaloisUInt8 GaloisUInt8::operator*(const GaloisUInt8& rhs) const
{
    //
}

GaloisUInt8 GaloisUInt8::operator/(const GaloisUInt8& rhs) const
{
    if (rhs.isZero())
    {
        panicAndAbort("");
    }

    if (isZero())
    {
        return GaloisUInt8(zero_uint8);
    }

    return GaloisUInt8(zero_uint8);
}

}
