#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void swapArr1p(int i, int a[], int n)
{
    // *i = 0;
    // if (*i >= n/2) return;
    // (i, n-i-1);

    if (i >= n / 2)
        return;
    swap(a[i], a[n - i - 1]);
    swapArr1p(i + 1, a, n);
}

bool check_pal(int i, string &s)
{
    if (i >= s.size() / 2)
        return true;
    if (s[i] != s[s.size() - i - 1])
        return false;
    return check_pal(i + 1, s);
}

int main()
{
    /*  Swap array using one variable

    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    swapArr1p(0, a, n);
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    return 0;

    */

    string s = "abhi";
    cout << check_pal(0, s);
    return 0;
}
