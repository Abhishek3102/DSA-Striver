#include <bits/stdc++.h>
using namespace std;

int findMaxConsecutive(int arr[], int n)
{
    int maxi = 0;
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == 1)
        {
            count++;
            maxi = max(maxi, count);
        }
        else
        {
            count = 0;
        }
    }
    return maxi;
}

// same using vector
int findMaxConseVec(vector<int> &nums)
{
    int maxi = 0;
    int count = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] == 1)
        {
            count++;
            maxi = max(maxi, count);
        }
        else
        {
            count = 0;
        }
    }
    return maxi;
}

int main()
{
    // int n;
    // cin >> n;
    // int arr[n];
    // for (int i = 0; i < n; i++)
    // {
    //     cin >> arr[i];
    // }

    // cout << findMaxConsecutive(arr, n) << endl;

    // Static input (Comment out if using dynamic input)
    /*
    vector<int> nums = {1, 1, 0, 1, 1, 1, 0, 1, 1};
    cout << "Maximum length of consecutive 1's: " << findMaxConseVec(nums) << endl;
    */

    // User input version
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter the elements of the array (0's and 1's only): ";
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    cout << "Maximum length of consecutive 1's: " << findMaxConseVec(nums) << endl;

    return 0;
}