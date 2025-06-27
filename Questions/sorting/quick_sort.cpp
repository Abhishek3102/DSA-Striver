#include <bits/stdc++.h>
using namespace std;

int mypartition(vector<int> &arr, int low, int high)
{
    int pivot = arr[low];
    int i = low;
    int j = high;

    // Explanation of partition:
    // This function rearranges elements such that:
    // - All elements <= pivot are on the left side
    // - All elements > pivot are on the right side
    // Finally, pivot is placed at its correct sorted position,
    // and the index of the pivot is returned.

    while (i < j)
    {
        // Move i forward while arr[i] is less than or equal to pivot
        // and i doesn't go out of bounds.
        while (arr[i] <= pivot && i <= high - 1)
        {
            i++;
        }
        // Move j backward while arr[j] is greater than pivot
        // and j doesn't go out of bounds.
        while (arr[j] > pivot && j >= low + 1)
        {
            j--;
        }
        // Swap elements at i and j if i < j to move misplaced elements.
        if (i < j)
        {
            swap(arr[i], arr[j]);
        }
    }

    // Place pivot at its correct position.
    swap(arr[low], arr[j]);

    // Return the pivot index for further recursive calls.
    return j;
}

void quickSort(vector<int> &arr, int low, int high)
{
    // QuickSort recursively sorts subarrays divided by the pivot position.

    if (low < high)
    {
        int loc = mypartition(arr, low, high);
        quickSort(arr, low, loc - 1);
        quickSort(arr, loc + 1, high);
    }
}

int main()
{
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    quickSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    return 0;
}

/*
---------------------------------------------
Time Complexity Analysis of QuickSort Algorithm
---------------------------------------------

1. Partition Function Complexity:
   - The partition function traverses the subarray between indices 'low' and 'high' at most once.
   - The pointers 'i' and 'j' move towards each other and each element is examined at most once during partitioning.
   - Therefore, the time complexity of partitioning a subarray of size 'm' is O(m).

2. QuickSort Recursive Complexity:
   - QuickSort recursively calls itself on two subarrays divided by the pivot position returned from partition.
   - In the best and average case, the pivot splits the array into two roughly equal halves.

   Best/Average Case:
   - At each level of recursion, the array is split approximately in half.
   - Number of levels of recursion = O(log n).
   - At each level, the partition function runs over all elements currently in the subarrays.
   - Summing the work at each level gives: O(n) + O(n) + ... (log n times) = O(n log n).

   Worst Case:
   - Worst case occurs when the pivot is always the smallest or largest element (e.g., when the input is already sorted or reverse sorted and pivot is chosen as the first element).
   - The partition divides the array into one subarray of size 1 and another of size n-1.
   - Number of recursion levels becomes O(n).
   - At each level, partition takes O(n), O(n-1), O(n-2), ..., total O(n^2).
   - Hence, worst-case time complexity is O(n^2).

Summary:
- Best/Average case: O(n log n)
- Worst case: O(n^2)

---------------------------------------------
Space Complexity Analysis
---------------------------------------------

1. Space Complexity for Partition Function:
   - The partition function uses constant extra space (only a few integer variables).
   - So, space complexity of partition function itself is O(1).

2. Space Complexity for QuickSort:
   - QuickSort is an in-place sorting algorithm, meaning it sorts the array without allocating extra arrays.
   - However, recursive calls consume stack space.
   - The depth of recursion determines the space complexity.

   Best/Average Case:
   - When partition divides the array evenly, the depth of recursion is O(log n).
   - Therefore, space complexity due to recursion stack is O(log n).

   Worst Case:
   - When partition is unbalanced (like always picking smallest/largest element as pivot), recursion depth becomes O(n).
   - Thus, worst-case space complexity is O(n) due to the stack.

Summary:
- Best/Average case space complexity: O(log n) (due to recursion)
- Worst case space complexity: O(n) (due to recursion stack)

---------------------------------------------
Note:
- This implementation always picks the first element as pivot.
- Pivot selection strategy affects the average and worst-case time complexity.
- Randomized pivot or median-of-three pivot selection often improves average case performance and avoids worst case.

*/
