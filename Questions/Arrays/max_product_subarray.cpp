#include <bits/stdc++.h>
using namespace std;

// brute force approach
int maxSubarrayProduct(int arr[], int n)
{
    // tc : ~ O(N^3)
    int maxi = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            int product = 1;
            for (int k = i; k <= j; k++)
            {
                product *= arr[k];
                maxi = max(product, maxi);
            }
        }
    }
    return maxi;
}

// better approach
int maxSubarrayProductBetter(vector<int> arr)
{
    // tc : O(N ^ 2)
    int n = arr.size();
    int maxi = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        int product = 1;
        for (int j = i; j < n; j++)
        {
            product *= arr[j];
            maxi = max(maxi, product);
        }
    }
    return maxi;
}

// optimal approach (observation based, check how many are psoitive and negative in given array)
int maxSubarrayProductOptimal(vector<int> arr)
{
    // tc : O(N)
    int n = arr.size();
    int prefix = 1, suffix = 1;
    int maxi = INT_MIN;
    for (int i = 0; i < n; i++)
    {

        if (prefix == 0)
            prefix = 1;
        if (suffix == 0)
            suffix = 1;

        prefix = prefix * arr[i];         // from the start
        suffix = suffix * arr[n - i - 1]; // from the end

        maxi = max(maxi, max(prefix, suffix));
    }
    return maxi;
}

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << maxSubarrayProductOptimal(arr) << endl;
    return 0;
}