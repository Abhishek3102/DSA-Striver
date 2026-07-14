/*

1. try to represent problems in terms of index even if it is not an array qs
2. Do all possible stuffs on that index acc to the prob statement
3. (i) -> Sum up all stuffs -> if qs says count all ways
3. (ii) -> Min of all stuffs -> if qs says find min

*/

#include <bits/stdc++.h>
using namespace std;

int countAllWaysToClimbStairs(int index)
{
    // Base Cases:
    // 0 stairs -> 1 way (do nothing)
    // 1 stair  -> 1 way
    if (index <= 1)
        return 1;

    // Take one step
    int left = countAllWaysToClimbStairs(index - 1);

    // Take two steps
    int right = countAllWaysToClimbStairs(index - 2);

    // Total ways = sum of all possible choices
    return left + right;
}

/*

Memoization
------------
Time Complexity : O(n)
Space Complexity: O(n) recursion stack + O(n) dp array

*/

int countAllWaysToClimbStairsMemo(int index, vector<int> &dp)
{
    // Base Cases
    if (index <= 1)
        return 1;

    // If already calculated, return stored answer
    if (dp[index] != -1)
        return dp[index];

    // Compute answer recursively
    int left = countAllWaysToClimbStairsMemo(index - 1, dp);
    int right = countAllWaysToClimbStairsMemo(index - 2, dp);

    // Store and return
    return dp[index] = left + right;
}

/*

Memoization (Top-Down DP)
Idea

The recursive solution recalculates the same subproblems many times.

Example:

f(5)
├── f(4)
│   ├── f(3)
│   └── f(2)
└── f(3)   <-- calculated again

int main(){
    int n = 5;

vector<int> dp(n + 1, -1);

cout << countAllWaysToClimbStairsMemo(n, dp);
}

*/

// Tabulation (Bottom-Up DP)

/*

Idea

Instead of going from n -> 0 recursively,

build answers from

0
↓
1
↓
2
↓
...
↓
n

because every state depends only on smaller states.

/*

Tabulation
-----------
Time Complexity : O(n)
Space Complexity: O(n)



*/

int countAllWaysToClimbStairsTabulation(int index)
{
    vector<int> dp(index + 1);

    // Base Cases
    dp[0] = 1;
    dp[1] = 1;

    // Build answer from smaller indices
    for (int i = 2; i <= index; i++)
    {
        // One step from (i-1)
        int left = dp[i - 1];

        // Two steps from (i-2)
        int right = dp[i - 2];

        dp[i] = left + right;
    }

    return dp[index];
}

/*

Space Optimized DP

Notice that

dp[i] depends only on

dp[i-1]
dp[i-2]


/*

Space Optimized DP
-------------------
Time Complexity : O(n)
Space Complexity: O(1)

So the entire DP array is unnecessary.

*/

int countAllWaysToClimbStairsSpaceOptimisation(int index)
{
    if (index <= 1)
        return 1;

    int prev2 = 1; // dp[0]
    int prev1 = 1; // dp[1]

    for (int i = 2; i <= index; i++)
    {
        int curr = prev1 + prev2;

        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}