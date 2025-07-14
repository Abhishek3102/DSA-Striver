// #include <bits/stdc++.h>
// using namespace std;

// int find_num_subarray_Sum_k(int arr[], int n, int target)
// {
//     int count = 0;
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = i; j < n; j++)
//         {
//             int sum = 0;
//             for (int k = i; k <= j; k++)
//             {
//                 sum = sum + arr[k];
//             }
//             if (sum == target)
//                 count++;
//         }
//     }
//     return count;
// }

// int main()
// {
//     int arr[] = {1, 5, -2, 4, 1, 2, 1, 1, 1};
//     int n = sizeof(arr) / sizeof(arr[0]);
//     int target = 3;
//     cout << find_num_subarray_Sum_k(arr, n, target) << endl; // Output: 2
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

// returns the number of times sum is reached in the subarray
int find_num_subarray_Sum_k(int arr[], int n, int target)
{
    int count = 0;
    for (int i = 0; i < n; i++) // Start of the subarray
    {
        for (int j = i; j < n; j++) // End of the subarray
        {
            int sum = 0;
            for (int k = i; k <= j; k++) // Sum the subarray
            {
                sum = sum + arr[k];
            }
            cout << "Subarray: ";
            for (int k = i; k <= j; k++) // Print the subarray
            {
                cout << arr[k] << " ";
            }
            cout << "Sum: " << sum << endl;

            if (sum == target)
                count++;
        }
    }
    return count;
}
int find_num_subarray_Sum_k_better(int arr[], int n, int target)
{
    int count = 0;
    for (int i = 0; i < n; i++) // Start of the subarray
    {
        int sum = 0;
        for (int j = i; j < n; j++) // End of the subarray
        {
            sum = sum + arr[j];

            cout << "Subarray: ";
            for (int j = i; j <= i; j++) // Print the subarray
            {
                cout << arr[j] << " ";
            }
            cout << "Sum: " << sum << endl;

            if (sum == target)
                count++;
        }
    }
    return count;
}

int findAllSubarraysWithGivenSumOptimal(vector<int> &arr, int k)
{
    // Step 1: Declare a map to store the frequency of prefix sums
    map<int, int> mpp;

    // Step 2: Initialize the map with {0: 1}.
    // This is because a prefix sum of 0 means a valid subarray can start from index 0 itself if the sum equals `k`.
    mpp[0] = 1;

    // Step 3: Initialize variables for prefix sum and the result count
    int preSum = 0, count = 0;

    // Step 4: Iterate through the array to calculate prefix sums and count subarrays with sum `k`
    for (int i = 0; i < arr.size(); i++)
    {

        // Step 5: Add the current element to the prefix sum
        preSum += arr[i];

        // Step 6: Calculate the difference (remove) between current prefix sum and target sum `k`
        // This represents the sum that should have existed earlier in the array for the subarray sum to be `k`
        int remove = preSum - k;

        // Step 7: If this difference (remove) exists in the map, it means we've seen a prefix sum before
        // that, when subtracted from the current prefix sum, gives the target sum `k`
        count += mpp[remove];

        // Step 8: Update the map with the current prefix sum.
        // It helps to count how many times we've seen this prefix sum
        mpp[preSum] += 1;
    }

    // Step 9: Return the final count of subarrays with sum `k`
    return count;
}

int main()
{
    int arr[] = {1, 5, -2, 4, 1, 2, 1, 1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 3;
    cout << "Number of subarrays: " << find_num_subarray_Sum_k_better(arr, n, target) << endl;
    return 0;
}
