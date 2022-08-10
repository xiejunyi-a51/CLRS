/* Breaking a string
It costs n time units to break a string of n characters into two pieces.
Suppose a programmer wants to break a string into many pieces.
Given a string S with n characters and an array L[1..m] containing the numbers of characters after which to break,
compute the lowest cost for a sequence of breaks, along with a sequence of breaks that achieves this cost.

Time Complexity : O(m*n^2)

Idea1 : try always choose the middle as the best break
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;
using Range = vector<int>;
class Solution
{
public:
    void breakAString(string &s, vector<uint16_t> &breakPoints)
    {
        init(s, breakPoints);
        cout << "minCost: " << breakAStringij(0, n - 1, breakPoints) << endl;
        cout << "sequence of breaks:";
        printSequenceOfBreaks(0, n-1);
    }

    void printSequenceOfBreaks(int i, int j)
    {
        if (i < j)
        {
            auto p{b.at(i).at(j)};
            if (p == -1)
            {
                return;
            }
            cout << p << " ";
            printSequenceOfBreaks(i, p);
            printSequenceOfBreaks(p+1, j);
        }
    }

    int breakAStringij(int i, int j, vector<uint16_t> &breakPoints)
    {
        if (c.at(i).at(j) != -1)
        {
            return c.at(i).at(j);
        }
        if (i >= j)
        {
            c.at(i).at(j) = 0;
            return 0;
        }
        Range range = breakPointsWithinSubstringSij.at(i).at(j);
        if (range.size() == 0 or range.size()==1 and range.at(0) == j)
        {
            c.at(i).at(j) = 0;
            return 0;
        }
        auto bestBreak{range.at(0)};
        int minCost{std::numeric_limits<uint16_t>::max()};
        for (uint16_t p : range)
        {
            if (not (p == j))
            {
                auto cost = breakAStringij(i, p, breakPoints) + breakAStringij(p + 1, j, breakPoints) + (j - i + 1);
                if (cost < minCost)
                {
                    minCost = cost;
                    bestBreak = p;
                }
            }
        }
        b.at(i).at(j) = bestBreak;
        c.at(i).at(j) = minCost;
        return minCost;
    }

private:
    // outputs:
    vector<int> sequenceOfBreaks{};

    int n{};
    vector<vector<Range>> breakPointsWithinSubstringSij{};
    vector<vector<int>> c{};
    vector<vector<int>> b{};
    void init(string &s, vector<uint16_t> &breakPoints);
};

void Solution::init(string &s, vector<uint16_t> &breakPoints)
{
    n = s.size();
    c = vector<vector<int>>(n, vector<int>(n, -1));
    b = vector<vector<int>>(n, vector<int>(n, -1));
    breakPointsWithinSubstringSij = vector<vector<Range>>(n, vector<Range>(n, Range()));
    vector<bool> existsBreak(n, false);
    for (auto p : breakPoints)
    {
        existsBreak.at(p) = true;
    }

    for (int i = 0; i < n; i++)
    {
        Range range{};
        breakPointsWithinSubstringSij.at(i).reserve(n);
        for (int j = i; j < n; j++)
        {
            if (existsBreak.at(j))
            {
                range.push_back(j);
            }
            breakPointsWithinSubstringSij.at(i).at(j) = range;
        }
    }
}

int main()
{
    Solution sol;
    string s = "illusional";
    vector<uint16_t> breakPoints = {0,3,5,7};
    sol.breakAString(s, breakPoints);
}