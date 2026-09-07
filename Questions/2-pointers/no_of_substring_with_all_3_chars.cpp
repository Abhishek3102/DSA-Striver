#include <bits/stdc++.h>
using namespace std;

int findNoOfSubstrings(string &s)
{
    int n = s.size();
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        int hash[3] = {0};
        for (int j = i; j < n; j++)
        {
            hash[s[j] - 'a'] = 1;

            if (hash[0] + hash[1] + hash[2] == 3)
                count++;
        }
    }
    return count;
}

int findNoOfSubsOptimal(string s){
    int lastSeen[3] = {-1, -1, -1};
    int count = 0;
    int n = s.size();
    for(int i = 0; i < n; i++){
        // set last seen value to current index whatever char it is
        lastSeen[s[i] - 'a'] = i;

        if(lastSeen[0] == -1 && lastSeen[1] == -1 && lastSeen[2] == -1){
            count = count + (1 + min(lastSeen[0], min(lastSeen[1], lastSeen[2])));
        }
    }
    return count;
}

int main()
{
    string s = "bbacba";
    cout << findNoOfSubstrings(s);
}