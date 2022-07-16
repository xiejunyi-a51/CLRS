/* Longest monotonically increasing Subsequence
    Turning problem into finding LIS ending with last item of sequence, which has optimal substructure.
    Given sequence A, let Ai be its prefix A[0] ... A[i],
    1.  for each Ai:
        find its LIS ending with A[i]
    2.  finding the longest one in all i
    c[i] is the length of LIS ending with A[i]
    c[i] =  {
                max(j=1, ..., i-1) { A[j] | A[j] < A[i] } + 1
            }
    an algorithm that takes O(n^2) time.
*/

#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>

using namespace std;

tuple<int, int> findLongestMonotonicallyIncreasingSubsequence(vector<int> &c, int A[], int n)
{
    int max{numeric_limits<int>::min()};
    int maxIndex{};
    c[0] = 1;
    for (int i = 1; i < n; i++)
    {
        c[i] = 1;
        for (int j = 0; j < i; j++)
        {
            if (A[j] < A[i] and (c[j] + 1) > c[i])
            {
                c[i] = c[j] + 1;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (c[i] > max)
        {
            max = c[i];
            maxIndex = i;
        }
    }
    return make_tuple(max, maxIndex);
}

void reconstructLIS(int maxIndex, vector<int> &c, int A[], int n)
{
    if (c[maxIndex] > 1)
    {
        int index{maxIndex};
        for (int i = 0; i < index; i++)
        {
            if (A[i] < A[index] and c[i] + 1 == c[index])
            {
                index = i;
                break;
            }
        }
        reconstructLIS(index, c, A, n);
    }
    cout << A[maxIndex] << endl;
}

int main()
{
    constexpr int n{10}; // len(A)
    int A[n]{3, 6, 7, 1, 3, 0, 1, -3, 2, -1};
    vector<int> c(n, 0);
    auto [max, index] = findLongestMonotonicallyIncreasingSubsequence(c, A, n);
    cout << "Longest monotonically increasing Subsequence of length " << max << ":" << endl;
    reconstructLIS(index, c, A, n);
}