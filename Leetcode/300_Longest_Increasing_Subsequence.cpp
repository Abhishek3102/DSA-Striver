#include <bits/stdc++.h>
using namespace std;

// Recursive function to find the length of the
// Longest Increasing Subsequence (LIS)
//
// index      -> current element we are considering
// prev_index -> index of the previously selected element
// arr        -> input array
// n          -> size of the array
int f(int index, int prev_index, int arr[], int n)
{
    // Base case:
    // If we have reached the end of the array,
    // there are no more elements to choose.
    if (index == n)
        return 0;

    // Option 1: Don't include arr[index] in the subsequence
    //
    // Move to the next element while keeping the same
    // previous selected element.
    int len = 0 + f(index + 1, prev_index, arr, n);

    // Option 2: Include arr[index]
    //
    // We can include the current element if:
    // 1. We haven't selected any element yet (prev_index == -1)
    // OR
    // 2. Current element is greater than the previously selected element
    if (prev_index == -1 || arr[index] > arr[prev_index])
    {
        // Include arr[index], so:
        // - length increases by 1
        // - current index becomes the new previous index
        len = max(len, 1 + f(index + 1, index, arr, n));
    }

    // Return the maximum length obtained by either:
    // - skipping the current element
    // - taking the current element
    return len;
}

// Function to find the length of the
// Longest Increasing Subsequence
int longestIncreasingSubsquence(int arr[], int n)
{
    // Start from index 0.
    // prev_index = -1 means we haven't selected
    // any element yet.
    return f(0, -1, arr, n);
}
