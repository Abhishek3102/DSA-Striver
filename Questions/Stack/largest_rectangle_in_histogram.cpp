#include <bits/stdc++.h>
using namespace std;

vector<int> findPSEOptimal(vector<int> arr)
{
    int n = arr.size();
    vector<int> nse(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && st.top() >= arr[i])
        {
            st.pop();
        }

        nse[i] = st.empty() ? -1 : st.top();
        st.push(arr[i]);
    }
    return nse;
}

vector<int> findNSEOptimal(vector<int> arr)
{
    int n = arr.size();
    vector<int> nse(n, -1);
    stack<int> st;

    for (int i = n - 1; i >= 0; i--)
    {
        while (!st.empty() && st.top() >= arr[i])
        {
            st.pop();
        }

        nse[i] = st.empty() ? -1 : st.top();
        st.push(arr[i]);
    }
    return nse;
}

// this is brute coz we use both pse and nse which increases time and space complexity
int findLargestRectAreaHisto(vector<int> arr)
{
    vector<int> nse = findNSEOptimal(arr);
    vector<int> pse = findPSEOptimal(arr);
    int n = arr.size();

    int maxi = 0;
    for (int i = 0; i < n; i++)
    {
        maxi = max(maxi, arr[i] * (nse[i] - pse[i] - 1));
    }
    return maxi;
}

// optimal for finding max area
int findMaxAreaHisto(vector<int> arr)
{
    int n = arr.size();
    stack<int> st;
    int maxArea = 0;
    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && arr[st.top()] > arr[i])
        {
            int element = st.top();
            st.pop();
            int nse = i;
            int pse = st.empty() ? -1 : st.top();
            maxArea = max(arr[element] * (nse - pse - 1), maxArea);
        }
        st.push(i);
    }
    while (!st.empty())
    {
        int nse = n;
        int element = st.top();
        st.pop();

        int pse = st.empty() ? -1 : st.top();
        maxArea = max(maxArea, (nse - pse - 1) * arr[element]);
    }
    return maxArea;
}

int main()
{
    vector<int> arr = {3, 2, 10, 11, 5, 10, 6, 3};
    int maxArea = findMaxAreaHisto(arr);
    cout << "The maximum rectangular area is: " << maxArea << endl;
    return 0;
}