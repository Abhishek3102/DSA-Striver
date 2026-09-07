#include <bits/stdc++.h>
using namespace std;

int findMaxReplacementLength(string s, int k)
{
    int n = s.size();
    int maxLength = 0;

    for (int i = 0; i < n; i++)
    {
        int hash[26] = {0};
        int maxFreq = 0;

        for (int j = i; j < n; j++)
        {
            hash[s[j] - 'A']++;
            maxFreq = max(maxFreq, hash[s[j] - 'A']);

            int changes = (j - i + 1) - maxFreq;

            if (changes <= k)
                maxLength = max(maxLength, j - i + 1);
            else
                break;
        }
    }

    return maxLength;
}

// optimal
int findMaxReplacementLengthOptimal(string s, int k)
{
    int l = 0;
    int maxLength = 0;
    int maxFreq = 0;

    int hash[26] = {0};

    for (int r = 0; r < s.size(); r++)
    {
        hash[s[r] - 'A']++;

        maxFreq = max(maxFreq, hash[s[r] - 'A']);

        while ((r - l + 1) - maxFreq > k)
        {
            hash[s[l] - 'A']--;
            l++;
        }

        maxLength = max(maxLength, r - l + 1);
    }

    return maxLength;
}