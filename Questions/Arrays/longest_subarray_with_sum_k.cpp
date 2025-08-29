#include <bits/stdc++.h>
using namespace std;

// contiguous part of the array is called subarray
int find_longest_subArr(int arr[], int n, int num)
{
    // total tc : O(N^2)
    int length = 0;
    for (int i = 0; i < n; i++) // tc : O(N)
    {
        int sum = 0;
        for (int j = i; j < n; j++) // tc : O(N)
        {
            sum += arr[j];
            if (sum == num)
            {
                length = max(length, j - i + 1);
            }
        }
    }
    cout << "Length is : " << length << endl;
    return length;
}

int longestSubarrayWithSumKBetter(vector<int> arr, long long k)
{
    // tc : O(N * log N) N for iteration and log N for using ordered map(hashmap)
    // if unordered map is used then tc can be O(N * 1) but in worst can that 1 can become N when it has a lot of collisions, so tc in worst case is O(N^2)
    // sc : O(N)

    // If prefixSumMap[10] = 2, this means:
    //  "The first time the cumulative sum became 10 was at index 2."
    //  Later, if at index 6, the running sum is 15, and you want a subarray that sums to 5,
    //  you'd check if 15 - 5 = 10 exists. Since it does at index 2, the subarray from index 3 to 6 sums to 5.
    map<long long, int> prefixSumMap; // Stores {prefix_sum, first_index_where_it_occurs}.

    // It holds the cumulative sum of the array elements as you iterate through the array.
    // For each index i, it represents the sum of all elements from index 0 to i.
    long long sum = 0;

    /*
    Why prefix sum is used:
    It allows for constant-time calculation of the sum of any subarray using:
    sum(i to j) = prefixSum[j] - prefixSum[i - 1]

    In this logic:
    If you know prefixSum[j] = current sum and prefixSum[i - 1] = sum - k
    Then the subarray from i to j has sum = k.
    */

    int maxLength = 0; // Maximum length of subarray found with sum = k
    for (int i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
        // Case 1: If the prefix sum itself equals k, then the subarray from 0 to i has sum k
        if (sum == k)
        {
            maxLength = max(maxLength, i + 1); // i+1 elements from index 0 to i
        }

        // Case 2: Check if there's a prefix sum earlier such that
        // current_sum - earlier_prefix_sum = k
        // i.e., the subarray between that earlier index + 1 and i sums to k
        long long remaining = sum - k;

        // If such a prefix sum exists
        if (prefixSumMap.find(remaining) != prefixSumMap.end())
        {
            // Get the index where that prefix sum occurred
            int length = i - prefixSumMap[remaining];
            // Update the max length if this subarray is longer
            maxLength = max(maxLength, length);
        }

        // Store the current prefix sum in the map, if it's not already present
        // We only want to store the *first* occurrence because we want the *longest* subarray
        if (prefixSumMap.find(sum) == prefixSumMap.end())
        {
            prefixSumMap[sum] = i;
        }
    }
    return maxLength;
}

int longestSubarrayWithSumKOptimal(vector<int> arr, long long k)
{
    // study in detail self -> done
    // Left and right pointers for the sliding window
    int left = 0, right = 0;
    long long sum = arr[0];
    int maxLength = 0;
    int n = arr.size();

    // Iterate until the right pointer reaches the end
    while (right < n)
    {
        // If current window sum is greater than k, shrink the window from the left
        // until sum <= k
        while (left <= right && sum > k)
        {
            sum -= arr[left]; // remove the leftmost element from the sum
            left++;           // move the left boundary to the right
        }

        // If sum becomes equal to k, update maxLength if this window is longer
        if (sum == k)
        {
            maxLength = max(maxLength, right - left + 1);
        }
        // Move the right pointer to expand the window
        right++;

        // Add the new element to the sum if still within bounds
        if (right < n)
            sum += arr[right];
    }
    return maxLength;
    // for(int i = 0; i<arr.size(); i++){
    //     for(int j = i; j<arr.size(); j++){
    //         sum += arr[j];
    //         if(sum == k) i++;
    //     }
    // }
}

int main()
{
    // int n;
    // cin >> n;
    // int arr[n];                 // sc : O(1)
    // for (int i = 0; i < n; i++) // tc : O(N)
    // {
    //     cin >> arr[i];
    // }

    // int num;
    // cin >> num;

    // cout << find_longest_subArr(arr, n, num) << endl;

    vector<int> arr;
    long long k;

    // --- Static input  ---
    /*
    arr = {1, 2, 3, 1, 1, 1, 1};
    k = 5;
    */

    // --- User input ---
    int n;
    cout << "Enter number of elements in the array: ";
    cin >> n;

    cout << "Enter " << n << " elements: ";
    arr.resize(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    cout << "Enter the target sum k: ";
    cin >> k;

    int result = longestSubarrayWithSumKOptimal(arr, k);
    cout << "Length of the longest subarray with sum " << k << " is: " << result << endl;

    return 0;
}