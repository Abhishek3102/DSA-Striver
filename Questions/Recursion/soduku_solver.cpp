#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    void solveSoduku(vector<vector<char>> &board)
    {
        // Start the backtracking process.
        // The board is modified in-place.
        solve(board);
    }

    bool solve(vector<vector<char>> &board)
    {
        // Traverse the entire board to find an empty cell ('.')
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                // If an empty cell is found, try filling it.
                if (board[i][j] == '.')
                {
                    // Try placing digits '1' to '9'
                    for (char c = '1'; c <= '9'; c++)
                    {
                        // Check whether placing c at (i,j) is valid
                        if (isValid(board, i, j, c))
                        {
                            // Choose:
                            // Place the digit temporarily.
                            board[i][j] = c;

                            // Explore:
                            // Recursively solve the remaining board.
                            if (solve(board) == true)
                                return true;

                            // Backtrack:
                            // If placing c does not lead to a solution,
                            // reset the cell and try another digit.
                            else
                                board[i][j] = '.';
                        }
                    }

                    // If no digit from 1 to 9 works for this cell,
                    // current configuration cannot lead to a solution.
                    return false;
                }
            }
        }

        // No empty cells left.
        // Sudoku has been solved successfully.
        return true;
    }

    bool isValid(vector<vector<char>> &board, int row, int col, char c)
    {
        // Check whether digit c already exists in:
        // 1. Same column
        // 2. Same row
        // 3. Same 3x3 subgrid

        for (int i = 0; i < 9; i++)
        {
            // Check column
            if (board[i][col] == c)
                return false;

            // Check row
            if (board[row][i] == c)
                return false;

            // Check 3x3 subgrid
            // Formula maps i = 0..8 to all cells
            // inside the corresponding 3x3 box.
            if (board[3 * (row / 3) + i / 3]
                     [3 * (col / 3) + i % 3] == c)
                return false;
        }

        // Digit can be safely placed.
        return true;
    }
};