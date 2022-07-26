#include <vector>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
/*
ToDo : 可以对每个单词的长度加1，行的长度也加1，于是就不用考虑单词之间的空格了。
*/
void prettyPrint(vector<int> l, size_t M, int index, vector<size_t> cost, vector<size_t> res)
{
    // res[j] number of words put in one line.
    // cost[j] = minimum cost for lestmost j words.
    size_t n = l.size();
    for (int j = index; j >= 0; j--)
    {
        int extraSpaceInLine = M;
        for (int i = 1; (j - 1 + i < n) and (extraSpaceInLine - l.at(j - 1 + i) >= 0); i++)
        {
            extraSpaceInLine -= l.at(j - 1 + i);
            int costJ = pow(extraSpaceInLine, 3) + cost.at(j + i);
            if (costJ < cost.at(j))
            {
                cost.at(j) = costJ;
                res.at(j) = i;
            }
            extraSpaceInLine -= 1;
        }
        cout << "j " << j << " extraSpaceInLine " << extraSpaceInLine + 1
             << " number of words " << res.at(j) << "\n";
    }
    int countOfLines = 1;
    int countOfWords = 0;
    while (countOfWords < n)
    {
        cout << "line " << countOfLines << ": ";
        int numOfWords = res.at(countOfWords);
        for (int i = 0; i < numOfWords; i++)
        {
            cout << l.at(countOfWords + i) << ", ";
        }
        cout << "\n";
        countOfWords += numOfWords;
        countOfLines++;
    }
}

int main()
{
    vector<int> l{7, 5, 3, 9, 1, 3, 4, 6, 3, 2, 1, 5, 6};
    int n = l.size();
    size_t M = 13;
    vector<size_t> res(n, 0);
    vector<size_t> cost(n, numeric_limits<size_t>::max());
    int index = n - 1;
    int sum = 0;
    while (index >= 0 and sum + l.at(index) <= M)
    {
        sum += l.at(index);
        cost.at(index) = 0;
        res.at(index) = n - index;
        index--;
    }
    prettyPrint(l, M, index, cost, res);
}