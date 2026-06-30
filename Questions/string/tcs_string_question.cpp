// one was a given paragraph of text and int n, and we had to find n most frequent words used in para with count of each.

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

// #include <iostream>      // For input (cin) and output (cout)
// #include <sstream>       // For stringstream (used to split a sentence into words)
// #include <unordered_map> // Stores word-frequency pairs
// #include <vector>        // Dynamic array used for sorting
// #include <algorithm>     // Contains sort()

// using namespace std;

// /*
//     Custom comparator function for sorting.

//     sort() does not know how we want to arrange the words, so we
//     create our own comparison function.

//     Each element is a pair:
//         first  -> word (string)
//         second -> frequency (int)

//     Sorting rules:
//     1. Higher frequency comes first.
//     2. If frequencies are equal, sort alphabetically.
// */
// bool compare(pair<string, int> &a, pair<string, int> &b)
// {
//     // If both words have the same frequency
//     if (a.second == b.second)
//     {
//         // Compare alphabetically
//         return a.first < b.first;
//     }

//     // Otherwise, higher frequency comes first
//     return a.second > b.second;
// }

// int main()
// {
//     // Stores the complete paragraph entered by the user
//     string paragraph;

//     // Number of top frequent words to display
//     int n;

//     // Prompt for paragraph
//     cout << "Enter a paragraph:\n";

//     /*
//         getline() reads the ENTIRE LINE until Enter is pressed.

//         Example input:
//         I love coding because coding is fun

//         paragraph becomes:
//         "I love coding because coding is fun"

//         If we had used:
//             cin >> paragraph;

//         It would only store:
//             "I"

//         because cin stops reading at the first space.
//     */
//     getline(cin, paragraph);

//     // Ask how many top frequent words to print
//     cout << "Enter the number of top frequent words to display: ";
//     cin >> n;

//     /*
//         unordered_map stores:

//             Key   -> Word
//             Value -> Frequency

//         Example:

//             apple  -> 3
//             banana -> 2
//             mango  -> 1
//     */
//     unordered_map<string, int> freqMap;

//     /*
//         Convert the paragraph into a stringstream.

//         Think of stringstream as turning the string into something
//         that behaves like keyboard input (cin).

//         Example:

//         paragraph =
//         "apple banana apple mango"

//         stringstream allows us to read

//         apple
//         banana
//         apple
//         mango

//         one word at a time.
//     */
//     stringstream ss(paragraph);

//     // Variable that temporarily stores one word at a time
//     string word;

//     /*
//         Read words until there are no more.

//         First iteration:
//             word = apple

//         Second:
//             word = banana

//         Third:
//             word = apple

//         Fourth:
//             word = mango

//         Then loop ends.
//     */
//     while (ss >> word)
//     {
//         /*
//             Increase the frequency of the word.

//             If the word does not exist,
//             unordered_map automatically creates it with value 0.

//             Example:

//             apple

//             becomes

//             apple -> 1

//             Next time apple appears

//             apple -> 2

//             Next

//             apple -> 3
//         */
//         freqMap[word]++;
//     }

//     /*
//         unordered_map cannot be sorted directly.

//         So we copy every (word, frequency) pair into a vector.

//         Example:

//         Map

//         apple -> 3
//         banana -> 2
//         mango -> 1

//         becomes

//         Vector

//         ("apple",3)
//         ("banana",2)
//         ("mango",1)
//     */
//     vector<pair<string, int>> vec(freqMap.begin(), freqMap.end());

//     /*
//         Sort the vector using our custom compare() function.

//         Example before sorting:

//         orange 2
//         apple 5
//         banana 5
//         grape 1

//         After sorting:

//         apple 5
//         banana 5
//         orange 2
//         grape 1
//     */
//     sort(vec.begin(), vec.end(), compare);

//     cout << "\nTop " << n << " most frequent words:\n";

//     /*
//         Print only the first n elements.

//         Condition explanation:

//         i < n
//             Don't print more than the user requested.

//         i < vec.size()
//             Prevent going beyond the number of available words.

//         Example:

//         Vector size = 4

//         User entered n = 10

//         Loop prints only 4 words.
//     */
//     for (int i = 0; i < n && i < vec.size(); i++)
//     {
//         cout << vec[i].first << " : " << vec[i].second << endl;

//         /*
//             vec[i].first  -> word

//             vec[i].second -> frequency

//             Example:

//             ("apple",3)

//             Output:

//             apple : 3
//         */
//     }

//     return 0;
// }
