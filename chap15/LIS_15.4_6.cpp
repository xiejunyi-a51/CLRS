/*

Given a sequence A, find the longest monotonically increasing subsequence(LMIS)

Algorithm

For each A_i, find LMIS ending with A_i(LMIS(i)), and the longest one is the answer.
    To calculate LMIS(i), assume we already know LMIS(0) to LMIS(i-1). Let maxLMIS be the maximum length of LMIS so far. Also keep
    record of smallest ending elements for LMIS of length 1 to maxLMIS, which is in sorted order. Binary search for largest ending
    element smaller than A_i, which leads to largest LMIS(j) that satisfies. Add one to it.

*/

#include <vector>
#include <cstdint>
#include <iostream>
using namespace std;

class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        vector<int> endingElems;
        int maxLMIS{0};
        for (int num : nums)
        {
            int index = binary_search_for_less(num, endingElems);
            int currentLMIS = index + 2;
            if (currentLMIS > maxLMIS)
            {
                endingElems.push_back(num);
                maxLMIS += 1;
            }
            else if (endingElems.at(currentLMIS - 1) > num)
            {
                endingElems.at(currentLMIS - 1) = num;
            }
        }
        return maxLMIS;
    }

    int binary_search_for_less(int num, vector<int> &endingElems)
    {
        int start{0};
        int end{static_cast<int>(endingElems.size() - 1)};
        while (start <= end)
        {
            int mid = (start + end) / 2;
            if (endingElems.at(mid) >= num)
            {
                end = mid - 1;
            }
            else if (endingElems.at(mid) < num)
            {
                if (end == start + 1)
                {
                    start = end;
                    continue;
                }
                else if (end == start)
                {
                    return mid;
                }
                start = mid;
            }
        }
        return end;
    }
};

int main()
{
    vector<int> nums{10, 9, 2, 5, 3, 7, 101, 18};
    Solution sol;
    cout << "Longest monotonically increasing Subsequence of length " << sol.lengthOfLIS(nums) << endl;
    return 0;
}