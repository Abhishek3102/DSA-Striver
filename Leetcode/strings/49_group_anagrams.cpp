#include <bits/stdc++.h>
using namespace std;

vector<vector<string>> groupAnagrams(vector<string> strs)
{
    unordered_map<string, vector<string>> map;
    vector<vector<string>> res;

    for (string s : strs)
    {
        string sSorted = s;
        sort(sSorted.begin(), sSorted.end());
        map[sSorted].push_back(s);
    }

    for (auto &x : map)
    {
        res.push_back(x.second);
    }

    return res;
}

// Sure. The key idea is that **anagrams have the same characters, so after sorting their characters, they produce the same string**.

//  For example:

// ```
// "eat" → "aet"
// "tea" → "aet"
// "ate" → "aet"
// ```

//  So `"aet"` can be used as the key in the hash map.

// ```
// #include <bits/stdc++.h>
// using namespace std;

// /*
//     ============================================================
//                         GROUP ANAGRAMS
//     ============================================================

//     Anagrams are words/strings that contain the same characters
//     with the same frequency, but possibly in a different order.

//     Example:

//         "eat", "tea", "ate"

//     All three contain:

//         e -> 1 time
//         a -> 1 time
//         t -> 1 time

//     If we sort each string:

//         "eat" -> "aet"
//         "tea" -> "aet"
//         "ate" -> "aet"

//     Since all anagrams produce the same sorted string, we can
//     use the sorted string as a key in a hash map.

//     Example input:

//         ["eat", "tea", "tan", "ate", "nat", "bat"]

//     After sorting:

//         "eat" -> "aet"
//         "tea" -> "aet"
//         "tan" -> "ant"
//         "ate" -> "aet"
//         "nat" -> "ant"
//         "bat" -> "abt"

//     Hash map becomes:

//         "aet" -> ["eat", "tea", "ate"]
//         "ant" -> ["tan", "nat"]
//         "abt" -> ["bat"]

//     Finally, we put all the groups into the result vector.
// */

// vector<vector<string>> groupAnagrams(vector<string> strs)
// {
//     /*
//         --------------------------------------------------------
//         HASH MAP
//         --------------------------------------------------------

//         The key will be the sorted version of a string.

//         The value will be a vector containing all strings
//         that have the same sorted version.

//         Example:

//             map["aet"] = {"eat", "tea", "ate"}

//         We use unordered_map because it provides average
//         O(1) insertion and lookup.
//     */
//     unordered_map<string, vector<string>> map;

//     /*
//         This vector will store the final answer.

//         Each element of 'res' represents one group of anagrams.

//         Example:

//             res = {
//                 {"eat", "tea", "ate"},
//                 {"tan", "nat"},
//                 {"bat"}
//             }
//     */
//     vector<vector<string>> res;

//     /*
//         --------------------------------------------------------
//         PROCESS EVERY STRING
//         --------------------------------------------------------
//     */
//     for (string s : strs)
//     {
//         /*
//             Make a copy of the current string.

//             We don't want to modify the original string 's'
//             because we need to store the original string
//             in the answer.

//             Example:

//                 s = "tea"

//                 sSorted = "tea"
//         */
//         string sSorted = s;

//         /*
//             Sort the characters of the copied string.

//             Example:

//                 "tea" -> "aet"
//                 "eat" -> "aet"
//                 "tan" -> "ant"
//                 "bat" -> "abt"

//             Anagrams will always produce the same sorted string.
//         */
//         sort(sSorted.begin(), sSorted.end());

//         /*
//             Use the sorted string as the key in the hash map.

//             map[sSorted] gives us the vector containing all
//             anagrams found so far.

//             Then we add the ORIGINAL string 's' to that group.

//             Example:

//                 s = "tea"
//                 sSorted = "aet"

//                 map["aet"].push_back("tea");

//             If "eat" was already processed:

//                 map["aet"] = {"eat"}

//             After adding "tea":

//                 map["aet"] = {"eat", "tea"}
//         */
//         map[sSorted].push_back(s);
//     }

//     /*
//         --------------------------------------------------------
//         MOVE ALL GROUPS FROM HASH MAP TO RESULT
//         --------------------------------------------------------

//         At this point, the hash map contains all the groups.

//         Example:

//             map = {
//                 "aet" -> {"eat", "tea", "ate"},
//                 "ant" -> {"tan", "nat"},
//                 "abt" -> {"bat"}
//             }

//         We now need to put each vector of strings into 'res'.
//     */
//     for (auto &x : map)
//     {
//         /*
//             x.first  -> the sorted string (the key)
//             x.second -> vector containing the anagrams

//             We only need x.second.

//             Example:

//                 x.second = {"eat", "tea", "ate"}

//             Add this complete group to the result.
//         */
//         res.push_back(x.second);
//     }

//     /*
//         Return the final collection of anagram groups.
//     */
//     return res;
// }
// ```

//  ### Example

//  For:

// ```
// vector<string> strs = {
//     "eat", "tea", "tan", "ate", "nat", "bat"
// };
// ```

//  The map conceptually becomes:

// ```
// "aet" → ["eat", "tea", "ate"]
// "ant" → ["tan", "nat"]
// "abt" → ["bat"]
// ```

//  So the result is groups like:

// ```
// [
//     ["eat", "tea", "ate"],
//     ["tan", "nat"],
//     ["bat"]
// ]
// ```

//  ### Complexity

//  Let:

//  - `N` = number of strings
// - `K` = maximum length of a string

//  For every string, we sort it:

// ```
// sort(sSorted.begin(), sSorted.end());
// ```

//  Sorting one string costs **O(K log K)**.

//  Therefore:

//  - **Time:** `O(N × K log K)`
// - **Space:** `O(N × K)` for the hash map and result.

//  The main trick to remember is:

//  > **Anagrams → same characters → sorting gives the same key → use that key to group them.**