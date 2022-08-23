#ifndef REED_SOLOMON_MATRIC_H_
#define REED_SOLOMON_MATRIC_H_

#include <vector>

#include "galois.h"

namespace reedsolomon
{

class Matrix
{
public:
    explicit Matrix(const std::vector<std::vector<GaloisUInt8>>& a);

    int get_row_num() const
    {
        return row_num_;
    }

    int get_column_num() const
    {
        return column_num_;
    }

private:
    std::vector<std::vector<GaloisUInt8>> a_;
    int row_num_;
    int column_num_;

public:
    static Matrix mut(const Matrix& a, const Matrix& b);

    // 计算行列式
    GaloisUInt8 det() const;

    // 计算余子阵
    Matrix minor(int i, int j) const;

    // 计算伴随矩阵
    Matrix reciprocal() const;

    // 移除若干行
    Matrix removeRows(const std::vector<int>& rows);

    std::vector<std::vector<GaloisUInt8>> rawData() const
    {
        return a_;
    }
};

}

#endif
