// sorted part may or may not have the answer
// pick the minimun from sorted half and eliminate

#include <bits/stdc++.h>
using namespace std;

int findMinimum(vector<int> arr)
{
    int low = 0, high = arr.size() - 1;
    int answer = INT_MAX;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        // Check if the left half is sorted
        if (arr[low] <= arr[mid])
        {
            // If sorted, eliminate left half
            answer = min(answer, arr[low]); // selecting the min first
            low = mid + 1;                  // after selecting the min, eliminating all other elements from left side
        }
        else
        {
            // If not sorted, eliminate right half
            high = mid - 1;
            answer = min(answer, arr[mid]);
        }
    }
    return answer;
}

// optimal code. just better than previous one
int findMinimum(vector<int> arr)
{
    int low = 0, high = arr.size() - 1;
    int answer = INT_MAX; // Initialize answer to maximum possible value

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        // ✅ Case 1: The current search space [low...high] is already sorted
        // In a sorted subarray, the smallest element is at index `low`
        if (arr[low] <= arr[high])
        {
            answer = min(answer, arr[low]);
            break; // Since the subarray is sorted, no need to continue searching
        }

        // ✅ Case 2: Left half [low...mid] is sorted
        if (arr[low] <= arr[mid])
        {
            // Since left half is sorted, arr[low] is the minimum in this half
            answer = min(answer, arr[low]);

            // Eliminate the left half and search in the right half
            low = mid + 1;
        }

        // ✅ Case 3: Right half [mid...high] is sorted
        else
        {
            // Since right half is sorted, arr[mid] is the minimum in this half
            answer = min(answer, arr[mid]);

            // Eliminate the right half and search in the left half
            high = mid - 1;
        }
    }

    return answer;
}

/*

Your Original Code:
high = mid - 1;
answer = min(answer, arr[mid]);


Here:
You update high, eliminating the right half. Then you update answer with arr[mid]. This is fine, because arr[mid] is still accessible before changing any boundaries.

🔄 Reversed Order:
answer = min(answer, arr[mid]);
high = mid - 1;


This is also fine, and arguably better, because:
You're evaluating arr[mid] while all indices are still valid. Then you move the high pointer to continue the loop.

✅ Conclusion:
In this specific case, both orders are equivalent and safe, because:
arr[mid] is calculated before either line.

You're not accessing arr[high] or arr[low] after modifying them.
However, as a general habit, it's safer to perform logic based on values first, then update indices — to avoid subtle bugs in more complex algorithms.

🧠 Rule of Thumb:
💡 Always use array values before modifying indices, unless you're absolutely sure index changes won't affect subsequent operations.

*/