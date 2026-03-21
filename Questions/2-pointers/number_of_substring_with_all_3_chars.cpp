// eg : s = b b a c b a -> here find count of substring which has all 3 chars involved
//  [b b a c] is one string, like that [b b a c b] is another. means minimum 3 aur max kitne bhi

#include <bits/stdc++.h>
using namespace std;

int findSubstringLength(string s)
{
    int n = s.size();
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        // int count = 0;
        int hash[3] = {0};

        for (int j = i; j < n; j++)
        {
            hash[s[j] - 'a'] = 1;

            if (hash[0] + hash[1] + hash[2] == 3)
            {
                count = count + 1;
            }
        }
    }
    return count;
}

// here once we find a substring which has all 3 chars and yet the chars in string are remaining, so all chars from there will also be a valid substring
int findSubstringLengthLittleBetter(string s)
{
    int n = s.size();
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        // int count = 0;
        int hash[3] = {0};

        for (int j = i; j < n; j++)
        {
            hash[s[j] - 'a'] = 1;

            if (hash[0] + hash[1] + hash[2] == 3)
            {
                // count = count + 1;
                count = count + (n - j); // this adds all other substring to the count from where it becomes a valid substring itself.
                break;
            }
        }
    }
    return count;
}

// optimal way
int findSubstringLengthOptimal(string s)
{
    int lastSeen[3] = {-1, -1, -1};
    int n = s.size();
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        lastSeen[s[i] - 'a'] = i;

        if (lastSeen[0] != -1 && lastSeen[1] != -1 && lastSeen[2] != -1)
        {
            int mini = min(lastSeen[0], min(lastSeen[1], lastSeen[2]));
            count += (mini + 1);
        }
    }
    return count;
}

int main()
{
    string s = "bbacba";
    cout << findSubstringLength(s);
    return 0;
}