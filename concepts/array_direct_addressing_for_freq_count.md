int freq[256] = {0};

- int freq[256]: Creates an array of 256 integers. Each index (0 to 255) represents a unique numeric value a byte can hold.
- = {0}: Initializes all 256 slots to 0. Without this, the array would contain random garbage data from memory.

for (int i = 0; i < n; i++) {
freq[(unsigned char)s[i]]++;
}

- for loop: Steps through the string s from the first character (i = 0) to the last (i = n - 1).
- s[i]: Extracts the character at position i (e.g., 'A').
- (unsigned char): Forces the computer to read the character as a positive number from 0 to 255. If a character is negative (like some extended symbols), this prevents the program from crashing due to negative index boundaries.
- freq[...]++: Finds the slot matching that number and adds 1 to its count. If s[i] is 'A' (ASCII 65), freq[65] increases by 1.

---

## Real-World Examples with Code

Here is how you can use this exact array logic to solve the 5 scenarios mentioned earlier.

## 1. Basic Strings: Valid Anagram

Two strings are anagrams if they have the exact same characters with the exact same frequencies.

#include <string>
bool isAnagram(std::string s, std::string t) {
if (s.length() != t.length()) return false;

    int freq[256] = {0}; // Track counts

    // Step 1: Add counts for string s
    for (int i = 0; i < s.length(); i++) {
        freq[(unsigned char)s[i]]++;
    }

    // Step 2: Subtract counts for string t
    for (int i = 0; i < t.length(); i++) {
        freq[(unsigned char)t[i]]--;

        // If any count drops below 0, characters don't match
        if (freq[(unsigned char)t[i]] < 0) {
            return false;
        }
    }
    return true;

}

## 2. Sliding Window: Find All Anagrams in a String

Finds the starting positions of all substrings in s that match any permutation of p.

#include <vector>#include <string>
std::vector<int> findAnagrams(std::string s, std::string p) {
std::vector<int> result;
if (s.length() < p.length()) return result;

    int pCount[256] = {0};
    int sCount[256] = {0};

    // Fill target frequencies and initial window
    for (int i = 0; i < p.length(); i++) {
        pCount[(unsigned char)p[i]]++;
        sCount[(unsigned char)s[i]]++;
    }

    // Check if the first window matches
    auto matches = [](int a[256], int b[256]) {
        for (int i = 0; i < 256; i++) if (a[i] != b[i]) return false;
        return true;
    };

    if (matches(pCount, sCount)) result.push_back(0);

    // Slide the window across the string
    for (int i = p.length(); i < s.length(); i++) {
        sCount[(unsigned char)s[i]]++;                  // Add new character on the right
        sCount[(unsigned char)s[i - p.length()]]--;     // Remove old character from the left

        if (matches(pCount, sCount)) {
            result.push_back(i - p.length() + 1);
        }
    }
    return result;

}

## 3. Data Encoding: Run-Length Encoding (Pre-calculation)

Analyzes character distributions before applying simple compression techniques.

#include <string>#include <iostream>
void analyzeDistribution(std::string s) {
int freq[256] = {0};
for (int i = 0; i < s.length(); i++) {
freq[(unsigned char)s[i]]++;
}

    // Print out only characters that actually showed up
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            std::cout << (char)i << " appears " << freq[i] << " times\n";
        }
    }

}

## 4. Byte Processing: Basic File Integrity Check

Counts byte values (0-255) to verify if a file block consists entirely of empty null bytes (0x00).

#include <vector>
bool isBufferEmpty(const std::vector<char>& fileBuffer) {
int freq[256] = {0};

    // Count raw bytes
    for (int i = 0; i < fileBuffer.size(); i++) {
        freq[(unsigned char)fileBuffer[i]]++;
    }

    // If index 0 equals total file size, the buffer contains nothing but zeroes
    return freq[0] == fileBuffer.size();

}

## 5. Competitive Programming: Lowercase Constraints

When a problem states "only lowercase English letters", you can shrink the array space to 26 and map 'a' to index 0.

#include <string>
bool hasAll26Letters(std::string s) {
int freq[26] = {0}; // Only need 26 slots for 'a' through 'z'

    for (int i = 0; i < s.length(); i++) {
        // Subtracting 'a' converts ASCII values (97-122) directly to indexes (0-25)
        freq[s[i] - 'a']++;
    }

    // Verify if every single lowercase slot has been visited
    for (int i = 0; i < 26; i++) {
        if (freq[i] == 0) return false;
    }
    return true;

}
