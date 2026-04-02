#include <bits/stdc++.h>
using namespace std;

int findSubarrayWithKDifferentInt(vector<int> arr, int k)
{
    int l = 0, r = 0, n = arr.size(), count = 0;
    map<int, int> mpp;
    while (r < n)
    {
        mpp[arr[r]]++;

        while (mpp.size() <= k)
        {
            mpp[arr[l]]--;

            if (mpp[arr[l]] == 0)
                mpp.erase(arr[l]);
            l = l - 1;
        }

        count = count + (r - l + 1);
        r = r + 1;
    }
    return count;
}

int main()
{
    int findSubarrayWithKDifferentInt(vector<int> arr, int k);
    vector<int> arr = {1, 2, 1, 3, 4};
    int k = 3;
    cout << findSubarrayWithKDifferentInt(arr, k) - findSubarrayWithKDifferentInt(arr, k - 1);
    return 0;
}