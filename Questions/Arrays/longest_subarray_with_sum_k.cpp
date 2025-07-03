#include <bits/stdc++.h>
using namespace std;

// contiguous part of the array is called subarray
int find_longest_subArr(int arr[], int n, int num)
{
    // total tc : O(N^2)
    int length = 0;
    for (int i = 0; i < n; i++) // tc : O(N)
    {
        int sum = 0;
        for (int j = i; j < n; j++) // tc : O(N)
        {
            sum += arr[j];
            if (sum == num)
            {
                length = max(length, j - i + 1);
            }
        }
    }
    cout << "Length is : " << length << endl;
    return length;
}

int longestSubarrayWithSumKBetter(vector<int> arr, long long k)
{
    // tc : O(N * log N) N for iteration and log N for using ordered map(hashmap)
    // if unordered map is used then tc can be O(N * 1) but in worst can that 1 can become N when it has a lot of collisions, so tc in worst case is O(N^2)
    // sc : O(N)
    map<long long, int> prefixSumMap;
    long long sum = 0;
    int maxLength = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
        if (sum == k)
        {
            maxLength = max(maxLength, i + 1);
        }

        long long remaining = sum - k;
        if (prefixSumMap.find(remaining) != prefixSumMap.end())
        {
            int length = i - prefixSumMap[remaining];
            maxLength = max(maxLength, length);
        }
        if (prefixSumMap.find(sum) == prefixSumMap.end())
        {
            prefixSumMap[sum] = i;
        }
    }
    return maxLength;
}

int longestSubarrayWithSumKOptimal(vector<int> arr, long long k)
{
    // study in detail self
    int left = 0, right = 0;
    long long sum = arr[0];
    int maxLength = 0;
    int n = arr.size();

    while (right < n)
    {
        while (left <= right && sum > k)
        {
            sum -= arr[left];
            left++;
        }

        if (sum == k)
        {
            maxLength = max(maxLength, right - left + 1);
        }
        right++;
        if (right < n)
            sum += arr[right];
    }
    return maxLength;
    // for(int i = 0; i<arr.size(); i++){
    //     for(int j = i; j<arr.size(); j++){
    //         sum += arr[j];
    //         if(sum == k) i++;
    //     }
    // }
}

int main()
{
    // int n;
    // cin >> n;
    // int arr[n];                 // sc : O(1)
    // for (int i = 0; i < n; i++) // tc : O(N)
    // {
    //     cin >> arr[i];
    // }

    // int num;
    // cin >> num;

    // cout << find_longest_subArr(arr, n, num) << endl;

    vector<int> arr;
    long long k;

    // --- Static input  ---
    /*
    arr = {1, 2, 3, 1, 1, 1, 1};
    k = 5;
    */

    // --- User input ---
    int n;
    cout << "Enter number of elements in the array: ";
    cin >> n;

    cout << "Enter " << n << " elements: ";
    arr.resize(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    cout << "Enter the target sum k: ";
    cin >> k;

    int result = longestSubarrayWithSumKOptimal(arr, k);
    cout << "Length of the longest subarray with sum " << k << " is: " << result << endl;

    return 0;
}