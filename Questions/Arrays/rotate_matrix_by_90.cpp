#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> rotateMatrix(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    // vector<vector<int>> ans[n][n]; wrong syntax
    vector<vector<int>> ans(n, vector<int>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            ans[j][n - 1 - i] = matrix[i][j];
        }
    }
    return ans;
}

// optimal approach using transpose of matrix
void rotateMatrixOptimal(vector<vector<int>> &mat)
{
    int n = mat.size();
    // O(N/2 * N/2)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            swap(mat[i][j], mat[j][i]);
        }
    }

    // reverse
    // O(N * N/2)
    for (int i = 0; i < n; i++)
    {
        // row is mat[i]
        reverse(mat[i].begin(), mat[i].end());
    }
}

int main()
{
    // brute force

    // vector<vector<int>> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // vector<vector<int>> rotated = rotateMatrix(mat);

    // for(auto row : rotated) {
    //     for(auto val : row) cout << val << " ";
    //     cout << endl;
    // }

    // return 0;

    // Optimal one
    // Example matrix
    vector<vector<int>> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    cout << "Original matrix:" << endl;
    for (auto row : mat)
    {
        for (auto val : row)
        {
            cout << val << " ";
        }
        cout << endl;
    }

    // Rotate the matrix
    rotateMatrixOptimal(mat);

    cout << "\nRotated matrix (90 degrees clockwise):" << endl;
    for (auto row : mat)
    {
        for (auto val : row)
        {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}

/*

for (int i = 0; i < n - 1; i++) {           // Outer loop for rows
    // The outer loop (`i`) is used to iterate through each row, except for the last one.
    // We don't need to loop over the last row because the transpose operation involves swapping
    // elements above the diagonal (i.e., elements where the row index is less than the column index).
    // By going from `i = 0` to `i < n - 1`, we are ensuring we don't try to swap elements along the diagonal
    // or swap elements that have already been processed. For example, we don't want to swap `mat[2][2]` with itself.

    for (int j = i + 1; j < n; j++) {       // Inner loop for columns (only above the diagonal)
        // The inner loop (`j`) starts from `i + 1` to avoid swapping along the diagonal (where i == j),
        // and to only swap elements that are **above** the diagonal.
        // `j = i + 1` means that for each row `i`, the column `j` starts from the element just to the right
        // of the diagonal element (i.e., the element at `mat[i][i+1]`).

        // The condition `j < n` ensures that the column `j` stays within the bounds of the matrix.
        // This will only loop through the columns that are positioned **right** of the diagonal.

        // The swap operation then occurs between `mat[i][j]` and `mat[j][i]`,
        // which will transpose the matrix (swap rows and columns) above the diagonal.
        swap(mat[i][j], mat[j][i]);           // Swap element at (i, j) with element at (j, i)
    }
}


*/