#include <bits/stdc++.h>
using namespace std;

int maximumProfit(vector<int> &prices)
{
    int mini = prices[0];
    int maxProfit = 0;
    int n = prices.size();
    for (int i = 0; i < n; i++)
    {
        int cost = prices[i] - mini;
        maxProfit = max(maxProfit, cost);
        mini = min(mini, prices[i]);
    }
    return maxProfit;
}

int maximumProfitAllSteps(vector<int> &prices)
{
    int mini = prices[0]; // Initialize the minimum price to the first price
    int maxProfit = 0;    // Start with 0 profit
    int n = prices.size();

    cout << "Starting maximum profit calculation..." << endl;
    cout << "Initial minimum price: " << mini << endl;

    // Loop through each price
    for (int i = 0; i < n; i++)
    {
        // Calculate the potential profit if sold at the current price
        int cost = prices[i] - mini;

        // Update the maximum profit if the current profit is larger
        maxProfit = max(maxProfit, cost);

        // Update the minimum price encountered so far
        mini = min(mini, prices[i]);

        // Print the important intermediate values
        cout << "At day " << i + 1 << ", price: " << prices[i] << endl;
        cout << "Current minimum price: " << mini << endl;
        cout << "Current profit: " << cost << endl;
        cout << "Max profit so far: " << maxProfit << endl;
    }

    return maxProfit; // Return the maximum profit

    /*
    n = 6
    arr = 7 1 5 3 6 4
    Starting maximum profit calculation...
    Initial minimum price: 7
    At day 1, price: 7
    Current minimum price: 7
    Current profit: 0
    Max profit so far: 0
    At day 2, price: 1
    Current minimum price: 1
    Current profit: -6
    Max profit so far: 0
    At day 3, price: 5
    Current minimum price: 1
    Current profit: 4
    Max profit so far: 4
    At day 4, price: 3
    Current minimum price: 1
    Current profit: 2
    Max profit so far: 4
    At day 5, price: 6
    Current minimum price: 1
    Current profit: 5
    Max profit so far: 5
    At day 6, price: 4
    Current minimum price: 1
    Current profit: 3
    Max profit so far: 5
    5

        */
}

int main()
{
    int n;
    cin >> n;
    vector<int> prices(n);
    for (int i = 0; i < n; i++)
    {
        cin >> prices[i];
    }
    cout << maximumProfitAllSteps(prices) << endl;
    return 0;
}