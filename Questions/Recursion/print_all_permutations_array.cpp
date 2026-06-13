// this is solved by using a map data structure which takes an extra space

#include <bits/stdc++.h>
using namespace std;

// ds is array used to store all permutations
void recurPermute(vector<int> &ds, vector<int> &nums, vector<vector<int>> &ans, int freq[])
{
    // when size of array storing all permutation in a recursion, reaches the size of given array then
    //  it is a permuation and it then gets added to ans array. so stop when size of ds array reaches size of given array of qs
    if (ds.size() == nums.size())
    {
        ans.push_back(ds);
        return;
    }

    for (int i = 0; i < nums.size(); i++)
    {
        if (!freq[i])
        {                                      // umarked freq -> element has not been picked
            ds.push_back(nums[i]);             // then we add the unpicked element
            freq[i] = 1;                       // mark that element in freq as picked
            recurPermute(ds, nums, ans, freq); // call the recursion to pick other elements
            freq[i] = 0;                       // now after coming back, mark the element as unpicked
            ds.pop_back();                     // also remove that element from ds array which was picked earlier
        }
    }
}

vector<vector<int>> permute(vector<int> &nums)
{
    vector<vector<int>> ans; // this array of array will store all permutations
    vector<int> ds;
    int freq[nums.size()];
    for (int i = 0; i < nums.size(); i++)
        freq[i] = 0; // freq is initialised with zero means this is not taken in permutation

    recurPermute(ds, nums, ans, freq);
    return ans;
}