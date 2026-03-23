// this is similar to count subarray sum equals k which was an array question.
// there the optimal approach was using map, to check a target which pre-existed
// but here we get rid of map due to extra space and we use 2-pointer and sliding window

#include <bits/stdc++.h>
using namespace std;

int findBinarySubarrayWiSum(vector<int> &arr, int k)
{
    int n = arr.size();
    if (k < 0)
        return 0;
    int l = 0, r = 0;
    int sum = 0;
    int count = 0;
    while (r < n)
    {
        sum += arr[r];

        while (sum > k)
        {
            sum = sum - arr[l];
            l = l + 1;
        }
        count = count + (r - l + 1);
        r = r + 1;
    }
    return count;
}

int main()
{
    vector<int> arr = {1, 0, 0, 1, 1, 0};
    int k = 2;
    cout << findBinarySubarrayWiSum(arr, k) - findBinarySubarrayWiSum(arr, k - 1) << endl;
    cout << findBinarySubarrayWiSum(arr, 2) << endl;
    cout << findBinarySubarrayWiSum(arr, 1) << endl;
    return 0;
}