/*

### 1. ICPC Preparation

You were selected to be the next ICPC organizer. Your task is to get **n computers ready** for the event. 

Each of these computers has some requirements such that there are at most **m requirements**. The requirements of the i-th computer are
represented as a binary string of length m, where the j-th bit is on (1) if this requirement is required for the i-th computer. 

For each computer, you can buy this computer and spend **1 coin**, and the same thing for each requirement
(each individual requirement costs **1 coin**). 

You will not have to buy the i-th computer if you've bought all its requirements as you can construct it instead. 

Find the **minimum amount of money** you need so that you can get all computers ready. 

**Note:** If we buy any requirement then we can use it for constructing multiple computers. 

### Function Description

Complete the get_ans function in the editor. 

### Parameters:

* **n**: INTEGER — The number of computers.
* **m**: INTEGER — The number of requirements.
* **r**: STRING ARRAY — The binary requirements for each computer.

### Return Value:

* The function must return an INTEGER denoting the minimum money you need so that you can get all computers ready.

### Input Format for Debugging:

* The first line contains an integer, n, denoting the number of elements in r.
* The next line contains an integer, m, denoting the length of each string.
* Each line i of the n subsequent lines (where 0 <= i < n) contains a string describing r[i].

### Sample Testcases

### **Sample Case 1**

* **Input:** 

text

3
3
000
000
000

Use code with caution.
* **Output:** 

text

0

Use code with caution.
* **Explanation:**
Here, n = 3, m = 3, r = ["000", "000", "000"].
For the first computer, it does not have any requirements, so instead of buying we can construct it for 0 coins as it does not have any
requirements. Similarly, for second and third computer we need 0 coins for each computer. Hence, the minimum amount of money required
is 0 + 0 + 0 = 0.

### **Sample Case 2**

* **Input:** 

text

3
3
001
010
100

Use code with caution.
* **Output:** 

text

3

Use code with caution.
* **Explanation:**
Here, n = 3, m = 3, r = ["001", "010", "100"].
We can buy computer first, second and third computers each for 1 coin. Hence, total money we need is 3.
Another possible solution is that we can buy requirement 3 for 1 coin and computer 2 for 1 coin and requirements 1 for 1 coin.
Here, we spend 3 coins. Please note that, we do not need to buy computer 1 and computer 3 as we can construct computer 1 from requirement
3 and computer 3 from requirement 1.
There are also other solutions in which we spend 3 coins. Hence, the minimum amount of money needed so that we can get all computers ready is 3.

### **Sample Case 3**

* **Input:** 

text

3
3
100
111
100

Use code with caution.
* **Output:** 

text

2

Use code with caution.
* **Explanation:**
Here, n = 3, m = 3, r = ["100", "111", "100"].
We can buy requirement 1 for 1 coin and buy computer 2 for 1 coin. Hence, total we need 2 coins.
Please note that we do not need to buy computer 1 because we bought requirement 1 so it can be used to construct computer
1. Also note that we do not need to buy computer 3 because we bought requirement 1 so it can be used to construct computer 1 (and 3).
Hence, the minimum amount of money needed so that we can get all computers ready is 2.

*/

#include <bits/stdc++.h>
using namespace std;

/**
 * Function to find the minimum amount of money to get all computers ready.
 *
 * @param n Number of computers
 * @param m Number of requirements
 * @param r Array of binary strings representing requirements
 * @return Minimum coins needed
 */
int get_ans(int n, int m, vector<string> r)
{
    // total_masks represents 2^m possible subsets of requirements
    int total_masks = 1 << m;

    // dp[S] will store the number of computers whose requirements are exactly a submask of S
    vector<int> dp(total_masks, 0);

    // Step 1: Convert each binary string to an integer bitmask and count frequencies
    for (int i = 0; i < n; ++i)
    {
        int mask = 0;
        for (int j = 0; j < m; ++j)
        {
            if (r[i][j] == '1')
            {
                mask |= (1 << j); // Set the j-th bit if requirement is needed
            }
        }
        dp[mask]++; // Increment count of computers matching this exact mask
    }

    // Step 2: Sum Over Subsets (SOS) DP
    // dp[S] transforms to store the total number of computers covered by requirement subset S
    for (int j = 0; j < m; ++j)
    {
        for (int mask = 0; mask < total_masks; ++mask)
        {
            if (mask & (1 << j))
            {
                dp[mask] += dp[mask ^ (1 << j)];
            }
        }
    }

    int min_cost = n; // Max possible cost is buying all n computers directly

    // Step 3: Iterate through all possible requirement subsets to find the minimum cost
    for (int mask = 0; mask < total_masks; ++mask)
    {
        // Cost of buying the chosen requirements
        int requirement_cost = __builtin_popcount(mask);

        // Computers not covered by this mask must be bought individually
        int computers_to_buy = n - dp[mask];

        int total_cost = requirement_cost + computers_to_buy;
        min_cost = min(min_cost, total_cost);
    }

    return min_cost;
}

// Driver code matching the template structure from the platform
int main()
{
    // Optimize standard I/O operations for performance
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    if (cin >> n >> m)
    {
        vector<string> r(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> r[i];
        }
        cout << get_ans(n, m, r) << "\n";
    }
    return 0;
}

/*


*/