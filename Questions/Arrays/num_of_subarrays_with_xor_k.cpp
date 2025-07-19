#include <bits/stdc++.h>
using namespace std;

// answer to be verified from this, doesn't give all subarrays
// https://www.geeksforgeeks.org/count-number-subarrays-xor-k/
int find_num_subarray_xor_k(vector<int> &arr, int k)
{
    int n = arr.size();
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            int xor_sum = 0;
            for (int l = i; l < j; l++)
            {
                xor_sum = xor_sum ^ arr[l];
            }
            if (xor_sum == k)
                count++;
        }
    }
    return count;
}

// better approach
int find_num_subarray_xor_k_better(vector<int> &arr, int k)
{
    int n = arr.size();
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        int xor_sum = 0;
        for (int j = i; j < n; j++)
        {
            xor_sum = xor_sum ^ arr[j];
            if (xor_sum == k)
                count++;
        }
    }
    return count;
}

// optimal approach using prefix XOR and hash map
int subarraysWithXOR_K(vector<int> a, int k)
{
    int xr = 0;
    map<int, int> mpp;
    mpp[xr]++; // Initialize with 0 XOR count i.e., {0,1}
    int count = 0;
    for (int i = 0; i < a.size(); i++)
    {
        xr = xr ^ a[i];

        // now that we have xr, we are looking for (xr ^ k) in the map
        int x = xr ^ k;
        // if x is present in the map, it means we have found some subarrays with
        // XOR equal to k
        count += mpp[x];
        mpp[xr]++; // Increment the count of current XOR in the map
    }
    return count;
}

int main()
{
    int n, k;
    cout << "Enter number of elements in the array: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements of the array:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "Enter the value of k: ";
    cin >> k;

    int result = find_num_subarray_xor_k(arr, k);
    cout << "Number of subarrays with XOR equal to " << k << " is: " << result << endl;

    return 0;
}