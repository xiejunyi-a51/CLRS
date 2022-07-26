#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
    using Table = vector<vector<uint16_t>>;
public:
    int longestPalindromeSubseq(string s)
    {
        auto n = s.size();
        Table c(n, vector<uint16_t>(n, 0));
        for (int i = 0; i < n; i++)
        {
            c.at(i).at(i) = 1;
        }
        return LongestPalindromeSubsequence(s, c);
    }

    int LongestPalindromeSubsequence(string s, Table &c)
    {
        for (int j = 0; j < s.size(); j++)
        {
            optional<uint16_t> m{};
            for (int i = j - 1; i >= 0; i--)
            {
                if (s.at(i) == s.at(j))
                {
                    m = i;
                    c.at(i).at(j) = (j - i) > 1 ? c.at(i + 1).at(j - 1) + 2 : 2;
                }
                else if (m.has_value() and c.at(m.value()).at(j) > c.at(i).at(j - 1))
                {
                    c.at(i).at(j) = c.at(m.value()).at(j);
                }
                else
                {
                    c.at(i).at(j) = c.at(i).at(j - 1);
                }
            }
        }
        return c.at(0).at(s.size()-1);
    }
};