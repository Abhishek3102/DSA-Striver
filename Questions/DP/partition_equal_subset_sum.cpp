#include <bits/stdc++.h>
using namespace std;

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

bool canPartition(vector<int> &arr, int n)
{
    int totalSum = 0;
    for (int i = 0; i < n; i++)
    {
        totalSum += arr[i];
    }

    if (totalSum % 2)
        return false;
    int target = totalSum / 2;

    return subsetSumTab(n, target, arr);
}

/*

```
#include <bits/stdc++.h>
using namespace std;

/*
    ============================================================
                    SUBSET SUM - TABULATION
    ============================================================

    This function checks whether there exists a subset of the
    given array whose sum is exactly equal to 'k'.

    We use Dynamic Programming with SPACE OPTIMIZATION.

    Normal 2D DP would look like:

        dp[index][target]

    But each row only depends on the previous row:

        dp[index - 1][...]

    Therefore, instead of storing the complete 2D table,
    we only maintain two arrays:

        prev -> DP results for the previous index
        cur  -> DP results for the current index

    Time Complexity:
        O(n * k)

    Space Complexity:
        O(k)
*/

bool subsetSumTab(int n, int k, vector<int> &arr)
{
    /*
        'prev[target]' tells us whether we can form
        the sum 'target' using the elements processed
        so far.

        We have targets from:

            0 to k

        Therefore, size of prev is k + 1.

        Initially, every value is false.
    */
    vector<bool> prev(k + 1, false);

    /*
        BASE CASE:

        Sum = 0 is always possible.

        Why?

        Because we can always choose an empty subset.

        For example:

            arr = {2, 3, 7}

        We can make sum 0 by choosing nothing.

        Therefore:

            prev[0] = true;
    */
    prev[0] = true;

    /*
        Handle the first element separately.

        If arr[0] itself is less than or equal to k,
        then we can create the subset:

            {arr[0]}

        whose sum is arr[0].

        Example:

            arr[0] = 5
            k = 10

        Then:

            prev[5] = true;
    */
    if (arr[0] <= k)
    {
        prev[arr[0]] = true;
    }

    /*
        Now process the remaining elements.

        We start from index 1 because index 0 has
        already been handled above.
    */
    for (int ind = 1; ind < n; ind++)
    {
        /*
            'cur[target]' represents whether we can
            form 'target' using elements from:

                arr[0] ... arr[ind]

            Initially, assume no target can be formed.
        */
        vector<bool> cur(k + 1, false);

        /*
            Sum 0 is always possible.

            Even after considering more elements,
            we can still choose the empty subset.
        */
        cur[0] = true;

        /*
            Try to form every possible target from
            1 to k.
        */
        for (int target = 1; target <= k; target++)
        {
            /*
                ------------------------------------------------
                OPTION 1: DON'T TAKE arr[ind]
                ------------------------------------------------

                If we don't take the current element,
                then we simply use the answer from the
                previous row.

                So if:

                    prev[target] == true

                it means we were already able to form
                'target' without using arr[ind].

                Therefore:

                    notTake = prev[target]
            */
            bool notTake = prev[target];

            /*
                ------------------------------------------------
                OPTION 2: TAKE arr[ind]
                ------------------------------------------------

                Suppose:

                    target = 10
                    arr[ind] = 3

                If we take 3, then we still need:

                    10 - 3 = 7

                from the previous elements.

                Therefore, we check:

                    prev[target - arr[ind]]

                If this is true, then we can take arr[ind]
                and form the required target.
            */
            bool take = false;

            /*
                We can only take arr[ind] if it is less than
                or equal to the current target.

                Example:

                    target = 5
                    arr[ind] = 7

                We cannot take 7 because it is already
                greater than the target 5.
            */
            if (arr[ind] <= target)
            {
                take = prev[target - arr[ind]];
            }

            /*
                If either of the two choices works:

                    1. Don't take arr[ind]
                    2. Take arr[ind]

                then target can be formed.

                Therefore:

                    cur[target] = take || notTake;
            */
            cur[target] = take || notTake;
        }

        /*
            We have finished processing the current element.

            'cur' now contains all the answers for elements
            from index 0 to index 'ind'.

            For the next element, this current row becomes
            the previous row.

            Therefore:

                prev = cur;
        */
        prev = cur;
    }

    /*
        Finally, we need to know whether the target 'k'
        can be formed.

        If:

            prev[k] == true

        then a subset with sum exactly equal to k exists.

        Otherwise, no such subset exists.
    */
    return prev[k];
}

