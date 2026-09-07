/*

Here is the summary of the questions and their test cases in a concise, single-line format:
## Problem 3: Army Escape

* Goal: Find number of paths from top-left $(1,1)$ to bottom-right $(N,N)$ moving only down/right without hitting 1s.
* Test Case 1: N=2, grid=[[0,0],[0,0]] $\rightarrow$ Output: 2
* Test Case 2: N=2, grid=[[0,0],[1,0]] $\rightarrow$ Output: 1
* Test Case 3: N=5, grid=[[0,1,1,1,1],[0,0,0,0,0],[1,1,0,1,0],[0,0,1,0,1],[1,1,1,0,0]] $\rightarrow$ Output: 0

## Problem 4: Minimal Array Picking Cost

* Goal: Find the minimum total cost to pick all $N$ elements where the cost of the $t$-th picked element is $\text{val}_i \oplus \text{cost}_{t-1}$.
* Test Case 1: N=1, val=[7] $\rightarrow$ Output: 7
* Test Case 2: N=2, val=[7, 2] $\rightarrow$ Output: 7 (Pick order: $2 \rightarrow 7$)
* Test Case 3: N=2, val=[1, 2] $\rightarrow$ Output: 4 (Pick order: $1 \rightarrow 2$)

------------------------------
Would you like the full C source code solutions or the optimal logic/algorithm to solve either of these challenges?



*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Completes the costToPick function to find the minimum cost to pick all elements.
 *
 * @param val Pointer to the flattened 1D array of values
 * @param N Size of the array (passed from main via environment context)
 * @return Minimum cost modulo 10^9 + 7
 */
int costToPick(int *val, int N)
{
    long long MOD = 1e9 + 7;
    int total_states = 1 << N;

    // dp[mask] stores the minimum cumulative cost to pick the subset of elements in 'mask'
    // Initialize with a sufficiently large value (infinity)
    vector<long long> dp(total_states, 1e18);

    // Base case: 0 elements picked costs 0
    dp[0] = 0;

    // Iterate through all possible subsets (masks)
    for (int mask = 0; mask < total_states; ++mask)
    {
        if (dp[mask] == 1e18)
            continue; // Skip unreachable states

        // Try to pick the next element 'i' that is not yet in the current subset
        for (int i = 0; i < N; ++i)
        {
            if (!(mask & (1 << i)))
            {
                int next_mask = mask | (1 << i);

                // Current cumulative cost acts as cost_{i-1}
                long long current_cost = dp[mask];

                // Calculate the cost of picking the i-th element
                long long step_cost = val[i] ^ current_cost;
                long long next_cost = current_cost + step_cost;

                // Minimize the cost for the new subset
                if (next_cost < dp[next_mask])
                {
                    dp[next_mask] = next_cost;
                }
            }
        }
    }

    // The answer is the minimum cost to pick all elements (all bits set) modulo 10^9 + 7
    return dp[total_states - 1] % MOD;
}

// Global or environment main wrapper matching the platform's I/O structure
int main()
{
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (cin >> N)
    {
        vector<int> val(N);
        for (int i = 0; i < N; ++i)
        {
            cin >> val[i];
        }
        cout << costToPick(val.data(), N) << "\n";
    }

    return 0;
}
