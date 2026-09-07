#include <bits/stdc++.h>
using namespace std;

// brute force
int maxPts(vector<int> &arr, int k)
{
    int leftSum = 0, rightSum = 0, maxSum = 0;
    for (int i = 0; i < k; i++)
    {
        leftSum = leftSum + arr[i];
    }
    maxSum = leftSum;

    int rightIndex = arr.size() - 1;
    for (int i = k - 1; i >= 0; i--)
    {
        leftSum = leftSum - arr[i];
        rightSum = rightSum + arr[rightIndex];
        rightIndex = rightIndex - 1;
        maxSum = max(maxSum, leftSum + rightSum);
    }

    return maxSum;
}

/*

arr = [1, 2, 3, 4, 5, 6, 1]
k = 3

3 left, 0 right → 1 + 2 + 3 = 6
2 left, 1 right → 1 + 2 + 1 = 4
1 left, 2 right → 1 + 1 + 6 = 8
0 left, 3 right → 1 + 6 + 5 = 12
*/