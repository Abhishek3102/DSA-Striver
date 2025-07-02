#include <bits/stdc++.h>
using namespace std;

vector<int> findArrayIntersection(vector<int> &A, int n, vector<int> &B, int m)
{
    // tc : O(N1 * N2) & sc : O(N2)
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

vector<int> findArrayIntersectionOptimal(vector<int> &A, int n, vector<int> &B, int m)
{
    // tc : O(N1+N2)
    // sc : O(1)

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
    cin >> n >> m;

    vector<int> A(n), B(m);

    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
    }

    for (int i = 0; i < m; i++)
    {
        cin >> B[i];
    }

    vector<int> result = findArrayIntersectionOptimal(A, n, B, m);

    for (int i : result)
    {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}