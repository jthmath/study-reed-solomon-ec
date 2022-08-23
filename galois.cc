#include "galois.h"

namespace reedsolomon
{

constexpr uint16 PRIMITIVE_POLYNOMIAL = 0b100011101; // x^8 + x^4 + x^3 + x^2 + 1

uint8 gf_power[FIELD_SIZE - 1];
uint8 gf_log[FIELD_SIZE];

// 计算指数表和对数表
// 在实际生产中，提前在别的地方算好放入 const 数组，这里为了演示无所谓了
void init()
{
    constexpr uint16 MASK = 0xFF00;

    gf_power[0] = uint8(1);
    gf_power[1] = uint8(1) << 1;
    for (int i = 2; i < FIELD_SIZE - 1; ++i)
    {
        uint16 temp = gf_power[i - 1] << 1;
        if ((temp & MASK) != 0)
        {
            // 越界了，取模
            temp ^= PRIMITIVE_POLYNOMIAL;
        }
        gf_power[i] = static_cast<uint8>(temp);
    }

    gf_log[0] = 0; // 注意，0 没有对数
    for (int i = 0; i < FIELD_SIZE - 1; ++i)
    {
        gf_log[gf_power[i]] = i;
    }
}


GaloisUInt8 GaloisUInt8::operator*(const GaloisUInt8& rhs) const
{
    if (isZero() || rhs.isZero())
    {
        return GaloisUInt8(zero_uint8);
    }

    int n = gf_log[a_];
    int m = gf_log[rhs.a_];
    int k = (n + m) % 255;

    return GaloisUInt8(gf_power[k]);
}

GaloisUInt8 GaloisUInt8::operator/(const GaloisUInt8& rhs) const
{
    if (rhs.isZero())
    {
        panicForDividedByZero();
    }

    if (isZero())
    {
        return GaloisUInt8(zero_uint8);
    }

    int n = gf_log[a_];
    int m = gf_log[rhs.a_];

    int k = 0;
    if (n >= m)
    {
        k = n - m;
    }
    else
    {
        k = n + 255 - m;
    }

    return GaloisUInt8(gf_power[k]);
}

}
