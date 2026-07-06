#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string longestPalindrome(string s)
    {
        string res = "";
        int resLen = 0;

        for (int i = 0; i < s.length(); i++)
        {

            // Odd length palindrome (here l, r starts from 0 and then acc to conditions traversal happens and check is done at each traversal)
            int l = i; //(0) here b. so l-- => l = -1 means loop stop, then goes to even condition check. and once that stops then again l,r = 1.
            int r = i; // (0) here b. r++ => r = 1. so since l : -1 != r = 1 (means elements are not equal, s[l] != s[r]) loop stops.

            while (l >= 0 && r < s.length() && s[l] == s[r])
            {
                if ((r - l + 1) > resLen)
                {
                    res = s.substr(l, r - l + 1);
                    resLen = r - l + 1;
                }
                l--;
                r++;
            }

            // Even length palindrome (since even length hence two centres so one starts at one center that is l and r starts at other center)
            l = i;     // ( so suppose s.size() = 4, in that case l will start from s[0]) but its center for a palindrome would be s[1]
            r = i + 1; // (and in same case r will start from s[1]) but its center for a palindrome would be s[2]

            while (l >= 0 && r < s.length() && s[l] == s[r])
            {
                if ((r - l + 1) > resLen) // condition check if current length is greater than longest length
                {
                    res = s.substr(l, r - l + 1); // if greater than extract that part of string and assign to res
                    resLen = r - l + 1;           // and length of that longest would be this from l to r
                }
                l--;
                r++;
            }
        }

        return res;
    }
};