#include <string>
#include <vector>
#include <iostream>
/*
c(i,j) 表示子字符串word1[1..i]和子字符串word2[1..j] 的最小编辑距离
c(i,j) = {
            max{i,j}                                    if i = 0 or j = 0
            c(i-1,j-1)                                  else if word1[i] == word2[j]
            min {c(i-1,j-1), c(i,j-1), c(i-1,j)} + 1    else
         }
*/
using namespace std;

class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        m = word1.size();
        n = word2.size();
        c = vector<vector<int>>(m + 1, vector<int>(n + 1, invalidDistance));
        bestOperation = vector<vector<Operation>>(m + 1, vector<Operation>(n + 1, Operation::INVALID_OPERATION));
        init();
        for (size_t i = 1; i <= m; i++)
        {
            for (size_t j = 1; j <= n; j++)
            {
                if (word1.at(i-1) == word2.at(j-1))
                {
                    c.at(i).at(j) = c.at(i - 1).at(j - 1);
                    bestOperation.at(i).at(j) = Operation::doNothing;
                }
                else
                {
                    int min{c.at(i - 1).at(j - 1)};
                    Operation bestOp{Operation::replace};
                    if (c.at(i).at(j - 1) < min)
                    {
                        min = c.at(i).at(j - 1);
                        bestOp = Operation::insert;
                    }
                    if (c.at(i - 1).at(j) < min)
                    {
                        min = c.at(i - 1).at(j);
                        bestOp = Operation::del;
                    }
                    c.at(i).at(j) = min + 1;
                    bestOperation.at(i).at(j) = bestOp;
                }
            }
        }
        reconstruct(word1, word2);
        return c.at(m).at(n);
    }

private:
    enum class Operation : uint8_t
    {
        doNothing = 0,
        insert = 1,
        del = 2,
        replace = 3,
        INVALID_OPERATION = 0xFF
    };
    void reconstruct(string word1, string word2)
    {
        int i{m};
        int j{n};
        while (i >= 0 and j >= 0)
        {
            switch (bestOperation.at(i).at(j))
            {
            case Operation::doNothing:
                i--;
                j--;
                break;
            case Operation::insert:
                cout << word1 << "-->" << word1.insert(i, 1, word2.at(j-1)) << "\n";
                j--;
                break;
            case Operation::del:
                cout << word1 << "-->" << word1.erase(i-1, 1) << "\n";
                i--;
                break;
            case Operation::replace:
                cout << word1 << "-->" << word1.replace(i-1, 1, 1, word2.at(j-1)) << "\n";
                i--;
                j--;
                break;
            default:
                cout << "Error! invalid operation!\n";
                break;
            }
        }
    }
    void init()
    {
        for (int i = 0; i <= m; i++)
        {
            c.at(i).at(0) = i;
            bestOperation.at(i).at(0) = Operation::del;
        }
        for (int j = 0; j <= n; j++)
        {
            c.at(0).at(j) = j;
            bestOperation.at(0).at(j) = Operation::insert;
        }
        bestOperation.at(0).at(0) = Operation::doNothing;
    }
    int m{};
    int n{};
    vector<vector<int>> c;
    vector<vector<Operation>> bestOperation;
    const static int invalidDistance{-1};
};

int main()
{
    Solution sol;
    string word1{"intention"};
    string word2{"execution"};
    sol.minDistance(word1, word2);
}