// here we have to find max length of subarray where there are at most 2 types of numbers
// arr = [3 3 3 1 2 1 1 2 3 3 4], here the max length is 5 for subarray 1 2 1 1 2.

#include <bits/stdc++.h>
using namespace std;

int findMaxLength(vector<int> arr)
{
    int n = arr.size();
    int l = 0;
    int r = 0;
    int k = 2;
    int maxLength = 0;
    map<int, int> mpp;
    while (r < n)
    {
        mpp[arr[r]]++;

        if (mpp.size() > k)
        {
            while (mpp.size() > k)
            {
                mpp[arr[l]]--;

                if (mpp[arr[l]] == 0)
                    mpp.erase(arr[l]);
                l++;
            }
        }

        if (mpp.size() <= k)
        {
            maxLength = max(maxLength, r - l + 1);
        }
        r++;
    }
    return maxLength;
}

int main()
{
    int findMaxLength(vector<int> arr);
    vector<int> arr = {3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4};
    cout << findMaxLength(arr);
}