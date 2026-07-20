/*

Given a 2D grid of size m x n and an integer k. You need to shift the grid k times.
In one shift operation:
Element at grid[i][j] moves to grid[i][j + 1].
Element at grid[i][n - 1] moves to grid[i + 1][0].
Element at grid[m - 1][n - 1] moves to grid[0][0].
Return the 2D grid after applying shift operation k times.
 
Example 1:
Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 1 Output: [[9,1,2],[3,4,5],[6,7,8]]
Example 2:
Input: grid = [[3,8,1,9],[19,7,2,5],[4,6,11,10],[12,0,21,13]], k = 4 Output: [[12,0,21,13],[3,8,1,9],[19,7,2,5],[4,6,11,10]]
Example 3:
Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 9 Output: [[1,2,3],[4,5,6],[7,8,9]]
 
Constraints:
m == grid.length
n == grid[i].length
1 <= m <= 50
1 <= n <= 50
-1000 <= grid[i][j] <= 1000
0 <= k <= 100

*/

#include <vector>

using namespace std;

class Solution
{
public:
    vector<vector<int>> shiftGrid(vector<vector<int>> &grid, int k)
    {
        int m = grid.size();    // Number of rows
        int n = grid[0].size(); // Number of columns
        int total = m * n;      // Total number of elements

        // Optimization: Shifting 'total' times results in the same grid.
        k = k % total;

        // Create a new grid of the same size filled with 0s to store the result
        vector<vector<int>> result(m, vector<int>(n, 0));

        // Traverse every element in the original 2D grid
        for (int r = 0; r < m; ++r)
        {
            for (int c = 0; c < n; ++c)
            {

                // Step 1: Convert the current 2D position (r, c) to a 1D index
                int old_1d_idx = r * n + c;

                // Step 2: Calculate the new 1D index after shifting k times
                // We use % total to wrap around to the beginning if it goes past the end
                int new_1d_idx = (old_1d_idx + k) % total;

                // Step 3: Convert the new 1D index back to 2D coordinates (new_r, new_c)
                int new_r = new_1d_idx / n;
                int new_c = new_1d_idx % n;

                // Step 4: Place the original value into its new home
                result[new_r][new_c] = grid[r][c];
            }
        }

        return result;
    }
};

/*

Explanation :
Matrix problems can feel intimidating because you're dealing with two dimensions (rows and columns) instead of just one linear array.
But here is the secret: almost every grid-flattening or shifting problem can be simplified by pretending the 2D grid is just one long 1D array.
Let’s break down the intuition, the math formulas you need to remember, and how to write the C++ code.
How to Think About 2D MatricesWhen you see a 2D grid of size m times n (where $m$ is the number of rows and $n$ is the number of columns), imagine stretching it out into a single line.

[[1, 2, 3],
 [4, 5, 6],
 [7, 8, 9]]

 If we flatten it, it becomes a 1D array of total size m * n = 9.
 Index: [0, 1, 2, 3, 4, 5, 6, 7, 8]
Value: [1, 2, 3, 4, 5, 6, 7, 8, 9]

Shifting the grid k times is exactly the same as shifting this 1D array to the right by k positions!

The Golden Formulas for 2D Grid Conversion

To master matrix problems, you only need to memorize two simple formulas to convert between 1D and 2D indexes:

2D to 1D: If you are at row r and column c, your 1D index is:
1D_Index = r * n + c

1D to 2D: If you have a 1D index idx, you can find its row and column using division and modulo:
Row = idx / n
Col = idx % n

(Note: We always use n, the number of columns, for these calculations).

The Algorithm

Find the total number of elements: total = m * n.

Since shifting a grid of size X by X times brings it back to its original state, we can optimize k using modulo: k = k % total.

Create a new result grid of the same size.

Loop through every element in the original grid, convert its position to a 1D index, add k to it (modulo total to prevent going out of bounds), convert it back to 2D coordinates, and place it in the new grid.

*/