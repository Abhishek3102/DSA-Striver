// Write a C++ program to read a complete sentence from the user and count the total number of words present in it.

#include <iostream>
#include <sstream>
using namespace std;

int main()
{
    string sentence;

    cout << "Enter a sentence: ";

    // Read complete line
    getline(cin, sentence);

    // Break sentence into words
    stringstream ss(sentence);

    string word;

    // Counter variable
    int count = 0;

    // Read every word
    while (ss >> word)
    {
        count++;
    }

    cout << "\nTotal number of words = " << count;

    return 0;
}