// here the examples requires the celebrity, i.e., a position in matrix which is known by all positions and it itself doesn't know anyone.
// by knowing it means. 1 - knows, 0 - doesn't know

#include <bits/stdc++.h>
using namespace std;

// brute force
int findCeleb(int mat[][100], int n)
{
    vector<int> knowMe(n, 0);
    vector<int> iKnow(n, 0);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (mat[i][j] == 1)
            {
                knowMe[j]++;
                iKnow[i]++;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (knowMe[i] == n - 1 && iKnow[i] == 0)
            return i;
    }

    return -1;
}

// optimal way
int findCelebOptimal(int mat[][100], int n)
{
    int top = 0, down = n - 1;

    // Step 1: Find potential celebrity
    while (top < down)
    {
        if (mat[top][down] == 1)
            top++;
        else
            down--;
    }

    int cand = top;

    // Step 2: Verify candidate
    for (int i = 0; i < n; i++)
    {
        if (i == cand)
            continue;

        // candidate should NOT know i
        // everyone should know candidate
        if (mat[cand][i] == 1 || mat[i][cand] == 0)
            return -1;
    }

    return cand;
}

int main()
{
    int mat[100][100] = {
        {0, 1, 0},
        {0, 0, 0},
        {0, 1, 0}};

    int n = 3;

    int celeb2 = findCelebOptimal(mat, n);

    if (celeb2 == -1)
        cout << "Optimal: No Celebrity\n";
    else
        cout << "Optimal Celebrity Index: " << celeb2 << "\n";

    return 0;
}
