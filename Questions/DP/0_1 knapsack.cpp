#include <bits/stdc++.h>
using namespace std;

int f(int index, vector<int> &weight, int capacity)
{
    if (index == 0)
    {
        if (weight[0] <= capacity)
            return weight[0];
        else
            return 0;
    }

    int notTake = f(index - 1, weight, capacity);

    int take = INT_MIN;

    if (weight[index] <= capacity)
    {
        take = weight[index] + f(index - 1, weight, capacity - weight[index]);
    }

    return max(notTake, take);
}

// memoization
int fMemoi(int index, vector<int> &weight, int capacity, vector<vector<int>> &dp)
{
    if (index == 0)
    {
        if (weight[0] <= capacity)
            return weight[0];
        return 0;
    }

    if (dp[index][capacity] != -1)
        return dp[index][capacity];

    int notTake = fMemoi(index - 1, weight, capacity, dp);

    int take = INT_MIN;

    if (weight[index] <= capacity)
    {
        take = weight[index] +
               fMemoi(index - 1, weight, capacity - weight[index], dp);
    }

    return dp[index][capacity] = max(take, notTake);
}

// memo 2
int fSO(int index, int capacity, vector<int> &weight, vector<int> &val, vector<vector<int>> &dp)
{
    if (index == 0)
    {
        if (weight[0] <= capacity)
            return val[0];
        return 0;
    }

    if (dp[index][capacity] != -1)
        return dp[index][capacity];
    int notTake = 0 + fSO(index - 1, capacity, weight, val, dp);
    int take = INT_MIN;
    if (weight[index] <= capacity)
    {
        take = val[index] + fSO(index - 1, capacity - weight[index], weight, val, dp);
    }

    return dp[index][capacity] = max(take, notTake);
}

int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight)
{
    vector<vector<int>> dp(n, vector<int>(maxWeight + 1, -1));
    return fSO(n - 1, maxWeight, weight, value, dp);
}

int main()
{
    vector<int> weight = {1, 2, 3, 4};
    int capacity = 6;

    int n = weight.size();

    // THIS is where dp is initialized - first init whole dp array to 0 then calculate for all. and while checking if anything is not -1
    // means it is already calculated so dont do again and just return
    vector<vector<int>> dp(n, vector<int>(capacity + 1, -1));

    int answer = fMemoi(n - 1, weight, capacity, dp);

    cout << answer << endl;
}

// space optimization
int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight)
{
    // dp[capacity] = maximum value we can get
    // with the current items and this capacity
    vector<int> dp(maxWeight + 1, 0);

    // Base case: only item 0
    for (int capacity = weight[0]; capacity <= maxWeight; capacity++)
    {
        dp[capacity] = value[0];
    }

    // Process remaining items
    for (int index = 1; index < n; index++)
    {
        // IMPORTANT: go from right to left
        for (int capacity = maxWeight; capacity >= 0; capacity--)
        {
            int notTake = dp[capacity];

            int take = INT_MIN;

            if (weight[index] <= capacity)
            {
                take = value[index] +
                       dp[capacity - weight[index]];
            }

            dp[capacity] = max(take, notTake);
        }
    }

    return dp[maxWeight];
}

int main()
{
    vector<int> weight = {1, 2, 3, 5};
    vector<int> value = {5, 10, 15, 20};

    int n = weight.size();
    int maxWeight = 5;

    cout << knapsack(weight, value, n, maxWeight) << endl;

    return 0;
}
