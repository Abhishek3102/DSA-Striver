#include <bits/stdc++.h>
using namespace std;

/*
vector<int> removeKNum(vector<int> arr, int k)
{
    int n = arr.size();
    stack<int> st;
    vector<int> nse(n, -1);

    for (int i = 0; i < n; i++)
    {
        if(k == n) return {0};
        while (!st.empty() && st.top() >= arr[i] || k == 0)
        {
            st.pop();
            k--;
        }
        if (k == 0)
            break;
        else
        {
            nse[i] = st.empty() ? -1 : st.top();
            st.push(arr[i]);
        }
    }
    return nse;
}
    */

string findKNum(string s, int k)
{
    stack<char> st;
    int n = s.size();

    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && k > 0 && st.top() > s[i])
        {
            st.pop();
            k--;
        }
        st.push(s[i]);
    }

    // If k still > 0, remove from the end
    while (k > 0 && !st.empty())
    {
        st.pop();
        k--;
    }

    if (st.empty())
        return "0";

    string res = "";
    while (!st.empty())
    {
        res += st.top();
        st.pop();
    }

    reverse(res.begin(), res.end());

    // Remove leading zeros
    int idx = 0;
    while (idx < res.size() && res[idx] == '0')
        idx++;

    res = res.substr(idx);

    if (res.empty())
        return "0";

    return res;
}

int main()
{
    string s = "1432219";
    int k = 3;
    cout << findKNum(s, k) << endl; // Output: 1219
    return 0;
}