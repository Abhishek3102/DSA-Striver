#include <bits/stdc++.h>
using namespace std;

int maxSubarrayBrute(int arr[], int n, int num)
{
    // tc : O(N^3)
    int maxi = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            int sum = 0;
            for (int k = i; k <= j; k++)
            {
                sum += arr[k];
                maxi = max(sum, maxi);
            }
        }
    }
    return maxi;
}

int maxSubarrayBetter(int arr[], int n, int num)
{
    // tc : O(N^2)
    int maxi = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = i; j < n; j++)
        {

            sum += arr[j];
            maxi = max(sum, maxi);
        }
    }
    return maxi;
}

long long maxSubarraySumOptimal(int arr[], int n)
{
    long long sum = 0;
    long long maxi = LONG_LONG_MIN;
    int start = 0, ansStart = -1, ansEnd = -1;
    for (int i = 0; i < n; i++)
    {
        if (sum == 0)
            start = i;
        sum += arr[i];

        if (sum > maxi)
        {
            maxi = sum;
            ansStart = start, ansEnd = i;
        }

        if (sum < 0)
        {
            sum = 0;
        }
    }
    cout << "Subarray with max sum: ";
    for (int i = ansStart; i <= ansEnd; i++)
        cout << arr[i] << " ";
    cout << endl;
    return maxi;
}

int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << maxSubarraySumOptimal(arr, n) << endl;
    return 0;
}