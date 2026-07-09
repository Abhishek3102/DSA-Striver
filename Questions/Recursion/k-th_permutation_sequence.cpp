#include <bits/stdc++.h> // Includes all standard C++ libraries
using namespace std;

class Solution
{
public:
    string getPermutation(int n, int k)
    {
        // Stores (n-1)! initially.
        // This represents the size of each permutation block.
        int fact = 1;

        // Stores the numbers that are still available
        // to be placed in the permutation.
        vector<int> numbers;

        // Calculate (n-1)! and store numbers from 1 to n-1.
        for (int i = 1; i < n; i++)
        {
            fact = fact * i;      // Compute factorial: (n-1)!
            numbers.push_back(i); // Add number to available list
        }

        // Add the last number (n) separately.
        numbers.push_back(n);

        // Stores the final kth permutation.
        string ans = "";

        // Convert k from 1-based indexing to 0-based indexing.
        // Makes calculations easier.
        k = k - 1;

        // Keep selecting digits until no numbers remain.
        while (true)
        {
            // Find which block the kth permutation belongs to.
            // Each block has 'fact' permutations.
            int index = k / fact;

            // Pick that number and append it to the answer.
            ans = ans + to_string(numbers[index]);

            // Remove the selected number since it can't be reused.
            numbers.erase(numbers.begin() + index);

            // If all numbers are used, permutation is complete.
            if (numbers.size() == 0)
            {
                break;
            }

            // Find the new position inside the selected block.
            k = k % fact;

            // Update factorial for the remaining numbers.
            // Example:
            // If previous fact = 6 (3!)
            // Remaining numbers = 3
            // New fact = 6 / 3 = 2 (2!)
            fact = fact / numbers.size();
        }

        // Return the kth permutation sequence.
        return ans;
    }
};

/*

eg : (n = 4, k = 17)

Numbers = [1,2,3,4]
fact = 3! = 6
k = 16 (0-based)

Step 1:
index = 16 / 6 = 2
Pick numbers[2] = 3
Answer = "3"

Remaining = [1,2,4]
k = 16 % 6 = 4
fact = 6 / 3 = 2

Step 2:
index = 4 / 2 = 2
Pick numbers[2] = 4
Answer = "34"

Remaining = [1,2]
k = 4 % 2 = 0
fact = 2 / 2 = 1

Step 3:
index = 0 / 1 = 0
Pick numbers[0] = 1
Answer = "341"

Remaining = [2]
k = 0 % 1 = 0
fact = 1 / 1 = 1

Step 4:
index = 0 / 1 = 0
Pick numbers[0] = 2
Answer = "3412"

*/