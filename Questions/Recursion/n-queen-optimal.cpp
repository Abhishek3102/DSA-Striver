#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    void solve(int col, vector<string> &board, vector<vector<string>> &ans,
               vector<int> &leftRow, vector<int> &upperDiagonal,
               vector<int> &lowerDiagonal, int n)
    {
        // Base case:
        // If all columns have been processed,
        // a valid arrangement of queens is found.
        if (col == n)
        {
            ans.push_back(board);
            return;
        }

        // Try placing a queen in every row of the current column.
        for (int row = 0; row < n; row++)
        {
            // Check if the current position (row, col) is safe.
            //
            // leftRow[row]                  -> checks same row
            // lowerDiagonal[row + col]     -> checks lower diagonal (/)
            // upperDiagonal[n-1+col-row]   -> checks upper diagonal (\)
            if (leftRow[row] == 0 &&
                lowerDiagonal[row + col] == 0 &&
                upperDiagonal[n - 1 + col - row] == 0)
            {
                // Choose:
                // Place queen at (row, col).
                board[row][col] = 'Q';

                // Mark row and diagonals as occupied.
                leftRow[row] = 1;
                lowerDiagonal[row + col] = 1;
                upperDiagonal[n - 1 + col - row] = 1;

                // Explore:
                // Move to the next column.
                solve(col + 1, board, ans,
                      leftRow, upperDiagonal, lowerDiagonal, n);

                // Backtrack:
                // Remove queen and unmark occupied paths.
                board[row][col] = '.';

                leftRow[row] = 0;
                lowerDiagonal[row + col] = 0;
                upperDiagonal[n - 1 + col - row] = 0;
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n)
    {
        // Stores all valid board configurations.
        vector<vector<string>> ans;

        // Create an empty chessboard of size n x n.
        vector<string> board(n);

        // One row initially filled with '.'
        string s(n, '.');

        for (int i = 0; i < n; i++)
        {
            board[i] = s;
        }

        // Optimization arrays:
        //
        // leftRow[row]
        // -> whether a queen already exists in that row.
        //
        // lowerDiagonal[row + col]
        // -> identifies diagonals running from top-left to bottom-right.
        //
        // upperDiagonal[n - 1 + col - row]
        // -> identifies diagonals running from bottom-left to top-right.
        vector<int> leftRow(n, 0),
            upperDiagonal(2 * n - 1, 0),
            lowerDiagonal(2 * n - 1, 0);

        // Start placing queens from column 0.
        solve(0, board, ans,
              leftRow, upperDiagonal, lowerDiagonal, n);

        return ans;
    }
};