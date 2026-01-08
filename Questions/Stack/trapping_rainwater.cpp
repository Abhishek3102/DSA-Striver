/*
  TRAPPING RAINWATER
  
  This code calculates the amount of water that can be trapped between elevation bars.
  
  WHAT IT DOES:
  - Given elevation heights, calculates water trapped after rainfall
  - Water trapped at position i = min(maxLeft, maxRight) - height[i]
  - Uses two-pointer approach moving from both ends
  - Tracks leftMax and rightMax simultaneously for O(1) space complexity
  
  INPUT:
  - Array of integers representing elevation heights
  - Example: [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
  
  OUTPUT:
  - Single integer: total units of water that can be trapped
  - Example output: 6 units
  - Water level at each position determined by minimum of max heights on left and right
*/

#include <bits/stdc++.h>
using namespace std;

// optimal
int findTrappedWater(vector<int> arr)
{
    int n = arr.size();
    int leftMax = 0, rightMax = 0, total = 0;
    int left = 0, right = n - 1;

    while (left < right)
    {
        if (arr[left] <= arr[right])
        {
            if (leftMax > arr[left])
            {
                total += leftMax - arr[left];
            }

            else
            {
                leftMax = arr[left];
            }
            left = left + 1;
        }

        else
        {
            if (rightMax > arr[right])
            {
                total += rightMax - arr[right];
            }

            else
            {
                rightMax = arr[right];
            }
            right = right - 1;
        }
    }
    return total;
}

int main()
{
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements (space-separated): ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int result = findTrappedWater(arr);
    cout << "The total trapped water is: " << result << endl;

    return 0;
}