#include <bits/stdc++.h>
using namespace std;

int f(int index, int prev_index, int arr[], int n)
{
    if (index == n)
        return 0;
    int len = 0 + f(index + 1, prev_index, arr, n);

    if (prev_index == -1 || arr[index] > arr[prev_index])
    {
        len = max(len, 1 + f(index + 1, index, arr, n));
    }

    return len;
}

int longestIncreasingSubsquence(int arr[], int n)
{
    return f(0, -1, arr, n);
}