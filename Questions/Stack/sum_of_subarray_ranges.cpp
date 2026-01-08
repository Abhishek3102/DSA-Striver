/*
  SUM OF SUBARRAY RANGES

  This code calculates the sum of ranges (max - min) for all subarrays.

  WHAT IT DOES:
  - For each subarray, find the maximum and minimum elements
  - Calculate range as (max - min) for each subarray
  - Sum all these ranges
  - Uses stack to find Previous/Next Greater and Previous/Next Smaller elements
  - Optimal approach uses contribution of each element to total sum

  INPUT:
  - Array of integers
  - Example: [1, 2, 3]

  OUTPUT:
  - Single integer: sum of ranges of all subarrays
  - Example: Subarrays [1]=0, [2]=0, [3]=0, [1,2]=1, [2,3]=1, [1,2,3]=2, Total=4
  - Brute force: iterate all subarrays and sum their ranges
*/

#include <bits/stdc++.h>
using namespace std;

// brute force
int findSumSubarrayRanges(int arr[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        int largest = arr[i];
        int smallest = arr[i];
        for (int j = i + 1; j < n; j++)
        {
            largest = max(largest, arr[j]);
            smallest = min(smallest, arr[j]);
            sum = sum + (largest - smallest);
        }
    }
    return sum;
}

// optimal - like sum of subarray minimum problem
// Function to calculate the total sum of subarray ranges (max - min for each subarray)
int findSumSubarrayRangesOptimal(int arr[], int n)
{
    // Arrays to store the index of the previous and next greater/smaller elements
    int prevGreater[n], nextGreater[n];
    int prevSmaller[n], nextSmaller[n];

    stack<int> st;

    // Initialize the previous and next greater elements with default values
    for (int i = 0; i < n; i++)
    {
        prevGreater[i] = -1;
        nextGreater[i] = n;
        prevSmaller[i] = -1;
        nextSmaller[i] = n;
    }

    // Find the previous and next greater elements for each index
    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && arr[st.top()] < arr[i])
        {
            nextGreater[st.top()] = i; // The next greater element for index st.top()
            st.pop();
        }
        if (!st.empty())
        {
            prevGreater[i] = st.top(); // The previous greater element for index i
        }
        st.push(i);
    }

    // Clear the stack for the next part
    while (!st.empty())
        st.pop();

    // Find the previous and next smaller elements for each index
    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && arr[st.top()] > arr[i])
        {
            nextSmaller[st.top()] = i; // The next smaller element for index st.top()
            st.pop();
        }
        if (!st.empty())
        {
            prevSmaller[i] = st.top(); // The previous smaller element for index i
        }
        st.push(i);
    }

    // Now calculate the total sum of subarray ranges using the information
    long long totalSum = 0;

    for (int i = 0; i < n; i++)
    {
        // Contribution of arr[i] as the maximum element
        long long maxContrib = (i - prevGreater[i]) * (nextGreater[i] - i);

        // Contribution of arr[i] as the minimum element
        long long minContrib = (i - prevSmaller[i]) * (nextSmaller[i] - i);

        // Add the contributions to the total sum
        totalSum += arr[i] * maxContrib - arr[i] * minContrib;
    }

    return totalSum;
}

int main()
{
    int arr[] = {2, 1, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = findSumSubarrayRangesOptimal(arr, n);
    cout << "Total sum of subarray ranges: " << result << endl;

    return 0;
}