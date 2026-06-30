// arr = [-1, 2 3 3 4 5 -1] k = 4. find max sum from window size k = 4

/*
Problem:
Given an array of integers and an integer k,
find the maximum sum of any contiguous subarray of size k.

Approach:
Use Sliding Window technique:
1. Compute sum of first window of size k.
2. Slide the window by one element at a time.
3. Update sum by removing left element and adding right element.
4. Track maximum sum during the process.
*/

#include <bits/stdc++.h>
using namespace std;

int returnMaxSum(vector<int> arr, int k)
{
    int n = arr.size();

    // If window size is larger than array, no valid result
    if (k > n)
        return 0;

    int l = 0;     // left pointer of window
    int r = k - 1; // right pointer of window
    int sum = 0;   // current window sum

    // Step 1: Calculate sum of first window [0 ... k-1]
    for (int i = l; i <= r; i++)
    {
        sum += arr[i];
    }

    int maxSum = sum; // store maximum sum found so far

    // Step 2: Slide the window across the array
    while (r < n - 1)
    {
        // Remove the element going out of the window
        sum -= arr[l];
        l++;

        // Move right boundary of window
        r++;

        // Add the new element entering the window
        sum += arr[r];

        // Update maximum sum
        maxSum = max(maxSum, sum);
    }

    return maxSum;
}

int main()
{
    vector<int> arr = {-1, 2, 3, 3, 4, 5, -1};
    int k = 4;

    cout << returnMaxSum(arr, k); // Output: 15 (subarray [2,3,3,4] or [3,3,4,5] -> 15)
}