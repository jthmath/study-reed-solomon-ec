#include "matric.h"

namespace reedsolomon
{

Matrix::Matrix(const std::vector<std::vector<GaloisUInt8>>& a)
{
    const int row_num = static_cast<int>(a.size());
    if (row_num < 1)
    {
        panicForBadOperation();
    }
    const int column_num = static_cast<int>(a[0].size());
    if (column_num < 1)
    {
        panicForBadOperation();
    }
    for (int i = 1; i < row_num; ++i)
    {
        if (a[i].size() != column_num)
        {
            panicForBadOperation();
        }
    }

    a_.resize(row_num);
    for (int i = 0; i < row_num; ++i)
    {
        a_[i].resize(column_num);
        for (int j = 0; j < column_num; ++j)
        {
            a_[i][j] = a[i][j];
        }
    }

    row_num_ = row_num;
    column_num_ = column_num;
}

Matrix Matrix::mut(const Matrix& a, const Matrix& b)
{
    const int k = a.get_column_num();
    if (k != b.get_row_num())
    {
        panicForUndefinedOperation();
    }

    const int row_num = a.get_row_num();
    const int column_num = b.get_column_num();

    std::vector<std::vector<GaloisUInt8>> t;
    t.resize(row_num);
    for (int i = 0; i < row_num; ++i)
    {
        t[i].resize(column_num);
        for (int j = 0; j < column_num; ++j)
        {
            GaloisUInt8 s;
            for (int z = 0; z < k; ++z)
            {
                s = s + a.a_[i][z] * b.a_[z][j];
            }
            t[i][j] = s;
        }
    }

    return Matrix { t };
}

GaloisUInt8 Matrix::det() const
{
    if (row_num_ != column_num_)
    {
        panicForUndefinedOperation();
    }
    const int n = row_num_;

    if (n == 1)
    {
        return a_[0][0];
    }
    else if (n == 2)
    {
        return a_[0][0] * a_[1][1] - a_[0][1] * a_[1][0];
    }

    GaloisUInt8 d;

    // 计算代数余子式
    for (int i = 0; i < n; ++i)
    {
        Matrix mat = minor(0, i);

        if ((1 + i + 1) % 2 == 0)
        {
            d = d + a_[0][i] * mat.det();
        }
        else
        {
            d = d - a_[0][i] * mat.det();
        }
    }

    return d;
}

Matrix Matrix::minor(int i, int j) const
{
    if (row_num_ < 2 || column_num_ < 2)
    {
        panicForUndefinedOperation();
    }
    if (i < 0 || i >= row_num_ || j < 0 || j >= column_num_)
    {
        panicForUndefinedOperation();
    }

    std::vector<std::vector<GaloisUInt8>> to_matrix;
    to_matrix.resize(row_num_ - 1);
    for (auto& t : to_matrix)
    {
        t.reserve(column_num_ - 1);
    }

    for (int p = 0; p < row_num_; ++p)
    {
        if (p == i)
        {
            continue;
        }
        auto& row = to_matrix[p < i ? p : p - 1];

        for (int q = 0; q < column_num_; ++q)
        {
            if (q != j)
            {
                row.push_back(a_[p][q]);
            }
        }
    }

    return Matrix { to_matrix };
}

Matrix Matrix::reciprocal() const
{
    if (row_num_ != column_num_)
    {
        panicForUndefinedOperation();
    }
    const GaloisUInt8 d = det();
    if (d.isZero())
    {
        panicForDividedByZero();
    }
    const GaloisUInt8 one(uint8(1));
    if (row_num_ == 1)
    {
        std::vector<std::vector<GaloisUInt8>> m;
        m.resize(1);
        m[0].resize(1);
        m[0][0] = one / d;
        return Matrix { m };
    }

    std::vector<std::vector<GaloisUInt8>> to_matrix;
    to_matrix.resize(row_num_);
    for (int i = 0; i < row_num_; ++i)
    {
        to_matrix[i].resize(column_num_);
    }

    for (int i = 0; i < row_num_; ++i)
    {
        for (int j = 0; j < column_num_; ++j)
        {
            Matrix mnr = minor(i, j);
            if ((i + j + 2) % 2 == 0)
            {
                to_matrix[j][i] = mnr.det() / d;
            }
            else
            {
                to_matrix[j][i] = -mnr.det() / d;
            }
        }
    }

    return Matrix { to_matrix };
}

Matrix Matrix::removeRows(const std::vector<int>& rows)
{
    if (rows.size() >= row_num_)
    {
        panicForBadOperation();
    }

    std::vector<std::vector<GaloisUInt8>> to_matrix;

    for (int i = 0; i < row_num_; ++i)
    {
        if (std::find(rows.begin(), rows.end(), i) != rows.cend())
        {
            continue;
        }
        to_matrix.push_back(a_[i]);
    }

    return Matrix { to_matrix };
}

}
