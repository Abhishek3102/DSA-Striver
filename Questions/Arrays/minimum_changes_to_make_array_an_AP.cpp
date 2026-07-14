/*

3. Minimum Changes to Make Array an A.P.Problem: Given an array, find the minimum number of elements and what elements with what you need to alter to turn it into an arithmetic progression with an arbitrary common difference.
Logic: Fix two elements or guess the target starting term and common difference, checking how many positions match A_i = A_0 + i * d.

*/

#include <bits/stdc++.h>
using namespace std;

// Function to find the minimum number of changes required
// to convert the given array into an Arithmetic Progression (AP)
// and print the required modifications.
void minChangesToAP(vector<int> &arr)
{
    int n = arr.size();

    // Arrays of size 0, 1, or 2 are already APs.
    if (n <= 2)
    {
        cout << "Minimum changes = 0\n";
        return;
    }

    // Stores the maximum number of elements that already fit an AP.
    int max_matches = 0;

    // Stores the starting term and common difference
    // of the best Arithmetic Progression found.
    int best_start = 0;
    int best_d = 0;

    // Try every pair of elements as part of the final AP.
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {

            // The common difference must be an integer.
            // If not divisible, this pair cannot define an integer AP.
            if ((arr[j] - arr[i]) % (j - i) != 0)
                continue;

            // Compute common difference.
            int d = (arr[j] - arr[i]) / (j - i);

            // Compute the first element of the AP.
            // Formula:
            // arr[i] = start + i*d
            // => start = arr[i] - i*d
            int start = arr[i] - i * d;

            int matches = 0;

            // Count how many elements already match this AP.
            for (int k = 0; k < n; k++)
            {
                if (arr[k] == start + k * d)
                    matches++;
            }

            // Keep the AP with the maximum matches.
            if (matches > max_matches)
            {
                max_matches = matches;
                best_start = start;
                best_d = d;
            }
        }
    }

    // Minimum changes = total elements - elements already matching.
    cout << "Minimum changes required = "
         << n - max_matches << "\n\n";

    // Print the target AP.
    cout << "Target Arithmetic Progression:\n";
    for (int i = 0; i < n; i++)
        cout << best_start + i * best_d << " ";
    cout << "\n\n";

    // Print the modifications needed.
    cout << "Steps:\n";
    for (int i = 0; i < n; i++)
    {

        // Expected value at index i in the best AP.
        int expected = best_start + i * best_d;

        // If current value differs, print the required change.
        if (arr[i] != expected)
        {
            cout << "Change arr[" << i << "] from "
                 << arr[i] << " to " << expected << "\n";
        }
    }
}

int main()
{

    // Example input.
    vector<int> arr = {2, 5, 7, 9, 13};

    minChangesToAP(arr);

    return 0;
}