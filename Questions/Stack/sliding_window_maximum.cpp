/*
  SLIDING WINDOW MAXIMUM

  This code finds the maximum element in every sliding window of size k in an array.

  WHAT IT DOES:
  - Slides a window of size k through an array from left to right
  - For each window position, finds and returns the maximum element
  - Uses deque (double-ended queue) to maintain indices in decreasing order of values
  - Optimal solution runs in O(n) time and O(k) space

  INPUT:
  - Array of integers
  - Integer k (window size)
  - Example: [1, 3, -1, -3, 5, 3, 6, 7], k=3

  OUTPUT:
  - Array containing the maximum of each window
  - Example output: [3, 3, 5, 5, 6, 7]
  - Window [1,3,-1]→3, [3,-1,-3]→3, [-1,-3,5]→5, [-3,5,3]→5, [5,3,6]→6, [3,6,7]→7
*/

#include <bits/stdc++.h>
using namespace std;

list<int> findMaxInSlidingWindow(vector<int> &nums, int k)
{
    list<int> ls;
    int n = nums.size();

    // Iterate through the array, ensuring the window size is valid
    for (int i = 0; i <= n - k; i++)
    {
        int maxi = nums[i];

        // Find the maximum in the current window
        for (int j = i; j < i + k; j++)
        {
            maxi = max(maxi, nums[j]);
        }

        // Add the maximum of the current window to the list
        ls.push_back(maxi);
    }

    return ls;
}

// Optimal O(n) solution
list<int> findMaxInSlidingWindowOptimal(vector<int> &nums, int k)
{
    int n = nums.size();
    list<int> lst;
    deque<int> dq; // stores indices

    for (int i = 0; i < n; i++)
    {

        // Remove indices that are out of this window
        if (!dq.empty() && dq.front() <= i - k)
        {
            dq.pop_front();
        }

        // Maintain decreasing order in deque
        while (!dq.empty() && nums[dq.back()] <= nums[i])
        {
            dq.pop_back();
        }

        dq.push_back(i);

        // Window becomes valid when i >= k-1
        if (i >= k - 1)
        {
            lst.push_back(nums[dq.front()]);
        }
    }

    return lst;
}

int main()
{
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    list<int> result = findMaxInSlidingWindow(nums, k);
    for (int x : result)
    {
        cout << x << " ";
    }
    return 0;
}
