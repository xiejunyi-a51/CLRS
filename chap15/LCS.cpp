/*  longest-common-subsequence problem
    Ai 表示 A 的前缀序列 A[0] ... A[i],
    Bj 表示 B 的前缀序列 B[0] ... B[j],
    c(i,j) 表示Ai和Bj的LCS的长度.
    c(i,j) = {0                         if i = 0 or j = 0
              c(i-1,j-1)                else if A[i] = b[j]
              max{c(i-1,j), c(i,j-1)}   else
              }

    a bottom-up algorithm taking O(mn) time.
*/

#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>

using namespace std;

template <class T>
void LongestCommonSubsequence(vector<vector<int>> &c, T A[], T B[], int m, int n)
{
    for (int j = 1; j <= n; j++)
    {
        // for each row
        for (int i = 1; i <= m; i++)
        {
            if (A[i] == B[j])
            {
                c[i][j] = c[i - 1][j - 1] + 1;
            }
            else
            {
                c[i][j] = std::max(c[i - 1][j], c[i][j - 1]);
            }
        }
    }
}

template <class T>
void recontructLCS(vector<T> &LCS, vector<vector<int>> c, T A[], T B[], int i, int j)
{
    while (i > 0 and j > 0)
    {
        if (A[i] == B[j])
        {
            LCS.push_back(A[i]);
            i--;
            j--;
        }
        else if (c[i - 1][j] > c[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }
}

int main()
{
    // int m{8};
    // int n{9};
    // int A[m + 1]{invalid1, 1, 0, 0, 1, 0, 1, 0, 1};
    // int B[n + 1]{invalid2, 0, 1, 0, 1, 1, 0, 1, 1, 0};
    constexpr int m{7};
    constexpr int n{6};
    int A[m + 1]{'x', 'a', 'b', 'c', 'b', 'd', 'a', 'b'};
    int B[n + 1]{'y', 'b', 'd', 'c', 'a', 'b', 'a'};
    vector<vector<int>> c(m + 1, vector<int>(n + 1, 0));
    vector<int> LCS;
    LongestCommonSubsequence(c, A, B, m, n);
    cout << "longest-common-subsequence of lenth " << c[7][6] << " :" << endl;
    recontructLCS(LCS, c, A, B, m, n);
    for (auto iter = LCS.rbegin(); iter != LCS.rend(); iter++)
    {
        printf("%c \n", *iter);
    }
}