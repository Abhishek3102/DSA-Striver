#include <bits/stdc++.h>
using namespace std;

bool search_in_2d_matrix_I(const vector<vector<int>> mat, int target)
{
    int rows = mat.size();
    int cols = mat[0].size();

    if (rows == 0)
        return false;

    // Iterate over each row
    for (int i = 0; i < rows; i++)
    {
        // Iterate over each column in the row
        for (int j = 0; j < cols; j++)
        {
            if (mat[i][j] == target)
            {
                return true;
            }
        }
    }
    return false;
}

// code for finding position where target is found
/*
pair<int, int> linear_search_in_2d_matrix(const vector<vector<int>>& mat, int target) {
    int rows = mat.size();
    int cols = mat[0].size();

    // Iterate over each row
    for (int i = 0; i < rows; i++) {
        // Iterate over each column in the row
        for (int j = 0; j < cols; j++) {
            if (mat[i][j] == target) {
                return {i, j};  // Return the position (row, column)
            }
        }
    }
    return {-1, -1};  // Return (-1, -1) if not found
}

int main() {
    // Create a dynamic 2D matrix using vectors
    vector<vector<int>> mat = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };

    int target = 16;  // Example target value
    pair<int, int> result = linear_search_in_2d_matrix(mat, target);

    if (result.first != -1) {
        // If the result is not (-1, -1), it means the target was found
        cout << "Found at position: (" << result.first << ", " << result.second << ")" << endl;
    } else {
        cout << "Not Found" << endl;
    }

    return 0;
}
*/

/*
int main()
{
    vector<vector<int>> mat = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}};

    int target = 16;
    if (search_in_2d_matrix_I(mat, target))
        cout << "Found" << endl;
    else
        cout << "Not Found" << endl;

    return 0;
}
*/

bool searchMatrix(vector<vector<int>> mat, int target)
{
    // Get the number of rows in the matrix
    int rows = mat.size();

    // Get the number of columns in the matrix
    int columns = mat[0].size();

    int low = 0, high = rows * columns - 1; // We treat the matrix as a flattened 1D array

    // We have effectively flattened the 2D matrix into a 1D array, where:
    // - `row` = index of 1D array / number of columns
    // - `col` = index of 1D array % number of columns

    while (low <= high)
    {
        // Find the middle element (index in the flattened 1D array)
        int mid = low + (high - low) / 2;

        // Convert this index back to the 2D matrix coordinates (row and column)
        int row = mid / columns; // Row is the quotient of dividing `mid` by the number of columns
        int col = mid % columns; // Column is the remainder when dividing `mid` by the number of columns

        // Check if the target value is found at this position
        if (mat[row][col] == target)
        {
            return true;
        }
        // If the target is larger than the middle element, move the `low` pointer
        else if (mat[row][col] < target)
        {
            low = mid + 1; // Move to the right half of the matrix
        }
        // If the target is smaller than the middle element, move the `high` pointer
        else
        {
            high = mid - 1; // Move to the left half of the matrix
        }
    }

    // If we exit the loop, the target was not found in the matrix
    return false;
}

int main()
{
    vector<vector<int>> mat = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}};

    int target;
    cout << "Enter the target number to search for: ";
    cin >> target;

    if (searchMatrix(mat, target))
    {
        cout << "Target " << target << " found in the matrix!" << endl;
    }
    else
    {
        cout << "Target " << target << " not found in the matrix." << endl;
    }

    return 0;
}