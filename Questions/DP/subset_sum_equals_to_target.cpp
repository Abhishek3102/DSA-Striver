#include <bits/stdc++.h>
using namespace std;

bool f(int index, int target, vector<int> &arr)
{
    if (target == 0)
        return true;

    if (index == 0)
        return arr[0] == target;

    bool notTake = f(index - 1, target, arr);

    bool take = false;
    if (target >= arr[index])
    {
        take = f(index - 1, target - arr[index], arr);
    }

    return take || notTake;
}

// tabulation
bool fTab(int index, int target, vector<int> &arr, vector<vector<int>> &dp)
{
    if (target == 0)
        return true;
    if (index == 0)
        return (arr[0] == target);
    if (dp[index][target] != -1)
        return dp[index][target];
    bool notTake = fTab(index - 1, target, arr, dp);
    bool take = false;

    if (arr[index] <= target)
    {
        take = fTab(index - 1, target - arr[index], arr, dp);
    }
    return dp[index][target] = take | notTake;
}

bool subsetSumTab(int n, int k, vector<int> &arr)
{
    vector<vector<bool>> dp(n, vector<bool>(k + 1, false));

    // Target = 0 is always possible
    for (int i = 0; i < n; i++)
    {
        dp[i][0] = true;
    }

    // Base case for index 0
    if (arr[0] <= k)
    {
        dp[0][arr[0]] = true;
    }

    // Fill the DP table
    for (int ind = 1; ind < n; ind++)
    {
        for (int target = 1; target <= k; target++)
        {

            // Don't take current element
            bool notTake = dp[ind - 1][target];

            // Take current element
            bool take = false;
            if (arr[ind] <= target)
            {
                take = dp[ind - 1][target - arr[ind]];
            }

            dp[ind][target] = take || notTake;
        }
    }

    return dp[n - 1][k];
}

// space optimization
bool subsetSumTab(int n, int k, vector<int> &arr)
{
    vector<bool> prev(k + 1, false);

    prev[0] = true;

    if (arr[0] <= k)
        prev[arr[0]] = true;

    for (int ind = 1; ind < n; ind++)
    {
        vector<bool> cur(k + 1, false);

        cur[0] = true;

        for (int target = 1; target <= k; target++)
        {
            bool notTake = prev[target];

            bool take = false;
            if (arr[ind] <= target)
            {
                take = prev[target - arr[ind]];
            }

            cur[target] = take || notTake;
        }

        prev = cur;
    }

    return prev[k];
}
