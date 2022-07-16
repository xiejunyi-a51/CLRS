#include <vector>
#include <limits>
#include <cstdint>
#include <iostream>
#include <deque>
#include <tuple>
#include <optional>
using std::cout;
using std::endl;
using std::optional;
using std::vector;
using UnsignedMatrix = vector<vector<size_t>>;
using Matrix = vector<vector<double>>;
using MatrixChain = vector<Matrix>;

optional<Matrix> MatrixMultiply(Matrix &A, Matrix &B)
{
    int l = A.size();
    int m = A[0].size();
    int m2 = B.size();
    int n = B[0].size();
    if (m != m2)
    {
        cout << "ERROR, matrix sizes incompatible!";
        return std::nullopt;
    }
    Matrix C{vector<vector<double>>(l, vector<double>(n, 0))};
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < m; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

optional<Matrix> MatrixChainMultiply(MatrixChain &A, UnsignedMatrix &s, size_t i, size_t j)
{
    if (i == j - 1)
    {
        auto res{MatrixMultiply(A[i], A[j])};
        if (res.has_value())
        {
            return res.value();
        }
        return std::nullopt;
    }
    size_t k = s[i][j];
    auto left = MatrixChainMultiply(A, s, i, k);
    auto right = MatrixChainMultiply(A, s, k + 1, j);
    if (left.has_value() and right.has_value())
    {
        return MatrixMultiply(left.value(), right.value());
    }
    return std::nullopt;
}

void printMatrixChain(UnsignedMatrix &s, size_t i, size_t j)
{
    if (i == j)
    {
        cout << "A" << i;
        return;
    }
    size_t k = s[i][j];
    cout << "(";
    printMatrixChain(s, i, k);
    printMatrixChain(s, k + 1, j);
    cout << ")";
}

void printMatrix(UnsignedMatrix &s)
{
    for (int i = 1; i < s.size(); i++)
    {
        auto &row = s[i];
        for (int j = 1; j < row.size(); j++)
        {
            cout << row[j] << " ";
        }
        cout << endl;
    }
}

void matrixChainOrder(vector<uint8_t> &p)
{
    size_t n = p.size() - 1;
    vector<int> a(n + 1, -1);

    UnsignedMatrix r(n + 1, vector<size_t>(n + 1, std::numeric_limits<size_t>::max()));
    UnsignedMatrix s(n + 1, vector<size_t>(n + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        r[i][i] = 0;
    }
    printMatrix(s);
    cout << endl;
    for (int len = 2; len <= n; len++)
    {
        for (int i = 1, j = len - 1 + i; j <= n; i++, j++)
        {
            for (int k = i; k < j; k++)
            {
                uint32_t order = r[i][k] + r[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (order < r[i][j])
                {
                    r[i][j] = order;
                    s[i][j] = k;
                }
            }
        }
        printMatrix(s);
        cout << endl;
    }
    cout << "minimum multiplication order " << r[1][n] << endl;
    printMatrixChain(s, 1, n);
    cout<<endl;
}

int main()
{
    vector<uint8_t> p{5, 10, 3, 12, 5, 50, 6};
    matrixChainOrder(p);
}
