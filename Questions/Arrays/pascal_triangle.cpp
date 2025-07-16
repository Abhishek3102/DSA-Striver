/*
There can be 3 types of question in this :

1. given row and col., find element at that place, eg : r = 5, c = 3

2. print the n^th row of pascal triangle, eg : n = 5 -> 1 4 6 4 1

3. given n. print the entire pascal triangle till n^th row.
*/

#include <bits/stdc++.h>
using namespace std;

// find element at given row and column
int nCr(int n, int r)
{
    // tc : O(r) and sc : O(1)
    long long resultant = 1;
    for (int i = 0; i < r; i++)
    {
        resultant = resultant * (n - i);
        resultant = resultant / (i + 1);
    }
    return resultant;
}

// second type : print n^th row
void nCrFullRow(int n)
{ // tc : O(n * r)
    // here since pascal triangle is one based index, that is it starts from 1, so we have taken r from 1 and condition also is n-1, r-1
    // if it was zero based index, then we would have taken r = 0, and condition : (n,r)
    for (int r = 1; r <= n; r++)
    {
        if (r > 1)
            cout << " "; // this is for space b/w nos.
        cout << nCr(n - 1, r - 1);
    }
    cout << endl;
}

// 3rd type : print all elements till n^th row
list<list<int>> nCrTillNthRow(int n)
{
    // here tc : approx to O(n * n * r) which can be near to n^3 at worst
    list<list<int>> ans;
    for (int r = 1; r <= n; r++)
    {
        list<int> tempList;
        for (int c = 1; c <= r; c++)
        {
            tempList.push_back(nCr(r - 1, c - 1));
        }
        ans.push_back(tempList);
    }
    return ans;
}

// optimal approach for third type
vector<int> generateRow(int row)
{
    long long ans = 1;
    vector<int> ansRow;
    ansRow.push_back(1);
    for (int col = 1; col < row; col++)
    {
        ans = ans * (row - col);
        ans = ans / (col);
        ansRow.push_back(ans);
    }
    return ansRow;
}

vector<vector<int>> pascalTriangleFullTillN(int n)
{
    vector<vector<int>> ans;
    for (int i = 1; i <= n; i++)
    {
        ans.push_back(generateRow(i));
    }
    return ans;
}

int main()
{
    int n, r;
    cin >> n;
    // cin >> r;
    // cout << nCr(n, r) << endl;

    // second type
    // nCrFullRow(n);

    // third type
    // list<list<int>> pascalTriangle = nCrTillNthRow(n);

    // print pascal traingle's rows
    // for (auto &row : pascalTriangle)
    // {
    //     for (auto &num : row)
    //     {
    //         cout << num << " ";
    //     }
    //     cout << endl;
    // }

    // third type optimal way
    vector<vector<int>> pascalTriangle = pascalTriangleFullTillN(n);

    for (const auto &row : pascalTriangle)
    {
        for (const auto &num : row)
        {
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}