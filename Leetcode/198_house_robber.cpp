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

    // Edge case: if the array is empty, maximum sum is 0.
    if (n == 0)
        return 0;

    /*
        prev = maximum sum we can get from the previous index (i - 1)

        prev2 = maximum sum we can get from two indices back (i - 2)

        Initially:

        For i = 0:
            There is no element before index 0.
            So the answer for i - 2 is considered 0.

            prev = arr[0]
            prev2 = 0
    */

    int prev = arr[0];
    int prev2 = 0;

    // Start from index 1 because index 0 is already handled above.
    for (int i = 1; i < n; i++)
    {
        /*
            CASE 1: TAKE the current element

            If we take arr[i], we CANNOT take arr[i - 1]
            because the elements must be non-adjacent.

            Therefore, we add arr[i] to the best answer
            from two positions back.

                    current
                       ↓
            ...  i-2   i-1   i
                  ↑
                prev2

            take = arr[i] + prev2
        */
        int take = arr[i] + prev2;

        /*
            CASE 2: DON'T TAKE the current element

            If we don't take arr[i], then we can simply keep
            the best answer we already had up to i - 1.

            prev = answer for the previous element
        */
        int notTake = prev;

        /*
            We have two choices:

            1. Take current element
            2. Don't take current element

            Choose whichever gives the larger sum.
        */
        int curi = max(take, notTake);

        /*
            Move our variables forward.

            The current answer becomes the "previous" answer
            for the next iteration.

            The old prev becomes prev2 because for the next
            index, it will represent the answer from i - 2.
        */
        prev2 = prev;
        prev = curi;
    }

    /*
        prev now contains the maximum sum possible
        for the entire array.
    */
    return prev;
}