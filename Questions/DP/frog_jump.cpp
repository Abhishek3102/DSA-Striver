#include <bits/stdc++.h>
using namespace std;

// Recursive function to find the minimum energy required
// to reach the stone at 'index'.
int f(int index, vector<int> &heights)
{

    // Base case:
    // If the frog is already on the first stone,
    // no energy is required.
    if (index == 0)
        return 0;

    // Option 1:
    // Jump from the previous stone (index - 1)
    int left = f(index - 1, heights) + abs(heights[index] - heights[index - 1]);

    // Option 2:
    // Jump from two stones before (index - 2)
    // Initialize with a large value because this jump
    // may not always be possible.
    int right = INT_MAX;

    if (index > 1)
        right = f(index - 2, heights) + abs(heights[index] - heights[index - 2]);

    // Return the minimum energy among the two choices.
    return min(left, right);
}

// Function that starts the recursion from the last stone.
int frogJump(int n, vector<int> &heights)
{
    return f(n - 1, heights);
}

int fMemoization(int index, vector<int> &heights, vector<int> &dp)
{
    if (index == 0)
        return 0;

    if (dp[index] != -1)
        return dp[index];

    int left = fMemoization(index - 1, heights, dp) + abs(heights[index] - heights[index - 1]);
    int right = INT_MAX;
    if (index > 1)
        right = fMemoization(index - 2, heights, dp) + abs(heights[index] - heights[index - 2]);

    return dp[index] = min(left, right);
}

int frogJumpMemo(int n, vector<int> &heights)
{
    vector<int> dp(n + 1, -1);
    return fMemoization(n - 1, heights, dp);
}

// Tabulation
int frogJumpTabulation(int n, vector<int> &heights)
{
    vector<int> dp(n, 0);
    dp[0] = 0;
    for (int i = 1; i < n; i++)
    {
        int first_step = dp[i - 1] + abs(heights[i] - heights[i - 1]);
        int second_step = INT_MAX;
        if (i > 1)
            second_step = dp[i - 2] + abs(heights[i] - heights[i - 2]);

        dp[i] = min(first_step, second_step);
    }

    return dp[n - 1];
}

// Space Optimization - whenever there is something like ind - 1 & ind - 2 then we can have space optimization there
int frogJumpSpaceOpti(int n, vector<int> &heights)
{
    int prev = 0;
    int prev2 = 0;
    for (int i = 1; i < n; i++)
    {
        int fs = prev + abs(heights[i] - heights[i - 1]);
        int ss = INT_MAX;
        if (i > 1)
            ss = prev2 + abs(heights[i] - heights[i - 2]);

        int curr_i = min(fs, ss);
        prev2 = prev;
        prev = curr_i;
    }
    return prev;
}

int main()
{

    // Number of stones
    int n;
    cin >> n;

    // Heights of all stones
    vector<int> heights(n);

    for (int i = 0; i < n; i++)
        cin >> heights[i];

    // Print the minimum energy required
    cout << frogJump(n, heights) << endl;

    return 0;
}