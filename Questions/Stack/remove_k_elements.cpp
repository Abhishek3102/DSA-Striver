/*
  REMOVE K DIGITS - SMALLEST NUMBER
  
  This code finds the smallest number possible after removing exactly k digits from a number.
  
  WHAT IT DOES:
  - Takes a string representation of a number and removes k digits
  - Removes digits greedily to get the lexicographically smallest result
  - Uses a stack to track which digits to keep/remove
  - A digit is removed if the next digit is smaller and k removals are still available
  
  INPUT:
  - String representing a number
  - Integer k (number of digits to remove)
  - Example: "1432219", k=3
  
  OUTPUT:
  - String representing the smallest number after removing k digits
  - Example output: "1219" (removed 4, 3, 2)
  - If all digits removed, returns "0"
*/

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