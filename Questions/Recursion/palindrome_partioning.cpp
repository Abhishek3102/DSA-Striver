#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<string>> partition(string s)
    {
        // res will store all valid answers(all partitions of one recursion)
        vector<vector<string>> res;

        vector<string> path; // path will store individual list of substring

        // Start backtracking from index 0
        func(0, s, path, res);

        // Return all possible palindrome partitions
        return res;
    }

    void func(int index, string s, vector<string> &path, vector<vector<string>> &res)
    {
        // Base case:
        // If index reaches the end of the string,
        // it means we have successfully partitioned the entire string.
        if (index == s.size())
        {
            // Store the current partition in the result.
            res.push_back(path);
            return;
        }

        // Try every possible substring starting from 'index'
        for (int i = index; i < s.size(); i++)
        {
            // Consider substring s[index...i]
            // Only proceed if it is a palindrome.
            if (isPalindrome(s, index, i))
            {
                // Choose:
                // Add the palindrome substring to the current partition.
                path.push_back(s.substr(index, i - index + 1));

                // Explore:
                // Recursively partition the remaining string
                // starting from the next index.
                func(i + 1, s, path, res); // when recursion of one index is done, we move to next

                // Backtrack:
                // Remove the previously chosen substring so that
                // we can try another possible partition.
                path.pop_back(); // while coming back from recursion, remove the element selected previously in path
            }
        }
    }

    bool isPalindrome(string s, int start, int end)
    {
        // Two-pointer check for palindrome.
        // Compare characters from both ends moving toward the center.
        while (start <= end)
        {
            if (s[start++] != s[end--])
                return false;
        }

        // All characters matched.
        return true;
    }
};