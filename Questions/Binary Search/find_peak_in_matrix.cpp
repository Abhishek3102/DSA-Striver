#include <bits/stdc++.h>
using namespace std;

// Function to find the row index of the maximum element in a given column.
// Why maximum? Because if any element in this column can be a peak,
// it is most likely the largest one (it already beats top/bottom).
int findMaxIndex(vector<vector<int>> mat, int n, int m, int col)
{
    int maxValue = -1;
    int index = -1;

    // Scan through the column to find the row containing the maximum value.
    for (int i = 0; i < n; i++)
    {
        if (mat[i][col] > maxValue)
        {
            maxValue = mat[i][col];
            index = i;
        }
    }
    return index; // Return the row index of the max element in this column
}

// Function to find a peak element in a 2D grid using Binary Search on columns
vector<int> findPeakGrid(vector<vector<int>> mat)
{
    int n = mat.size();
    int m = mat[0].size();

    int low = 0, high = m - 1; // Binary search across columns
    while (low <= high)
    {
        int mid = (low + high) / 2; // Current middle column

        // Step 1: Find the row where this mid column has the maximum element
        int maxRowIndex = findMaxIndex(mat, n, m, mid);

        // Step 2: Get values of left and right neighbors (or -1 if out of bounds)
        int left = mid - 1 >= 0 ? mat[maxRowIndex][mid - 1] : -1;
        int right = mid + 1 < m ? mat[maxRowIndex][mid + 1] : -1;

        // Step 3: Check if the current element is greater than both neighbors
        if (mat[maxRowIndex][mid] > left && mat[maxRowIndex][mid] > right)
        {
            // Found a peak, return its coordinates
            return {maxRowIndex, mid};
        }
        // Step 4: If left neighbor is greater, peak must exist on the left side
        else if (mat[maxRowIndex][mid] < left)
        {
            high = mid - 1; // Discard right half
        }
        // Step 5: Otherwise, move to the right side
        else
        {
            low = mid + 1;
        }
    }

    // Dummy return if no peak (though problem guarantees at least one exists)
    return {-1, -1};
}

int main()
{
    vector<vector<int>> mat = {
        {10, 8, 10, 10},
        {14, 13, 12, 11},
        {15, 9, 11, 21},
        {16, 17, 19, 20}};

    vector<int> peak = findPeakGrid(mat);

    if (peak[0] != -1 && peak[1] != -1)
    {
        cout << "Peak found at: (" << peak[0] << ", " << peak[1]
             << ") with value " << mat[peak[0]][peak[1]] << endl;
    }
    else
    {
        cout << "No peak found." << endl;
    }

    return 0;
}

/*
===================== DETAILED LOGIC EXPLANATION =====================

1️⃣ Problem Definition:
   - A peak in a 2D grid is an element greater than its
     top, bottom, left, and right neighbors.
   - If no neighbor exists (border element), assume -1.

2️⃣ Brute Force:
   - Check each element and compare with its 4 neighbors.
   - Time Complexity: O(n*m*4) → not efficient.

3️⃣ Optimized Binary Search Approach:
   - Instead of checking every element, apply Binary Search on columns.
   - Why columns? Because it reduces the search space by half each step.

4️⃣ Key Idea:
   - In each mid column, find the maximum element (say at row = r).
   - This max is guaranteed to be greater than top/bottom,
     so only left and right neighbors matter.
   - Compare mat[r][mid] with its left and right neighbors:
       • If it is greater than both → Peak found.
       • If left is greater → Peak lies in the left half → move high.
       • If right is greater → Peak lies in the right half → move low.

5️⃣ Why Maximum in Column?
   - Taking the maximum ensures we pick the candidate with the
     highest chance of being a peak (already beats top/bottom).
   - Then, just check horizontal neighbors.

6️⃣ Termination:
   - Each step halves the number of columns → O(log m).
   - At each step we scan n rows for max element → O(n).
   - Final Time Complexity = O(n * log m).
   - Space Complexity = O(1).

7️⃣ Example (Matrix used in main):
       {10, 8, 10, 10}
       {14, 13, 12, 11}
       {15,  9, 11, 21}
       {16, 17, 19, 20}

   - Step 1: mid = 1 → max element in column 1 is 17 (row 3).
     Compare 17 with neighbors → right = 19 → move right.
   - Step 2: mid = 2 → max element in column 2 is 19 (row 3).
     Compare 19 with neighbors → right = 20 → move right.
   - Step 3: mid = 3 → max element in column 3 is 21 (row 2).
     Compare 21 with neighbors → both smaller → Peak found at (2, 3).

=====================================================================
*/
