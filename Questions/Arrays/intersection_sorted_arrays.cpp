#include <bits/stdc++.h>
using namespace std;

vector<int> findArrayIntersection(vector<int> &A, int n, vector<int> &B, int m)
{
    vector<int> ans;
    int vis[m] = {0};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (A[i] == B[j] && vis[j] == 0)
            {
                ans.push_back(A[i]);
                vis[j] = 1;
                break;
            }
            if (B[j] > A[i])
                break;
        }
    }
    return ans;
}

// optimal me ek hi intersection mil raha hai sab nahi
vector<int> findArrayIntersectionOptimal(vector<int> &A, int n, vector<int> &B, int m)
{
    int i = 0, j = 0;
    vector<int> ans;
    while (i < n && j < m)
    {
        if (A[i] < B[j])
        {
            i++;
        }
        else if (B[j] < A[i])
        {
            j++;
        }
        else
        {
            ans.push_back(A[i]);
            i++;
            j++;
        }
    }
    return ans;
}

int main()
{
    int n, m;
    cin >> n >> m; // Input size of two arrays

    vector<int> A(n), B(m); // Declare vectors A and B

    // Input elements for array A
    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
    }

    // Input elements for array B
    for (int i = 0; i < m; i++)
    {
        cin >> B[i];
    }

    // Get the intersection of the two arrays
    vector<int> result = findArrayIntersectionOptimal(A, n, B, m);

    // Print the intersection result
    for (int i : result)
    {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}