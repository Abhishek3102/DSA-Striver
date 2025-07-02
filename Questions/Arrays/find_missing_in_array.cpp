#include <bits/stdc++.h>
using namespace std;

int find_missing(int arr[], int n)
{
    // tc : O(N*N) = O(N^2) & sc : O(1)
    for (int i = 1; i < n; i++)
    {
        int flag = 0;
        for (int j = 0; j < n - 1; j++)
        {
            if (arr[j] == i)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            return i;
        }
    }
}

int find_missing_better(int arr[], int n)
{
    int hash[n + 1] = {0};      // sc : O(N) coz array on N size is used
    for (int i = 0; i < n; i++) // tc: O(N)
    {
        hash[arr[i]] = 1;
    }

    for (int i = 1; i < n; i++) // tc : O(N)
    {
        if (hash[i] == 0)
            return i;
    }
}

int find_missing_optimal1(int arr[], int n)
{
    int sum = n * (n + 1) / 2; // sc : O(1)
    int s2 = 0;
    for (int i = 0; i < n - 1; i++) // tc : O(N)
    {
        s2 += arr[i];
    }
    return sum - s2;
}

int find_missing_zor_optimal(int arr[], int n)
{
    /*
    int XOR1 = 0;
    for (int i = 1; i < n; i++)
    {
        XOR1 = XOR1 ^ i;
        int XOR2 = 0;


        for (int i = 0; i < n - 1; i++)
        {
            XOR2 = XOR2 ^ arr[i];
        }
        return XOR1 ^ XOR2;
    }
    */

    int xor1 = 0;
    int xor2 = 0;
    for (int i = 0; i < n - 1; i++)
    {
        xor2 = xor2 ^ arr[i];
        xor1 = xor1 ^ (i + 1);
    }
    xor1 = xor1 ^ n;
    return xor1 ^ xor2;
}

int main()
{
    int n;
    cin >> n;
    int arr[n - 1];                 // sc : O(1)
    for (int i = 0; i < n - 1; i++) // tc : O(N)
    {
        cin >> arr[i];
    }
    cout << find_missing_zor_optimal(arr, n);
    return 0;
}