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