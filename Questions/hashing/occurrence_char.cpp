#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;

    // pre compute
    int hash[26] = {0}; // this is when only small alphabets are included

    // when capital letters are included too, then
    // int hash[256] = {0};
    // everything that was subtracted when arr size was 26, is removed when capital letters are included
    // bcoz then size of array becomes 356 and all alphabets big and small are included with no need to calculate index for anyone

    // so if only small letters, then c - 'a' // The line below uses this approach where we subtract 'a' from a character in the string `s` to get the index for the hash array.
    // This works because 'a' has an ASCII value of 97, and subtracting it gives us 0 for 'a', 1 for 'b', ..., and 25 for 'z'.
    // This technique maps the 26 lowercase English letters directly to the indices of the hash array.

    // so if only big letters, then c - 'A'
    // For uppercase letters, we would subtract 'A' from the character to get the index (i.e., 'A' maps to 0, 'B' to 1, etc.).
    // However, in this case, we're only using lowercase letters, so we do not need this for the current implementation.

    // else 256
    // This would apply if we had an array of size 256 to store the counts of all possible ASCII characters.

    for (int i = 0; i < s.size(); i++)
    {
        hash[s[i] - 'a']++; // Increment the count for the character in the hash array.
        // The expression `s[i] - 'a'` maps the character to the corresponding index in the `hash` array.
        // For example, for character 'a', 'a' - 'a' = 0, so hash[0] will be incremented.
        // This ensures that we store the frequency of each character in the string efficiently.

        // hash[s[i]];
    }

    int q;
    cin >> q;
    while (q--)
    {
        char c;
        cin >> c;
        cout << hash[c - 'a'] << endl;
        // cout << hash[c] << endl;
    }
    return 0;
}