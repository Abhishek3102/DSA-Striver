/*

A peak element is an element that is strictly greater than its neighbors.
Given a 0-indexed integer array nums, find a peak element, and return its index. If the array contains multiple peaks, return the index to any of the peaks.
You may imagine that nums[-1] = nums[n] = -∞. In other words, an element is always considered to be strictly greater than a neighbor that is outside the array.
You must write an algorithm that runs in O(log n) time.



Example 1:

Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the index number 2.
Example 2:

Input: nums = [1,2,1,3,5,6,4]
Output: 5
Explanation: Your function can return either index number 1 where the peak element is 2, or index number 5 where the peak element is 6.


Constraints:
1 <= nums.length <= 1000
-231 <= nums[i] <= 231 - 1
nums[i] != nums[i + 1] for all valid i.

*/

class Solution
{
public:
    int findPeakElement(vector<int> &nums)
    {
        int low = 0, high = nums.size() - 1; // Initialize search space from 0 to n-1

        while (low <= high)
        {
            int mid = low + (high - low) / 2; // Calculate mid index to divide the array

            // Case 1: Check if the current mid element is a peak
            if ((mid == 0 || nums[mid] > nums[mid - 1]) &&             // Handle left boundary
                (mid == nums.size() - 1 || nums[mid] > nums[mid + 1])) // Handle right boundary
            {
                return mid; // Found a peak element, return its index
            }

            // Case 2: If the right neighbor is greater, the slope is rising
            // So the peak must be on the right side of mid
            if (mid < nums.size() - 1 && nums[mid] < nums[mid + 1])
            {
                low = mid + 1; // Eliminate the left half, move to right half
            }

            // Case 3: Else the left neighbor is greater (or slope is falling)
            // So the peak must be on the left side of mid
            else
            {
                high = mid - 1; // Eliminate the right half, move to left half
            }
        }
        return -1;
    }
};
