How to Think About 2D Matrices
When you see a 2D grid of size m×n (where m is the number of rows and n is the number of columns), imagine stretching it out into a single line.

For example, a 3×3 grid:

Plaintext
[[1, 2, 3],
 [4, 5, 6],
 [7, 8, 9]]
If we flatten it, it becomes a 1D array of total size m×n=9:

Plaintext
Index: [0, 1, 2, 3, 4, 5, 6, 7, 8]
Value: [1, 2, 3, 4, 5, 6, 7, 8, 9]
Shifting the grid k times is exactly the same as shifting this 1D array to the right by k positions!

The Golden Formulas for 2D Grid Conversion
To master matrix problems, you only need to memorize two simple formulas to convert between 1D and 2D indexes:

2D to 1D: If you are at row r and column c, your 1D index is:

1D_Index=r×n+c
1D to 2D: If you have a 1D index idx, you can find its row and column using division and modulo:

Row=idx/n
Col=idx%n
(Note: We always use n, the number of columns, for these calculations).

The Algorithm
Find the total number of elements: total=m×n.

Since shifting a grid of size X by X times brings it back to its original state, we can optimize k using modulo: k=k%total.

Create a new result grid of the same size.

Loop through every element in the original grid, convert its position to a 1D index, add k to it (modulo total to prevent going out of bounds), convert it back to 2D coordinates, and place it in the new grid.

C++ Code
Here is the clean, well-commented C++ solution:

C++
#include <vector>

using namespace std;

class Solution {
public:
vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
int m = grid.size(); // Number of rows
int n = grid[0].size(); // Number of columns
int total = m \* n; // Total number of elements

        // Optimization: Shifting 'total' times results in the same grid.
        k = k % total;

        // Create a new grid of the same size filled with 0s to store the result
        vector<vector<int>> result(m, vector<int>(n, 0));

        // Traverse every element in the original 2D grid
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {

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
C++ Syntax Breakdown for Beginners
vector<vector<int>>: This is how C++ represents a 2D dynamic array (a matrix). Think of it as a "vector of vectors".

grid.size(): Gives you the number of outer elements, which represents the rows (m).

grid[0].size(): Gives you the size of the first row, which represents the columns (n).

vector<vector<int>> result(m, vector<int>(n, 0));: This initializes a 2D vector with m rows, where each row is a vector of size n filled with zeros.

Tip for Matrix Problems: Whenever a problem talks about moving elements across row boundaries (like moving from the end of one row to the start of the next), immediately think of the 1D flattening trick. It turns a complex coordinate tracking problem into simple addition!
