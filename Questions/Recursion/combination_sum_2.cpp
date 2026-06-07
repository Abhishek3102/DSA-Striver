// here we can choose a number at an index only once

#include <bits/stdc++.h>
using namespace std;

void findCombinations2(int index, int target, vector<int> &arr, vector<vector<int>> &ans, vector<int> &ds)
{
    if (target == 0)
    {
        ans.push_back(ds);
        return;
    }

    for (int i = index; i < arr.size(); i++)
    {
        if (i > index && arr[i] == arr[i - 1])
            continue;

        if (arr[i] > target)
            break;
        ds.push_back(arr[i]);
        findCombinations2(i + 1, target - arr[i], arr, ans, ds);
        ds.pop_back();
    }
}

vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
{
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> ans;
    vector<int> ds;
    findCombinations2(0, target, candidates, ans, ds);
    return ans;
}

int main()
{
    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;

    vector<vector<int>> result = combinationSum2(candidates, target);

    for (auto &vec : result)
    {
        for (int x : vec)
            cout << x << " ";
        cout << endl;
    }

    return 0;
}