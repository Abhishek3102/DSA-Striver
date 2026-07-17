/*

string hai suppose usko compress krna tha like for example:
aaabass ka output hoga a3bas2

*/

#include <bits/stdc++.h>
using namespace std;

string compressString(const string &s)
{
    int n = s.size();
    if (n == 0)
        return "";

    string result = "";
    int count = 1;

    for (int i = 0; i < n; i++)
    {
        // Check if the next character is the same as the current one
        if (i + 1 < n && s[i] == s[i + 1])
        {
            count++;
        }
        else
        {
            // Append the character
            result += s[i];

            // Append the count only if it is greater than 1
            if (count > 1)
            {
                result += to_string(count);
            }

            // Reset count for the next unique character
            count = 1;
        }
    }
    return result;
}

int main()
{
    string s;
    cout << "Enter string to compress: ";
    cin >> s;

    string compressed = compressString(s);
    cout << "Compressed string: " << compressed << endl;

    return 0;
}