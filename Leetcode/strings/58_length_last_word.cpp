/*
here eg : Input: s = "Hello World"
Output: 5
Explanation: The last word is "World" with length 5.
Example 2:

Input: s = "   fly me   to   the moon  "
Output: 4
Explanation: The last word is "moon" with length 4.

*/

class Solution
{
public:
    int lengthOfLastWord(string s)
    {
        int n = s.size();

        // Start checking from the last character of the string
        int i = n - 1;
        int length = 0;

        // ----------------------------------------------------
        // STEP 1: Skip trailing spaces (if any)
        // ----------------------------------------------------
        // If the string ends with spaces, we ignore them.
        // Example: "Hello World   "
        // We move backward until we find a non-space character.
        while (i >= 0 && s[i] == ' ')
        {
            i--;
        }

        // ----------------------------------------------------
        // STEP 2: Count characters of the last word
        // ----------------------------------------------------
        // Now 'i' is at the last character of the last word.
        // Keep moving backward and counting characters
        // until we reach a space or the beginning of the string.
        while (i >= 0 && s[i] != ' ')
        {
            length++; // Increment length for each character
            i--;      // Move to the previous character
        }

        // ----------------------------------------------------
        // STEP 3: Return the final count
        // ----------------------------------------------------
        // 'length' now contains the number of characters in the last word of the string.
        return length;
    }
};
