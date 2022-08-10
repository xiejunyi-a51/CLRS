/* image compression by seam carving

Given image consisting of an m*n array A[1..m, 1..n] of pixels. We wish to remove one pixel from each row, where pixels
to be removed in adjacent rows must be in same or adjacent columns. The pixels removed form a seam from the top row to
the bottom row. Suppose along with each pixel A[i,j] we calculated a disruption measure d[i,j] indicating how bad it would
be to remove pixel A[i,j]. Suppose further that we define the disruption measure of a seam to be the sum of the disruption
measures of its pixels. Give an algorithm to find a seam with the lowest disruption measure.

optimal substructure:
find beat seam is equal to find best seam starting with each element in first row.
redefine problem as P(i,j): lowest cost for seam starting with pixel A[i,j]. Problem is dependent on at most three
subproblems, i.e. cost for seams with uppermost pixel A[i+1,j-1], pixel A[i+1, j] and pixel A[i+1, j+1]. optimal solution
of P(i,j) must consist of optimum solution of P(i+1,j-1), P(i+1,j), P(i+1,j+1).
P(i,j) = min{P(i+1,j-1), P(i+1,j), P(i+1,j+1)} + d[i,j]
Suppose there is one path P'(i+1,j-1) that will give P(i,j) lower cost, then P'(i+1,j-1) < P(i+1,j-1), which violates that
P(i+1,j-1) is optimum solution.

time complexity : O(mn)
*/

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int bestSeamCarving(vector<vector<int>> &c, vector<vector<int>> &d);

private:
    void init(vector<vector<int>> &c, vector<vector<int>> &d)
    {
        for (int j = 0; j <= n - 1; j++)
        {
            c.at(m - 1).at(j) = d.at(m - 1).at(j);
        }
    }
    int m{};
    int n{};
};

int Solution::bestSeamCarving(vector<vector<int>> &c, vector<vector<int>> &d)
{
    m = c.size();
    n = c.at(0).size();
    init(c, d);
    for (int i = m - 2; i >= 0; i--)
    {
        for (int j = 0; j <= n - 1; j++)
        {
            c.at(i).at(j) = (j == 0) ? std::min(c.at(i + 1).at(j), c.at(i + 1).at(j + 1)) : (j == n - 1) ? std::min(c.at(i + 1).at(j - 1), c.at(i + 1).at(j))
                                                                                                                         : std::min(c.at(i + 1).at(j + 1), std::min(c.at(i + 1).at(j - 1), c.at(i + 1).at(j)));
            c.at(i).at(j) += d.at(i).at(j);                                                                                                                         
        }
    }
    return *std::min_element(c.at(0).begin(), c.at(0).end());
}

int main()
{
    constexpr int m{8};
    constexpr int n{9};
    constexpr int INVALID_COST{-1};
    std::random_device rd;
    vector<vector<int>> c{m, vector<int>(n, INVALID_COST)};
    vector<vector<int>> d{m, vector<int>(n, INVALID_COST)};
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            d.at(i).at(j) = rd() % 10 + 1;
        }
    }
    Solution sol;
    cout << "seam carving with lowset disruption measure :" << sol.bestSeamCarving(c, d) << endl;
    return 0;
}