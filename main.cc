#include <iostream>
#include <vector>

#include "reedsolomon.h"

using GaloisUInt8 = reedsolomon::GaloisUInt8;
using Matrix = reedsolomon::Matrix;

// 测试 k = 6, m = 3 的里德所罗门编码
int testReedSolomon();

int main()
{
    return testReedSolomon();
}

std::vector<int> mockBrokenList()
{
    return { 1, 5, 7 };
}

int testReedSolomon()
{
    reedsolomon::init();

    const GaloisUInt8 zero = GaloisUInt8(static_cast<uint8>(0));
    const GaloisUInt8 one = GaloisUInt8(static_cast<uint8>(1));

    constexpr int K = 6;
    constexpr int M = 3;

    constexpr uint8 data[K] = { 0x24, 0x44, 0x98, 0xC8, 0xF2, 0x1E };
    std::cout << "原始数据为" << std::endl;
    for (int i = 0; i < K; ++i)
    {
        printf("0x%02X ", data[i]);
        if (i == K - 1)
        {
            printf("\n");
        }
    }

    std::vector<std::vector<GaloisUInt8>> to_matrix_data;
    to_matrix_data.resize(K);
    for (int i = 0; i < K; ++i)
    {
        to_matrix_data[i].push_back(GaloisUInt8(data[i]));
    }
    Matrix matrix_data(to_matrix_data);

    // 构建矩阵
    std::vector<std::vector<GaloisUInt8>> a;
    a.resize(K + M);
    for (auto& t : a)
    {
        t.resize(K);
    }
    // 上半部分是单位矩阵
    for (int i = 0; i < K; ++i)
    {
        for (int j = 0; j < K; ++j)
        {
            if (i == j)
            {
                a[i][j] = one;
            }
            else
            {
                a[i][j] = zero;
            }
        }
    }
    // 下半部分是范德蒙德矩阵
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < K; ++j)
        {
            if (j == 0)
            {
                a[K + i][j] = one;
            }
            else if (j == 1)
            {
                a[K + i][j] = GaloisUInt8(uint8(i + 1));
            }
            else
            {
                a[K + i][j] = a[K + i][j - 1] * GaloisUInt8(uint8(i + 1));
            }
        }
    }
    Matrix ma(a);

    Matrix to_matrix_store = Matrix::mut(ma, matrix_data);

    const std::vector<int> broken_list = mockBrokenList();

    if (broken_list.size() > M)
    {
        std::cout << "损坏数据过多，恢复不过来" << std::endl;
        return 1;
    }

    Matrix mat_of_repair = ma.removeRows(broken_list);
    Matrix mat_of_fine_data = to_matrix_store.removeRows(broken_list);

    Matrix data_after_repair = Matrix::mut(mat_of_repair.reciprocal(), mat_of_fine_data);

    const std::vector<std::vector<GaloisUInt8>> data_repair = data_after_repair.rawData();
    std::cout << "复原之后的数据" << std::endl;
    const int temp_size = static_cast<int>(data_repair.size());
    for (int i = 0; i < temp_size; ++i)
    {
        printf("0x%02X ", data_repair[i][0].rawValue());
        if (i == temp_size - 1)
        {
            printf("\n");
        }
    }

    return 0;
}
