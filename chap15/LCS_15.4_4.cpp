/*  longest-common-subsequence problem
    Ai 表示 A 的前缀序列 A[0] ... A[i],
    Bj 表示 B 的前缀序列 B[0] ... B[j],
    c(i,j) 表示Ai和Bj的LCS的长度.
    c(i,j) = {0                         if i = 0 or j = 0
              c(i-1,j-1)                else if A[i] = b[j]
              max{c(i-1,j), c(i,j-1)}   else
              }
    
    an algorithm using only O(m) + O(1) space,
    can not reconstruct LCS.
*/

#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>

using namespace std;

template <class T>
int LongestCommonSubsequence(vector<int> &row, T A[], T B[], int m, int n)
{
    int now{};
    int last{};
    for (int j = 1; j <= n; j++)
    {
        last = 0;
        for (int i = 1; i <= m; i++)
        {
            if (A[i] == B[j])
            {
                now = row[i-1] + 1;
            }
            else
            {
                now = std::max(last,row[i]);
            }
            row[i-1] = last;
            last = now;
        }
    }
    return now;
}

int main()
{
    constexpr int m{7};
    constexpr int n{6};
    int A[m + 1]{'x', 'a', 'b', 'c', 'b', 'd', 'a', 'b'};
    int B[n + 1]{'y', 'b', 'd', 'c', 'a', 'b', 'a'};
    vector<int> downRow(m + 1, 0);
    cout << "longest-common-subsequence of lenth " << LongestCommonSubsequence(downRow, A, B, m, n) << endl;
}