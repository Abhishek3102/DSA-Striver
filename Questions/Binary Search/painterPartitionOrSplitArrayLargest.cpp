// here an array will be given and number of painters will be given.
// each painter should get a chance to paint atleast one element of array.
// also a painter can only paint consecutive part of the array which is basically the subarray.
// here we have to try all possible subarray combinations and find the max of each subarray.
// then choose the combination whose sum of max subarray is minimum.
// eg : [10 20 30 40] and k = 2 (no. of painters)
// [10]  [20 30 40] -> sum of max subarray is 20+30+40 = 90
// [10 20]  [30 40] -> sum = 30 + 40 = 70
// [10 20 30]  [40] -> sum = 10 + 20 + 30 = 60 so this combinations will be chosen as it returns minimum sum.
// also we have to split arrays into given k number of subarrays.

#include <bits/stdc++.h>
using namespace std;

int countPainter(vector<int> &arr, int) {}

int main()
{
    return 0;
}