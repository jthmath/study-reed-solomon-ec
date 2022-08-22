#ifndef REED_SOLOMON_GALOIS_H_
#define REED_SOLOMON_GALOIS_H_

#include "common.h"

namespace reedsolomon
{

constexpr int FIELD_SIZE = 256;

void init();

class GaloisUInt8
{
private:
    static constexpr uint8 zero_uint8 = 0;
    static constexpr uint8 one_uint8 = 1;

public:
    GaloisUInt8()
        : a_(zero_uint8)
    {
    }

    explicit GaloisUInt8(uint8 a)
        : a_(a)
    {
    }

    GaloisUInt8(const GaloisUInt8& rhs) = default;

    GaloisUInt8(GaloisUInt8&& rhs) = default;

    ~GaloisUInt8() noexcept = default;

    uint8 rawValue() const
    {
        return a_;
    }

    bool isZero() const
    {
        return a_ == zero_uint8;
    }

    bool isOne() const
    {
        return a_ == one_uint8;
    }

    GaloisUInt8& operator=(const GaloisUInt8& rhs) = default;

    GaloisUInt8& operator=(GaloisUInt8&& rhs) = default;

    bool operator==(GaloisUInt8 rhs) const
    {
        return a_ == rhs.a_;
    }

    bool operator!=(GaloisUInt8 rhs) const
    {
        return a_ != rhs.a_;
    }

    GaloisUInt8 operator+(const GaloisUInt8& rhs) const
    {
        return GaloisUInt8(a_ ^ rhs.a_);
    }

    GaloisUInt8 operator-(const GaloisUInt8& rhs) const
    {
        return GaloisUInt8(a_ ^ rhs.a_);
    }

    GaloisUInt8 operator*(const GaloisUInt8& rhs) const;

    GaloisUInt8 operator/(const GaloisUInt8& rhs) const;

    GaloisUInt8 operator-() const
    {
        return GaloisUInt8(a_);
    }

private:
    uint8 a_;
};

}

#endif
