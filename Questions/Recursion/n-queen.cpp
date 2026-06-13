#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool isSafe1(int row, int col, vector<string> board, int n)
    {
        // check upper diagonal
        int duprow = row;
        int dupcol = col;

        // this if left upper diagonal check
        while (row >= 0 && col >= 0)
        {
            if (board[row][col] == 'Q')
                return false;
            row--;
            col--;
        }

        // this is left column check(sideways, row waala matlab left me)
        col = dupcol;
        row = duprow;
        while (col >= 0)
        {
            if (board[row][col] == 'Q')
                return false;
            col--;
        }

        // this is left bottom diagonal check
        row = duprow;
        col = dupcol;
        while (row < n && col >= 0)
        {
            if (board[row][col] == 'Q')
                return false;
            row++;
            col--;
        }

        return true;
    }

public:
    void solve(int col, vector<string> &board, vector<vector<string>> &ans, int n)
    {
        if (col == n)
        {
            ans.push_back(board);
            return;
        }

        for (int row = 0; row < n; row++)
        {
            if (isSafe1(row, col, board, n))
            {
                board[row][col] = 'Q';
                solve(col + 1, board, ans, n);
                board[row][col] = '.';
            }
        }
    }
};