/*
    ============================================================
                    PARTITION EQUAL SUBSET SUM
    ============================================================

    Problem:

    Given an array, determine whether it can be divided
    into TWO subsets such that both subsets have the
    SAME SUM.

    Example:

        arr = {1, 5, 11, 5}

        Total sum = 1 + 5 + 11 + 5
                  = 22

        Half = 22 / 2
             = 11

        We can divide the array as:

            Subset 1 = {11}
            Sum      = 11

            Subset 2 = {1, 5, 5}
            Sum      = 11

        Therefore, answer is TRUE.
*/

bool canPartition(vector<int> &arr, int n)
{
    /*
        --------------------------------------------------------
        STEP 1: Calculate the total sum of the array
        --------------------------------------------------------
    */
    int totalSum = 0;

    for (int i = 0; i < n; i++)
    {
        totalSum += arr[i];
    }

    /*
        --------------------------------------------------------
        STEP 2: Check whether total sum is EVEN
        --------------------------------------------------------

        Suppose the array is divided into two subsets:

            subset1 + subset2 = totalSum

        For equal partition:

            subset1 = subset2

        Therefore:

            subset1 + subset1 = totalSum

            2 * subset1 = totalSum

            subset1 = totalSum / 2

        So totalSum must be EVEN.

        Example:

            totalSum = 10

            Each subset must have:
                10 / 2 = 5

        But if:

            totalSum = 11

        Then:

            11 / 2 = 5.5

        Since array elements are integers, we cannot
        have two subsets with sum 5.5.

        Therefore, if totalSum is odd, immediately return false.
    */
    if (totalSum % 2 != 0)
    {
        return false;
    }

    /*
        --------------------------------------------------------
        STEP 3: Calculate the required target
        --------------------------------------------------------

        Since the total sum is even, both subsets must have:

            totalSum / 2

        as their sum.

        So instead of directly finding two subsets,
        we only need to find ONE subset whose sum is
        equal to totalSum / 2.

        The remaining elements will automatically have
        the same sum.
    */
    int target = totalSum / 2;

    /*
        --------------------------------------------------------
        STEP 4: Solve the Subset Sum problem
        --------------------------------------------------------

        We now ask:

            "Can we select some elements from arr
             whose sum is exactly equal to target?"

        If yes:

            subset1 = target
            subset2 = totalSum - target
                     = target

        Therefore, both subsets have equal sum.

        If no, equal partition is impossible.
    */
    return subsetSumTab(n, target, arr);
}

/*
    ============================================================
                            MAIN
    ============================================================

    This main function is only for testing the solution.

    You can remove main() if the coding platform already
    provides its own main function.
*/

int main()
{
    /*
        Example array:

            {1, 5, 11, 5}

        Total sum = 22

        Required subset sum = 11

        Possible partition:

            {11}
            {1, 5, 5}

        Both have sum 11.
    */
    vector<int> arr = {1, 5, 11, 5};

    /*
        Number of elements in the array.
    */
    int n = arr.size();

    /*
        Call canPartition() to check whether the array
        can be divided into two subsets having equal sum.
    */
    bool answer = canPartition(arr, n);

    /*
        Print the result.

        If answer is true, print 1.
        If answer is false, print 0.
    */
    cout << answer << endl;

    return 0;
}
/*
```

 ### Core idea to remember

```
Total Sum
    |
    |-- Odd --> false
    |
    |-- Even
          |
          v
    target = totalSum / 2
          |
          v
    Subset Sum(target)
          |
       /     \
     true    false
      |        |
    true     false
```

 The most important DP transition is:

```
bool notTake = prev[target];

bool take = false;

if (arr[ind] <= target)
{
    take = prev[target - arr[ind]];
}

cur[target] = take || notTake;
```

 This is simply:

 > **For every element, either take it or don't take it.**

*/