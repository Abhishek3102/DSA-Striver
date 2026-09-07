// in house robber 1, it was a straight array now here it is circular array coz first house is neighbor to last house

#include <bits/stdc++.h>
using namespace std;

int findMaxSum(vector<int> &arr)
{
    int n = arr.size();
    int prev = arr[0];
    int prev2 = 0;
    for (int i = 1; i < n; i++)
    {
        int take = arr[i];
        if (i > 1)
            take += prev2;

        int notTake = 0 + prev;

        int curi = max(take, notTake);
        prev2 = prev;
        prev = curi;
    }
    return prev;
}

long long int houseRobber2(vector<int> &valuesInHouse)
{
    int n = valuesInHouse.size();
    vector<int> temp1, temp2;
    if (n == 1)
        return valuesInHouse[0];
    for (int i = 0; i < n; i++)
    {
        if (i != 0)
            temp1.push_back(valuesInHouse[i]);
        if (i != n - 1)
            temp2.push_back(valuesInHouse[i]);
    }

    return max(findMaxSum(temp1), findMaxSum(temp2));
}

int main()
{
    vector<int> valuesInHouse = {2, 3, 2, 1, 5};
    cout << houseRobber2(valuesInHouse);
}