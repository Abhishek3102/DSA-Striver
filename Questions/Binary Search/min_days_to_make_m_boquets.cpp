/*
Problem: Minimum Days to Make M Bouquets

Description:
You are given an array 'bloomDay' where bloomDay[i] represents the day the ith flower will bloom.
You are also given two integers 'm' and 'k'.

You need to make 'm' bouquets.
To make one bouquet, you need 'k' **adjacent** flowers that have bloomed (i.e., bloomDay[i] <= current day).

Your task is to return the **minimum number of days** needed to make all 'm' bouquets.
If it's not possible to make m bouquets with the given flowers, return -1.

Approach:
Use Binary Search on the number of days (range: min(bloomDay) to max(bloomDay)).
For each mid day, use a helper function to check if it's possible to make m bouquets.
If yes, try to find a smaller day (search left); otherwise, search right.

Time Complexity: O(N * log M), where:
- N is the number of flowers,
- M is the range between minimum and maximum bloom days.
*/

#include <bits/stdc++.h>
using namespace std;

// Checks if we can make m bouquets on a given day using count / k logic
bool possible(vector<int> arr, int day, int m, int k)
{
    int n = arr.size();
    int count = 0;       // To count how many consecutive flowers have bloomed (i.e., bloomDay[i] <= day)
    int noOfBoquets = 0; // To count how many bouquets we can make on this day

    for (int i = 0; i < n; i++)
    {
        // If the flower has bloomed on or before the given 'day'
        if (arr[i] <= day)
        {
            count++; // Increase count of consecutive bloomed flowers
        }
        else
        {
            // Once we hit a flower that hasn't bloomed, we can't extend the current group
            // So we compute how many full bouquets we can make from the previous group
            noOfBoquets += (count / k); // Integer division: only full groups of k flowers count
            count = 0;                  // Reset count for the next group
        }
    }

    // After the loop, handle any remaining group at the end of the array
    noOfBoquets += (count / k); // e.g., if count = 5 and k = 2 ⇒ 5 / 2 = 2 bouquets from the final group

    return noOfBoquets >= m;
}

// Main brute-force logic
int minDays(vector<int> arr, int m, int k)
{
    int n = arr.size();
    if (n < m * k)
        return -1;

    int mini = *min_element(arr.begin(), arr.end());
    int maxi = *max_element(arr.begin(), arr.end());

    for (int i = mini; i <= maxi; i++)
    {
        if (possible(arr, i, m, k))
            return i;
    }

    return -1;
}

// tc : O(N * log base 2(maxi - mini + 1))
int bs(vector<int> arr, int m, int k)
{
    int n = arr.size();
    int maxi = *max_element(arr.begin(), arr.end());
    int mini = *min_element(arr.begin(), arr.end());
    int low = mini, high = maxi;

    int ans = high; // this ans variable can be avoided and answer will be returned by low.

    long long productNumFlowAndAdjacentFlow = m * 1LL * k * 1LL;

    if (n < productNumFlowAndAdjacentFlow)
        return -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (possible(arr, mid, m, k))
        {
            ans = mid;
            high = mid - 1; // eliminate right half
        }

        else
        {
            low = mid + 1; // eliminate left half
        }
    }
    return ans;
    // return low; this will also provide the answer
}

int main()
{
    vector<int> bloomDay = {1, 10, 3, 10, 2};
    int m = 3, k = 1;

    cout << bs(bloomDay, m, k) << endl;

    return 0;
}
