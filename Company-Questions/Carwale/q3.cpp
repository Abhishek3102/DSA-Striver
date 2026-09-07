/*

### 3. Army Escape

Given a binary grid of size **N × N**. You cannot pass through cells with a value of **1**. You can move in 4 directions (**up, down, left, right**). 

Find the total number of **unique paths** from **(1,1)** to **(N,N)**. 

**Notes:** 

* Total paths will not exceed 1000.
* The grid is 1-indexed.

### Function Description

Complete the EscapeWays function. 

* **N**: INTEGER — Dimension of the matrix.
* **A**: 2D INTEGER ARRAY — The grid matrix.
* **Returns**: INTEGER — Number of unique paths.

### Constraints:

* 1

≤𝑁

≤20
* 𝐴

[

𝑖

]

[

𝑗

]

∈

{

0

,

1

}

### Debugging Input Format:

* Line 1: Integer N
* Next N lines: N space-separated integers for each row.

### Sample Testcases

### **Case 1**

* **Input:** 

text

2
0 0
0 0

Use code with caution.
* **Output:** 2
* **Paths:** 

  1. (1,1) → (1,2) → (2,2)
  2. (1,1) → (2,1) → (2,2)

### **Case 2**

* **Input:** 

text

2
0 0
1 0

Use code with caution.
* **Output:** 1
* **Paths:** 

  1. (1,1) → (1,2) → (2,2)

### **Case 3**

* **Input:** 

text

5
0 1 0 1 1
0 0 0 0 0
1 1 0 1 0
0 0 1 0 1
1 1 1 0 0

Use code with caution.
* **Output:** 0
* **Explanation:** No valid paths exist.

*/

#include <iostream>
#include <vector>

using namespace std;

// Direction arrays for moving Down, Up, Right, Left
int dr[] = {1, -1, 0, 0};
int dc[] = {0, 0, 1, -1};

/**
 * Helper function to perform backtracking DFS to count unique paths.
 */
void dfs(int r, int c, int N, int *A, vector<vector<bool>> &visited, int &path_count)
{
    // Base Case: If destination (N-1, N-1) is reached, increment the counter
    if (r == N - 1 && c == N - 1)
    {
        path_count++;
        return;
    }

    // Mark the current cell as visited so we don't form cycles
    visited[r][c] = true;

    // Explore all 4 possible neighbor movements
    for (int i = 0; i < 4; ++i)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];

        // Check if the neighbor position is within grid boundaries
        if (nr >= 0 && nr < N && nc >= 0 && nc < N)
        {
            // Check if the cell is unvisited and does not contain an obstacle (1)
            // Flattened array index mapping: A[nr * N + nc]
            if (!visited[nr][nc] && A[nr * N + nc] == 0)
            {
                dfs(nr, nc, N, A, visited, path_count);
            }
        }
    }

    // Backtrack: Unmark the current cell to allow other path combinations
    visited[r][c] = false;
}

/**
 * Complete the EscapeWays function as required by the environment.
 */
int EscapeWays(int N, int *A)
{
    // If the start or destination cell itself is blocked, no path is possible
    if (A[0] == 1 || A[N * N - 1] == 1)
    {
        return 0;
    }

    // 2D visited array to keep track of the current path path cells
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    int path_count = 0;

    // Initiate depth-first search starting from index (0, 0)
    dfs(0, 0, N, A, visited, path_count);

    return path_count;
}

int main()
{
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (cin >> N)
    {
        vector<int> A(N * N);
        for (int i = 0; i < N * N; ++i)
        {
            cin >> A[i];
        }
        cout << EscapeWays(N, A.data()) << "\n";
    }
    return 0;
}
