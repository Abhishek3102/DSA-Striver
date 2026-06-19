// here an array will be given and number of painters will be given.
// each painter should get a chance to paint atleast one element of array.
// also a painter can only paint consecutive part of the array which is basically the subarray.
// here we have to try all possible subarray combinations and find the max of each subarray.
// then choose the combination whose sum of max subarray is minimum.
// eg : [10 20 30 40] and k = 2 (no. of painters)
// [10]  [20 30 40] -> sum of max subarray is 20+30+40 = 90
// [10 20]  [30 40] -> sum = 30 + 40 = 70
// [10 20 30]  [40] -> sum = 10 + 20 + 30 = 60 so this combinations will be chosen as it returns minimum sum.
// also we have to split arrays into given k number of subarrays.

#include <bits/stdc++.h>
using namespace std;

/*
    Given a maximum amount of work (k),
    determine how many painters are required.

    Each painter can only paint a consecutive
    sequence of boards (subarray).

    We greedily assign boards to the current painter
    until adding another board would exceed k.
    Then we allocate a new painter.
*/
int countPainter(vector<int> &arr, int k)
{
    int n = arr.size();

    // At least one painter is always needed.
    int painters = 1;

    // Current workload assigned to the current painter.
    long long colors = 0;

    for (int i = 0; i < n; i++)
    {
        // If current board can be assigned to the
        // current painter without exceeding limit k.
        if (colors + arr[i] <= k)
        {
            colors += arr[i];
        }
        else
        {
            // Need a new painter.
            painters++;

            // Start the new painter with current board.
            colors = arr[i];
        }
    }

    return painters;
}

/*
    Find the minimum possible maximum workload
    among all painters.

    l = number of boards
    m = number of painters

    Binary Search Range:
    --------------------
    low  = largest board length
           (because some painter must paint it)

    high = sum of all board lengths
           (one painter paints everything)

    We binary search for the smallest feasible
    maximum workload.
*/
int findPainters(vector<int> &arr, int l, int m)
{
    // More painters than boards is invalid because
    // every painter must paint at least one board.
    if (m > l)
        return -1;

    // Minimum possible answer.
    int low = *max_element(arr.begin(), arr.end());

    // Maximum possible answer.
    int high = accumulate(arr.begin(), arr.end(), 0);

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        // Number of painters required if no painter
        // is allowed to paint more than 'mid' work.
        int painters = countPainter(arr, mid);

        if (painters > m)
        {
            /*
                Too many painters are needed.

                This means the workload limit (mid)
                is too small, so increase it.
            */
            low = mid + 1;
        }
        else
        {
            /*
                We can paint everything using
                <= m painters.

                Try to reduce the maximum workload
                further and search on left side.
            */
            high = mid - 1;
        }
    }

    /*
        low will point to the smallest feasible
        maximum workload.
    */
    return low;
}

/*
    Wrapper function.
*/
int findLargestMinAllocation(vector<int> &houses, int x)
{
    return findPainters(houses, houses.size(), x);
}

int main()
{
    vector<int> arr = {10, 20, 30, 40};
    int painters = 2;

    cout << findLargestMinAllocation(arr, painters);

    return 0;
}