#include <iostream>

#include "reedsolomon.h"

// 测试 k = 6, m = 3 的里德所罗门编码
int testReedSolomon();

int main()
{
    return testReedSolomon();
}

int testReedSolomon()
{
    reedsolomon::init();

    constexpr int k = 6;
    constexpr int m = 3;

    uint8 data[k] = { 0x24, 0x44, 0x98, 0xC8, 0xF2, 0x1E };

    return 0;
}
