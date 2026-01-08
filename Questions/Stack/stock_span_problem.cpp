/*
  STOCK SPAN PROBLEM

  This code finds the span of stock prices - consecutive days where price <= current price.

  WHAT IT DOES:
  - Span is the maximum number of consecutive days just before current day where price <= current price
  - For each day, calculates how many consecutive days back have price <= today's price
  - Uses stack to efficiently find previous greater price positions
  - Optimal solution: O(n) time for n queries

  INPUT:
  - Stock prices given one by one (as stream input)
  - Example: prices = [100, 80, 60, 70, 60, 75, 85]

  OUTPUT:
  - Span for each price when queried
  - Example output: [1, 1, 1, 2, 1, 4, 6]
  - Day 100: span=1, day 80: span=1, day 60: span=1, day 70: span=2 (70 and 60), etc.
*/

#include <bits/stdc++.h>
using namespace std;

class StockSpanner
{
    list<int> arr; // Use list instead of vector

public:
    StockSpanner()
    {
        arr.clear(); // Initialize the list to be empty
    }

    int next(int val)
    {
        arr.push_back(val);
        int count = 1;
        auto it = prev(arr.end(), 2); // Iterator pointing to the second last element
        for (; it != arr.begin(); --it)
        {
            if (*it <= val)
            {
                count++;
            }
            else
            {
                break;
            }
        }
        return count;
    }
};

class StockSpannerOptimal
{
    stack<pair<int, int>> st;
    int index = -1;

public:
    StockSpannerOptimal()
    {
        index = -1;
        while (!st.empty()) // used to clear the full stack
            st.pop();
    }

    int nextOpti(int val)
    {
        index++;
        while (!st.empty() && st.top().first <= val)
            st.pop();
        int ans = index - (st.empty() ? -1 : st.top().second);
        st.push({val, index});
        return ans;
    }
};

int main()
{
    StockSpannerOptimal spanner;
    cout << spanner.nextOpti(100) << endl; // Output: 1
    cout << spanner.nextOpti(80) << endl;  // Output: 1
    cout << spanner.nextOpti(60) << endl;  // Output: 1
    cout << spanner.nextOpti(70) << endl;  // Output: 2
    cout << spanner.nextOpti(60) << endl;  // Output: 1
    cout << spanner.nextOpti(75) << endl;  // Output: 4
    cout << spanner.nextOpti(85) << endl;  // Output: 6
    return 0;
}
