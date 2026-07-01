// return the length of binary substring containing maximum number of 1's you can replace atmost k 0's
// 01001011001 => max length of substring containig 1's is 5

#include <bits/stdc++.h>
using namespace std;

int main()
{
    string str = "01001011001";
    int maxLen = 0;
    int zeroCount = 0;
    int k = 2;
    int start = 0, end = 0;
    for (int end = 0; end < str.size(); end++)
    {
        if (str[end] == '0')
        {
            zeroCount++;
        }
        while (zeroCount > k)
        {
            if (str[start] == '0')
            {
                zeroCount--;
            }
            start++;
        }
        maxLen = max(maxLen, end - start + 1);
        cout << maxLen << endl;
    }
    cout << "Maximum length of substring with at most " << k << " zero flips is: " << maxLen << endl;
    return 0;
}