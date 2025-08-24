#include <bits/stdc++.h>
using namespace std;

// formula for finding missing numbers = arr[high] - (high + 1)
// ans -> arr[high] + more. more = (k - missing). so ans = arr[high] + (k - missing).
// missing = arr[high] - high - 1;
// so final ans = arr[high] + k - (arr[high] - high - 1)
// ans = high + 1 + k
// low is also high + 1, so ans = low + k. low = high + 1 when final ans is found. this is for every bs problem, ans is not found until high crosses low. which means high goes one position behind low which is why low = high + 1

int findKthMissingNo(vector<int> arr, int k)
{
    int n = arr.size();
    int low = 0, high = n - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        // Calculate how many numbers are missing until the current mid index
        int missing = arr[mid] - (mid + 1); // The formula to calculate missing numbers at index mid

        // If the number of missing numbers is less than k, move to the right half
        // We need to find a larger number, hence adjusting low to mid + 1
        if (missing < k)
        {
            low = mid + 1; // Move the search to the right side
        }

        else
        {
            high = mid - 1; // Move the search to the left side
        }
    }
    // The final position of the kth missing number is at high + 1, since high has moved one step behind low
    return high + 1 + k; // Final answer: the number at the high + 1 position + k missing numbers
    // return low + k; both are same since low = high + 1
}

int main()
{
    vector<int> arr = {2, 3, 4, 7, 11}; // The sorted array
    int k = 5;                          // We want to find the 5th missing number in the sorted sequence

    int result = findKthMissingNo(arr, k);

    cout << "The " << k << "th missing number is: " << result << endl;

    return 0;
}