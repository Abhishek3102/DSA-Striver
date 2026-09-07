#include <bits/stdc++.h>
using namespace std;

int f(int index, vector<int> &arr)
{
    if (index == 0)
        return arr[index];
    if (index < 0)
        return 0;

    int pick = arr[index] + f(index - 2, arr);
    int notPick = 0 + f(index - 1, arr);

    return max(pick, notPick);
}

int MaxSumNotAdjacent(vector<int> &arr)
{
    int n = arr.size();
    return f(n - 1, arr);
}

// memoization
int fDP(int index, vector<int> &arr, vector<int> &dp)
{
    if (index == 0)
        return arr[index];
    if (index < 0)
        return 0;

    if (dp[index] != -1)
        return dp[index];

    int pick = arr[index] + f(index - 2, arr, dp);
    int notPick = 0 + f(index - 1, arr, dp);

    return dp[index] = max(pick, notPick);
}

int MaxSumNotAdjacentDP(vector<int> &arr)
{
    int n = arr.size();
    vector<int> dp(n, -1);
    return fDP(n - 1, arr, dp);
}

/*

#include <bits/stdc++.h>
using namespace std;

// Recursive approach
int f(int index, vector<int> &arr)
{
    if (index == 0)
        return arr[index];

    if (index < 0)
        return 0;

    int pick = arr[index] + f(index - 2, arr);
    int notPick = f(index - 1, arr);

    return max(pick, notPick);
}

int MaxSumNotAdjacent(vector<int> &arr)
{
    int n = arr.size();

    if (n == 0)
        return 0;

    return f(n - 1, arr);
}


// Memoization approach
int fDP(int index, vector<int> &arr, vector<int> &dp)
{
    if (index == 0)
        return arr[index];

    if (index < 0)
        return 0;

    // Already calculated
    if (dp[index] != -1)
        return dp[index];

    int pick = arr[index] + fDP(index - 2, arr, dp);
    int notPick = fDP(index - 1, arr, dp);

    // Store result in dp
    return dp[index] = max(pick, notPick);
}

int MaxSumNotAdjacentDP(vector<int> &arr)
{
    int n = arr.size();

    if (n == 0)
        return 0;

    vector<int> dp(n, -1);

    return fDP(n - 1, arr, dp);
}


int main()
{
    vector<int> arr = {2, 1, 4, 9};

    cout << "Recursive: "
         << MaxSumNotAdjacent(arr) << endl;

    cout << "Memoization: "
         << MaxSumNotAdjacentDP(arr) << endl;

    return 0;
}

*/

// space optimisation
int maximumSumNotAdjacentSO(vector<int> &arr)
{
    int n = arr.size();
    int prev = arr[0];
    int prev2 = 0;

    for (int i = 0; i < n; i++)
    {
        int take = arr[i];

        if (i > 1)
            take += prev2;
        int notTake = 0 + prev;

        int curi = max(take, notTake);
        prev2 = prev;
        prev = curi;
    }
    return prev;
}