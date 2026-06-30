// Write a C++ program to read a sentence from the user and find the longest word present in the sentence.
// Display the longest word along with its length.

#include <iostream>
#include <sstream>
using namespace std;

int main()
{
    string sentence;

    cout << "Enter a sentence: ";

    // Reads the whole line
    getline(cin, sentence);

    // Converts the sentence into a stream
    stringstream ss(sentence);

    string word;

    // Stores the longest word found so far
    string longest = "";

    // Read one word at a time
    while (ss >> word)
    {
        // Compare lengths
        if (word.length() > longest.length())
        {
            longest = word;
        }
    }

    cout << "\nLongest word: " << longest << endl;
    cout << "Length: " << longest.length();

    return 0;
}