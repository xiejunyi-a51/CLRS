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
            int index = find_prev(num, endingElems);
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

private:
    int find_prev(int num, vector<int> &endingElems)
    {
        if (endingElems.empty()) return -1;
        auto [success, index] = binary_search(num, endingElems);
        if (success) return index-1;
        if (num < endingElems.at(index)) return index-1;
        return index;
    }
    tuple<bool, int> binary_search(int num, vector<int> &arr)
    {
        int l{0};
        int r{static_cast<int>(arr.size())-1};
        int lastCompared{0};
        while (l <= r)
        {
            int mid = (l+r)/2;
            if (num == arr.at(mid))
            {
                return make_tuple(true, mid);
            }
            lastCompared = mid;
            if (num < arr.at(mid))
            {
                r--;
            }
            else
            {
                l++;
            }
        }
        return make_tuple(false, lastCompared);
    }
};

int main()
{
    vector<int> nums{10, 9, 2, 5, 3, 7, 101, 18};
    Solution sol;
    cout << "Longest monotonically increasing Subsequence of length " << sol.lengthOfLIS(nums) << endl;
    return 0;
}