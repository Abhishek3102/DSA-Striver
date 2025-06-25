#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    // pre compute
    map<int, int> mpp;
    for (int i = 0; i < n; i++)
    {
        // time complexity in map
        // functions like storing and fetching takes O(log N) where N is num of elements in map, in best, avg and worst case.
        // im map. any data structure can be a key, like pair<int,int> too
        mpp[arr[i]]++;

        // in unordered map, only single valued data structures can be a key
        // if unordered map is used here in place of map,
        // then t.c. : for storing and fetching -> O(1) i.e. constant time in best and average cases
        // but in worst case it takes O(N) where N is num of elements in map
        // the worst case happens due to internal collisions

        // so make use of unordered in most and mostly all cases, but if it gives time limit exceeded error, then switch back to map.
    }

    // iterate in the map
    for (auto it : mpp)
    {
        cout << it.first << "->" << it.second << endl;
    }

    int q;
    cin >> q;
    while (q--)
    {
        int number;
        cin >> number;
        cout << mpp[number] << endl;
    }
    return 0;
}