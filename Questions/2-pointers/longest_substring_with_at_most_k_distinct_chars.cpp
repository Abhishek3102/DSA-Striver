// same as fruits into basket question where max length subarray was to be formed with at most k distinct numbers.
// so similarly, here k distinct characters

#include <bits/stdc++.h>
using namespace std;

// int findMaxLength(vector<string> arr, int k)
// {
//     int maxLength = 0;
//     int n = arr.size();
//     map<char, int> mpp;
//     for (int i = 0; i < n; i++)
//     {
//         mpp.clear(); // coz we are starting fresh, so nothing should be there in map before

//         for (int j = i; j < n; j++)
//         {
//             mpp[arr[j]]++;

//             if (mpp.size() <= k)
//             {
//                 maxLength = max(maxLength, j - i + 1);
//             }

//             else
//             {
//                 break;
//             }
//         }
//     }
//     return maxLength;
// }

int findMaxLength(string s, int k)
{
    int maxLength = 0;
    int n = s.size();
    map<char, int> mpp;

    for (int i = 0; i < n; i++)
    {
        mpp.clear(); // coz we are starting fresh, so nothing should be there in map before

        for (int j = i; j < n; j++)
        {
            mpp[s[j]]++;

            if (mpp.size() <= k)
            {
                maxLength = max(maxLength, j - i + 1);
            }
            else
            {
                break;
            }
        }
    }
    return maxLength;
}

// int main(){
//     vector<char> arr = {'a', 'b', 'c', 'a', 'b', 'b', 'c'};
//     int k = 2;

//     int result = findMaxLength(arr, k);

//     cout << "Maximum length of subarray with at most " << k
//          << " distinct characters: " << result << endl;

//     return 0;
// }

int main()
{
    string s = "abcabbc";
    int k = 2;

    cout << findMaxLength(s, k) << endl;

    return 0;
}