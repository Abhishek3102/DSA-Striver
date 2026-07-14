/*

2. Missing Number in Arithmetic ProgressionProblem: You are given an array representing an arithmetic progression where exactly one element is
missing. Find the missing element.Logic: The common difference $d$ can be found using the first and last element:
d = arr[n-1] - arr[0] / n. Use a modified binary search or linear check to find where the gap occurs.

*/

#include <bits/stdc++.h>
using namespace std;

int findMissingInAP(vector<int> &arr)
{
    int n = arr.size();
    int d = (arr[n - 1] - arr[0]) / n;
    int low = 0, high = n - 1;
    while (low < high)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] == arr[0] + mid * d)
            low = mid + 1;
        else
            high = mid;
    }
    return arr[0] + low * d;
}