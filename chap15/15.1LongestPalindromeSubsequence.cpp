#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <optional>
#include <tuple>
using namespace std;

/*
algorithm
c[i,j] = {
            c[m,j]
                if there exist a i <= m < j, so that s[m] = s[j] and
                c[m,j] = c[m+1, j-1] +2 > c[i,j-1]
            c[i, j-1]                                      otherwise
          }
c[i,j] is the length of longest palindrome in substring s[i,j] 
Time Complexity O(n^2)
*/

using Table = vector<vector<uint16_t>>;
using PairTable = vector<vector<tuple<int, int>>>;
string reconstructPalindrome(string s, PairTable &b)
{
    string res{};
    uint16_t n = s.size();
    int l{0};
    int r{n - 1};
    cout << "---------------reconstructPalindrome---------------" << endl;
    cout << "original string: " << s << endl;
    auto iter = res.begin();
    while (l <= r)
    {
        auto [index1, index2] = b.at(l).at(r);
        int16_t mid = res.size() / 2;
        if (index1 != index2)
        {
            cout << "(palindromeL, palindromeR) (" << s.at(index1) << ", " << s.at(index2) << " )" << endl;
            res.insert(iter++, s.at(index1));
            res.insert(iter, s.at(index2));
        }
        else
        {
            cout << "palindrome center " << s.at(index1) << endl;
            res.insert(iter, s.at(index1));
        }
        l = index1 + 1;
        r = index2 - 1;
    }
    return res;
}
string LongestPalindromeSubsequence(string s, Table &c, PairTable &b)
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
                b.at(i).at(j) = make_tuple(i, j);
            }
            else if (m.has_value() and c.at(m.value()).at(j) > c.at(i).at(j - 1))
            {
                c.at(i).at(j) = c.at(m.value()).at(j);
                b.at(i).at(j) = make_tuple(m.value(), j);
            }
            else
            {
                c.at(i).at(j) = c.at(i).at(j - 1);
                b.at(i).at(j) = b.at(i).at(j - 1);
            }
        }
    }
    return reconstructPalindrome(s, b);
}

int main()
{
    string s{"character"};
    auto n = s.size();
    tuple<int16_t, int16_t> INVALID_INDEX_PAIR{-1, -1};
    Table c(n, vector<uint16_t>(n, 0));
    PairTable b(n, vector<tuple<int, int>>(n, INVALID_INDEX_PAIR));
    for (int i = 0; i < n; i++)
    {
        c.at(i).at(i) = 1;
        b.at(i).at(i) = make_tuple(i, i);
    }
    string res = LongestPalindromeSubsequence(s, c, b);
    cout << "Longest Palindrome: " << res << endl;
}