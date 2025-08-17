// here from given array, find all subsets. i.e, power set.
// so if n is the size of array, the total number of power sets or subsets will be 2^n.

// code 1 :
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> subsetsIterative(vector<int> &nums)
{
    // Start with the empty subset
    vector<vector<int>> result = {{}};

    // For each number in the input array
    for (int num : nums)
    {
        int n = result.size(); // Current number of subsets in result

        // For each existing subset in result
        for (int i = 0; i < n; ++i)
        {
            // Make a copy of the current subset
            vector<int> subset = result[i];

            // Add the current number to the copy
            subset.push_back(num);

            // Add the new subset to the result
            result.push_back(subset);
        }
    }

    return result;
}

// code 2 :

vector<vector<int>> subsetsBitmasking(vector<int> &nums)
{
    int n = nums.size();        // Number of elements in input
    int total = 1 << n;         // Total subsets = 2^n
    vector<vector<int>> result; // To store all subsets

    // Iterate over all possible bitmasks from 0 to 2^n - 1
    for (int mask = 0; mask < total; ++mask)
    {
        vector<int> subset;

        // For each bit position, check if it's set in the mask
        for (int i = 0; i < n; ++i)
        {
            // If the i-th bit is set, include nums[i] in the subset
            if (mask & (1 << i))
            {
                subset.push_back(nums[i]);
            }
        }

        // Add the formed subset to the result
        result.push_back(subset);
    }

    return result;
}

int main()
{
    vector<int> nums = {1, 2, 3};                         // Input array
    vector<vector<int>> result = subsetsBitmasking(nums); // Get all subsets

    // vector<vector<int>> result = subsetsIterative(nums); for code 1

    // Print all subsets
    for (auto &subset : result)
    {
        cout << "[";
        for (int x : subset)
            cout << x << " ";
        cout << "]\n";
    }

    return 0;
}
