#include <bits/stdc++.h>
using namespace std;

void findCombinations(int index,
                      vector<int> &arr,
                      int target,
                      vector<vector<int>> &ans,
                      vector<int> &combi)
{
    if (index == arr.size())
    {
        if (target == 0)
        {
            ans.push_back(combi);
        }
        return;
    }

    // Pick the current element
    if (arr[index] <= target)
    {
        combi.push_back(arr[index]);
        findCombinations(index, arr, target - arr[index], ans, combi);
        combi.pop_back();
    }

    // Skip the current element
    findCombinations(index + 1, arr, target, ans, combi);
}

vector<vector<int>> combinationSum(vector<int> &candidates, int target)
{
    vector<vector<int>> ans;
    vector<int> combi;

    findCombinations(0, candidates, target, ans, combi);

    return ans;
}

int main()
{
    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;

    vector<vector<int>> result = combinationSum(candidates, target);

    for (auto &vec : result)
    {
        for (int x : vec)
            cout << x << " ";
        cout << endl;
    }

    return 0;
}