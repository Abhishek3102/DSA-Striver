#include <bits/stdc++.h>
using namespace std;

// my code, fell short, incorrect
int find_no_app_once(int arr[], int n)
{
    int xor1 = 0;
    int xor2 = 0;
    for (int i = 0; i < n; i++)
    {
        xor2 = xor2 ^ arr[i];
        xor1 = xor1 ^ (i + 1);
    }
    // xor1 = xor1 ^ n;
    return xor1 ^ xor2;
}

// optimal approach using xor
int find_no_app_once_optimal(int arr[], int n)
{
    // tc : O(N) & sc : O(1)
    int xor1 = 0;
    for (int i = 0; i < n; i++)
    {
        xor1 = xor1 ^ arr[i];
    }
    return xor1;
}

// brute force by linear search method
int find_no_app_once_brute(int arr[], int n)
{
    for (int i = 0; i < n; i++) // tc: O(N^2) coz nested for loop both till n & sc : 0(1)
    {
        int num = arr[i];
        int count = 0;
        for (int j = 0; j < n; j++)
        {
            if (arr[j] == num)
                count++;
        }
        if (count == 1)
            return num;
    }
    return -1;
}

int find_no_app_once_better(int arr[], int n)
{
    int maxi = arr[0];
    for (int i = 0; i < n; i++)
    {
        maxi = max(maxi, arr[i]);
    }
    int hash[maxi] = {0};
    for (int i = 0; i < n; i++)
    {
        hash[arr[i]]++;
    }
    for (int i = 0; i < n; i++)
    {
        if (hash[arr[i]] == 1)
            return arr[i];
    }
    return -1;
}

int find_no_app_once_better_map(int arr[], int n)
{
    map<int, int> mpp1;
    for (int i = 0; i < n; i++)
    {
        mpp1[arr[i]]++;
    }

    for (auto it : mpp1)
    {
        if (it.second == 1)
        {
            return it.first;
        }
    }
    return -1;

    // total tc : O(N log M) + O(N/2 + 1) where N is size of array and M is size of map which is (N/2 + 1)
    // sc : O(N/2 + 1)
}

int main()
{
    int n;
    cin >> n;
    int arr[n];                 // sc : O(1)
    for (int i = 0; i < n; i++) // tc : O(N)
    {
        cin >> arr[i];
    }

    cout << find_no_app_once_optimal(arr, n) << endl;
}