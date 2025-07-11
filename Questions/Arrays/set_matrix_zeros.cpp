#include <bits/stdc++.h>
using namespace std;

// Function to mark a row as -1 where there is a 0
void markRow(int arr[][100], int i, int m)
{
    for (int j = 0; j < m; j++)
    {
        if (arr[i][j] != 0)
        {
            arr[i][j] = -1;
        }
    }
}

// Function to mark a column as -1 where there is a 0
void markCol(int arr[][100], int j, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i][j] != 0)
        {
            arr[i][j] = -1;
        }
    }
}

// Function to set rows and columns to -1 where there are 0s
void set_mat_zero(int arr[][100], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (arr[i][j] == 0)
            {
                markRow(arr, i, m);
                markCol(arr, j, n);
            }
        }
    }
}

// Function to convert all -1s to 0s after processing the matrix
void setFinalZero(int arr[][100], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (arr[i][j] == -1)
            {
                arr[i][j] = 0; // Convert the temporary -1 to 0
            }
        }
    }
}

// Function to print the matrix
void printMatrix(int arr[][100], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

// better solution with tc : O(2 * n * m) approx to O(2 N^2)
// sc : (n + m)
vector<vector<int>> zeroMatrix(vector<vector<int>> &matrix, int n, int m)
{
    int col[m] = {0};
    int row[n] = {0};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (matrix[i][j] == 0)
            {
                row[i] = 1;
                col[j] = 1;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (row[i] || col[j])
            {
                matrix[i][j] = 0;
            }
        }
    }
    return matrix;
}

vector<vector<int>> zeroMatrixOptimal(vector<vector<int>> &matrix, int n, int m)
{
    // int col[m] = {0} -> matrix[0][..]
    // int row[n] = {0} -> matrix[..][0]
    int col0 = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (matrix[i][j] == 0)
            {
                // mark the i-th row
                matrix[i][0] = 0;
                // mark the j-th column
                if (j != 0)
                    matrix[0][j] = 0;
                else
                    col0 = 0;
            }
        }
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            if (matrix[i][j] != 0)
            {
                // check for col & row
                if (matrix[0][j] == 0 || matrix[i][0] == 0)
                {
                    matrix[i][j] = 0;
                }
            }
        }
    }
    if (matrix[0][0] == 0)
    {
        for (int j = 0; j < m; j++)
            matrix[0][j] = 0;
    }

    if (col0 == 0)
    {
        for (int i = 0; i < n; i++)
        {
            matrix[i][0] = 0;
        }
    }
    return matrix;
}

int main()
{
    /*
    // brute force approach
    int arr[3][100] = {
        {1, 1, 0},
        {1, 0, 1},
        {1, 1, 1}};

    int n = 3, m = 3;

    cout << "Original Matrix: " << endl;
    printMatrix(arr, n, m);

    // Call the function to modify the matrix
    set_mat_zero(arr, n, m);

    // Convert all -1s to 0s
    setFinalZero(arr, n, m);

    cout << "\nModified Matrix: " << endl;
    printMatrix(arr, n, m);

    return 0;
    */

    // Static input
    vector<vector<int>> matrix = {
        {1, 1, 0},
        {1, 0, 1},
        {1, 1, 1}};
    int n = 3, m = 3;

    // Uncomment for user input
    /*
    // User input (commented out for now)
    int n, m;
    cout << "Enter number of rows and columns: ";
    cin >> n >> m;
    vector<vector<int>> matrix(n, vector<int>(m));

    cout << "Enter the matrix values: \n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }
    */

    cout << "Original Matrix: \n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    // Call zeroMatrix function
    matrix = zeroMatrix(matrix, n, m);

    cout << "\nModified Matrix: \n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
