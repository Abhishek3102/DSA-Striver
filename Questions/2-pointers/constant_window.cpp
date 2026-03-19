// arr = [-1, 2 3 3 4 5 -1] k = 4. find max sum from window size k = 4

#include <bits/stdc++.h>
using namespace std;

int returnMaxSum(vector<int> arr, int k)
{
    int n = arr.size();
    if (k > n)
        return 0;

    int l = 0;
    int r = k - 1;
    int sum = 0;

    // Calculate initial window sum
    for (int i = l; i <= r; i++)
    {
        sum += arr[i];
    }

    int maxSum = sum;

    // Slide the window
    while (r < n - 1)
    {
        sum -= arr[l]; // remove left element
        l++;
        r++;
        sum += arr[r]; // add new right element
        maxSum = max(maxSum, sum);
    }

    return maxSum;
}

int main()
{
    vector<int> arr = {-1, 2, 3, 3, 4, 5, -1};
    int k = 4;
    cout << returnMaxSum(arr, k);
}