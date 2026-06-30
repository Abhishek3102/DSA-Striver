/*

The program reads an entire sentence from the user, counts how many times each character appears (excluding spaces), and stores the counts in an unordered_map<char, int>.

For example,

Input:

hello world

Output (order may vary):

h : 1
e : 1
l : 3
o : 2
w : 1
r : 1
d : 1

*/

#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{

    // Stores the complete sentence
    string text;

    cout << "Enter a sentence: ";

    // Reads the entire line including spaces
    getline(cin, text);

    // Map to store character -> frequency
    unordered_map<char, int> freq;

    // Loop through every character in the string
    for (char ch : text)
    {
        // Ignore spaces
        if (ch != ' ')
        {
            // If character doesn't exist, it becomes 1
            // Otherwise its value increases by 1
            freq[ch]++;
        }
    }

    cout << "\nCharacter Frequencies:\n";

    // Print every character and its count
    for (auto x : freq)
    {
        cout << x.first << " : " << x.second << endl;
    }

    return 0;
}