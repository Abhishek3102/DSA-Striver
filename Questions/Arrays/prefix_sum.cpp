#include <bits/stdc++.h>
using namespace std;

int findPreSum(vector<int> arr, int l, int r)
{
    int n = arr.size();
    int sum = 0;
    vector<int> prefix(n);
    prefix[0] = arr[0];
    for (int i = 1; i < n; i++)
    {
        prefix[i] = prefix[i - 1] + arr[i];
    }
    if (l == 0)
    {
        sum = prefix[r];
    }
    else
    {
        sum = prefix[r] - prefix[l - 1];
    }
    return sum;
}

int main()
{
    vector<int> arr = {10, -2, 3, 1};
    int l = 1, r = 3;
    cout << findPreSum(arr, l, r);
    return 0;
}

// arr = {3, 1, 4, 1, 5}
// Query: L = 0, R = 2
// 3 + 1 + 4 = 8