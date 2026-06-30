/*

Question 1:

N Most Frequent Words
Problem: Given a paragraph of text and an integer n, find the n most frequent words with their counts.

Approach:

Parse the paragraph to extract individual words.

Store the frequencies in a Hash Map (std::unordered_map).

Transfer the map data to a std::vector of pairs and sort it. Sort primarily by frequency (descending) and secondarily by lexicographical order if frequencies match.

*/

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// Custom comparator to sort by frequency (descending), then alphabetically
bool compare(pair<string, int> &a, pair<string, int> &b)
{
    if (a.second == b.second)
        return a.first < b.first;
    return a.second > b.second;
}

int main()
{
    string paragraph;
    int n;

    // Using getline to read the full paragraph containing spaces
    getline(cin, paragraph);
    cin >> n;

    unordered_map<string, int> freqMap;
    stringstream ss(paragraph);
    string word;

    // Extract words and count frequencies
    while (ss >> word)
    {
        freqMap[word]++;
    }

    // Move to vector for sorting
    vector<pair<string, int>> vec(freqMap.begin(), freqMap.end());
    sort(vec.begin(), vec.end(), compare);

    // Print the top 'n' words
    for (int i = 0; i < n && i < vec.size(); i++)
    {
        cout << vec[i].first << " " << vec[i].second << endl;
    }

    return 0;
}