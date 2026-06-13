#include <bits/stdc++.h>
using namespace std;

void recurPermuteOptimal(int index, vector<int> &nums, vector<vector<int>> &ans)
{
    // base case when to stop recursion
    if (index == nums.size())
    {
        ans.push_back(nums);
        return;
    }

    // this mean size has not reached the last element, base case not satisfied till now
    for (int i = index; i < nums.size(); i++)
    {                                              // iterate over all indexes
        swap(nums[index], nums[i]);                // swap element with possible permutaions (array -> 1,2,3 me first u swao 1 with one so 1 at 1st pos, then 2 with one which means 2 at 1st pos)
        recurPermuteOptimal(index + 1, nums, ans); // move the recursion call to other indexes
        swap(nums[index], nums[i]);                //  backtrack and reswap the originally swapped elements
    }
}

vector<vector<int>> permuteOptimal(vector<int> &nums)
{
    vector<vector<int>> ans;
    recurPermuteOptimal(0, nums, ans);
    return ans;
}