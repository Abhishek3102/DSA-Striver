#include <bits/stdc++.h>
using namespace std;

int lengthOfLongestSubstring(string s)
{

    // Stores the last occurrence of every character
    vector<int> mpp(256, -1);

    int left = 0, right = 0;
    int n = s.size();
    int len = 0;

    while (right < n)
    {

        // If the character already exists in the current window,
        // move the left pointer after its previous occurrence.
        if (mpp[s[right]] != -1)
        {
            left = max(left, mpp[s[right]] + 1);
        }

        // Update the latest occurrence of the current character
        mpp[s[right]] = right;

        // Calculate the current window length
        len = max(len, right - left + 1);

        // Expand the window
        right++;
    }

    return len;
}