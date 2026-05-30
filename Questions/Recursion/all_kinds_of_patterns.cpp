#include <bits/stdc++.h>
using namespace std;

// print all the subsets whose sum is equal to given sum
void printSum(int index, vector<int> &ds, vector<int> &arr, int n, int s, int sum)
{
    if (index == n)
    {
        if (s == sum)
        {
            for (auto it : ds)
            {
                cout << it << " ";
            }
            cout << endl;
        }
        return;
    }

    ds.push_back(arr[index]);
    s += arr[index];

    printSum(index + 1, ds, arr, n, s, sum);

    s -= arr[index];
    ds.pop_back();

    // not pick
    printSum(index + 1, ds, arr, n, s, sum);
}

// technique to print any 1 subsequence where sum is equal to given sum
/*
f(){

f() -> this is for pick so this should be written

f() -> this is for not pick so no need to write this
we used to write this previously coz we needed all subsequences there

}


f(){

base check

condition -> satisfied ->
return true

condition -> not satisfied ->
return false


if(f() == true){
return true;
f();
}


}
*/

bool printOnly1Subsequence(int index, vector<int> &ds, vector<int> &arr, int n, int s, int sum)
{
    if (index == n)
    {

        // base case check
        if (s == sum)
        { // condition satisfied
            for (auto it : ds)
            {
                cout << it << " ";
            }
            cout << endl;
            return true;
        }
        // condition not satisfied
        else
            return false;
    }

    ds.push_back(arr[index]);
    s += arr[index];

    if (printOnly1Subsequence(index + 1, ds, arr, n, s, sum) == true)
    {
        return true;
    }

    s -= arr[index];
    ds.pop_back();

    // not pick
    if (printOnly1Subsequence(index + 1, ds, arr, n, s, sum) == true)
    {
        return true;
    }

    return false;
}

int countSubsequences(int index, int s, int sum, vector<int> arr, int n)
{
    if (index == n)
    {
        // condition satisfied
        if (s == sum)
            return 1;

        // condition not satisfied
        else
            return 0;
    }

    s += arr[index];

    int l = countSubsequences(index + 1, s, sum, arr, n);

    s -= arr[index];

    // not pick
    int r = countSubsequences(index + 1, s, sum, arr, n);
    return l + r;
}

int main()
{
    vector<int> arr = {1, 2, 1, 1};
    int n = 4;
    int sum = 2;
    cout << countSubsequences(0, 0, sum, arr, n) << endl;
    return 0;
}