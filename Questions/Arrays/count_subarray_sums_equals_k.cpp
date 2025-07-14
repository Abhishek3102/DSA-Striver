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

int main()
{
    int arr[] = {1, 5, -2, 4, 1, 2, 1, 1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 3;
    cout << "Number of subarrays: " << find_num_subarray_Sum_k_better(arr, n, target) << endl;
    return 0;
}
